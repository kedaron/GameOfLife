#include <string>

class GameOfLife{
private:
    int x_, y_;
    char *field_;
    void parseSize();
public:
    GameOfLife();
    ~GameOfLife();
    bool validateField(std::string path) const;
    bool loadField(std::string path);
    bool saveField(std::string path) const;
    void printField() const;
};