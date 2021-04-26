#pragma once

#include <array>
#include <codecvt>
#include <cstring>
#include <fstream>
#include <locale>
#include <optional>
#include <string>
#include <sstream>
#include <vector>

#include "../Visuals/Colour.h"
#include "../Interface/Terminal.h"
#include "../Interface/Inputs.h"
#include "../Interaction/Dialogue.h"
#include "../Interaction/Prompt.h"
#include "../Data/Sprites.h"
#include "../Misc/Random.h"

using namespace std;

class Renderer {

private:
    int viewportWidth, viewportHeight;
    int prevViewportWidth, prevViewportHeight;
    int canvasWidth = 80, canvasHeight = 24;

    optional<Dialogue> activeDialogue = {};
    optional<Prompt> activePrompt = {};

    int lastRender;
    int fps = 20;

public:
    static constexpr std::u32string_view FRAME_STYLE_1 = U"─|++++";
    static constexpr std::u32string_view FRAME_STYLE_2 = U"═║╔╗╚╝";

    char32_t *viewportGlyphs = nullptr;
    Colour *viewportFg = nullptr;
    Colour *viewportBg = nullptr;

    char32_t *canvasGlyphs = nullptr;
    Colour *canvasFg = nullptr;
    Colour *canvasBg = nullptr;

    Renderer();

    ~Renderer();

    void clearBuf();

    void onUpdate(const int &elapsed);

    void onRender(const int &elapsed);

    inline void drawPixel(int x, int y, char32_t c);

    inline void drawPixel(int x, int y, char32_t c, Colour fgColour);

    inline void drawPixel(int x, int y, char32_t c, Colour fgColour, Colour bgColour);

    void drawScene(int mapWidth, int mapHeight,
                   const char32_t *mapGlyphs, const Colour *mapFg, const Colour *mapBg,
                   int playerX, int playerY);

    void drawFrame(int x, int y, int w, int h, const u32string_view &style);

    void drawText(int x, int y, int w, int h, const u32string &msg);

    void drawDialogue(const int &elapsed);

    void drawQuestion(const int &elapsed);

    void drawStatus(int x, int y, const u32string &name, float health, int level, float exp, bool male);

    void drawSprite(int x, int y, int id, bool flipped);

    void debug(const string &msg);

    void tell(const u32string &msg,
              bool animated,
              const function<void()> &onProceed);

    void tell(const string &msg,
              bool animated,
              const function<void()> &onProceed);

    void ask(const u32string &question,
             const vector<u32string> &choices,
             const function<void(const int &)> &onDecide);

    bool ready();
};