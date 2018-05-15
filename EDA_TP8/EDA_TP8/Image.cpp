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

void image::createBitmap(modo_t modo)
{
	my_image = NULL;
	
	if (modo == COMPRESION)	//tengo o no que mostrar las imagenes
	{
		const char * hola = path.c_str();
		my_image = al_load_bitmap(hola);	//cargo bitmap de imagene
		if (my_image == NULL)	//Chequeo que haya cargado bien el bitmap
		{
			cout << "El bitmap del path " << path << " no se ha cargado correctamente" << endl;
		}
	}
	else		//si se esta en modo descompresion
		my_image = NULL;
	
	

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