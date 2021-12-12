#include "GameOfLife.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cstring>


GameOfLife::GameOfLife() 
    : x_(0), y_(0), fieldSize_(0), field_(nullptr)
{}

GameOfLife::~GameOfLife(){
    delete [] field_;
}

int GameOfLife::pmod(int i, int n){
    return (i % n + n) % n;
}

int GameOfLife::checkSurroundings(char *const field, const int index, const char checkChar){
    int count = 0;

    //left/right
    if(index%x_ == 0){
        if(field[index+x_-1] == checkChar)
            count++;
        if(field[(index+1)] == checkChar)
            count++;
    }
    else if(index%x_ == x_-1){
        if(field[index-x_+1] == checkChar)
            count++;
        if(field[(index-1)] == checkChar)
            count++;
    }
    else{
        if(field[(index-1)] == checkChar)
            count++;
        if(field[(index+1)] == checkChar)
            count++;
    }
    //top row
    if(field[pmod(index-x_, fieldSize_)] == checkChar)
        count++;
    if(field[pmod(index-x_-1, fieldSize_)] == checkChar)
        count++;
    if(field[pmod(index-x_+1, fieldSize_)] == checkChar)
        count++;

    //bottom row
    if(field[pmod(index+x_, fieldSize_)] == checkChar)
        count++;
    if(field[pmod(index+x_-1, fieldSize_)] == checkChar)
        count++;
    if(field[pmod(index+x_+1, fieldSize_)] == checkChar)
        count++;

    return count;
}

void GameOfLife::simulateGenerations(int gens){
    char* snapshot = new char[fieldSize_];
    for(int gen = 0; gen < gens; gen++){
        for(int i = 0; i < fieldSize_; i++)
            snapshot[i] = field_[i];

        for(int y = 0; y < y_; y++){
            for(int x = 0; x < x_; x++){
                const int i = y*x_ + x;
                // Rule 1
                if(snapshot[i] == '.'){
                    if(checkSurroundings(snapshot, i, 'x') == 3)
                        field_[i] = 'x';
                }
                
                // Rule 2-4
                else if(snapshot[i] == 'x' ){
                    int s = checkSurroundings(snapshot, i, 'x');
                    if(s < 2 || s > 3)
                        field_[i] = '.';
                }
            }
        }
    }
    delete [] snapshot;
}

void GameOfLife::parseSize(std::ifstream& file, std::string& line, int& x, int& y){
    std::getline(file, line);
    std::string delimiter = ",";
    x = std::stoi(line.substr(0, line.find(delimiter)));
    y = std::stoi(line.substr(line.find(delimiter) + 1, line.find('\n')));
}

bool GameOfLife::validateField(std::string path) {
    std::ifstream file(path);
    if(file.fail()){
        return false;
    }
    std::string line;
    int x, y;
    parseSize(file, line, x, y);
    int row = 0;
    while(std::getline(file, line)){
        int len = line.length();
        if (len != x){
            file.close();
            return false;
        }
        row++;
    }
    file.close();
    return row == y;
}

bool GameOfLife::loadField(std::string path){
    std::ifstream file(path);
    if(file.fail()){
        return false;
    }
    std::string line;
    parseSize(file, line, x_, y_);
    fieldSize_ = x_*y_;
    field_ = new char[x_*y_];

    int row = 0;
    while(std::getline(file, line)){
        int len = line.length();
        for(int i = 0; i < len; i++)
            field_[row*x_ + i] = line[i];
        row++;
    }
    file.close();
    return true;
}

void GameOfLife::output(std::streambuf* buf){
    std::ostream out(buf);
    out << x_ << "," << y_ << std::endl;
    for(int y = 0; y < y_; y++){
        for(int x = 0; x < x_; x++)
            out << field_[y*x_ + x];
        if(y < y_-1)
            out << std::endl;
    }
}

bool GameOfLife::saveField(std::string path) {
    std::ofstream file(path);
    if(file.fail()){
        return false;
    }
    output(file.rdbuf());
    file.close();
    return true;
}

void GameOfLife::printField() {
    output(std::cout.rdbuf());
}