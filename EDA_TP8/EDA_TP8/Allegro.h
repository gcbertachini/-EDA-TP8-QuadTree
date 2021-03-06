#pragma once

#include <allegro5/allegro5.h> 
#include <allegro5/allegro_color.h> 
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define SCREEN_W 1000
#define SCREEN_H 600
#define PROCESSING "processing.png"
#define BACKGROUND "background.jpg"


class Allegro
{
public:
	Allegro();
	~Allegro();
	ALLEGRO_EVENT_QUEUE * getEventQueue();
	bool load_music(char * music_file);
	ALLEGRO_FONT* getFont();
	ALLEGRO_BITMAP * give_me_my_background();
	ALLEGRO_BITMAP * give_me_my_backgroundbis();

	

private:
	ALLEGRO_DISPLAY * display = NULL;
	ALLEGRO_EVENT_QUEUE * ev_queue = NULL;
	ALLEGRO_BITMAP * processing = NULL;
	ALLEGRO_BITMAP * background = NULL;
	ALLEGRO_SAMPLE * music = NULL;
	ALLEGRO_FONT * font = NULL;
};

