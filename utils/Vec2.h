#ifndef VEC2_H
#define VEC2_H

struct Vec2 {
    int x;
    int y;

    Vec2(int startX = 0, int startY = 0): x(startX), y(startY) {}

    bool operator==(const Vec2& other) const = default;

    Vec2 operator+(const Vec2& other) const {
        Vec2 result = *this;
        result += other;
        return result;
    }

    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
};

#endif //VEC2_H
