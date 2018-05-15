#pragma once
#include "Parser.h"
#include"Allegro.h"

class modeSelector
{
public:
	modeSelector();
	modo_t modeSelect(ALLEGRO_EVENT_QUEUE* ev_que, ALLEGRO_FONT * font);
	~modeSelector();
	bool getQuit();
private:
	bool quit;
};

