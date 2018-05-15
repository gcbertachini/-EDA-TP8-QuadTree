#include "modeSelector.h"





modeSelector::modeSelector()
{
	quit = false;
}


modeSelector::~modeSelector()
{
}

modo_t modeSelector::modeSelect(ALLEGRO_EVENT_QUEUE* ev_que, ALLEGRO_FONT * font)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_filled_rectangle(SCREEN_W / 8, SCREEN_H / 8, 7 * (SCREEN_W / 8), 3 * (SCREEN_H / 8),
		al_map_rgb(0, 0, 255));

	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, 2 * (SCREEN_H / 8),
		ALLEGRO_ALIGN_CENTER, "Seleccione Modo");
	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, (SCREEN_H / 2),
		ALLEGRO_ALIGN_CENTER, "COMPRESION = C     DESCOMPRESION = D");

	al_flip_display();

	bool exit_loop = false;

	modo_t respuesta = COMPRESION;
	ALLEGRO_EVENT ev;

	while (!exit_loop)
	{
		al_get_next_event(ev_que, &ev);

		switch (ev.type)
		{

		case ALLEGRO_EVENT_KEY_UP:
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_D:
				respuesta = DESCOMPRESION;
				exit_loop = true;
				quit = false;
				break;
			case ALLEGRO_KEY_C:
				respuesta = COMPRESION;
				exit_loop = true;
				quit = false;
				break;
			}
			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			this->quit = true;
			exit_loop = true;
			break;
		}


	}
	return respuesta;

}

bool modeSelector::getQuit()
{
	return quit;
}