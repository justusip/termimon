#include "Renderer.h"

Renderer::Renderer() {
    canvasGlyphs = new char32_t[canvasWidth * canvasHeight];
    canvasFg = new Colour[canvasWidth * canvasHeight];
    canvasBg = new Colour[canvasWidth * canvasHeight];
}

Renderer::~Renderer() {
    delete[] canvasGlyphs;
    delete[] canvasFg;
    delete[] canvasBg;
}

void Renderer::clearBuf() {
    memset(canvasGlyphs, 0, canvasWidth * canvasHeight * sizeof(char32_t));
    memset(canvasFg, 0, canvasWidth * canvasHeight * sizeof(Colour));
    memset(canvasBg, 0, canvasWidth * canvasHeight * sizeof(Colour));
}

void Renderer::onUpdate(const int &elapsed) {
    if (activePrompt) {
        int x = activePrompt->choice % 2, y = activePrompt->choice / 2;
        if (Inputs::isKeydown(1))
            y--;
        if (Inputs::isKeydown(2))
            y++;
        if (Inputs::isKeydown(3))
            x++;
        if (Inputs::isKeydown(4))
            x--;
        x = clamp(x, 0, 1);
        y = clamp(y, 0, 1);
        activePrompt->choice = clamp(y * 2 + x, 0, (int) activePrompt->answers.size() - 1);

        if (Inputs::isKeydown('\n')) {
            const auto prompt = activePrompt;
            activePrompt = {};
            if (prompt->callbackDecided)
                prompt->callbackDecided(prompt->choice);
        }
    } else if (activeDialogue) {
        if (Inputs::isKeydown('\n') && activeDialogue->animationCompleted()) {
            const auto dialogue = activeDialogue;
            activeDialogue = {};
            if (dialogue->callback)
                dialogue->callback();
        }
    }
}

void Renderer::onRender(const int &elapsed) {
    if (elapsed - lastRender < 1 / fps * 1000)
        return;
    lastRender = elapsed;

    Terminal::getViewportSize(viewportWidth, viewportHeight);

    if (viewportWidth < 80 || viewportHeight < 24) {
        if (prevViewportWidth != viewportWidth || prevViewportHeight != viewportHeight) {
            Terminal::clearScreen();
            Terminal::moveTo(0, 0);
            cout << "\x1b[0m";
            cout << "Please scale up your terminal window." << endl;
            cout << "A minimum window size of 80x24 is required to play this game." << endl;
            cout << "Current size: " << viewportWidth << "x" << viewportHeight << endl;
            cout.flush();

            prevViewportWidth = viewportWidth;
            prevViewportHeight = viewportHeight;
        }
        return;
    }

    drawDialogue(elapsed);
    drawQuestion(elapsed);
    Terminal::moveTo(0, 0);
    wstring_convert<codecvt_utf8<char32_t>, char32_t> converter;

    if (prevViewportWidth != viewportWidth || prevViewportHeight != viewportHeight) {
        delete[] viewportGlyphs;
        viewportGlyphs = new char32_t[viewportWidth * viewportHeight];

        delete[] viewportFg;
        viewportFg = new Colour[viewportWidth * viewportHeight];

        delete[] viewportBg;
        viewportBg = new Colour[viewportWidth * viewportHeight];

        prevViewportWidth = viewportWidth;
        prevViewportHeight = viewportHeight;
    }
    for (int j = 0; j < viewportHeight; j++) {
        for (int i = 0; i < viewportWidth; i++) {
            viewportGlyphs[j * viewportWidth + i] = 0;
            viewportFg[j * viewportWidth + i] = {0, 0, 0, 0};
            viewportBg[j * viewportWidth + i] = {0, 0, 0};
        }
    }
    for (int j = 0; j < canvasHeight; j++) {
        for (int i = 0; i < canvasWidth; i++) {
            int x = viewportWidth / 2 - canvasWidth / 2 + i;
            int y = viewportHeight / 2 - canvasHeight / 2 + j;
            viewportGlyphs[y * viewportWidth + x] = canvasGlyphs[j * canvasWidth + i];
            viewportFg[y * viewportWidth + x] = canvasFg[j * canvasWidth + i];
            viewportBg[y * viewportWidth + x] = canvasBg[j * canvasWidth + i];
        }
    }

    optional<Colour> prevFgColour;
    optional<Colour> prevBgColour;
    for (int y = 0; y < viewportHeight; y++) {
        ostringstream line;
        for (int x = 0; x < viewportWidth; x++) {
            const Colour &fgColour = viewportFg[y * viewportWidth + x];
            if (prevFgColour != fgColour) {
                if (fgColour.a > 0) {
                    line << "\x1b[38;2;"
                         << to_string(fgColour.r) << ";"
                         << to_string(fgColour.g) << ";"
                         << to_string(fgColour.b) << "m";
                } else {
                    line << "\x1b[39m";
                }
                prevFgColour = fgColour;
            }

            const Colour &bgColour = viewportBg[y * viewportWidth + x];
            if (prevBgColour != bgColour) {
                if (bgColour.a > 0) {
                    line << "\x1b[48;2;"
                         << to_string(bgColour.r) << ";"
                         << to_string(bgColour.g) << ";"
                         << to_string(bgColour.b) << "m";
                } else {
                    line << "\x1b[39m";
                }
                prevBgColour = bgColour;
            }

            const char32_t &c = viewportGlyphs[y * viewportWidth + x];
            if (c == 0) {
                line << " ";
                continue;
            }
            line << converter.to_bytes(c);
        }
//            Terminal::formatColour(viewportGlyphs[y]);
        if (y != viewportHeight - 1)
            line << endl;
        cout << line.str();
    }
    cout.flush();
}

void Renderer::drawPixel(int x, int y, char32_t c) {
    if (x < 0 || x >= canvasWidth || y < 0 || y >= canvasHeight)
        return;
    canvasGlyphs[y * canvasWidth + x] = c;
}

void Renderer::drawPixel(int x, int y, char32_t c, Colour fgColour) {
    if (x < 0 || x >= canvasWidth || y < 0 || y >= canvasHeight)
        return;
    canvasGlyphs[y * canvasWidth + x] = c;
    canvasFg[y * canvasWidth + x] = fgColour;
}

void Renderer::drawPixel(int x, int y, char32_t c, Colour fgColour, Colour bgColour) {
    if (x < 0 || x >= canvasWidth || y < 0 || y >= canvasHeight)
        return;
    canvasGlyphs[y * canvasWidth + x] = c;
    canvasFg[y * canvasWidth + x] = fgColour;
    canvasBg[y * canvasWidth + x] = bgColour;
}

void Renderer::drawScene(int mapWidth, int mapHeight,
                         const char32_t *mapGlyphs, const Colour *mapFg, const Colour *mapBg,
                         int playerX, int playerY) {
    for (int j = 0; j < canvasHeight; j++)
        for (int i = 0; i < canvasWidth; i++)
            canvasBg[j * canvasWidth + i] = {0, 0, 0};

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            int j = canvasHeight / 2 + y - playerY;
            if (j < 0 || j >= canvasHeight)
                continue;
            int i = canvasWidth / 2 + x - playerX - 1;
            if (i < 0 || i >= canvasWidth)
                continue;
            if (playerX == x && playerY == y) {
                drawPixel(i, j, U'@', {255, 215, 0}, {210, 105, 30});
                continue;
            }
            drawPixel(i, j, mapGlyphs[y * mapWidth + x],
                      mapFg[y * mapWidth + x],
                      mapBg[y * mapWidth + x]);
        }
    }
}

void Renderer::drawFrame(int x, int y, int w, int h, const u32string_view &style) {
    for (int j = y; j < h + y; j++) {
        for (int i = x; i < w + x; i++) {
            drawPixel(i, j, U' ', {0x77, 0x77, 0x77}, {255, 255, 255});
        }
    }
    for (int i = x + 1; i < x + w - 1; i++) {
        drawPixel(i, y, style[0], {0x77, 0x77, 0x77});
        drawPixel(i, y + h - 1, style[0], {0x77, 0x77, 0x77});
    }
    for (int j = y + 1; j < y + h - 1; j++) {
        drawPixel(x, j, style[1], {0x77, 0x77, 0x77});
        drawPixel(x + w - 1, j, style[1], {0x77, 0x77, 0x77});
    }
    drawPixel(x, y, style[2], {0x77, 0x77, 0x77});
    drawPixel(x + w - 1, y, style[3], {0x77, 0x77, 0x77});
    drawPixel(x, y + h - 1, style[4], {0x77, 0x77, 0x77});
    drawPixel(x + w - 1, y + h - 1, style[5], {0x77, 0x77, 0x77});
}

void Renderer::drawText(int x, int y, int w, int h, const u32string &msg) {
    int actualLength = 0;
    int curLength = 0;
    for (int j = y; j < h + y; j++) {
        for (int i = x; i < w + x; i++) {
            if (curLength >= msg.length())
                return;
            drawPixel(i, j, msg[actualLength]);
            curLength++;
            actualLength++;
        }
    }
}

void Renderer::drawDialogue(const int &elapsed) {
    if (!activeDialogue)
        return;
    if (elapsed - activeDialogue->prevUpdate > 50) {
        activeDialogue->prevUpdate = elapsed;
        if (!activeDialogue->animationCompleted())
            activeDialogue->cursor++;
    }
    drawFrame(0, canvasHeight - 4, canvasWidth, 4, Renderer::FRAME_STYLE_2);
    u32string msg = activeDialogue->msg->substr(0, activeDialogue->cursor);
    if (activeDialogue->cursor == activeDialogue->msg->length() && elapsed % 1000 < 500)
        msg += U'▼';

    drawText(1, canvasHeight - 3, canvasWidth - 2, 2, msg);
}

void Renderer::drawQuestion(const int &elapsed) {
    if (!activePrompt)
        return;
    drawFrame(0, canvasHeight - 4, canvasWidth, 4, Renderer::FRAME_STYLE_2);
    drawText(1, canvasHeight - 3, 47, 2, activePrompt->question);
    drawFrame(canvasWidth - 32, canvasHeight - 4, 32, 4, Renderer::FRAME_STYLE_2);
    array<pair<int, int>, 4> offsets = {
            {
                    {canvasWidth - 31, canvasHeight - 3},
                    {canvasWidth - 16, canvasHeight - 3},
                    {canvasWidth - 31, canvasHeight - 2},
                    {canvasWidth - 16, canvasHeight - 2}
            }
    };
    for (int i = 0; i < activePrompt->answers.size(); i++) {
        drawText(offsets[i].first, offsets[i].second, 16, 1,
                 u32string(activePrompt->choice == i ? U"➢" : U" ") + U" " +
                 activePrompt->answers[i]);
    }
}

void Renderer::drawStatus(int x, int y, const u32string &name, float health, int level, float exp, bool male) {
    std::wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;

    drawFrame(x, y, 40, 4, Renderer::FRAME_STYLE_2);
    drawText(x + 1, y + 1, 38, 1, name + U" " + (male ? U"♂" : U"♀"));
    drawText(x + 23, y + 1, 7, 1, U"Lv. " + conv.from_bytes(to_string(level)));
    drawText(x + 1, y + 2, 38, 1,
             U"HP "
             + u32string((int) floor(health * 16), U'▓')
             + u32string((int) floor((1 - health) * 16), U'░'));
    drawText(x + 23, y + 2, 38, 1,
             U"EXP "
             + u32string((int) floor(exp * 12), U'▄')
             + u32string((int) floor((1 - exp) * 12), U'▗'));
}

void Renderer::drawSprite(int x, int y, int id, bool flipped) {
    int w = 24;
    int h = 20;
    Colour c;
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            memcpy(&c, &SPRITES[(w * h * id + w * j + i) * 4], 4);
            if (c.a > 0) {
                int pixelY = y + j;
                int pixelX = !flipped ? (x + i * 2) : (x + 48 - (i * 2));
                drawPixel(pixelX, pixelY, U'█', c);
                drawPixel(pixelX + 1, pixelY, U'█', c);
            }
        }
    }
}

void Renderer::debug(const string &msg) {
    wstring_convert<codecvt_utf8<char32_t>, char32_t> converter;
    drawText(0, 0, canvasWidth, canvasHeight, converter.from_bytes(msg));
}

void Renderer::tell(const u32string &msg, bool animated, const function<void()> &onProceed) {
    activeDialogue = {
            msg,
            animated ? 0 : (int) msg.size(),
            0,
            onProceed
    };
}

void Renderer::tell(const string &msg, bool animated, const function<void()> &onProceed) {
    std::wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
    tell(conv.from_bytes(msg), animated, onProceed);
}

void Renderer::ask(const u32string &question,
                   const vector<u32string> &choices,
                   const function<void(const int &)> &onDecide) {
    activePrompt = {
            question,
            choices,
            onDecide,
            0
    };
}

bool Renderer::ready() {
    return !activePrompt && !activeDialogue;
}