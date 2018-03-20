#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int pp);
    double speed;
    bounding_box_t bounding_box();
    float speedy;
private:
    VAO *object1,*object2,*object3,*object4,*object5,*object6;
};

#endif // BALL_H
