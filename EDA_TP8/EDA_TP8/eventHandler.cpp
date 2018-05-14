#include "EventHandler.h"

using namespace std;

Evnt trasformAllegroEvents(int key);


void dispatchEvent(Evnt ev, Draw& info)
{
	switch (ev)
	{
	case POS1: info.toggle(compatibleFiles, 0); break;
	case POS2: info.toggle(compatibleFiles, 1); break;
	case POS3: info.toggle(compatibleFiles, 2); break;
	case POS4: info.toggle(compatibleFiles, 3); break;
	case POS5: info.toggle(compatibleFiles, 4); break;
	case POS6: info.toggle(compatibleFiles, 5); break;
	case POS7: info.toggle(compatibleFiles, 6); break;
	case POS8: info.toggle(compatibleFiles, 7); break;
	case POS9: info.toggle(compatibleFiles, 8); break;
	case PAGEUP: info.nextPage(); break;
	case PAGEDOWN: info.prevPage(); break;
	case ALL: info.toggleAll(compatibleFiles); break;
	case NONE: info.toggleNone(compatibleFiles); break;
	case ENTER:
	}

}

Evnt trasformAllegroEvents(int key)
{
	Evnt ev = NOEVENT;

	switch (key)
	{
	case ALLEGRO_KEY_1:
		ev = POS1;
		break;
	case ALLEGRO_KEY_2:
		ev = POS2;
		break;
	case ALLEGRO_KEY_3:
		ev = POS3;
		break;
	case ALLEGRO_KEY_4:
		ev = POS4;
		break;
	case ALLEGRO_KEY_5:
		ev = POS5;
		break;
	case ALLEGRO_KEY_6:
		ev = POS6;
		break;
	case ALLEGRO_KEY_7:
		ev = POS7;
		break;
	case ALLEGRO_KEY_8:
		ev = POS8;
		break;
	case ALLEGRO_KEY_9:
		ev = POS9;
		break;
	case ALLEGRO_KEY_A:
		ev = ALL;
		break;
	case ALLEGRO_KEY_N:
		ev = NONE;
		break;
	case ALLEGRO_KEY_RIGHT:
		ev = PAGEUP;
		break;
	case ALLEGRO_KEY_LEFT:
		ev = PAGEDOWN;
		break;
	case ALLEGRO_KEY_ENTER:
		ev = ENTER;
		break;
	}
	return ev;
}

Evnt getEvent(ALLEGRO_EVENT_QUEUE * eq)
{
	ALLEGRO_EVENT ev;
	Evnt retEv = NOEVENT;
	static Timer * time = NULL;		// Ya se que no deberiamos usar 'static' pero necesito que este objeto no se destruya al terminar
									// la funcion ya que es el encargado de regular el tiempo. Creo este objeto solo cuando se detecta 
									// que se toco una tecla y lo destruyo cuando dejan de apretarla.
	al_get_next_event(eq, &ev);


	switch (ev.type)
	{
	case ALLEGRO_EVENT_KEY_DOWN:
		if (time == NULL)
		{
			time = new Timer();
			time->start();
		}
		break;
	case ALLEGRO_EVENT_KEY_UP:
		if (time != NULL)
		{
			time->stop();
			if (time->getTime() >= 100)
				retEv = trasformAllegroEvents(ev.keyboard.keycode);
			delete time;
			time = NULL;
		}
		break;
	case ALLEGRO_EVENT_TIMER:
		retEv = TIMER;
		break;
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		retEv = QUIT;
		break;
	}


	return retEv;

}