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
	parseDirectory();
	parseDirectory(string command_path, bool(*callback)(string exten));	// Constructor
	parseDirectory(string command_path);	//HAGO ESTE CONSTRUCTOR SINO VISUAL ME RETA
	~parseDirectory();
	bool parseDir();	//Parseo del directorio enviado
	bool isVectorempty();	
	vector<image> getVector();
	bool setCallback(bool(*callback)(string exten));
private:
	vector<image> correctFiles;	// Vector en donde entran los paths que cumplen con el condicional
	path recieved_path;
	bool(*callback)(string exten);	//callback enviado por el usuario
	int count_correct;		//Parametros extra
	int count_otherfile;
	bool vector_empty;
	image *aux;
};

