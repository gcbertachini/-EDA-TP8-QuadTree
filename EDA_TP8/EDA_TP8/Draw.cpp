#include "Draw.h"


Draw::Draw(vector<image>& images)
{
	vectSize = images.size();
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
	for (int i = (page * PAGE_SIZE); i < images.size(); i++)
	{
		al_draw_scaled_bitmap(images[i].getBitmap(), 0, 0, al_get_bitmap_width(images[i].getBitmap()), al_get_bitmap_height(images[i].getBitmap()),
			25*(i+1)+(i*300), (75/4)*(i+1)+(i*175), 300, 175, 0);
		if (images.getSelected())
		{
			al_draw_rectangle(25*(i+1)+(i*300), (75/4)*(i+1)+(i*175), 25*(i+1)+(i*300)+((i+1)*300), (75/4)*(i+1)+(i*175)+((i+1)*175),
				al_map_rgb(0, 255, 0), 3);
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
	images[n+(PAGE_SIZE*page)].toggleSelection();
}