#ifndef STOPWATCH
#define STOPWATCH

#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
#include <functional>
#include "GameOfLife.h"
#include "ParameterReader.h"

class Stopwatch{
private:
    decltype(std::chrono::high_resolution_clock::now()) start_, stop_;
public:

    void start(){
        start_ = std::chrono::high_resolution_clock::now();
    }
    void stop(){
        stop_ = std::chrono::high_resolution_clock::now();
    }
    long elapsedTimeMs() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(stop_ - start_).count();
    }
    std::string elapsedTimeFormated() const{
        long time = elapsedTimeMs();
        int ms = time%1000;
        int sec = (time%60000)/1000;
        int min = time/60000;
        std::stringstream buff;

        buff << std::setfill('0') << std::setw(2) << min;
        buff << ':' << std::setfill('0') << std::setw(2) << sec;
        buff << '.' << std::setfill('0') << std::setw(3) << ms;

        return buff.str();
    }
    int measure(std::function<int(GameOfLife*, ParameterReader*)> func, GameOfLife* gol, ParameterReader* reader) {
        start();
        int success = func(gol, reader);
        stop();

        return success;
    }
};

#endif