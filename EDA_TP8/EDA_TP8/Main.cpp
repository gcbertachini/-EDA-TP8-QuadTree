#include <vector> 
#include <iostream>
#include<cstdio>

//#include "Allegro.h"
#include "calbacks.h"
#include"parseDirectory.h"
#include"Parser.h"
//#include "Compresor.h"

void main(int argc, char** argv)
{
	vector<image>compatiblefiles;
	//Allegro allegro;
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
		/*if (run)
		{
			Allegro allegro;
			Compresor compresor;
			/* SELECIONAR ARCHIVOS AQUI*
			if (parsecmdln.modo == COMPRESION)
				compresor.compress();
			else if (parsecmdln.modo == DESCOMPRESION)
				compresor.decompress();
		}*/


		


	}
	cout << "El programa ha finalizado, oprima enter para salir" << endl;
	getchar();

}