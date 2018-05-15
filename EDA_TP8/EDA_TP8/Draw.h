#pragma once

#include <vector>
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Image.h"
#include "Allegro.h"
#include"Parser.h"
#include "Parser.h"

#define PAGE_SIZE 9

class Draw
{
public:
	Draw(vector<image>& images, modo_t modo, Allegro& all);
	~Draw();
	void updateDisplay();
	void drawPage(vector<image>& images);
	void nextPage();
	void prevPage();
	int getPage();
	void toggle(vector<image>& images, int n);
	void toggleAll(vector<image>& images);
	void toggleNone(vector<image>& images);
	bool getexit();
	bool getquit();
	void setexit(bool what);
	void setquit(bool what);
	void exitScreen();

private:
	int modo;
	int page = 0;
	int vectSize;
	bool exit;
	bool quit;
	ALLEGRO_FONT * font;
	modo_t mode;
};