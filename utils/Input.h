#ifndef INPUT_H
#define INPUT_H

enum class Key {
    Unknown,

    // movement
    Up, Down, Left, Right,
    W, A, S, D,

    // actions
    Enter,
    Space,
    I, // inventory
    Q,

    // nums 0-9
    Num0, Num1, Num2, Num3, Num4,
    Num5, Num6, Num7, Num8, Num9,

    // exit
    Escape
};

namespace Terminal {
    Key getKey();
}

#endif //INPUT_H
