#pragma once
#include <vector>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "Image.h"

using std::cout;
using std::vector;
using namespace boost::filesystem;

class parseDirectory
{
public:
	/*Constructores y destructor*/
	parseDirectory();
	parseDirectory(string command_path);	
	~parseDirectory();
	/*Funcion de Parseo*/
	bool parseDir();	//Parseo del directorio enviado
	/*Metodos de Acceso*/
	bool isVectorempty();	
	vector<image> getVector();
	bool setCallback(bool(*callback)(string exten));
private:
	vector<image> correctFiles;	// Vector en donde entran los paths que cumplen con el condicional
	path recieved_path;
	bool(*callback)(string exten);	//callback enviado por el usuario
	int count_correct;		//COntador de archivos correctos
	int count_otherfile;		//Contador de archivos o directorios no compatibles
	bool vector_empty;		//Indicador de si tiene alguna imagen compatible el vector
};

