class GameOfLife{
private:
    int x_, y_;
    char *field_;
public:
    GameOfLife();
    ~GameOfLife();
    void loadField();
    void saveField();
    void printField();
};