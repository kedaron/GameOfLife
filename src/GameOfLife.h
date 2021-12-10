#include <string>

class GameOfLife{
private:
    int x_, y_;
    char *field_;
    bool validateField();
public:
    GameOfLife();
    ~GameOfLife();
    bool loadField(std::string path);
    bool saveField(std::string path) const;
    void printField() const;
};