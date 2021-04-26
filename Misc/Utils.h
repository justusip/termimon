#pragma once

#include <codecvt>
#include <optional>
#include <string>
#include <locale>

using namespace std;

class Utils {
public:
    static int u8Length(const string &s) {
        int c, i, ix, q;
        for (q = 0, i = 0, ix = s.length(); i < ix; i++, q++) {
            c = (unsigned char) s[i];
            if (c >= 0 && c <= 127) i += 0;
            else if ((c & 0xE0) == 0xC0) i += 1;
            else if ((c & 0xF0) == 0xE0) i += 2;
            else if ((c & 0xF8) == 0xF0) i += 3;
            else return -1;
        }
        return q;
    }

    static string toU8(const u32string &from) {
        return converter.to_bytes(from);
    }

    static u32string toU32(const string &from) {
        return converter.from_bytes(from);
    }

private:
    static wstring_convert<codecvt_utf8<char32_t>, char32_t> converter;
};
