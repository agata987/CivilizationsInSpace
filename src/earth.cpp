#include "include/earth.h"

Earth::Earth(int x, int y, float radius=9) {
    this->x=x;
    this->y=y;
    
    if(radius>8)
    this->radius=radius;

    magazine1X=x-12;
    magazine1Y=y-1;

    magazine2X=x+5;
    magazine2Y=y-1;
}

int Earth::getX(){
    return x;
}

int Earth::getY() {
    return y;
}

void Earth::paint() {
           
    init_pair(3,COLOR_GREEN,COLOR_BLACK);


        attron(COLOR_PAIR(3));

        int x_=x-radius;
        int y_=y-radius;

        float k;
        float m = 2;

        for (int i = -radius; i <= radius; i++)
        {
            for (int j = -radius; j <= radius; j++)
            {
                k = ((i*m)/radius)*((i*m)/radius) + (j/radius)*(j/radius);

                if (k >0.95 && k<1.08)
                {
                    move(y_,x_);
                    printw("*");
                    x_++;
                }
                else
                {
                    move(y_,x_);
                    printw(" ");
                    x_++;
                }
            }
                y_++;
                x_=x-radius;
        }

        move(y-1,x-2);
        printw(name.c_str());

        move(y,x);
        printw("x");

        move(0,0);

    attroff(COLOR_PAIR(3));

    paint_magazine(1,12,-1);
    paint_magazine(2,5,-1);
}

/* 
    [ ||||| ]
    [ ||||| ]
*/

void Earth::paint_magazine(int id, int x, int y) {
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_BLUE,COLOR_BLACK);
    init_pair(3,COLOR_GREEN,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLACK);
    init_pair(5,COLOR_WHITE,COLOR_BLACK);

    if (id==1) {

        // gold
        move(this->y+y,this->x-x);

        attron(COLOR_PAIR(4));

        printw("[ ");

        for(int i=0;i<storage_1_gold;i++)
        {
            move(this->y+y,this->x-x+2+i);
            printw("*");
        }

        move(this->y+y,this->x-x+7);
        printw(" ]");

        attroff(COLOR_PAIR(4));

        //iron

        move(this->y+y+1,this->x-x);

        attron(COLOR_PAIR(5));

        printw("[ ");

        for(int i=0;i<storage_1_iron;i++)
        {
            move(this->y+y+1,this->x-x+2+i);
            printw("*");
        }

        move(this->y+y+1,this->x-x+7);
        printw(" ]");

        attroff(COLOR_PAIR(5));
    } else {
        // ore
        move(this->y+y,this->x+x);

        attron(COLOR_PAIR(1));

        printw("[ ");

        for(int i=0;i<storage_2_ore;i++)
        {
            move(this->y+y,this->x+x+2+i);
            printw("*");
        }

        move(this->y+y,this->x+x+7);
        printw(" ]");

        attroff(COLOR_PAIR(1));

        //diamond

        move(this->y+y+1,this->x+x);

        attron(COLOR_PAIR(2));

        printw("[ ");

        for(int i=0;i<storage_2_diamond;i++)
        {
            move(this->y+y+1,this->x+x+2+i);
            printw("*");
        }

        move(this->y+y+1,this->x+x+7);
        printw(" ]");

        attroff(COLOR_PAIR(2));
    }

}

bool Earth::store(std::string color) {
    if( color == "red" )
    {   if( storage_2_ore == max )
        return false;
        else {
            storage_2_ore++;
            return true;
        } 
    }else if(color == "blue")
    {   if( storage_2_diamond == max )
        return false;
        else {
            storage_2_diamond++;
            return true;
        } 
    } else if( color == "white" )
    {
        if( storage_1_iron == max )
        return false;
        else {
            storage_1_iron++;
            return true;
        } 
    }else
    {
        if( storage_1_gold == max )
        return false;
        else {
            storage_1_gold++;
            return true;
        } 
    }
}

bool Earth::get(std::string color) {
    if(color == "red")
    {
        if(storage_2_ore == 0)
        return false;
        else {
            storage_2_ore--;
            return true;
        }
    } else if (color == "blue") {
        if(storage_2_diamond == 0)
        return false;
        else {
            storage_2_diamond--;
            return true;
        }
    } else if (color == "white") {
        if (storage_1_iron == 0)
        return false;
        else {
            storage_1_iron--;
            return true;
        }
    } else {
        if(storage_1_gold == 0)
        return false;
        else {
            storage_1_gold--;
            return true;
        }
    }
}

int Earth::get_magazine1X(){
    return magazine1X;
}

int Earth::get_magazine1Y(){
    return magazine1Y;
}

int Earth::get_magazine2X(){
    return magazine2X;
}

int Earth::get_magazine2Y() {
    return magazine2Y;
}

int Earth::getRadius() {
    return radius;
}