#include "include/planet.h"

Planet::Planet(std::string resource, std::string color, int x, int y, float radius) {
    this->resource=resource;
    this->color=color;
    this->x=x;
    this->y=y;

    if(radius>=8)
    this->radius=radius;
    else
    this->radius=8;
}

std::string Planet::get_resource() {
    return resource;
}

std::string Planet::get_color() {
    return color;
}

int Planet::getX() {
    return x;
}

int Planet::getY() {
    return y;
}

float Planet::getRadius() {
    return radius;
}

void Planet::paint() {

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

        int name_length = resource.length();
        name_length /=2;
        move(y-2,x-name_length);
        printw(resource.c_str());

        move(y,x);
        printw("x");

        move(0,0);

    attroff(COLOR_PAIR(pair));
}