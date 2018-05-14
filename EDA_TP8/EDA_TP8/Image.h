#pragma once
#include <iostream>
#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>


using namespace std;

class image {
	image();
	image(string path, string name);
	void createBitmap(int modo);	//Depende de allegro

private:
	string path;
	string name;
	bool selected;
	ALLEGRO_BITMAP *  my_image;
};	
