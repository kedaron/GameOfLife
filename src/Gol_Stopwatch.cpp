#ifndef GOLSTOPWATCH
#define GOLSTOPWATCH

#include "Stopwatch.cpp"
#include "GameOfLife.h"
#include "ParameterReader.h"

class Gol_Stopwatch : public Stopwatch{
private:
    GameOfLife* gol_;
    ParameterReader* reader_;
public:
    Gol_Stopwatch(GameOfLife* gol, ParameterReader* reader) :
        gol_(gol), reader_(reader)    
    {}
    int measure(int (*func)(GameOfLife*, ParameterReader*)) {
        start();
        int success = func(gol_, reader_);
        stop();

        return success;
    }
};

#endif