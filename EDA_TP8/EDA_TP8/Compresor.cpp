#include "Compresor.h"
#include <limits>
#include <string>
#include <fstream>


Compresor::Compresor()
{
}

Compresor::~Compresor()
{

}

void Compresor::change_target_file(FILE * file_stream) {
	to_write_file = file_stream;
}
void Compresor::compress(unsigned int w, unsigned int h, char out_lineal[], unsigned int threshold) {
	
	char** matrix = new char*[h * 4];
	for (int i = 0; i < h * 4; ++i)
		matrix[i] = new char[w * 4];			//creo una matriz de char para facilitar la lectura y escritura de la imagen al comprimir.

	array_to_matrix(out_lineal, h*w,matrix, w);			//lleno la matriz acorde a lo que recibi.
	rec_comp(w, h, matrix, 0, 0, threshold);			//llamo a la funcion recursiva qeu realizara la compresion

	for (int i = 0; i < h * 4; ++i)
		delete[] matrix[i];
	delete[] matrix;						//borro la matriz para que no haya memory leaks
}
void Compresor::decompress(unsigned int w, unsigned int h, char * path) {

	std::ifstream inFile;
	inFile.open(path);	// aca poner el path del txt que necesito
	std::string f_input = "";
	while (inFile >> f_input) {
		
	}
	inFile.close();


	char** matrix = new char*[h*4];
	for (int i = 0; i < h*4; ++i)
		matrix[i] = new char[w*4];			//creo una matriz de char para facilitar la lectura y escritura de la imagen al comprimir.

	rec_decomp(matrix, w, h, (char * )f_input.c_str, 0, 0);

	char * array = new char[h*w * 16];
	matrix_to_array(array, h*w * 16, matrix, w, h);

	//FALTA EL LLAMADO A ENCODE!!!

	for (int i = 0; i < h*4; ++i)
		delete[] matrix[i];
	delete[] matrix;						//borro la matriz para que no haya memory leaks
	delete[] array;
}

void Compresor::rec_comp(unsigned int w, unsigned int h, char ** out, unsigned int init_x, unsigned int init_y, unsigned int threshold) {

	unsigned int punt = puntaje(w, h, out, init_x, init_y);		//obtengo el puntaje del cuadrado en particular

	if (punt >= threshold) {
		fputc('B', to_write_file);

		unsigned int new_w_izq = w / 2;
		unsigned int new_w_der = w / 2;
		unsigned int new_h_hi = h / 2;
		unsigned int new_h_lo = h / 2;

		if (w % 2)			//caso en que haya una cantidad impar de pixeles para el ancho
			new_w_der++;
		if (h % 2)			//caso en que haya una cantidad impar de pixeles para la altura
			new_h_lo++;
		//*-
		//--
		rec_comp(new_w_izq, new_h_hi, out, init_x, init_y, threshold);
		//-*
		//--
		rec_comp(new_w_der, new_h_hi, out, init_x, init_y + new_w_izq, threshold);
		//--
		//*-
		rec_comp(new_w_izq, new_h_lo, out, init_x + new_h_hi, init_y, threshold);
		//--
		//-*
		rec_comp(new_w_der, new_h_lo, out, init_x + new_h_hi, init_y + new_w_izq, threshold);

	}
	else {
		char prom[4];
		promedio(prom, w, h, out, init_x, init_y);

		std::string str = std::string("N ") + std::to_string(prom[0]) + " " + std::to_string(prom[1]) + " " + std::to_string(prom[2]);
		fputs(str.c_str(), to_write_file);
	}
}
/*
void Compresor::rec_decomp(char image[],unsigned int w, unsigned int h,char * current_pos, unsigned int init_x, unsigned int init_y, TreeNode * tree) {

	tree->this_h = h;
	tree->this_w = w;
	char c = *current_pos;
	if (c ==  'B') {

		unsigned int new_w_izq = w / 2;
		unsigned int new_w_der = w / 2;
		unsigned int new_h_hi = h / 2;
		unsigned int new_h_lo = h / 2;

		if (w % 2)			//caso en que haya una cantidad impar de pixeles para el ancho
			new_w_der++;
		if (h % 2)			//caso en que haya una cantidad impar de pixeles para la altura
			new_h_lo++;

		tree->give_birth();
		current_pos ++;

		rec_decomp(image, new_w_izq, new_h_hi, current_pos, tree->left);
		rec_decomp(image, new_w_der, new_h_hi, current_pos, tree->middle_left);
		rec_decomp(image, new_w_izq, new_h_lo, current_pos, tree->middle_right);
		rec_decomp(image, new_w_der, new_h_lo, current_pos, tree->right);
	}
	else if (c == 'N') {
		current_pos ++;
		get_colours(current_pos, tree);
	}
	else if (c == ' ') {
		rec_decomp(image, w, h, current_pos++, tree);
	}
}
*/
/*
void Compresor::get_colours(char * current_pos, TreeNode * tree) {
	int j = 0;
	bool received = false;
	unsigned int colour = 0;
	for (int i = 0; i < 14; i++) {
		char c = current_pos[i];
		if ((c <= '9') && (c > '0')) {
			received = true;
			colour = colour * 10 + (unsigned int)c;
		}
		else if (c == ' ') {
			if (received) {
				tree->RGB_T[j] = colour;
				j++;
			}
		}
		else {
			tree->RGB_T[3] = 0xff;
			break;
		}
	}
}
*/
void Compresor::promedio(char colores_prom[4], unsigned int w, unsigned int h, char ** out, unsigned int init_x, unsigned int init_y) {

	unsigned int sum_r = 0;
	unsigned int sum_g = 0;
	unsigned int sum_b = 0;

	unsigned int num_elements = 0;

	for (int i = init_x; i < init_x + h; i++)
		for (int j = init_y; j < init_y + w; j = j + 4) {
			sum_r += out[i][j];
			sum_g += out[i][j + 1];
			sum_b += out[i][j + 2];
			num_elements++;
		}

	colores_prom[0] = sum_r / (double)num_elements;
	colores_prom[1] = sum_g / (double)num_elements;
	colores_prom[2] = sum_b / (double)num_elements;
	colores_prom[3] = 0xff;

}

unsigned int Compresor::puntaje(unsigned int w, unsigned int h, char **out, unsigned int init_x, unsigned int init_y) {

	unsigned int max_R = 0;				
	unsigned int min_R = UINT_MAX;
	unsigned int max_G = 0;
	unsigned int min_G = UINT_MAX;
	unsigned int max_B = 0;
	unsigned int min_B = UINT_MAX;

	for (int i = init_x; i < init_x + h; i++)
		for (int j = init_y; j < init_y + w; j = j + 4) {

			if (out[i][j] > max_R)
				max_R = out[i][j];
			else if (out[i][j] < min_R)
				min_R = out[i][j];

			if (out[i][j + 1] > max_G)
				max_G = out[i][j + 1];
			else if (out[i][j] < min_G)
				min_G = out[i][j + 1];

			if (out[i][j + 2] > max_B)
				max_B = out[i][j + 2];
			else if (out[i][j + 2] < min_B)
				min_B = out[i][j + 2];
		}

	return (max_R - min_R + max_G - min_G + max_B - min_B);

}

void Compresor::array_to_matrix(char array[], unsigned int array_length, char **matrix, unsigned int w) {
	int fils = 0;		//filas
	int cols = 0;		//columnas

	for (int h = 0; h < array_length; cols++, h++) {

		if ((h + 1) % w == 0){		//cambio de fila!!!
			fils++;			//cambio de fila
			cols = 0;		//reinicio las columnas.
		}
		
		matrix[fils][cols] = array[h];
	}
}


void Compresor::matrix_to_array(char array[], unsigned int array_length, char **matrix, unsigned int w, unsigned int h) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w*4; j++)
		{
			array[i + j* w*4]= matrix[i][h];
		}
	}
}

void Compresor::rec_decomp(char **image, unsigned int w, unsigned int h, char * current_pos, unsigned int init_x, unsigned int init_y) {

	char c = *current_pos;
	if (c == 'B') {

		unsigned int new_w_izq = w / 2;
		unsigned int new_w_der = w / 2;
		unsigned int new_h_hi = h / 2;
		unsigned int new_h_lo = h / 2;

		if (w % 2)			//caso en que haya una cantidad impar de pixeles para el ancho
			new_w_der++;
		if (h % 2)			//caso en que haya una cantidad impar de pixeles para la altura
			new_h_lo++;

		current_pos++;

		rec_decomp(image, new_w_izq, new_h_hi, current_pos, init_x, init_y);
		rec_decomp(image, new_w_der, new_h_hi, current_pos, init_x, init_y + new_w_izq);
		rec_decomp(image, new_w_izq, new_h_lo, current_pos, init_x + new_h_hi, init_y);
		rec_decomp(image, new_w_der, new_h_lo, current_pos, init_x + new_h_hi, init_y + new_w_izq);
	}
	else if (c == 'N') {
		current_pos++;
		get_colours(image, current_pos, w, h, init_x, init_y);
	}
	else if (c == ' ') {
		current_pos++;
		rec_decomp(image, w, h, current_pos, init_x, init_y);
	}
}
void Compresor::get_colours(char ** image,char *current_pos, unsigned int w, unsigned int h, unsigned int init_x, unsigned int init_y) {

	char RGB_T[4];
	int j = 0;
	bool received = false;
	unsigned int colour = 0;

	for (int i = 0; i < 14; i++) {
		char c = current_pos[i];
		if ((c <= '9') && (c > '0')) {
			received = true;
			colour = colour * 10 + (unsigned int)c;
		}
		else if (c == ' ') {
			if (received) {
				RGB_T[j] = colour;
				j++;
			}
		}
		else {
			RGB_T[3] = 0xff;
			break;
		}
	}
	for(int i = init_x; i  <  (init_x + h * 4); i++)
		for (int j = init_y; j < (init_y + w * 4); j = j + 4)
		{
			image[i][j] = RGB_T[0];
			image[i][j + 1] = RGB_T[1];
			image[i][j + 2] = RGB_T[2];
			image[i][j + 3] = RGB_T[3];
		}
}


uint32_t * Compresor::give_me_dimensions(uint  w, uint  h, unsigned char ** out, const char *  filename) {

	uint32_t * desired_dimesion;
	uint32_t * my_dimension = new uint32_t[2]; //Va a haber que hacer free al haber leido las dimensiones
	lodepng_decode32_file(out, &w, &h, filename);

	desired_dimesion = (uint32_t *)(out + 16);
	my_dimension[0] = (*desired_dimesion); //se carga el width
	desired_dimesion = (uint32_t *)(out + 20);
	my_dimension[1] = (*desired_dimesion); //se carga el height


	return my_dimension;//[0]=w,[1]=h
}
