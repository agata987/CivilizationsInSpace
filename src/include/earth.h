#include <string>
#include <ncurses.h>
#include <mutex>

class Earth {

    int x,y; 
    float radius;
    std::string name="ZIEMIA";

    void paint_magazine(int id,int x, int y);
    int storage_1_gold=0;
    int storage_1_iron=0;
    int storage_2_ore=0;
    int storage_2_diamond=0;
    int max=5;

    int magazine1X;
    int magazine1Y;
    int magazine2X;
    int magazine2Y;

    public:

    Earth(int x, int y, float radius);
    ~Earth()=default;

    void paint();
    int getX();
    int getY();
    int getRadius();
    int get_magazine1X();
    int get_magazine1Y();
    int get_magazine2X();
    int get_magazine2Y();

    std::mutex gold_iron_mine_1;
    std::mutex ore_diamond_mine_2;

    bool store(std::string color);
    bool get(std::string color);
};