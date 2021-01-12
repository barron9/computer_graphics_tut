/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL OpenGL, standard IO, and, strings
#include <SDL.h>
#include <SDL_opengl.h>

#include <OpenGL/glu.h>
#include "GLUT/glut.h"
#include <stdio.h>
#include <string>
#include <thread>
#include <chrono>


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL, creates window, and initializes OpenGL
bool init();

//Initializes matrices and clear color
bool initGL();

//Input handler
void handleKeys(unsigned char key, int x, int y);

//Per frame update
void update();

//Renders quad to the screen
void render();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Render flag
bool gRenderQuad = true;

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;

    } else {
        //Use OpenGL 2.1
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        // Settings
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_SetRelativeMouseMode(SDL_TRUE);
        //Create window
        gWindow = SDL_CreateWindow("gl", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Create context
            gContext = SDL_GL_CreateContext(gWindow);
            if (gContext == NULL) {
                printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                //Use Vsync
                if (SDL_GL_SetSwapInterval(1) < 0) {
                    printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                }

                //Initialize OpenGL
                if (!initGL()) {
                    printf("Unable to initialize OpenGL!\n");
                    success = false;
                }
            }
        }
    }

    return success;
}

bool initGL() {
    bool success = true;
    GLenum error = GL_NO_ERROR;

    //Initialize Projection Matrix
    glMatrixMode(GL_PROJECTION);
   // glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -100.0, 100.0);
    //Check for error
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error initializing OpenGL! %s\n", gluErrorString(error));
        success = false;
    }

    //Initialize Modelview Matrix
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    //Check for error
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error initializing OpenGL! %s\n", gluErrorString(error));
        success = false;
    }

    //Initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    //Check for error
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error initializing OpenGL! %s\n", gluErrorString(error));
        success = false;
    }

    return success;
}

void handleKeys(unsigned char key, int x, int y) {
    //Toggle quad
    if (key == 'q') {
        gRenderQuad = !gRenderQuad;
    }
}

void update() {
    //No per frame update needed
}

void SetupRC() {
    // Light values and coordinates
    GLfloat ambientLight[] = {0.5f, .5f, .5f, 1.0f};
    GLfloat diffuseLight[] = {.5f, .5f, 0.5f, 1.0f};
    glEnable(GL_DEPTH_TEST); // Hidden surface removal
    glFrontFace(GL_CCW); // Counterclockwise polygons face out
    //glEnable(GL_CULL_FACE); // Do not calculate inside of jet
    // Enable lighting
    glEnable(GL_LIGHTING);
    // Set up and enable light 0
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
    glEnable(GL_LIGHT1);
    // glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);
    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
    // Set material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
#define PI 3.14

void render(float angle) {
    //Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SetupRC();
    if (gRenderQuad) {

        glBegin(GL_POINTS);
        for (int k = -10; k < 10; ++k) {
            for (int g = -10; g < 10; ++g) {
                for (int j = -10; j < 10; ++j) {
                    // glVertex3f(.30f * g, .30f * k, .30f * j);
                }
            }
        }
        glEnd();
        // glLoadIdentity();
        
        glPushMatrix();
       // glMatrixMode(GL_MODELVIEW);
        //angle++;
        //glRotatef(angle, 0, 1, 0);
   
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        for (int y = 0; y < 5; y++) {
            glBegin(GL_TRIANGLES);
            glColor3ub(0, 255, 128);
            glVertex3f(-.25f * y, 0.0f, .10f);
            glColor3ub(0, 255, 0);
            glVertex3f(0.0f, .30f * y, .10f);
            glColor3ub(255, 5, 8);
            glVertex3f(0.0f, 0.0f, -.16f * y);
            glEnd();
        }
        glPopMatrix();
        // glLoadIdentity();

       
        glPushMatrix(); 
        //angle++;
        glRotatef(angle, 0, 1, 0);
        //glPolygonMode(GL_BACK, GL_LINE);
        glColor3ub(255, 1, 1);
        glBegin(GL_POLYGON);
        glVertex3f(.6f, 0.0f, 0.0f);
        glVertex3f(0.0f, .6f, 0.0f);
        glVertex3f(-.6f, 0.0f, 0.0f);
        glVertex3f(0.0f, -.6f, 0.0f);
        glEnd();
        // }
        glPopMatrix();
    }

    glEnable(GL_DEPTH_TEST);
    glDepthRange(0, 1);
    glEnable(GL_DEPTH_TEST);

}

void close() {
    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char *args[]) {
    float angle = 1;
    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;

        //Enable text input
        SDL_StartTextInput();

        //While application is running
        while (!quit) {
            // glViewport(0,0,500,300);

            //Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                //User requests quit
                if (e.type == SDL_QUIT) {
                    quit = true;
                }//Handle keypress with current mouse position
                else if (e.type == SDL_TEXTINPUT) {
                    int x = 0, y = 0;
                    SDL_GetMouseState(&x, &y);
                    handleKeys(e.text.text[0], x, y);
                }
                if (e.type == SDL_MOUSEMOTION) {
                    e.motion.xrel;
                    e.motion.yrel;
                    //glRotatef(e.motion.xrel / 3, 0, 1, 0);
                    //glRotatef(e.motion.yrel / 3, 0, 0, 1);
                    
                    //quit = true;
                }
                if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case 1073741903:

                            break;
                        case 1073741904:

                            break;
                        case 1073741905:
                            angle += 1 ; 
                           // glRotatef(5, 0, 0, 0);
                            //glTranslatef(0, 0, 0);
                            break;
                        case 1073741906:
                         //   glRotatef(-5, 0, 0, 0);
                           // glTranslatef(0, 0, 0);
                            break;
                    }
                }
            }

            //Render quad
            render(angle);

            //Update screen
            SDL_GL_SwapWindow(gWindow);
        }

        //Disable text input
        SDL_StopTextInput();
    }

    //Free resources and close SDL
    close();

    return 0;
}