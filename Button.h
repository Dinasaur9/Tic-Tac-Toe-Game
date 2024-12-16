#ifndef BUTTON_H
#define BUTTON_H

#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <iostream>
#include <string>

class Button{
private:
    std::string text;
    float x, y, w, h;
    float r, g, b;
    float xr, xg, xb;
    bool selected;
    bool highlight;
public:
    Button() : x(0.0f), y(0.0f), w(0.10f), h(0.6f), selected(false), highlight(false),text("Button"){
    }
    Button(const std::string& text, float x, float y, float w, float h) : text(text), x(x), y(y), w(w), h(h), r(1.0f), g(0.0f), b(0.0f), xr(0.0f), xg(0.0f), xb(1.0f), selected(false), highlight(false){
        //
    }
    Button(std::string text, float x, float y, float w, float h, float r, float g, float b){
        this->text = text;
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->r = r;
        this->g = g;
        this->b = b;
        selected = false;
        highlight = false;
    }
    void draw(){
        if (selected){
            glColor3f(xr, xg, xb);
        }else if(highlight){
            glColor3f(((r + xr) / 2), ((g + xg) / 2), ((b + xb) / 2));
        }else {
            glColor3f(r, g, b);
        }
        glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
        glEnd();
        glColor3f(1.0f, 1.0f, 1.0f);
        glPushMatrix();
        glTranslatef(x + w / 2, y - h / 2, 0);
        glScalef(0.0005f, 0.0005f, 0.0005f);
        float textWidth = 0;
        for (char a : text){
            textWidth += glutStrokeWidth(GLUT_STROKE_ROMAN, a);
        }
        glTranslatef(-textWidth / 2, -50, 0);
        for (char a : text){
            glutStrokeCharacter(GLUT_STROKE_ROMAN, a);
        }
        glPopMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
            glVertex2f(x, y - h);
            glVertex2f(x, y);
        glEnd();
    }
    bool contains(float mx, float my){
        if (mx >= x && mx <= x + w && my <= y && my >= y - h){
            return true;
        }
        return false;
    }
    float getX(){
        return x;
    }
    float getY(){
        return y;
    }
    void select(){
        selected = true;
    }
    void deselect(){
        selected = false;
    }
    void setHighlighted(bool isHighlighted){
        highlight = isHighlighted;
    }
    bool isHighlighted() const{
        return highlight;
    }
    void setX(float x){
        this->x = x;
    }
    void setY(float y){
        this->y = y;
    }
};

#endif