#include "Input.h"
#include <conio.h>

namespace Terminal {
    Key getKey() {
        int ch = _getch();

        if (ch == 0 || ch == 224) {
            int code = _getch();
            switch (code) {
                case 72: return Key::Up;
                case 80: return Key::Down;
                case 75: return Key::Left;
                case 77: return Key::Right;
                default: return Key::Unknown;
            }
        }

        switch (ch) {
            case 13: return Key::Enter;
            case 27: return Key::Escape;
            case ' ': return Key::Space;

            case 'w': case 'W': return Key::W;
            case 'a': case 'A': return Key::A;
            case 's': case 'S': return Key::S;
            case 'd': case 'D': return Key::D;

            case 'i': case 'I': return Key::I;
            case 'q': case 'Q': return Key::Q;

            case '0': return Key::Num0;
            case '1': return Key::Num1;
            case '2': return Key::Num2;
            case '3': return Key::Num3;
            case '4': return Key::Num4;
            case '5': return Key::Num5;
            case '6': return Key::Num6;
            case '7': return Key::Num7;
            case '8': return Key::Num8;
            case '9': return Key::Num9;

            default: return Key::Unknown;
        }
    }
}