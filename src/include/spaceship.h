#include "planet.h"
#include <thread>
#include "civilization.h"

class Spaceship {
    
    public:

    Spaceship(std::array<Planet,4> &planets, Earth &earth, int x, int y, bool *stop, int id);
    virtual ~Spaceship();

    void paint();

    private:
    int id;
    bool *stop;
    std::array<Planet,4> &planets;
    Earth &earth;
    int x,y;
    std::string resource;
    std::string color;
    bool is_close=false;        // jest na orbicie

    int destination;

    std::thread thread_;
    void fly();
    void move_();
    void choose_destination();
    void go_to_earth();
};