#pragma once

class Reproduction {
public:
    virtual bool canReproduce() = 0;
    virtual void reproduce() = 0;
    virtual ~Reproduction() = default;
};

