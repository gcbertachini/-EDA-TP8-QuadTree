#pragma once
#include<string>

#define EXTENSION_COMPRIMIDO ".eda"


using namespace::std;
/*AMBAS FUNCIONES CHEQUEAN SI LA EXTENSION ENVIADA ES COMPATIBLE*/

bool isPNG(string extension);

bool isCompressed(string extension);