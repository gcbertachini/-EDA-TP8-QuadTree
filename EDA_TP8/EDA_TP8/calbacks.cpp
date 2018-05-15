#include "calbacks.h"


bool isPNG(string extension)
{
	string png = ".jpg";
	return (extension == png);
}

bool isCompressed(string extension)
{
	string ext = EXTENSION_COMPRIMIDO;
	return (extension == ext);
}

