#include "parseDirectory.h"



parseDirectory::parseDirectory()
{
	cout << "Parse Directory construction error" << endl;
}

parseDirectory::parseDirectory(string comand_path, bool(*callback_fun)(string exten) = NULL): recieved_path(comand_path)
{
	this->callback = callback_fun;
	count_correct = 0;
	count_otherfile = 0;
	vector_empty = true;
}

parseDirectory::parseDirectory(string comand_path) : recieved_path(comand_path)
{
	this->callback = NULL;
	count_correct = 0;
	count_otherfile = 0;
	vector_empty = true;
}


bool parseDirectory::parseDir()
{
	try
	{
		if (exists(recieved_path))
		{
			
			if (is_directory(recieved_path))
			{
				cout << recieved_path << " is a directory containing:\n";

				for (directory_entry& x : directory_iterator(recieved_path))	//Chequeo todos lo archivos del directorio
				{
					if (callback((((x.path()).extension())).string()))	//FALTA VER SI UN ARCHIVO ES UN DIRECTORIO
					{
						cout << "Archivo compatible encontrado = "<< x.path().filename()<<endl;
						correctFiles.push_back( image((x.path()).string(), (x.path().filename()).string()));
						vector_empty = false;
						count_correct++;
					}
					else
					{
						count_otherfile++;
					}
				}
				cout << "Se ha analizado el directorio. Se han encontrado " << count_correct << " archivos compatibles y " << count_otherfile << " directorios o archivos incompatibles" << endl;
				return true;
			}
			else
			{
				cout << "El camino que ha introducido existe pero no es un directorio" << endl;	//MOSTRAR PATH
				return false;
			}

		}
		else
		{
			cout << "El camino que ha introducido no existe en el equipo" << endl;	//MOSTRAR PATH
			return false;
		}
		
	}

	catch (const filesystem_error& ex)
	{
		cout << ex.what() << '\n';
	}

}

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
