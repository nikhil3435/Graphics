#include "main.h"

#ifndef Plank_H
#define Plank_H


class Plank{
public:
    Plank() {}
    Plank(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object1,*object2;
};

#endif // BALL_H
