#include "parseDirectory.h"



parseDirectory::parseDirectory()
{
	cout << "Parse Directory construction error, es necesario enviad un path" << endl;
}


parseDirectory::parseDirectory(string comand_path) : recieved_path(comand_path)
{
	this->callback = NULL;	//Inicializo el puntero en null
	count_correct = 0;
	count_otherfile = 0;
	vector_empty = true;		// En un principio el vector no tiene nada
}

/*PARSER*/
/*
	Utilizo el path del constructor, reviso si existe o si es un directorio. Si es un directorio itero sus contenidos.
	Cuando el iterador encuentra un archivo compatible(dado por la extension enviada al callback) lo guarda en el vector como
	una clase imagen.
	Si no existe el directorio se imprimira un mensaje avisando el error
*/
bool parseDirectory::parseDir()
{
	try
	{
		if (exists(recieved_path))
		{
			
			if (is_directory(recieved_path))
			{
				cout << recieved_path << " es un directorio"<<endl;
				if (boost::filesystem::is_empty(recieved_path))
				{
					cout << "El directorio introducido es vacio" << endl;
				}
				else
				{
					for (directory_entry& x : directory_iterator(recieved_path))	//Chequeo todos lo archivos del directorio
					{
						if (callback((((x.path()).extension())).string()))	//FALTA VER SI UN ARCHIVO ES UN DIRECTORIO
						{
							cout << "Archivo compatible encontrado = " << x.path().filename() << endl;
							correctFiles.push_back(image((x.path()).generic_string(), (x.path().filename()).generic_string()));
							vector_empty = false;
							count_correct++;
						}
						else
						{
							count_otherfile++;
						}
					}
				}
				cout << "Se ha analizado el directorio."<< recieved_path <<"Se han encontrado " << count_correct << " archivos compatibles y " << count_otherfile << " directorios o archivos incompatibles" << endl;
				return true;
			}
			else
			{
				cout << "El camino"<< recieved_path <<"existe pero no es un directorio" << endl;	//MOSTRAR PATH
				return false;
			}

		}
		else
		{
			cout << "El camino"<< recieved_path <<"no existe en el equipo" << endl;	//MOSTRAR PATH
			return false;
		}
		
	}

	catch (const filesystem_error& ex)
	{
		cout << ex.what() << '\n';
	}

}
/* SET CALLBACK*/
/*
	Seteo el calback dependiendo de si comprimo o descomprimo
*/
bool parseDirectory::setCallback(bool(*callback)(string exten))
{
	if (!callback)
	{
		cout << "NO se puede sobreescribir el puntero" << endl;
		return false;
	}
	else
	{
		this->callback = callback;
	}
}

/*GET VECTOR*/
/*
	Devuelve el vector con los archivos compatibles
*/
vector<image> parseDirectory::getVector()
{
	return correctFiles;
}

bool parseDirectory::isVectorempty()
{
	return vector_empty;
}


parseDirectory::~parseDirectory()
{
}
