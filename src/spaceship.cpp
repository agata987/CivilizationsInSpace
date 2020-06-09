#include "include/spaceship.h"
#include <ctime>
#include <stdlib.h>

Spaceship::Spaceship(std::array<Planet,4> &planets, Earth &earth, int x, int y, bool *stop, int id) : planets{planets}, earth{earth},thread_(&Spaceship::fly,this){

    this->x=x;
    this->y=y;
    this->stop=stop;
    this->id=id;

    color="green";
}

Spaceship::~Spaceship() {
    if(thread_.joinable())
    thread_.join();
}

void Spaceship::fly() {

    destination = x%4;

    while(!*stop) {

        if(is_close) {

            if(x==planets[destination].getX())
            {
                if(id>0) {
                    for(int i=0;i<id;i++)
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        x++;
                    }
                } else
                    {
                        for(int i=0;i>id;i--)
                        {
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        x--;
                        }
                    }
                    
                
            } else {
                if(id>0) {
                    for(int i=0;i<id;i++)
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        y++;
                    }
                } else
                    {
                        for(int i=0;i>id;i--)
                        {
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        y--;
                        }
                    }
                    
                
            }

            std::unique_lock<std::mutex> lock_mine(planets[destination].mine);
      //      lock_mine.lock();

            while(x!=planets[destination].getX()||y!=planets[destination].getY()) 
                move_();

            std::this_thread::sleep_for(std::chrono::seconds(20));
            resource=planets[destination].get_resource();
            color=planets[destination].get_color();
            is_close=false;
            
        }
        else
        move_();

        if(color!="green"){
            go_to_earth();
        choose_destination();
        }
        
    }
}

void Spaceship::move_() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    int x_dis = x - planets[destination].getX();
    int y_dis = y - planets[destination].getY();

    if(!is_close)
    if(x_dis>-planets[destination].getRadius()-6 && x_dis<planets[destination].getRadius()+6&&
    y_dis>-planets[destination].getRadius()&& y_dis<planets[destination].getRadius()&&resource!=planets[destination].get_resource())
    is_close=true;
    

    if(x_dis>0)
    x--;
    else if(x_dis<0)
    x++;

    if(y_dis>0)
    y--;
    else if(y_dis<0)
    y++;    
}

void Spaceship::choose_destination() {
        
    // wybieranie celu podrozy
    while(planets[destination].get_resource()==resource)
    destination = rand()%4;
}

void Spaceship::paint() {
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_BLUE,COLOR_BLACK);
    init_pair(3,COLOR_GREEN,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLACK);
    init_pair(5,COLOR_WHITE,COLOR_BLACK);

    int pair=5;

    if(color=="red")
    pair=1;
    else if(color=="blue")
    pair=2;
    else if(color=="green")
    pair=3;
    else if(color=="yellow")
    pair=4;

    attron(COLOR_PAIR(pair));

    move(y,x-1);
    printw("|XX|");

    attroff(COLOR_PAIR(pair));
}

void Spaceship::go_to_earth() {

    int dist;
    if(color=="yellow"||color=="white")
    dist = earth.getRadius()+3;
    else
    {
        dist=-earth.getRadius()-3;
        
    }

    int y_dist=0;
    if(color=="red"||color=="yellow")
    y_dist=1;
    
     int x_dis = x - earth.getX()+dist;
    int y_dis = y - earth.getY()+id;

    while(x_dis!=0||y_dis!=0)
    {
        x_dis = x - earth.getX()+dist;
        y_dis = y - earth.getY()+id;

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        if(x_dis>0)
        x--;
        else if(x_dis<0)
        x++;


        if(y_dis>0)
        y--;
        else if(y_dis<0)
        y++;    
    }

    if(color=="yellow"||color=="white")
    {
        // std::unique_lock<std::mutex> lock_magazine(earth.gold_iron_mine_1,std::defer_lock);
        // lock_magazine.lock();
        earth.gold_iron_mine_1.lock();
    } else {
        // std::unique_lock<std::mutex> lock_magazine(earth.ore_diamond_mine_2,std::defer_lock);
        // lock_magazine.lock();
        earth.ore_diamond_mine_2.lock();
    }

    x_dis = x - earth.getX()+dist;
    y_dis = y - earth.getY()+y_dist;
     while(x_dis!=0||y_dis!=0)
    {
        x_dis = x - earth.getX()+dist;
        y_dis = y - earth.getY()+y_dist;

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        if(x_dis>0)
        x--;
        else if(x_dis<0)
        x++;


        if(y_dis>0)
        y--;
        else if(y_dis<0)
        y++;    
    }

    while(!earth.store(color))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    if(color=="yellow"||color=="white")
    {
        // std::unique_lock<std::mutex> lock_magazine(earth.gold_iron_mine_1,std::defer_lock);
        // lock_magazine.lock();
        earth.gold_iron_mine_1.unlock();
    } else {
        // std::unique_lock<std::mutex> lock_magazine(earth.ore_diamond_mine_2,std::defer_lock);
        // lock_magazine.lock();
        earth.ore_diamond_mine_2.unlock();
    }


    color="green";
    


}