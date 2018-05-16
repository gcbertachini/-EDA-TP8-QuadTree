#include <vector> 
#include <iostream>
#include<cstdio>
#include "Compresor.h"

#include "Allegro.h"
#include "calbacks.h"
#include"parseDirectory.h"
#include"Parser.h"
#include "modeSelector.h"

#include "Draw.h"
#include "eventHandler.h"

int main(int argc, char** argv)
{
	Allegro allegro;	//instancio clase allegro
	vector<image>compatiblefiles;
	modeSelector selector;
	Compresor compresor;
	
	modo_t modo;

	Parser parsecmdln;
	bool run = false;
	parsecmdln.Read(argc, argv);	//parsea los argumentos recibidos por linea de comando
	modo = selector.modeSelect(allegro.getEventQueue(),allegro.getFont());
	al_clear_to_color(al_map_rgb(0, 0, 0));

	if (!parsecmdln.getError()&&!(selector.getQuit()))
	{
		parseDirectory parserDir(parsecmdln.path);
		if (modo == COMPRESION)
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
			
//			Compresor compresor;	//instancio clase compresor
			

 			Draw dibu(compatiblefiles, modo, allegro);	//creo objeto que dibuja en pantalla
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
				//dibu.setexit(false);//cambio el estado de esa variable
				///COMPRIMO / DESCOMPRIMO LAS IMAGENES SELECCIONADAS*/
					if (dibu.modo == COMPRESION){ 
					for(int i=0;i<compatiblefiles.size();i++){		//cada archivo a comprimir
						if(compatiblefiles[i].getSelected())
						compresor.compress(compatiblefiles[i],parsecmdln.get_threshold());
					}
						

					}
					else if (dibu.modo == DESCOMPRESION) {

						for (int i = 0; i<compatiblefiles.size(); i++) {		//cada archivo a comprimir
							compresor.decompress(compatiblefiles[i++]);
						}
					}
						
						//CUANDO TERMINA ALLEGRO TIENE QUE DECIR QUE TERMINO

				dispatchEvent(FINISH, dibu,compatiblefiles); //Actualizaria la pantalla con un mensaje de terminado

						/*ESTA SECCION TE DEJA ALLEGRO CORRIENDO HASTA QUE APRETES QUIT*/
				//dibu.drawPage(compatiblefiles);
				dibu.updateDisplay();
				while (!dibu.getexit())
				{
					evento = getEvent(allegro.getEventQueue());
					if (evento == QUIT || evento == ENTER)
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