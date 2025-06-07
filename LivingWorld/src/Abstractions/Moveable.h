#pragma once

class Moveable {
public:
    virtual void move(int dx, int dy) = 0;
    virtual ~Moveable() = default;
};