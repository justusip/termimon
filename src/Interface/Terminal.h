#pragma once

#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;

class Terminal {
public:
    static constexpr u32string_view RED = U"\x1B[31m";
    static constexpr u32string_view GRN = U"\x1B[32m";
    static constexpr u32string_view YEL = U"\x1B[33m";
    static constexpr u32string_view BLU = U"\x1B[34m";
    static constexpr u32string_view MAG = U"\x1B[35m";
    static constexpr u32string_view CYN = U"\x1B[36m";
    static constexpr u32string_view WHT = U"\x1B[37m";
    static constexpr u32string_view GRY = U"\x1B[90m";
    static constexpr u32string_view RST = U"\x1B[0m";
    static constexpr u32string_view BLD = U"\x1B[1m";
    static constexpr u32string_view ITC = U"\x1B[3m";
    static constexpr u32string_view UDL = U"\x1B[4m";

    static inline void cursorShown(bool shown) {
        cout << (shown ? "\033[?25h" : "\033[?25l");
    }

    //TODO deprecated
    static inline void getCanvasSize(int &width, int &height) {
        width = 80;
        height = 24;
    }

    static inline void getViewportSize(int &width, int &height) {
        struct winsize w{};
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        width = w.ws_col;
        height = w.ws_row;
        if (width == 0 && height == 0) {
            width = 80;
            height = 24;
        }
    }

    static inline void cursorUp(int lines) {
        for (int i = 0; i < lines; i++)
            cout << "\033[A";
        cout.flush();
    }

    static inline void cursorDown(int lines) {
        for (int i = 0; i < lines; i++)
            cout << "\033[B";
        cout.flush();
    }

    static inline void cursorToStart() {
        cout << "\r";
    }

    static inline void clearLine() {
        int w, h;
        getCanvasSize(w, h);
        cout << "\r";
        for (int x = 0; x < w; x++)
            cout << " ";
    }

    static inline void clearScreen() {
        moveTo(0, 0);
        padScreen();
    }

    static inline void padLines(int lines) {
        for (int i = 0; i < lines; i++) {
            clearLine();
            cout << endl;
        }
    }

    static inline void padScreen() {
        int w, h;
        getCanvasSize(w, h);
        for (int i = 0; i < h; i++) {
            clearLine();
            if (i + 1 < h)
                cout << endl;
        }
    }

    static inline void moveTo(int x, int y) {
        cout << "\033[" << y << ";" << x << "H";
    }

    static inline std::u32string formatColour(std::u32string &line) {
        std::u32string buf;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == U'&') {
                switch (line[i + 1]) {
                    case U'a':
                        buf += Terminal::GRN;
                        break;
                    case U'b':
                        buf += Terminal::BLU;
                        break;
                    case U'c':
                        buf += Terminal::RED;
                        break;
                    case U'd':
                        buf += Terminal::MAG;
                        break;
                    case U'e':
                        buf += Terminal::YEL;
                        break;
                    case U'f':
                        buf += Terminal::WHT;
                        break;
                    case U'r':
                        buf += Terminal::RST;
                        break;
                }
                i++;
            } else {
                buf += line[i];
            }
        }
        return buf;
    }
};
