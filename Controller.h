#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <GL/freeglut.h>
#include "AppController.h"

class Controller : public AppController {


public:
    Controller(){
        // Initialize your state variables
    }

    void render() {
        // Render some graphics
    }

    void leftMouseDown(float mx, float my) {
        //
    }

    ~Controller(){
        // Release memory
    }
};

#endif