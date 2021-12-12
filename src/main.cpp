#include <iostream>
#include "ParameterReader.h"
#include "GameOfLife.h"
#include "Stopwatch.cpp"

GameOfLife g_gol;
ParameterReader g_reader;

int setup(){
    std::string path = g_reader["--load"];
    if(!g_gol.validateField(path) || !g_gol.loadField(path)){
        std::cout << "File '" << path << "' not found or invalid shape." << std::endl;
        return 0;
    }
    return 1;
}

int compute(){
    try{
        int gens = std::stoi(g_reader["--generations"]);
        g_gol.simulateGenerations(gens);
    }catch(std::exception&){
        std::cout << "Invalid value for generations." << std::endl;
        return 0;
    }
    return 1;
}

int finalize(){
    std::string path = g_reader["--save"];
    if(!g_gol.saveField(path)){
        std::cout << "Error while trying to save File '" << path << std::endl;
        return 0;
    }
    return 1;
}

int main(int argc, char** argv){
    Stopwatch sw;

    // define input parameters
    const int epCount = 3, opCount = 1;
    const char *ep[epCount] = {"--load", "--save", "--generations"};
    const char *op[opCount] = {"--measure"};
    g_reader.setExpectedParams(ep, epCount);
    g_reader.setOptionalParams(op, opCount);

    if(!g_reader.parseParams(argv, argc)){
        std::cout << "Invalid parameters..." << std::endl;
        g_reader.printExpectedParams();
        std::cout << "Please Use the following shape:" << std::endl;
        std::cout << "--load <param1> --save <param2> --generations <param3> --measure" << std::endl;
    }
    bool measure = !(g_reader.params.find("--measure") == g_reader.params.end());

    // gameoflife
    if(measure){
        std::string time;
        if(sw.measure(setup)) time += sw.elapsedTimeFormated() + ";";
        else return 0;

        if(sw.measure(compute)) time += sw.elapsedTimeFormated() + ";";
        else return 0;

        if(sw.measure(finalize)) time += sw.elapsedTimeFormated() + ";";
        else return 0;
        std::cout << time;
    }
    else{
        setup();
        compute();
        finalize();
    }

    return 0;
}