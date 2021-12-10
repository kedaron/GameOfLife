#include <string>
#include <fstream>

class GameOfLife{
private:
    int x_, y_;
    char *field_;
    void parseSize(std::ifstream& file, std::string& line, int& x, int& y);
    void output(std::streambuf* buf);
public:
    GameOfLife();
    ~GameOfLife();
    bool validateField(std::string path);
    bool loadField(std::string path);
    bool saveField(std::string path);
    void printField();
};