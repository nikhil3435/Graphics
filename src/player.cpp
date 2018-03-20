#include "player.h"
#include "main.h"
#define pi 3.1459
int nn=0;
double tim = 0.0;
Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.03;
    speedy=0;
    double radius = 3;
    static GLfloat vertex_buffer_data[2000];
        int i,k,j;
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

          this->object1 = create3DObject(GL_TRIANGLES, 30, vertex_buffer_data,COLOR_VIOLET,GL_FILL);
          this->object2 = create3DObject(GL_TRIANGLES, 30, vertex_buffer_data + 9*10,COLOR_INDIGO,GL_FILL);
          this->object3 = create3DObject(GL_TRIANGLES, 30, vertex_buffer_data + 9*20,COLOR_BLUE,GL_FILL);
          this->object4 = create3DObject(GL_TRIANGLES, 30, vertex_buffer_data + 9*30,COLOR_GREEN,GL_FILL);
          this->object5 = create3DObject(GL_TRIANGLES, 30, vertex_buffer_data + 9*40,COLOR_YELLOW,GL_FILL);
          this->object6 = create3DObject(GL_TRIANGLES, 30, vertex_buffer_data + 9*50,COLOR_ORANGE,GL_FILL);

}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);

}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::tick(int pp) {
    //this->position.x = speed;
    //float nn = 0.2;
    // speedy = 0;
    //this->position.x -= speed;

        if(this->position.y<=-0.3 && (nn && this->speedy)){
            this->position.y=-0.3;
            this->speedy=0;
            nn=0;
            tim=0.01;

        }
        if(this->position.y >= 4.0){
        this->position.y= 4.0;
            this->speedy=-this->speedy;
        }

         if(this->speedy !=0 )
        {

            //this->position.y += (speedy*tim)-(4.9*(tim*tim));
            //tim+=0.01;
            //nn=1;
             this->position.y += this->speedy;
             this->speedy -= 0.01;
        }

    //float tt = 0.01;
    //this->position.y = ((0.04 * tt) - (0.5 * 9.8 * tt * tt));

}

bounding_box_t Player::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
