#include "GameOfLife.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

GameOfLife::GameOfLife() 
    : x_(0), y_(0), field_(nullptr)
{}

GameOfLife::~GameOfLife(){
    delete [] field_;
}

bool GameOfLife::validateField(std::string path) const {
    std::ifstream file(path);
    if(file.fail()){
        return false;
    }
    std::string line;
    std::getline(file, line);
    std::string delimiter = ",";
    int x = std::stoi(line.substr(0, line.find(delimiter)));
    int y = std::stoi(line.substr(line.find(delimiter) + 1, line.find('\n')));
    int row = 0;
    while(std::getline(file, line)){
        int len = line.length();
        if (len != x){
            file.close();
            return false;
        }
        row++;
    }
    return row == y;
}

bool GameOfLife::loadField(std::string path){
    std::ifstream file(path);
    if(file.fail()){
        return false;
    }
    std::string line;
    std::getline(file, line);
    std::string delimiter = ",";
    x_ = std::stoi(line.substr(0, line.find(delimiter)));
    y_ = std::stoi(line.substr(line.find(delimiter) + 1, line.find('\n')));
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