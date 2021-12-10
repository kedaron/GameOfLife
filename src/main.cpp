#include <iostream>
#include "ParameterReader.h"
#include "GameOfLife.h"

int main(int argc, char** argv){
    ParameterReader reader;
    GameOfLife gol;

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

    // gameoflife
    if(!gol.loadField(reader.params["--load"].c_str())){
        std::cout << "File '" << reader.params["--load"] << "' not found or invalid shape." << std::endl;
        return 0;
    }

    if(!gol.saveField(reader.params["--save"])){
        std::cout << "Error while trying to save File '" << reader.params["--save"] << std::endl;
        return 0;
    }

    gol.printField();
    return 0;
}