#pragma once
#include <iostream>
#include "lodepng.h"
#include "TreeNode.h"

class Compresor
{
public:
	Compresor();
	~Compresor();
	void compress(unsigned int w, unsigned int h, char out_lineal[], unsigned int threshold);
	void decompress(unsigned int w, unsigned int h, char * path);
private:

	FILE * to_write_file;		//archivo en el que se escribe para comprimir.
	void change_target_file(FILE * file_stream);

	char * get_colours(char ** image, char *current_pos, unsigned int w, unsigned int h, unsigned int init_x, unsigned int init_y);

	void rec_comp(unsigned int w, unsigned int h, char ** out, unsigned int init_x, unsigned int init_y, unsigned int threshold);
	void rec_decomp(char ** image, unsigned int w, unsigned int h, char * current_pos, unsigned int init_x, unsigned int init_y);

	unsigned int puntaje(unsigned int w, unsigned int h, char ** out, unsigned int init_x, unsigned int init_y);
	static void promedio(char colores_prom[4], unsigned int w, unsigned int h, char ** out, unsigned int init_x, unsigned int init_y);
	uint32_t * give_me_dimensions(uint  w, uint  h, unsigned char ** out, const char *  filename);

	void matrix_to_array(char array[], unsigned int array_length, char **matrix, unsigned int w, unsigned int h);
	void array_to_matrix(char array[], unsigned int array_length, char **matrix, unsigned int w);
};

typedef unsigned int uint;