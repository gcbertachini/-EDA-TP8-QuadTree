#pragma once
#include <iostream>
class Compresor
{
public:
	Compresor();
	~Compresor();
	void compress();
	void decompress();
private:
	void rec_comp(unsigned int w, unsigned int h, char ** out, unsigned int init_x, unsigned int init_y, unsigned int threshold);
	unsigned int puntaje(unsigned int w, unsigned int h, char ** out, unsigned int init_x, unsigned int init_y);
	static char* promedio(unsigned int w, unsigned int h, char ** out, unsigned int init_x, unsigned int init_y);
};

//	double a[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//double(*b)[3] = reinterpret_cast<double(*)[3]>(a);