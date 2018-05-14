#include "calbacks.h"


bool isPNG(string extension)
{
	string png = ".png";
	return (extension == png);
}

bool isCompressed(string extension)
{
	string ext = EXTENSION_COMPRIMIDO;
	return (extension == ext);
}

