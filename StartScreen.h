#ifndef START_SCREEN_H
#define START_SCREEN_H

#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <string>
#include "GridSize.h"
#include "Button.h"

class StartScreen{
private:
    Button* AI;
    Button* human;
    Button* threexthree;
    Button* fourxfour;
    Button* fivexfive;
    Button* play;
    int buttonCount;
    int selectedButtonIndex;
    int selectedGridSize;
    bool playingAgainstAI;
    bool playing;
    GridSize size;

    void deselectAll(){
        threexthree->deselect();
        fourxfour->deselect();
        fivexfive->deselect();
        human->deselect();
        play->deselect();
    }

    void checkHighlighted(float mx, float my){
        threexthree->setHighlighted(threexthree->contains(mx, my));
        fourxfour->setHighlighted(fourxfour->contains(mx, my));
        fivexfive->setHighlighted(fivexfive->contains(mx, my));
        human->setHighlighted(human->contains(mx, my));
        AI->setHighlighted(AI->contains(mx, my));
        play->setHighlighted(play->contains(mx, my));
    }
public:
    StartScreen() : buttonCount(6), selectedButtonIndex(-1), selectedGridSize(3), playingAgainstAI(true), playing(false), size (THREEXTHREE){
        threexthree = createButton("3 X 3 GRID", -0.4f, 0.3f);
        fourxfour = createButton("4 X 4 GRID", -0.4f, 0.1f);
        fivexfive = createButton("5 X 5 GRID", -0.4f, -0.1f);
        human = createButton("Human", -0.4f, -0.3f);
        AI = createButton("AI", -0.4f, -0.5f);
        play = createButton("Play", -0.4f, -0.7f);
    }
    Button* createButton(const std::string& text, float x, float y, float w = 0.8f, float h = 0.2f){
        return new Button(text, x, y, w, h);
    }

    void draw(){
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

        threexthree->draw();
        fourxfour->draw();
        fivexfive->draw();
        human->draw();
        AI->draw();
        play->draw();
        glColor3f(1.0f, 1.0f, 1.0f);
        drawText(-0.41f, 0.6f, "TIC TAC TOE");
        drawText(-0.41f, 0.4f, " GAME :D");
    }
    void handleMouseClick(float mx, float my){
        if (checkGridClick(threexthree, THREEXTHREE, 3, mx, my)) return;
        if (checkGridClick(fourxfour, FOURXFOUR, 4, mx, my)) return;
        if (checkGridClick(fivexfive, FIVEXFIVE, 5, mx, my)) return;
        if (human->contains(mx, my)){
            deselectAll();
            human->select();
            playingAgainstAI = false;
        }else if (AI->contains(mx, my)){
            deselectAll();
            AI->select();
            playingAgainstAI = true;
        }else if (play->contains(mx, my)){
            deselectAll();
            play->select();
            playing = true;
            std::cout << "Starting game with size " << selectedGridSize << ". You're playing against " << (playingAgainstAI ? "AI" : "Human") << std::endl;
        }
    }
    bool checkGridClick(Button* button, GridSize gridSizeEnum, int gridSizeValue, float mx, float my){
        if (button->contains(mx, my)){
            deselectAll();
            button->select();
            size = gridSizeEnum;
            selectedGridSize = gridSizeValue;
            std::cout << "You picked size " << selectedGridSize << std::endl;
            return true;
        }
        return false;
    }

    void handleMouseMotion(float mx, float my){
        checkHighlighted(mx, my);
    }

    void drawText(float x, float y, const std::string& text){
        glPushMatrix();
        glTranslatef(x, y, 0);
        glScalef(0.001f, 0.001f, 0.001f);
        for (size_t i = 0; i < text.size(); i++){
            glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
        }
        glPopMatrix();
    }

    bool isPlayClicked() const{
        return playing;
    }

    bool isPlayingAgainstAI(){
        if(playingAgainstAI){
            return true;
        }else {return false; }
    }

    GridSize getSelectedSize(){
        return size;
    }

    int getSize(){
        return selectedGridSize;
    }

    ~StartScreen(){
        delete AI;
        delete human;;
        delete threexthree;
        delete fourxfour;
        delete fivexfive;
        delete play;
    }
};

#endif