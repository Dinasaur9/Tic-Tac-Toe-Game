#ifndef TICTACTOEGRID_H
#define TICTACTOEGRID_H

#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include "StartScreen.h"
#include "GameOutcome.h"

class TicTacToeGrid{
private:
    char* grid;
    int size;

public:
    TicTacToeGrid(int gridSize) : size(gridSize), grid(new char[gridSize * gridSize]){
        std::fill(grid, grid + (size * size), ' ');
    }

    bool makeMove(int row, int column, char player){
        if (row < 0 || row >= size || column < 0 || column >= size){
            return false;
        }
        int index = row * size + column;
        if (grid[index] != ' '){
            return false;
        }
        grid[index]=player;
        return true;
    }
    
    void draw(){
        glColor3f(0.0f, 0.0f, 1.0f);
        glLineWidth(4.0f);
        
        float normalCellSize = 1.8f / size;
        float offset = 0.1f;

        glBegin(GL_LINES);
        for (int column = 0; column <= size; column++){
            float pos = -1.0f + offset + column * normalCellSize;
            glVertex2f(pos, 1.0f - offset);
            glVertex2f(pos, -1.0f + offset);
            glVertex2f(-1.0f + offset, pos);
            glVertex2f(1.0f - offset, pos);
        }
        glEnd();
        glColor3f(0.0f, 0.0f, 1.0f);
        glLineWidth(6.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(-1.0f + 0.1f, 1.0f - 0.1f);
        glVertex2f(1.0f - 0.1f, 1.0f - 0.1f);
        glVertex2f(1.0f - 0.1f, -1.0f + 0.1f);
        glVertex2f(-1.0f + 0.1f, -1.0f + 0.1f);
        glEnd();

        for (int row = 0; row < size; ++row){
            for (int column = 0; column < size; ++column){
            char cellContent = grid[row * size + column];
            if (cellContent != ' '){
            float xOffset = -1.0f + (column + 0.5f) * normalCellSize;
            float yOffset = 1.0f - (row + 0.5f) * normalCellSize;
            glColor3f(1.0f, 0.0f, 0.0f);
            glPushMatrix();
            glTranslatef(xOffset, yOffset, 0);
            glScalef(0.0015f, 0.0015f, 0.0015f);
            glTranslatef(-1.0f, -100.0f, 0);
            glutStrokeCharacter(GLUT_STROKE_ROMAN, cellContent);
            glPopMatrix();
        }
    }
}
}
    int getSize() const{
        return size;
    }
    char checkWinner(){
        auto checkLine = [&](int start, int step){
            char first = grid[start];
            if(first == ' ') return false;
            for (int row = 1; row < size; ++row){
                if (grid[start + row * step] != first) return false;
            }
            return true;
        };
        for (int column = 0; column < size; column++){
            if (checkLine(column * size, 1)) return (grid[column * size] == 'X') ? 'P' : 'C';
            if (checkLine(column, size)) return (grid[column] == 'X') ? 'P' : 'C';
        }
        if (checkLine(0, size + 1)) return (grid[0] == 'X') ? 'P' : 'C';
        if (checkLine(size - 1, size - 1)) return (grid[size - 1] == 'X') ? 'P' : 'C';
        bool gridFull = true;
        for (int i = 0; i < size * size; ++i){
            if (grid[i] == ' '){
                gridFull = false;
                break;
            }
        }
        if (gridFull) return 'T';
        return ' ';
    }
    void resetGrid(){
        for (int i = 0; i < size * size; ++i){
            grid[i] = ' ';
        }
    }

    ~TicTacToeGrid(){
        delete [] grid;
    }
};

#endif