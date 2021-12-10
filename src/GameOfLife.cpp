#include "GameOfLife.h"

GameOfLife::GameOfLife() 
    : x_(0), y_(0), field_(nullptr)
{}

GameOfLife::~GameOfLife(){
    delete [] field_;
}