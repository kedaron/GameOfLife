#include "GameOfLife.h"
#include <sstream>
#include <iostream>
#include <algorithm>

GameOfLife::GameOfLife() 
    : x_(0), y_(0), field_(nullptr)
{}

GameOfLife::~GameOfLife(){
    delete [] field_;
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

bool GameOfLife::saveField(std::string path) const {
    std::ofstream file(path);
    if(file.fail()){
        return false;
    }
    file << x_ << "," << y_ << std::endl;
    for(int y = 0; y < y_; y++){
        for(int x = 0; x < x_; x++)
            file << field_[y*x_ + x];
        if(y < y_-1)
            file << std::endl;
    }
    file.close();
    return true;
}

void GameOfLife::printField() const {
    std::cout << x_ << "," << y_ << std::endl;
    for(int y = 0; y < y_; y++){
        for(int x = 0; x < x_; x++)
            std::cout << field_[y*x_ + x];
        if(y < y_-1)
            std::cout << std::endl;
    }
}