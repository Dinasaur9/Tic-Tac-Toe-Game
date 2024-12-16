#ifndef END_SCREEN_H
#define END_SCREEN_H

#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <string>
#include "Button.h"
#include "GridSize.h"
#include "TicTacToeGrid.h"
#include "GameOutcome.h"

class EndScreen {
private:
    Button* playAgain;
    Button* quitGame;

    bool xQuit;
    bool xPlayAgain;

    void deselectAll(){
        if (playAgain) playAgain->deselect();
        if (quitGame) quitGame->deselect();
    }
    void checkHighlighted(float mx, float my){
        if (playAgain) playAgain->setHighlighted(playAgain->contains(mx, my));
        if (quitGame) quitGame->setHighlighted(quitGame->contains(mx, my));
    }
public:
    EndScreen() : xQuit(false), xPlayAgain(false){
        initializeButtons();
    }
    void initializeButtons(){
        float buttonWidth = 0.9f;
        float buttonHeight = 0.4f;
        float gap = 0.0f;
        quitGame = createButton("Quit Game", -0.45f, 0.1f, buttonWidth, buttonHeight);
        playAgain = createButton("Play Again", -0.45f, 0.1f - buttonHeight - gap, buttonWidth, buttonHeight);
    }
    Button* createButton(const std::string& text, float x, float y, float w = 0.8f, float h = 0.2f){
        return new Button(text, x, y, w, h);
    }
    void draw(GameOutcome outcome){
        drawBackground();
        drawButtons();
        drawTitle();
        drawOutcomeText(outcome);
    }
    void drawBackground(){
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_POLYGON);
            glVertex2f(-1.0f, 1.0f);
            glVertex2f(1.0f, 1.0f);
            glVertex2f(1.0f, -1.0f);
            glVertex2f(-1.0f, -1.0f);
        glEnd();
        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.6f, -0.9f);
            glVertex2f(0.6f, -0.9f);
            glVertex2f(0.6f, 1.0f);
            glVertex2f(-0.6f, 1.0f);
        glEnd();
    }
    void drawButtons(){
        if (quitGame) quitGame->draw();
        if (playAgain) playAgain->draw();
    }
    void drawTitle(){
        glColor3f(1.0f, 0.0f, 0.0f);
        drawText(-0.4f, 0.6f, "TIC TAC TOE");
    }
    void drawOutcomeText(GameOutcome outcome){
        const char* outcomeText = nullptr;
        switch (outcome){
            case PLAYER_WINS : outcomeText = "X WINS";
            break;
            case AI_WINS : outcomeText = "O WINS";
            break;
            case TIE : outcomeText = "TIE GAME";
            break;
            default : return;
        }
        if (outcomeText){
            drawText(-0.25f, 0.4f, outcomeText);
        }
    }
    void handleMouseClick(float mx, float my){
        if (playAgain && playAgain->contains(mx, my)){
            deselectAll();
            playAgain->select();
            xPlayAgain = true;
            std::cout << "You decided to play again" << std::endl;
        }
        else if (quitGame && quitGame->contains(mx, my)){
            deselectAll();
            quitGame->select();
            xQuit = true;
            std::cout << "You quit the game" << std:: endl;
        }
    }
    void handleMouseMotion(float mx, float my){
        checkHighlighted(mx, my);
    }
    void drawText(float x, float y, const std::string& text){
        glPushMatrix();
        glTranslatef(x, y, 0);
        glScalef(0.001f, 0.001f, 0.001f);
        for (char c : text){
            glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
        }
        glPopMatrix();
    }
    bool isAgainClicked(){
        if (xPlayAgain){
            return true;
        }else{
            return false;
        }
    }
    bool isQuitClicked(){
        if(xQuit){
            return true;
        }else{return false;}
    }
    void reset(){
        xQuit = false;
        xPlayAgain = false;
        if (quitGame){
            quitGame->deselect();
        }
        if (playAgain){
            playAgain->deselect();
        }
    }
    ~EndScreen(){
        delete quitGame;
        delete playAgain;
        quitGame = nullptr;
        playAgain = nullptr;
    }
};

#endif