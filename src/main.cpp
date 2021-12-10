#include <iostream>
#include "ParameterReader.h"
#include "GameOfLife.h"

int main(int argc, char** argv){
    ParameterReader reader;

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
    return 0;
}