#ifndef CANVAS_H
#define CANVAS_H

#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <iostream>
#include "TicTacToeGrid.h"
#include "GameOutcome.h"
#include "GameState.h"

class Canvas{
private:
    TicTacToeGrid* grid;
    char currentPlayer;
    bool againstAI;
    GameState state;
public:
    Canvas(int size, bool vsAI) : currentPlayer('X'), againstAI(vsAI), grid(new TicTacToeGrid(size)){
        //
    }
    void draw(){
        if(grid){
            grid->draw();
        }
    }
    void handleMouseClick(float mx, float my){
        int size = grid->getSize();
        int row = (1.0f - my) * size / 2.0f;
        int column = (1.0f + mx) * size / 2.0f;
        if (row >= 0 && row < size && column >= 0 && column < size){
            if (grid->makeMove(row, column, currentPlayer)){
                if (grid->checkWinner() == ' '){
                    switchPlayer();
                    if (againstAI && currentPlayer == 'O'){
                        makeAIMove();
                    }
                }
            }
        }
    }
    void makeAIMove(){
        int size = grid->getSize();
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                if (grid->makeMove(i, j, 'O')){
                    currentPlayer = 'X';
                    return;
                }
            }
        }
    }
    void switchToPlayerX(){
        currentPlayer = 'X';
    }
    void switchPlayer(){
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    char getGameStatus(){
        return grid->checkWinner();
    }
    void resetGame(){
        if (grid){
            grid->resetGrid();
        }
        resetCurrentPlayer();
    }
    void resetCurrentPlayer(){
        currentPlayer = 'X';
    }
    ~Canvas(){
        if (grid != nullptr){
            delete grid;
        }
    }
};

#endif