#include "Compresor.h"



Compresor::Compresor(uint threshold, Compress_type compress_mode)
{
	this->threshold = threshold;
	this->compress_mode = compress_mode;
}


Compresor::~Compresor()
{
}

void Compresor::compress() {

}



//Hice threshold dato miembro, menos villero
void Compresor::rec_comp(unsigned int w, unsigned int h, char ** out, unsigned int init_x, unsigned int init_y) {
		
	uint puntaje = give_me_the_score( w,   h,  out,   init_x,   init_y);

	if (puntaje >= this->threshold) {
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
			rec_comp(new_w_izq, new_h_hi, out, init_x, init_y);
			//-*
			//--
			rec_comp(new_w_der, new_h_hi, out, init_x, init_y + new_w_izq);
			//--
			//*-
			rec_comp(new_w_izq, new_h_lo, out, init_x + new_h_hi, init_y);
			//--
			//-*
			rec_comp(new_w_der, new_h_lo, out, init_x + new_h_hi, init_y + new_w_izq);

		}
		else {
			//hacer esto una función que llame a promedio y fputchar
			char * prom = new char[4];
			prom = promedio(w, h, out, init_x, init_y);
			//fputc
			delete prom;
		}

}

//Te tira error xq estas accediendo a cosas que no son stati desde un metodo static, el compilador no puede aseguar que esas cosas existan
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


uint Compresor::give_me_the_score(uint  w, uint  h, char ** out, uint  init_x, uint  init_y)
{
	uint score=0;
	uint * my_highest = new uint[6];
	fill(my_highest, my_highest + 6, 0);

	for (int i = init_x; i < init_x + h; i++)   //Searching for max and min of RGB pixels
		for (int j = init_y; j < init_y + w; j = j + 4) {

			if (out[i][j] > my_highest[0]) //max R
				my_highest[0] = out[i][j];

			if (out[i][j] < my_highest[1]) //min R
				my_highest[1] = out[i][j];

			if (out[i][j+1] > my_highest[2]) //max G
				my_highest[2] = out[i][j+1];

			if (out[i][j+1] < my_highest[3]) //min G
				my_highest[3] = out[i][j+1];

			if (out[i][j+2] > my_highest[4])  //max B
				my_highest[4] = out[i][j+2];

			if (out[i][j+2] < my_highest[5])   //min B
				my_highest[5] = out[i][j+2];

			for (int k=0; k < 6; k++)
			{
				if (k % 2)
					score -= my_highest[k];
				else
					score += my_highest[k];
			}
			
		}

	delete my_highest;
	return score;
}
