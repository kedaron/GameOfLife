#include <string>
#include <fstream>
#include <functional>

class GameOfLife{
private:
    int x_, y_;
    char *field_;
    void parseSize(std::ifstream& file, std::string& line, int& x, int& y);
    void output(std::function<void(int, int)> func, std::function<void()> func2);
public:
    GameOfLife();
    ~GameOfLife();
    bool validateField(std::string path);
    bool loadField(std::string path);
    bool saveField(std::string path);
    void printField();
};