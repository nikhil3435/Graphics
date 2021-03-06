#include "pond.h"
#include "main.h"
#define pi 3.1459

Pond::Pond(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.00;
    double radius = 8;
    static GLfloat vertex_buffer_data[2000];
        int i,k;
          for(i=0;i<60;i++)
          {
                vertex_buffer_data[9*i]=0.0f;
                vertex_buffer_data[9*i+1]=0.0f;
                vertex_buffer_data[9*i+2]=0.0f;

                    vertex_buffer_data[9*i+3]=cos(i*pi/30)*0.1f*radius;
                    vertex_buffer_data[9*i+4]=sin(i*pi/30)*0.1f*radius;
                    vertex_buffer_data[9*i+5]=0.0f;

                    vertex_buffer_data[9*i+6]=cos((i+1)*pi/30)*0.1f*radius;
                    vertex_buffer_data[9*i+7]=sin((i+1)*pi/30)*0.1f*radius;
                    vertex_buffer_data[9*i+8]=0.0f;
           }

    this->object = create3DObject(GL_TRIANGLES, 90, vertex_buffer_data + 9 *30, color, GL_FILL);
}

void Pond::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Pond::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Pond::tick() {
    this->position.x += speed;
     this->position.y += 0;
}

bounding_box_t Pond::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
