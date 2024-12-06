#include<raylib.h>

class Food{
    public:
    Food();
    ~Food();
    Vector2 position;
    void Draw();
    Vector2 GetFoodPos();
    private:
    Texture2D image;
};