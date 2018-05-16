#pragma once
#include <iostream>
#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

#include"Parser.h"

using namespace std;

class image {
public:
	image();
	image(string path, string name);
	~image();
	void createBitmap(modo_t modo);	//Depende de allegro
	bool getSelected();
	void toggleSelected();
	string tell_me_your_name();
	string tell_me_your_path();
	ALLEGRO_BITMAP * getBitmap();
private:
	string path;
	string name;
	bool selected;
	ALLEGRO_BITMAP *  my_image;
};	
