#include <string>
#include <mutex>
#include <ncurses.h>

class Planet {

    std::string resource;       // rodzaj surowca przechowywany na planecie
    int x,y;                    // wspolrzedne planety
    float radius;               // promien rysowania planety
    std::string color;          // kolor rysowania planety

    public:

    Planet(std::string resource, std::string color, int x, int y, float radius);
    ~Planet()=default;

    std::mutex mine;            // kopalnia

    std::string get_name();    
    std::string get_resource();
    std::string get_color();
    int getX();
    int getY();
    float getRadius();
    void paint();               // rysowanie planety na ekranie
};