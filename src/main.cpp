#include <iostream>
#include "ParameterReader.h"
#include "GameOfLife.h"
#include "Stopwatch.cpp"

int main(int argc, char** argv){
    // TODO: measure time; [] overloading in parameterreader
    ParameterReader reader;
    GameOfLife gol;
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
    // setup
    if(measure) sw.start();
    std::string path = reader.params["--load"].c_str();
    if(!gol.validateField(path) || !gol.loadField(path)){
        std::cout << "File '" << reader.params["--load"] << "' not found or invalid shape." << std::endl;
        return 0;
    }
    if(measure) {
        sw.stop();
        std::cout << sw.elapsedTimeFormated() << ";";
    }

    // computation
    if(measure) sw.start();
    int gens = std::stoi(reader.params["--generations"]);
    gol.simulateGenerations(gens);
    if(measure) {
        sw.stop();
        std::cout << sw.elapsedTimeFormated() << ";";
    }

    // finalization
    if(measure) sw.start();
    if(!gol.saveField(reader.params["--save"])){
        std::cout << "Error while trying to save File '" << reader.params["--save"] << std::endl;
        return 0;
    }
    if(measure) {
        sw.stop();
        std::cout << sw.elapsedTimeFormated() << std::endl;
    }

    //gol.printField();
    return 0;
}