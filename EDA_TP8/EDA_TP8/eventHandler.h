#pragma once

#include <allegro5\allegro.h>
#include <vector>
#include <ctype.h>
#include <iostream>

#include "Draw.h"

using namespace std;

typedef enum Evnt {
	NOEVENT, POS1, POS2, POS3, POS4, POS5, POS6, POS, POS7, POS8, POS9, ALL, NONE, PAGEUP, PAGEDOWN, ENTER,
};

void dispatchEvent(Evnt ev, Draw& info,vector<image>& compatibleFiles);

Evnt getEvent(ALLEGRO_EVENT_QUEUE *  eq);