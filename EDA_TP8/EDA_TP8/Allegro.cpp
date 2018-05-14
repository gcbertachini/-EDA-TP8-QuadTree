#include "Allegro.h"
#include <iostream>

using namespace std;
Allegro::Allegro()
{
	if (al_init())
{
		if (al_init_primitives_addon())
		{
			if (al_install_audio())
			{
				if (al_init_acodec_addon())
				{
					if ((al_reserve_samples(1)))
					{
						if (al_init_image_addon())
						{
							if (al_install_keyboard())
							{
								if ((ev_queue = al_create_event_queue()))
								{
									if ((display = al_create_display(SCREEN_W, SCREEN_H)))
									{
										al_register_event_source(this->ev_queue, al_get_keyboard_event_source());
										al_register_event_source(this->ev_queue, al_get_display_event_source(this->display));
									}
								}
							}
						}
						else
						{
							fprintf(stderr, "ERROR: Failed to load primitives addon\n");
							al_shutdown_primitives_addon();
						}
					}
					else
						fprintf(stderr, "ERROR: Failed to reserve sample\n");
				}
				else
					fprintf(stderr, "ERROR: Failed to install acodec addon\n");
			}
			else
				fprintf(stderr, "ERROR: Failed to install audio\n");
		}
		else
		{
			fprintf(stderr, "ERROR: Failed to install keyboard\n");
			al_uninstall_system();
		}
	}
	else
		fprintf(stderr, "ERROR: Failed to initialize allegro system\n");
}


Allegro::~Allegro()
{
	al_destroy_display(display);
	al_destroy_event_queue(ev_queue);
	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
	al_uninstall_audio();
}


bool Allegro::load_music(char * music_file) //Devuelve 1 si todo salio bien
{
	bool result;
	if ((music = al_load_sample(music_file)))
		result = true;
	else
		result = false;
	return result;

}


ALLEGRO_EVENT_QUEUE * Allegro::getEventQueue()
{
	return ev_queue;
}