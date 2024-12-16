#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <cstddef>
#include <iostream>
#include "AppController.h"
#include "StartScreen.h"
#include "Button.h"
#include "TicTacToeGrid.h"
#include "Canvas.h"
#include "EndScreen.h"
#include "GameOutcome.h"
#include "GameState.h"

class Controller : public AppController{
private:
    StartScreen* menuScreen;
    Canvas* gameCanvas;
    EndScreen resultScreen;
    GameOutcome finalOutcome;
    GameState state;
public:
    Controller() : state(STARTING), gameCanvas(nullptr), finalOutcome(NONE), menuScreen(new StartScreen()){
        //
    }
    void render(){
        glColor3f(1.0f, 1.0f, 1.0f);
        if (state == STARTING){
            menuScreen->draw();
        }else if (state == PLAYING && gameCanvas){
            gameCanvas->draw();
        }else if (state == END){
            resultScreen.draw(finalOutcome);
        }
        glutSwapBuffers();
    }
    void leftMouseDown(float mx, float my){
        if (state == STARTING){
            menuScreen->handleMouseClick(mx, my);
            if (menuScreen->isPlayClicked()){
                bool vsAI = menuScreen->isPlayingAgainstAI();
                int gridSize = menuScreen->getSize();
                gameCanvas = new Canvas(gridSize, vsAI);
                state = PLAYING;
            }
        }else if (state == PLAYING && gameCanvas){
            gameCanvas->handleMouseClick(mx, my);
            char status = gameCanvas->getGameStatus();
            if (status != ' '){
                if (status == 'P'){
                    finalOutcome = PLAYER_WINS;
                }else if (status == 'C'){
                    finalOutcome = AI_WINS;
                }else if (status == 'T'){
                    finalOutcome = TIE;
                }
                state = END;
            }
        }else if (state == END){
            resultScreen.handleMouseClick(mx, my);
            if (resultScreen.isAgainClicked()){
                if (gameCanvas){
                    delete gameCanvas;
                    gameCanvas = nullptr;
                }
                reset();
                glutPostRedisplay();
            }else if (resultScreen.isQuitClicked()){
                if (gameCanvas){
                    delete gameCanvas;
                    gameCanvas = nullptr;
                }
                exit (0);
            }
        }
        glutPostRedisplay();
    }
    void leftMouseUp(float mx, float my){
        if (state == STARTING){
            menuScreen->handleMouseMotion(mx, my);
        }
        else if (state == END){
            resultScreen.handleMouseMotion(mx, my);
        }
    }
    void reset(){
        if (gameCanvas){
            delete gameCanvas;
            gameCanvas = nullptr;
        }
        menuScreen = new StartScreen();
        state = STARTING;
        finalOutcome = NONE;
        resultScreen.reset();
    }

    ~Controller(){
        if (gameCanvas){
            delete gameCanvas;
            gameCanvas = nullptr;
        }
    }
};

#endif