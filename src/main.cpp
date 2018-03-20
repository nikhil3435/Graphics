#include "main.h"
#include "timer.h"
#include "ground.h"
#include "ball.h"
#include "player.h"
#include "tramp1.h"
#include "tramp2.h"
#include "pond.h"
#include "spike.h"
#include "plank.h"
#include "magnet.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ground floor1,floor2,floor3,floor4;
Ball ball1,ball2,ball3,ball4,ball5,ball6,ball7,ball8,ball9;
Player player1;
Tramp2 rect1,rect2;
Tramp1 scircle;
Pond water;
Spike spike1,spike2,spike3;
Plank plank1,plank2,plank3;
Magnet magnet;
int flag=1;
int pp=0,score,level=1;
int pan=0;
double rspeedy=0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(pan/8, 0, 3), glm::vec3(pan/8, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    player1.draw(VP);
    ball1.draw(VP);
    ball2.draw(VP);
    ball3.draw(VP);
    ball4.draw(VP);
    ball5.draw(VP);
    ball6.draw(VP);
    ball7.draw(VP);
    ball8.draw(VP);
    ball9.draw(VP);
    floor1.draw(VP);
    floor2.draw(VP);
    floor3.draw(VP);
    floor4.draw(VP);
    scircle.draw(VP);
    rect1.draw(VP);
    rect2.draw(VP);
    water.draw(VP);
    if(score >= 50){
    spike1.draw(VP);
    spike2.draw(VP);
    spike3.draw(VP);
    level=2;
    }
    if(score>200)
        level=4;
    plank1.draw(VP);
    plank2.draw(VP);
    plank3.draw(VP);
    if (score > 120){
    magnet.draw(VP);
    level=3;
    rspeedy=0.005;
    player1.position.x -= rspeedy;
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    if (left && flag) {
        player1.position.x -= 0.04;
      //  player1.rotation-=10;
        // Do something
    }
    if (right && flag) {
        player1.position.x += 0.04;
        //player1.rotation+=10;
    }
    if (up && flag && player1.position.y <= -0.2) {
        player1.speedy = 0.2;
    }
    int panright = glfwGetKey(window, GLFW_KEY_M);
    if(panright)
    {
      pan+=1;
    }
    int panleft = glfwGetKey(window, GLFW_KEY_N);
    if(panleft)
    {
      pan-=1;
    }

}

void tick_elements() {
    ball1.tick();
    ball2.tick();
    ball3.tick();
    ball4.tick();
    ball5.tick();
    ball6.tick();
    ball7.tick();
    ball8.tick();
    ball9.tick();
    spike1.tick();
    spike2.tick();
    spike3.tick();
    plank1.tick();
    plank2.tick();
    plank3.tick();
    player1.tick(pp);
        if (detect_collision(player1.bounding_box(),ball1.bounding_box()) && player1.speedy < 0){
            ball1.position.x=-5.0;
           // printf("detected\n");
            player1.speedy =0.2;
            score+=10;
            printf("Score:%d Level:%d\n",score,level);
             //rspeedy=0.00;
        }
        if (detect_collision(player1.bounding_box(),ball2.bounding_box()) && player1.speedy < 0){
            ball2.position.x=-5.0;
            //printf("detected\n");
            player1.speedy =0.2;
            score+=10;
            //rspeedy=0.00;
             printf("Score:%d Level:%d\n",score,level);
        }
        if (detect_collision(player1.bounding_box(),ball3.bounding_box()) && player1.speedy < 0){
            ball3.position.x=-5.0;
            //printf("detected\n");
            player1.speedy = 0.2;
            score+=10;
            //rspeedy=0.00;
             printf("Score:%d Level:%d\n",score,level);
        }
        if (detect_collision(player1.bounding_box(),ball4.bounding_box()) && player1.speedy < 0){
            ball4.position.x=-5.0;
            //printf("detected\n");
            player1.speedy = 0.2;
            //rspeedy=0.00;
            score+=10;
             printf("Score:%d Level:%d\n",score,level);
        }
        if (detect_collision(player1.bounding_box(),ball5.bounding_box()) && player1.speedy < 0){
            ball5.position.x=-5.0;
            //printf("detected\n");
            player1.speedy = 0.2;
            score+=10;
            //rspeedy=0.00;
             printf("Score:%d Level:%d\n",score,level);
        }
        if (detect_collision(player1.bounding_box(),ball6.bounding_box()) && player1.speedy < 0){
            ball6.position.x=-5.0;
            //printf("detected\n");
            player1.speedy = 0.2;
            score+=10;
            //rspeedy=0.00;
             printf("Score:%d Level:%d\n",score,level);
        }
        if (detect_collision(player1.bounding_box(),ball7.bounding_box()) && player1.speedy < 0){
            ball7.position.x=-5.0;
            player1.speedy = 0.2;
            score +=10;
            //rspeedy=0.00;
             printf("Score:%d Level:%d\n",score,level);
        }
        if (detect_collision(player1.bounding_box(),ball8.bounding_box()) && player1.speedy < 0){
            ball8.position.x=-5.0;
            //printf("detected\n");
            player1.speedy = 0.2;
            score+=10;
            //rspeedy=0.00;
             printf("Score:%d Level:%d\n",score,level);
        }
        if (detect_collision(player1.bounding_box(),ball9.bounding_box()) && player1.speedy < 0){
            ball9.position.x=-5.0;
            //printf("detected\n");
            player1.speedy = 0.2;
            score+=10;
            //rspeedy=0.00;
             printf("Score:%d Level:%d\n",score,level);
       }
        if (detect_collision_plank(player1.bounding_box(),plank1.bounding_box()) && player1.speedy < 0){

            player1.speedy = 0.25;
            //rspeedy=0.01;
        }
        player1.position.x -= rspeedy;
        if (detect_collision_plank(player1.bounding_box(),plank2.bounding_box()) && player1.speedy < 0){

            player1.speedy = 0.25;
             //rspeedy=0.01;

        }
        if (detect_collision_plank(player1.bounding_box(),plank3.bounding_box()) && player1.speedy < 0){

            player1.speedy = 0.25;
               //      rspeedy=0.01;
        }
       if (detect_collision_tramp(player1.bounding_box(),scircle.bounding_box())){
           if (player1.position.x >= 1.4  && player1.position.x <= 2.9 && player1.position.y <= 0.4){
               player1.speedy = 0.2;
           }
       }
       if (detect_collision_spike(player1.bounding_box(),spike1.bounding_box())){

           player1.position.x = 4.0;
           player1.position.y=-0.3;
           score-=15;
            printf("Score:%d Level:%d\n",score,level);
       }
       if (detect_collision_spike(player1.bounding_box(),spike2.bounding_box())){

           player1.position.x = 4.0;
           player1.position.y=-0.3;
           score-=15;
            printf("Score:%d Level:%d\n",score,level);
       }
       if (detect_collision_spike(player1.bounding_box(),spike3.bounding_box())){

           player1.position.x = 4.0;
           player1.position.y=-0.3;
           score-=15;
            printf("Score:%d Level:%d\n",score,level);
       }


    if (ball1.position.x > 5.0){
        ball1.position.x = -5.0;
    }
    if (ball2.position.x > 5.0){
        ball2.position.x = -5.0;
    }
    if (ball3.position.x > 5.0){
        ball3.position.x = -5.0;
    }
    if (ball4.position.x >5.0){
        ball4.position.x = -5.0;
    }
    if (ball5.position.x > 5.0){
        ball5.position.x = -5.0;
    }
    if (ball6.position.x > 5.0){
        ball6.position.x = -5.0;
    }
    if (ball7.position.x > 5.0){
        ball7.position.x = -5.0;
    }
    if (ball8.position.x > 5.0){
        ball8.position.x = -5.0;
    }
    if (ball9.position.x > 5.0){
        ball9.position.x = -5.0;
    }
    if (plank1.position.x > 5.0){
        plank1.position.x = -5.0;
    }
    if (plank2.position.x > 5.0){
        plank2.position.x = -5.0;
    }
    if (plank3.position.x > 5.0){
        plank3.position.x = -5.0;
    }
    if (player1.position.y < -0.2){
        player1.position.y= -0.3;
    }
    if (spike3.position.x >= -2 || spike1.position.x <= -4.5 ){
        spike1.speed = -spike1.speed;
        spike2.speed = -spike2.speed;
        spike3.speed = -spike3.speed;
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ball1        = Ball(-6.2,2,COLOR_YELLOW);
    ball2        = Ball(-4.8,3.2,COLOR_YELLOW);
    ball3        = Ball(-3.1,1.4,COLOR_YELLOW);
    ball4        = Ball(-2.2,3.1,COLOR_YELLOW);
    ball5        = Ball(-0.3,4,COLOR_YELLOW);
    ball6        = Ball(0.7,2,COLOR_YELLOW);
    ball7        = Ball(1.5,3.2,COLOR_YELLOW);
    ball8        = Ball(2,1.3,COLOR_YELLOW);
    ball9        = Ball(3,4,COLOR_YELLOW);
    floor1       = Ground(0, -0.6, COLOR_GREEN);
    floor2       = Ground(0, -3, COLOR_BROWN);
    floor3       = Ground(0, -2.2, COLOR_BROWN);
    floor4       = Ground(0,-1.4,COLOR_BROWN);
    player1      = Player(3.5,-0.4,COLOR_RED);
    scircle      = Tramp1(2,0.0,COLOR_TRAMP);
    rect1        = Tramp2(0.2,-0.4,COLOR_TRAMP);
    rect2        = Tramp2(-1.1,-0.4,COLOR_TRAMP);
    water         = Pond(-0.2,-0.6,COLOR_WATER);
    spike1       = Spike(-4,-0.6,COLOR_SPIKE);
    spike2       = Spike(-3.5,-0.6,COLOR_SPIKE);
    spike3       = Spike(-3,-0.6,COLOR_SPIKE);
    plank1       = Plank( -3,2.5,COLOR_INDIGO);
    plank2       = Plank(2,2.5,COLOR_INDIGO);
    plank3       = Plank(0,3,COLOR_INDIGO);
    magnet       = Magnet(-4,2,COLOR_RED);
    spike1.speed=0.03;
    spike2.speed=0.03;
    spike3.speed=0.03;
   //ball2.speed = -ball2.speed;
   pp = -0.3;
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 800;
    int height = 800;

    window = initGLFW(width, height);

    initGL (window, width, height);
    score=0;

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

//        printf("Score:%d\n",score);

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
//            printf("Score:%d\n",score);

            string Result;
                        stringstream convert;
                        //cout << "nonedit score:" << score << endl;
                        convert << score;
                        Result = convert.str();

                        const char *one = "Score ";
                        const char *two = Result.c_str();
                        const char *three = "   Level ";
                        string Result1;
                        stringstream convert1;
                        convert1 << level;
                        Result1 = convert1.str();
                        const char *four = Result1.c_str();
                        string total( string(one) + two + string(three) + four);
                        glfwSetWindowTitle(window, total.c_str());
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

   // printf("%d\n",score);
//    printf("Score:%d\n",score);

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    if(sqrt(abs(((a.x-b.x)*(a.x-b.x))+((a.y-b.y)*(a.y-b.y)))) < 0.3)
        return true ;
    return false;
  //  return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
    //       (abs(a.y - b.y) * 2 < (a.height + b.height));
}

bool detect_collision_plank(bounding_box_t a, bounding_box_t b){
    if(sqrt(abs(((a.x-b.x)*(a.x-b.x))+((a.y-b.y)*(a.y-b.y)))) <= 0.28)
        return true ;
    return false;
}
bool detect_collision_spike(bounding_box_t a, bounding_box_t b){
    if(sqrt(abs(((a.x-b.x)*(a.x-b.x))+((a.y-b.y)*(a.y-b.y)))) < 0.4)
        return true ;
    return false;
}
bool detect_collision_tramp(bounding_box_t a, bounding_box_t b){
    if(sqrt(abs(((a.x-b.x)*(a.x-b.x))+((a.y-b.y)*(a.y-b.y)))) <= 0.4)
        return true ;
    return false;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
void screen_zoom_in(){
    screen_zoom -= 0.1;
    reset_screen();
}
void screen_zoom_out(){
    screen_zoom += 0.1;
    reset_screen();
}
