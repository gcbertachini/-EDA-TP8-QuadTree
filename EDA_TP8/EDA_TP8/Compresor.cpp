#include "Compresor.h"
/*


Compresor::Compresor()
{
}


Compresor::~Compresor()
{
}

void Compresor::compress() {

}

typedef struct {
	char colores_prom[4];
} pixel_t;

void Compresor::rec_comp(unsigned int w, unsigned int h, char ** out, unsigned int init_x, unsigned int init_y, unsigned int threshold) {
		
		if (puntaje >= threshold) {
			unsigned int new_w_izq = w / 2;
			unsigned int new_w_der = w / 2;
			unsigned int new_h_hi = h / 2;
			unsigned int new_h_lo = h / 2;

			if (w % 2)
				new_w_der++;
			if (h % 2)
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
			prom = promedio(w, h, out, init_x, init_y);
		}

}

char* Compresor::promedio(unsigned int w, unsigned int h, char ** out, unsigned int init_x, unsigned int init_y) {

	char colores_prom[4];
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

	return colores_prom;
}

*/