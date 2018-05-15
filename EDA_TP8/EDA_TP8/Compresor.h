#pragma once
#include <iostream>
#include "lodepng.h"

using namespace std;
enum class Compress_type {Compress_mode,Decompress_mode};

class Compresor
{
public:
	Compresor(uint threshold, Compress_type compress_mode);
	~Compresor();
	void compress();
	void decompress();
	
private:
	void rec_comp(unsigned int w, unsigned int h, char ** out, unsigned int init_x, unsigned int init_y);
	static char* promedio(unsigned int w, unsigned int h, char ** out, unsigned int init_x, unsigned int init_y); //xq es static?????
	uint give_me_the_score(uint  w, uint  h, char ** out, uint  init_x, uint  init_y);
	uint32_t * give_me_dimensions(uint  w, uint  h, unsigned char ** out, const char *  filename); //Hay que tener el filename del archivo a trabajar
																									//Hay que liberar el ptr dps de usarlo
	uint threshold;
	Compress_type compress_mode;
};

//	double a[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//double(*b)[3] = reinterpret_cast<double(*)[3]>(a);

typedef unsigned int uint;
