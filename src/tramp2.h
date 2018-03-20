#include "main.h"

#ifndef TRAMP2_H
#define TRAMP2_H


class Tramp2{
public:
    Tramp2() {}
    Tramp2(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
