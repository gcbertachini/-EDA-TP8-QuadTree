#include <vector> 
#include <iostream>
#include<cstdio>

#include "Allegro.h"
#include "calbacks.h"
#include"parseDirectory.h"
#include"Parser.h"
//#include "Compresor.h"

#include"Draw.h"
#include"eventHandler.h"

void main(int argc, char** argv)
{
	vector<image>compatiblefiles;
	
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
		if (run)	//Corre solo si el vector de imagenes compatibles no es vacio
		{
			Allegro allegro;	//instancio clase allegro
//			Compresor compresor;	//instancio clase compresor
 			Draw dibu(compatiblefiles, parsecmdln.modo);	//creo objeto que dibuja en pantalla
			Evnt evento = NOEVENT;
			dibu.drawPage(compatiblefiles);
			dibu.updateDisplay();
			/* SELECCIONO IMAGENES EN ALLEGRO*/
			while (!dibu.getexit())	//AGREGAR LOGICA DE EXIT EN EL DRAW
			{
				evento = getEvent(allegro.getEventQueue());		//SE QUE ACA ME FALTA UN CONDICIONAL
				if (evento != NOEVENT)
				{
					dispatchEvent(evento, dibu, compatiblefiles);	//Actualizo la pantalla si me llega un evento
					dibu.drawPage(compatiblefiles);
					dibu.updateDisplay();

				}
			}
			if (!dibu.getquit())	//ESTO LO HAGO SI NO SE SALIO DEL PRGRAMA ANTES
			{
				dibu.setexit(false);//cambio el estado de esa variable
				/* COMPRIMO / DESCOMPRIMO LAS IMAGENES SELECCIONADAS*/
					/*if (parsecmdln.modo == COMPRESION)
						compresor.compress();
					else if (parsecmdln.modo == DESCOMPRESION)
						compresor.decompress();
						*/
						//CUANDO TERMINA ALLEGRO TIENE QUE DECIR QUE TERMINO

						//dispatchEvent(FINISH, dibu,compatiblefiles); //Actualizaria la pantalla con un mensaje de terminado

						/*ESTA SECCION TE DEJA ALLEGRO CORRIENDO HASTA QUE APRETES QUIT*/
				dibu.drawPage(compatiblefiles);
				dibu.updateDisplay();
				while (!dibu.getexit())
				{
					evento = getEvent(allegro.getEventQueue());
					if (evento == QUIT)
						dispatchEvent(QUIT, dibu, compatiblefiles);

				}
			}
		}
		else
		{		//Hago esto asi si el programa tiene un error el usuario puede seguir viendo la consola
			cout << "El programa ha finalizado, oprima enter para salir" << endl;
			getchar();
		}




	}
	else
	{		//Hago esto asi si el programa tiene un error el usuario puede seguir viendo la consola
		cout << "El programa ha finalizado, oprima enter para salir" << endl;
		getchar();
	}
}