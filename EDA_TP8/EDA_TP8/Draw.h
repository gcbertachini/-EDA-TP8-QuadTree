#pragma once

#include <vector>
#include <allegro5/allegro_primitives.h> 

#include "Image.h"
#include"Parser.h"

#define PAGE_SIZE 9

class Draw
{
public:
	Draw(vector<image>& images, int modo);
	~Draw();
	void updateDisplay();
	void drawPage(vector<image>& images);
	void nextPage();
	void prevPage();
	int getPage();
	void toggle(vector<image>& images, int n);
	void toggleAll(vector<image>& images);
	void toggleNone(vector<image>& images);

private:
	int modo;
	int page = 0;
	int vectSize;
};