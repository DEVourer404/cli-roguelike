#include "Input.h"
#include <termios.h>
#include <unistd.h>

namespace Terminal {
    Key getKey() {
        termios oldSettings{};
        if (tcgetattr(STDIN_FILENO, &oldSettings) < 0) {
            return Key::Unknown;
        }

        termios newSettings = oldSettings;
        newSettings.c_lflag &= ~(ICANON | ECHO);
        newSettings.c_cc[VMIN] = 1;
        newSettings.c_cc[VTIME] = 0;

        if (tcsetattr(STDIN_FILENO, TCSANOW, &newSettings) < 0) {
            return Key::Unknown;
        }

        char ch = 0;
        read(STDIN_FILENO, &ch, 1);

        Key result = Key::Unknown;

        if (ch == 27) {
            newSettings.c_cc[VMIN] = 0;
            newSettings.c_cc[VTIME] = 1;
            tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

            char seq[2] = {0, 0};
            if (read(STDIN_FILENO, &seq[0], 1) > 0 && read(STDIN_FILENO, &seq[1], 1) > 0) {
                if (seq[0] == '[') {
                    switch (seq[1]) {
                        case 'A': result = Key::Up; break;
                        case 'B': result = Key::Down; break;
                        case 'C': result = Key::Right; break;
                        case 'D': result = Key::Left; break;
                    }
                }
            } else {
                result = Key::Escape;
            }
        }
        else if (ch == '\n' || ch == '\r') {
            result = Key::Enter;
        }
        else if (ch == ' ') {
            result = Key::Space;
        }
        else {
            switch (ch) {

                case 'w': case 'W': result = Key::W; break;
                case 'a': case 'A': result = Key::A; break;
                case 's': case 'S': result = Key::S; break;
                case 'd': case 'D': result = Key::D; break;

                case 'i': case 'I': result = Key::I; break;
                case 'q': case 'Q': result = Key::Q; break;

                case '0': result = Key::Num0; break;
                case '1': result = Key::Num1; break;
                case '2': result = Key::Num2; break;
                case '3': result = Key::Num3; break;
                case '4': result = Key::Num4; break;
                case '5': result = Key::Num5; break;
                case '6': result = Key::Num6; break;
                case '7': result = Key::Num7; break;
                case '8': result = Key::Num8; break;
                case '9': result = Key::Num9; break;

                default: result = Key::Unknown; break;
            }
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
        return result;
    }
}