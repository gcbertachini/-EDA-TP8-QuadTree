#include "Image.h"

image::image()
{

}

image::image(string path, string name)
{
	this->path = path;
	this->name = name;
	this->selected = false;
}

image::~image()
{

}

void image::createBitmap(int modo)
{
	my_image = al_create_bitmap(10,10);
}

bool image::getSelected()
{
	return selected;
}

void image::toggleSelected()
{
	bool aux = !(this->selected);
	this->selected = aux;
}
string image::tell_me_your_name() {

	return this->name;
}