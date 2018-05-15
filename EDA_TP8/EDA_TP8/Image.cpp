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
	if(modo == COMPRESION)	//tengo o no que mostrar las imagenes
		my_image = al_load_bitmap(path.c_str());	//cargo bitmap de imagene
	//else		//AGREGAR QUE PASA SI ESTA EN DESCOMPRESION
		//my_image = al_load_bitmap(NOSE);
	if (my_image == NULL)	//Chequeo que haya cargado bien el bitmap
	{
		cout << "El bitmap del path " << path << " no se ha cargado correctamente" << endl;
	}
	

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

ALLEGRO_BITMAP * image::getBitmap()
{
	return my_image;
}