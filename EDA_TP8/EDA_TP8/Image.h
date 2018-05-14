#pragma once
#include <iostream>
#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>


using namespace std;

class image {
public:
	image();
	image(string path, string name);
	~image();
	void createBitmap(int modo);	//Depende de allegro
	bool getSelected();
	void toggleSelected();
private:
	string path;
	string name;
	bool selected;
	ALLEGRO_BITMAP *  my_image;
};	
