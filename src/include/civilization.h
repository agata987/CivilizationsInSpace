#include <string>
#include <thread>
#include <cstdlib>
#include <ctime>

#include "earth.h"

class Civilization {

    public:

    Civilization(std::string color, Earth &earth, int x, int y, bool *stop);
    virtual ~Civilization();
    int state=0; // 0 -idle, 1-magazine1_gold, 2-magazine1_iron 3-magazine2_ore 4-magazine2_diamond 

    void paint();

    private: 
    bool took=false;

    std::string color;
    Earth &earth;
    std::thread thread_;
    bool *stop;

    int x,y;

    void live();
};