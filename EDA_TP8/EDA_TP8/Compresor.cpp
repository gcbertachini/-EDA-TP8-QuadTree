#include "Compresor.h"
#include <limits>
#include <string>



Compresor::Compresor(FILE * file_stream)
{
	change_target_file(FILE * file_stream);
}

Compresor::~Compresor()
{

}

void Compresor::change_target_file(FILE * file_stream) {
	to_write_file = file_stream;
}
void Compresor::compress(unsigned int w, unsigned int h, char out_lineal[], unsigned int threshold) {
	
	char** matrix = new char*[h];
	for (int i = 0; i < h; ++i)
		matrix[i] = new char[w];			//creo una matriz de char para facilitar la lectura y escritura de la imagen al comprimir.

	array_to_matrix(out_lineal, h*w,matrix, w);
	rec_comp(w, h, matrix, 0, 0, threshold);

	for (int i = 0; i < h; ++i)
		delete[] matrix[i];
	delete[] matrix;						//borro la matriz para que no haya memory leaks
}
void Compresor::decompress() {

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