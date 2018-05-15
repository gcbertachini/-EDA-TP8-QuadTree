#pragma once
#include <iostream>
#include "lodepng.h"

class Compresor
{
public:
	Compresor(FILE * file_stream);
	~Compresor();
	void compress(unsigned int w, unsigned int h, char out_lineal[], unsigned int threshold);
	void decompress();
	
private:

	FILE * to_write_file;
	void change_target_file(FILE * file_stream);

	void rec_comp(unsigned int w, unsigned int h, char ** out, unsigned int init_x, unsigned int init_y, unsigned int threshold);
	unsigned int puntaje(unsigned int w, unsigned int h, char ** out, unsigned int init_x, unsigned int init_y);
	static void promedio(char colores_prom[4], unsigned int w, unsigned int h, char ** out, unsigned int init_x, unsigned int init_y);


	void array_to_matrix(char array[], unsigned int array_length, char **matrix, unsigned int w);
};
