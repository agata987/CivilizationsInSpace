#include "include/civilization.h"

Civilization::Civilization(std::string color, Earth &earth, int x, int y, bool *stop) : earth{earth}, thread_{&Civilization::live,this} {
    this->color=color;
    this->x=x;
    this->y=y;
    this->stop=stop;
}

Civilization::~Civilization() {
    if(thread_.joinable())
    thread_.join();
}

void Civilization::paint() {

/*
        ||
       ||||
*/  
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_BLUE,COLOR_BLACK);
    init_pair(3,COLOR_GREEN,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLACK);
    init_pair(5,COLOR_WHITE,COLOR_BLACK);
    init_pair(6,COLOR_CYAN,COLOR_BLACK);
    init_pair(7,COLOR_MAGENTA,COLOR_BLACK);

    int pair=6;

    // if(color=="cyan")
    // pair=6;
    // else if(color=="magneta")
    // pair=7;

    attron(COLOR_PAIR(pair));

    move(earth.getY()+y,earth.getX()+x-2);
    printw("||||");
    move(earth.getY()+y-1,earth.getX()+x-1);
    printw("||");

    attroff(COLOR_PAIR(pair));

    std::string state_s;
    int state_col;
    if(state ==1 && took)
    {
        state_s="zloto_m1";
        state_col=4;
    }
    else if(state ==2 && took)
    {
        state_s="zelazo_m1";
        state_col=5;
    }
    else if(state==3 && took)
    {
        state_s="ruda_m2";
        state_col=1;
    }
    else if(state==4 && took)
    {
        state_s="diament_m2";
        state_col=2;
    } else {
         state_s="";
         state_col=6;
    }   


    attron(COLOR_PAIR(state_col));
    int l=state_s.length()/2;
    if(y<0)
    {
        move(earth.getY()+y-3,earth.getX()+x-l);
    }
    else{
         move(earth.getY()+y+2,earth.getX()+x-1-l);
         if(x>0)
         move(earth.getY()+y+2,earth.getX()+x+1-l);
    }
    
    printw(state_s.c_str());
    
    attroff(COLOR_PAIR(state_col));

    

}

void Civilization::live() {

    srand(time(NULL));

    int wait = x%3;
    if(x%2==0)
    wait++;
    std::this_thread::sleep_for(std::chrono::seconds(wait));

    while(!*stop){
        

        std::this_thread::sleep_for(std::chrono::seconds(5));
        state=rand()%5;
        took=false; // czy udalo sie cos pobrac z magazynu

        if(state==1 || state==2)    // blokujemy pierwszy magazyn
        {
        std::unique_lock<std::mutex> lock_magazine(earth.gold_iron_mine_1,std::defer_lock);
        lock_magazine.lock();

        std::string color_;
        if(state==1)
        color="yellow";
        else
        color="white";
        
        if(earth.get(color))
        {
            took=true;      // pokazujemt jak tylko cos udalo sie zabrac, nie mozemy blokowac caly czas pustego magazynu
                            // bo statki nie beda mialy jak dostarczyc zasobow
        }

   

        } else if(state==3 || state ==4){ // blokujemy drugi magazyn
        std::unique_lock<std::mutex> lock_magazine(earth.ore_diamond_mine_2,std::defer_lock);
        lock_magazine.lock();

        std::string color_;
        if(state==3)
        color="red";
        else
        color="blue";

        if(earth.get(color))
        {
            took=true;
        }

        }


    }

}