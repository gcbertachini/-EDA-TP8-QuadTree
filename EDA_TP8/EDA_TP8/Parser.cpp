#include "Parser.h"


int Parser::Read(int argc, char * argv[])
{
	int final = 0, posible = 0, error = false;

	for (int i = 1; i<argc; ) {
		if (argv[i][0] == '-') { //Si el primer caracter es un - sera una opcion (opcion es clave+valor)
			if (argv[i][1] == 0) //si pasan - solo
			{
				error = ERROR2;
				i = argc;
			}
			else if ((i + 1) >= argc)
			{
				error = ERROR1; //si es el ultimo caracter obviamente no tiene valor
				i++;
			}

			else
			{
				Do(&(argv[i][1]), argv[i + 1]);
				if (posible >= 0) {
					i += 2; //avanzo 2 parametros
				}
				else {
					error = ERROR3;
					i = argc;
				}
			}
		}
		else {
			Do(nullptr, argv[i]); //si no es opcion es parametro
			if (posible >= 0) {
				i++;
			}
			else {
				error = ERROR3;
				i = argc;
			}
		}
	}
	if (error == ERROR1) //Opcion sin valor
		final = ERROR1;
	else if (error == ERROR2) //Opcion sin clave
		final = ERROR2;
	else if (error == ERROR3) //No encontrado
		final = ERROR3;
	else
		final = 0;

	return final;
}


Parser::~Parser()
{
}

void Parser::Do(char * key, char * value)
{
	int i = 0, equal;

	if (key == nullptr)
	{
		error_fran = true;
		cout << "Error, el programa no recibe parametros, solo opciones" << endl;

	}
	else
	{
		while (key[i]) //Case insensitive
		{
			key[i] = toupper(key[i]);
			i++;
		}

		for (i = 0; i < NKEYS; i++) //Busca Key conocida
		{
			equal = strcmp(key, parseData.key[i]);
			if (equal == 0)
			{
				switch (i)
				{
				case 0:
					path = value;	//El chequeo de error del path se hace luego
					break;
				case 1:
					if (atoi(value) == COMPRESION)
						modo = COMPRESION;
					else if (atoi(value) == DESCOMPRESION)
						modo = DESCOMPRESION;
					else
					{
						cout << "ERROR VALOR MODO, introduzca Compresion (0) Descopresion(1) " << endl;
						error_fran = true;
					}
					break;
				case 2:
					threshold = atoi(value);
					break;
				default:
					cout << "Problema en el parseo" << endl;
					break;
				}
			}
		}

	}
}

bool Parser::getError()
{
	return this->error_fran;
}
