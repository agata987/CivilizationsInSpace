#include "include/spaceship.h"

int main() {

	initscr();
	start_color();
	curs_set(0);

	if(!has_colors())
	{
		move(2,3);
		printw("Terminal does not support color");
		getch();
		return -1;
	}

	bool *stop = new bool(false);

	// moze powinine byc wskaznik na mutexy? XDD

	std::array<Planet,4> plantes =
	{{
		{"ZLOTO","yellow",20,16,8},
		{"DIAMENTY","blue",45,44,8},
		{"ZELAZO","white",114,30,8},
		{"RUDA","red",87,5,8},
	}};

	Earth earth(64,24,14);

	std::array<Spaceship,7> ships = 
	{{
		{plantes,earth,10,10,stop,-3},
		{plantes,earth,20,20,stop,-2},
		{plantes,earth,30,30,stop,-1},
		{plantes,earth,40,40,stop,0},
		{plantes,earth,50,10,stop,1},
		{plantes,earth,60,20,stop,2},
		{plantes,earth,70,30,stop,3},
	}};

	std::array<Civilization,3> civilizations = 
	{{
		{"magneta",earth,1,-3,stop},
		{"cyan",earth,-4,4,stop},
		{"white",earth,5,4,stop},
	}};

	while(true) {
		erase();

		// rysujemy planety
		for(int i=0;i<4;i++)
		plantes[i].paint();

		earth.paint();

		//rysowanie cywilizacji
		for(int i=0;i<3;i++)
		civilizations[i].paint();

		// rysowanie statkow
		for(int i=0;i<7;i++)
		ships[i].paint();


		refresh();
	}

	return 0;
}