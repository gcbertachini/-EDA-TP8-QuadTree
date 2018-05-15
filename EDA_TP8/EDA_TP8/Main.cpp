#include <vector> 
#include <iostream>
#include<cstdio>

#include "Allegro.h"
#include "calbacks.h"
#include"parseDirectory.h"
#include"Parser.h"
#include "Compresor.h"

#include"Draw.h"
#include"eventHandler.h"

void main(int argc, char** argv)
{
	vector<image>compatiblefiles;
	Allegro allegro;
	Parser parsecmdln;
	bool run = false;
	parsecmdln.Read(argc, argv);	//parsea los argumentos recibidos por linea de comando

	if (!parsecmdln.getError())
	{
		parseDirectory parserDir(parsecmdln.path);
		if (parsecmdln.modo == COMPRESION)
			parserDir.setCallback(isPNG);
		else //if (parsecmdln.modo == DESCOMPRESION)
			parserDir.setCallback(isCompressed);

		parserDir.parseDir();
		if (!parserDir.isVectorempty())	//Chequeo que haya algo en el vector del parser
		{
			compatiblefiles = parserDir.getVector();
			run = true;
		}
		else
		{
			cout << "El vector de archivos compatibles es vacio" << endl;
		}
		if (run)
		{
			Allegro allegro;
			Compresor compresor;
			Draw dibu(compatiblefiles, parsecmdln.modo);
			Evnt evento = NOEVENT;
			while(!draw.quit)	//AGREGAR LOGICA DE QUIT EN EL DRAW
			{
				evento = getEvent(allegro.getEventQueue());		//SE QUE ACA ME FALTA UN CONDICIONAL
				dispatchEvent(evento, dibu);
				//dibu.updateDisplay();	//HAY QUE PONER UN FLIP DISPLAY PERO NO ACA
			}

			if (parsecmdln.modo == COMPRESION)
				compresor.compress();
			else if (parsecmdln.modo == DESCOMPRESION)
				compresor.decompress();

			//CUANDO TERMINA ALLEGRO TIENE QUE DECIR QUE TERMINO

			dispatchEvent(finish, dibu); //Actualizaria la pantalla con un mensaje de terminado
		}




}