#include <iostream>

int main(int argc, char** argv){
    std::cout << (argc > 1 ? argv[1] : "Hello World") << std::endl;
    return 0;
}