#include "Draw.h"


Draw::Draw(vector<image>& images, modo_t modo, Allegro& all)
{
	vectSize = images.size();
	this->modo = modo;
	this->font = all.getFont();
	for (int i = 0; i < vectSize; i++)
	{
		images[i].createBitmap(modo);	//inicializo los bitmaps de las imagenes.
	}
	exit = false;
	quit = false;
}


Draw::~Draw()
{
}


void Draw::updateDisplay()
{
	al_flip_display();
}


void Draw::drawPage(vector<image>& images)
{
	int i = (page * PAGE_SIZE);

	for (int j = 0; j < 3, i<images.size(); j++, i++)
	{
		for (int z = 0; z < 3, i<images.size(); z++, i++)
		{
			if (modo == COMPRESION)
			{
				al_draw_scaled_bitmap(images[i].getBitmap(), 0, 0, al_get_bitmap_width(images[i].getBitmap()), al_get_bitmap_height(images[i].getBitmap()),
					25 * (z + 1) + (z * 300), (75 / 4)*(j + 1) + (j * 175), 300, 175, 0);
			}
			if (images[i].getSelected())
			{
				al_draw_rectangle(25 * (z + 1) + (z * 300), (75 / 4)*(j + 1) + (j * 175),
					25 * (z + 1) + (z * 300) + ((z + 1) * 300), (75 / 4)*(j + 1) + (j * 175) + ((j + 1) * 175),
					al_map_rgb(0, 255, 0), 3);
			}
			else
			{
				al_draw_rectangle(25 * (z + 1) + (z * 300), (75 / 4)*(j + 1) + (j * 175),
					25 * (z + 1) + (z * 300) + ((z + 1) * 300), (75 / 4)*(j + 1) + (j * 175) + ((j + 1) * 175),
					al_map_rgb(0, 0, 0), 3);
			}
			al_draw_text(font, al_map_rgb(255, 255, 255), 25 * (z + 1) + (z * 300) + ((z + 1) * 300), (75 / 4)*(j + 1) + (j * 175) + ((j + 1) * 175),
				ALLEGRO_ALIGN_RIGHT, images[i].tell_me_your_name().c_str());
		}
	}
}

void Draw::nextPage()
{
	if(page < vectSize)
		page++;
}

void Draw::prevPage()
{
	if(page > vectSize)
		page--;
}

int Draw::getPage()
{
	return page;
}


void Draw::toggle(vector<image>& images, int n)
{
	images[n+(PAGE_SIZE*page)].toggleSelected();	//cambie de selection a selected
}

void Draw::toggleAll(vector<image>& images)
{
	for (int i = (page * PAGE_SIZE); (i < images.size()) && (i < ((page + 1)*PAGE_SIZE)); i++)
	{
		if (!(images[i].getSelected()))
		{
			images[i].toggleSelected();
		}
	}
}



void Draw::toggleNone(vector<image>& images)
{
	for (int i = (page * PAGE_SIZE); (i < images.size()) && (i < ((page + 1)*PAGE_SIZE)); i++)
	{
		if (images[i].getSelected())
		{
			images[i].toggleSelected();
		}
	}
}

bool Draw::getexit()
{
	return this->exit;
}

bool Draw::getquit()
{
	return this->quit;
}


void Draw::setexit(bool what)
{
	this->exit = what;
}

void Draw::setquit(bool what)
{
	this->quit = what; 
}

void Draw::exitScreen()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_filled_rectangle(SCREEN_W/4, SCREEN_H/4, 3*(SCREEN_W/4), 3 * (SCREEN_H / 4),
		al_map_rgb(0, 0, 255));
	al_draw_text(font, al_map_rgb(255, 255, 255),SCREEN_W/2 ,SCREEN_H/2 ,
		ALLEGRO_ALIGN_CENTER, "EL PROGRAMA TERMINO");

}

