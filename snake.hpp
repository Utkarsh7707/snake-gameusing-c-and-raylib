#include<raylib.h>
#include<deque>
using namespace std;
class Snake
{
    public:
    deque<Vector2> body;
    Vector2 direction;
    bool snakeAddSegment;
    Snake();
    void update();
    void Draw();
    void gameOver();
    bool runing = true;
    private:

};