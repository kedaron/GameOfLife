#include <string>
#include <fstream>

class GameOfLife{
private:
    int x_, y_, fieldSize_;
    char *field_;
    void parseSize(std::ifstream& file, std::string& line, int& x, int& y);
    void output(std::streambuf* buf);
    int checkSurroundings(char *const field, const int index, const char checkChar);
    int pmod(int i, int j);
public:
    GameOfLife();
    ~GameOfLife();
    void simulateGenerations(int gens);
    bool validateField(std::string path);
    bool loadField(std::string path);
    bool saveField(std::string path);
    void printField();
};