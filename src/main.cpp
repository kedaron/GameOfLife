#include <iostream>
#include "ParameterReader.h"
#include "GameOfLife.h"
#include "Stopwatch.cpp"

int setup(GameOfLife* gol, ParameterReader* reader){
    std::string path = reader->params["--load"];
    if(!gol->validateField(path) || !gol->loadField(path)){
        std::cout << "File '" << path << "' not found or invalid shape." << std::endl;
        return 0;
    }
    return 1;
}

int compute(GameOfLife* gol, ParameterReader* reader){
    try{
        int gens = std::stoi(reader->params["--generations"]);
        gol->simulateGenerations(gens);
    }catch(std::exception& e){
        std::cout << "Invalid value for generations." << std::endl;
        return 0;
    }
    return 1;
}

int finalize(GameOfLife* gol, ParameterReader* reader){
    std::string path = reader->params["--save"];
    if(!gol->saveField(path)){
        std::cout << "Error while trying to save File '" << path << std::endl;
        return 0;
    }
    return 1;
}

int main(int argc, char** argv){
    // TODO: [] overloading in parameterreader
    GameOfLife gol;
    ParameterReader reader;
    Stopwatch sw;

    // define input parameters
    const int epCount = 3, opCount = 1;
    const char *ep[epCount] = {"--load", "--save", "--generations"};
    const char *op[opCount] = {"--measure"};
    reader.setExpectedParams(ep, epCount);
    reader.setOptionalParams(op, opCount);

    if(!reader.parseParams(argv, argc)){
        std::cout << "Invalid parameters..." << std::endl;
        reader.printExpectedParams();
        std::cout << "Please Use the following shape:" << std::endl;
        std::cout << "--load <param1> --save <param2> --generations <param3> --measure" << std::endl;
    }
    bool measure = !(reader.params.find("--measure") == reader.params.end());

    // gameoflife
    if(measure){
        std::string time;
        if(sw.measure(setup, &gol, &reader)) time += sw.elapsedTimeFormated() + ";";
        else return 0;

        if(sw.measure(compute, &gol, &reader)) time += sw.elapsedTimeFormated() + ";";
        else return 0;

        if(sw.measure(finalize, &gol, &reader)) time += sw.elapsedTimeFormated() + ";";
        else return 0;
        std::cout << time;
    }
    else{
        setup(&gol, &reader);
        compute(&gol, &reader);
        finalize(&gol, &reader);
    }

    return 0;
}