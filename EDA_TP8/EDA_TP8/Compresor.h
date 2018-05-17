#pragma once
#include <iostream>
#include "lodepng.h"
#include "TreeNode.h"
#include "Image.h"
#include <limits>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdint>

typedef unsigned int uint;
using namespace std;
class Compresor
{
public:
	Compresor();
	~Compresor();
	void compress(image& my_image, uint threshold);
	void decompress(image& my_image);

private:

	//Streams functions
	string filename;		//archivo en el que se escribe para comprimir.
	string complete_path;
	void create_file(string name);
	template <typename t1>void write_file(t1 a);



	char * get_colours(unsigned char ** image, char *current_pos, unsigned int w, unsigned int h, unsigned int init_x, unsigned int init_y);

	void rec_comp(unsigned int w, unsigned int h, unsigned char ** out, unsigned int init_x, unsigned int init_y, unsigned int threshold);
	void rec_decomp(unsigned char ** image, unsigned int w, unsigned int h, char * current_pos, unsigned int init_x, unsigned int init_y);

	unsigned int puntaje(unsigned int w, unsigned int h, unsigned char ** out, unsigned int init_x, unsigned int init_y);
	static void promedio(unsigned char colores_prom[4], unsigned int w, unsigned int h, unsigned char ** out, unsigned int init_x, unsigned int init_y);

	void matrix_to_array(unsigned char array[], unsigned int array_length, unsigned char **matrix, unsigned int w, unsigned int h);
	void array_to_matrix(unsigned char array[], unsigned int array_length, unsigned char **matrix, unsigned int w);
	unsigned char * allocate_file(image& my_image, uint * w, uint * h);

	string new_name(string my_image_path, string my_image);
};
