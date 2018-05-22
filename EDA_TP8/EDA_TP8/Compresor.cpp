#include "Compresor.h"


Compresor::Compresor()
{
}

Compresor::~Compresor()
{

}


/*
********************************************************
***********************compress*************************
********************************************************
*Comprime el archivo dado.

INPUT:
1) my_image : Imagen a comprimir
2) threshold : threshold con el qeu se va a comprimir.

OUTPUT:
void
*/
void Compresor::compress(image& my_image, uint threshold) {

	uint w=0, h=0;			//ancho y altura de la imagen
	uint control;
	this->complete_path = my_image.tell_me_your_path() + '/' + my_image.tell_me_your_name();
	unsigned char * out_lineal = NULL;

	create_file(my_image.tell_me_your_name().c_str());			//creo el archivo en el que voy a escribir la compresion.

	if(lodepng_decode32_file(&out_lineal, &w, &h, complete_path.c_str())){
		cout<<"Error al cargar la imagen"<<endl;				
		return;
	}

	ofstream myfile;
	myfile.open(this->filename, ios::out | ios::app | ios::binary);
	myfile << endl;
	/*
	for (int k = 0; k < w*h*4; k++) {		//para ver la el contenido de la imagen, lo imprime en el txt

		write_file<unsigned int>(out_lineal[k]);
		write_file<char>(' ');
		if (!(k % (4*w)) && (k!=0))
			write_file<char>('\n');
	}
	*/
	unsigned char** matrix = new unsigned char*[h];
	for (uint i = 0; i < h; ++i)
		matrix[i] = new unsigned char[w * 4];			//creo una matriz de char para facilitar la lectura y escritura de la imagen al comprimir.

	array_to_matrix(out_lineal, h*w*4, matrix, w*4);			//lleno la matriz acorde a lo que recibi.
	
	
	myfile.open(this->filename, ios::out | ios::app | ios::binary | ios::trunc);
	
	/*
	for (int i = 0; i < h; i++) {
		for (int j = 0; j< w*4; j++) {
			write_file<unsigned int>(matrix[i][j]);
			write_file<char>(' ');
		}
		write_file<char>('\n');
	}
	*/
	//guardo el height y el width en el txt
	write_file<uint32_t>(w);
	write_file<char>(' ');
	write_file<uint32_t>(h);
	write_file<char>(' ');

	//myfile.open(this->filename, ios::out | ios::app | ios::binary);
	//myfile << endl;


	rec_comp(w, h, matrix, 0, 0, threshold);			//llamo a la funcion recursiva qeu realizara la compresion

	for (uint i = 0; i < h; ++i)
		delete[] matrix[i];
	delete[] matrix;						//borro la matriz para que no haya memory leaks
}


/*
********************************************************
***********************decompress*************************
********************************************************
*Decomprime el archivo que esta comprimido en un txt.

INPUT:
1) w : cantidad de pixeles de ancho de la imagen a comprimir.
2) h : cantidad de pixeles de altura de la imagen a comprimir.
3) path : direccion del archivo txt donde esta comprimida la imagen

OUTPUT:
void
*/
void Compresor::decompress(image& my_image) {

	unsigned char * out_lineal;
	uint w = 0, h = 0;
	this->complete_path = my_image.tell_me_your_path() + '/' + my_image.tell_me_your_name();

	out_lineal = allocate_file(my_image, &w, &h); //Leo el arhcivo comprimido y lo guardo en memoria. Tambi�n recupero w y h del archivo
	//cout << out_lineal[0] << endl;
	unsigned char** matrix = new unsigned char*[h];
	for (uint i = 0; i < h; ++i)
		matrix[i] = new unsigned char[w * 4];			//creo una matriz de char para facilitar la lectura y escritura de la imagen al comprimir.


	rec_decomp(matrix, w, h, out_lineal, 0, 0);

	 unsigned char * array =  new unsigned char[h*w * 4];//Convierto mi matriz en un array asi la funci�n la puede decodificar
	matrix_to_array(array, h*w * 4, matrix, w, h);
	const unsigned char * new_array = array;

	string my_new_name = new_name (my_image.tell_me_your_path(),my_image.tell_me_your_name()); //Le doy un nuevo nombre al archivo decodificado
	
	lodepng_encode32_file(my_new_name.c_str(), new_array, w, h);

	for (uint i = 0; i < h; ++i)
		delete[] matrix[i];
	delete[] matrix;						//borro la matriz para que no haya memory leaks
	delete[] array;


	delete[] (out_lineal-10);
}


/*
********************************************************
***********************rec_comp*************************
********************************************************
*Comprime al archivo recursivamente, va cuadrante por cuadrante realizando divisiones consecutivas.

INPUT:
1) w : cantidad de pixeles de ancho del cuadrante en donde estoy parado.
2) h : cantidad de pixeles de altura del cuadrante en donde estoy parado.
3) out : matriz que representa a los pixeles del archivo.
4) init_x : posicion inicial en x donde esta parado el cuadrado (top left corner).
5) init_y : posicion inicial en y donde esta parado el cuadrado (top left corner).
6) threshold: trheshold de tolerancia con el que se va a comprimir segun consigna

OUTPUT:
void
*/
void Compresor::rec_comp(unsigned int w, unsigned int h, unsigned char ** out, unsigned int init_x, unsigned int init_y, unsigned int threshold) {

	unsigned int punt = puntaje(w, h, out, init_x, init_y);		//obtengo el puntaje del cuadrado en particular


	if ( ( (w > 2) && (h > 2) ) && (punt >= threshold) ) {			//verifico que no se llegue a la condicion de 1 pixel y que se supere el threshold para seguir dividiendo en cuadrantes.
		write_file<char>('B');

		if (w == 1)
			w = 2;		//para que cuando divida por dos me siga quedando uno en el valor, 
		if (h == 1)
			h = 2;

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
		rec_comp(new_w_der, new_h_hi, out, init_x + new_w_izq, init_y, threshold);
		//--
		//*-
		rec_comp(new_w_izq, new_h_lo, out, init_x , init_y + new_h_hi, threshold);
		//--
		//-*
		rec_comp(new_w_der, new_h_lo, out, init_x + new_w_izq, init_y + +new_h_hi, threshold);

		return; //Vuelvo dps de haber realizado de manera recursiva mis 4 mosaicos
	}
	else {
		unsigned char prom[4];
		promedio(prom, w, h, out, init_x, init_y);

		std::string str = std::string("N")+' ' + std::to_string(prom[0])  + ' ' + std::to_string(prom[1])  +' ' +std::to_string(prom[2]) + ' ';
		write_file<string>(str);
	}
}


/*
********************************************************
***********************promedio*************************
********************************************************
*Saca un promedio de cada color [RGB] de los pixeles del cuadrante en el que estoy parado

INPUT:
1) colores_prom : Arreglo donde estara situado el promedio de cada color [siguiendo el orden RGB y T= transparencia]
2) w : cantidad de pixeles de ancho del cuadrante en donde estoy parado.
2) h : cantidad de pixeles de altura del cuadrante en donde estoy parado.
3) out : matriz que representa a los pixeles del archivo.
4) init_x : posicion inicial en x donde esta parado el cuadrado (top left corner).
5) init_y : posicion inicial en y donde esta parado el cuadrado (top left corner).

OUTPUT:
void.
*/
void Compresor::promedio(unsigned char colores_prom[4], unsigned int w, unsigned int h, unsigned char ** out, unsigned int init_x, unsigned int init_y) {

	uint sum_r = 0;
	uint sum_g = 0;
	uint sum_b = 0;

	uint num_elements = 0;

	for (uint i = init_y; i < init_y + h; i++)
		for (uint j = init_x*4; j < (init_x + w)*4; j += 4) {
			sum_r += out[i][j];
			sum_g += out[i][j + 1];
			sum_b += out[i][j + 2];
			num_elements++;
		}

	colores_prom[0] =(unsigned char) (sum_r / (double)num_elements);
	colores_prom[1] = (unsigned char)(sum_g / (double)num_elements);
	colores_prom[2] = (unsigned char)(sum_b / (double)num_elements);
	colores_prom[3] = (unsigned char) 0xff;		

}

uint Compresor::puntaje(unsigned int w, unsigned int h,unsigned  char **out, unsigned int init_x, unsigned int init_y) {

	unsigned char max_R = out[init_y][init_x * 4];
	unsigned char min_R = out[init_y][init_x * 4];
	unsigned char max_G = out[init_y][init_x * 4 + 1];
	unsigned char min_G = out[init_y][init_x * 4 + 1];
	unsigned char max_B = out[init_y][init_x * 4 + 2];
	unsigned char min_B = out[init_y][init_x * 4 + 2];

	for (uint i = init_y; i < init_y + h; i++)

		for (uint j = init_x * 4; j < (init_x + w) * 4; j += 4) {

			if (out[i][j] > max_R)
				max_R = out[i][j];
			else if (out[i][j] < min_R)
				min_R = out[i][j];

			if (out[i][j + 1] > max_G)
				max_G = out[i][j + 1];
			else if (out[i][j+1] < min_G)
				min_G = out[i][j + 1];

			if (out[i][j + 2] > max_B)
				max_B = out[i][j + 2];
			else if (out[i][j + 2] < min_B)
				min_B = out[i][j + 2];
		}


	
	return (max_R - min_R + max_G - min_G + max_B - min_B);

}

/*
********************************************************
***********************array_to_matrix*************************
********************************************************
*hace el cambio de arreglo lineal a matriz

INPUT:
1) array : Arreglo lineal a convertir a matriz
2) array_length : Longitud del arreglo lineal.
3) matrix : matriz en la que se convertira al arreglo
4) w : longitud de las filas de la nueva matriz.

OUTPUT:
void.
*/
// .
void Compresor::array_to_matrix(unsigned char array[], unsigned int array_length, unsigned char **matrix, unsigned int w) {
	int fils = 0;		//filas
	int cols = 0;		//columnas

	for (uint i = 0; i < array_length; cols++, i++) {

		if (!(i % w) && (i != 0) ) {		//cambio de fila!!!
			fils++;			//cambio de fila
			cols = 0;		//reinicio las columnas.
		}

		matrix[fils][cols] = array[i];
	}
}


//hace el cambio de matriz a arreglo lineal
void Compresor::matrix_to_array(unsigned char array[], unsigned int array_length,unsigned char **matrix, unsigned int w, unsigned int h) {
	for (uint i = 0; i < h; i++) {
		for (uint j = 0; j < w * 4; j++)
		{
			array[i*w*4+ j] = matrix[i][j];
		}
	}
}

/*
********************************************************
***********************rec_decomp***********************
********************************************************
*Descomprime al archivo recursivamente, va cuadrante por cuadrante realizando divisiones consecutivas.

INPUT:
1) image: matriz de pixeles con la informacion del color y transparencia de cada pixel.
2) w : cantidad de pixeles de ancho del cuadrante en donde estoy parado.
3) h : cantidad de pixeles de altura del cuadrante en donde estoy parado.
4) current_pos : letra del txt en la que me encuentro parado.
5) init_x : posicion inicial en x donde esta parado el cuadrado (top left corner).
6) init_y : posicion inicial en y donde esta parado el cuadrado (top left corner).

OUTPUT:
void
*/
void Compresor::rec_decomp(unsigned char **image, unsigned int w, unsigned int h, unsigned char * current_pos, unsigned int init_x, unsigned int init_y) {

	cout << *current_pos << endl;

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

		//*-
		//--
		rec_decomp(image, new_w_izq, new_h_hi, current_pos+1, init_x, init_y);
		//-*
		//--
		rec_decomp(image, new_w_der, new_h_hi, current_pos+1, init_x + new_w_izq, init_y);
		//--
		//*-
		rec_decomp(image, new_w_izq, new_h_lo, current_pos+1, init_x, init_y + new_h_hi);
		//--
		//-*
		rec_decomp(image, new_w_der, new_h_lo, current_pos+1, init_x + new_w_izq, init_y + +new_h_hi);
	}
	else if (c == 'N') {
		current_pos = get_colours(image, current_pos+2, w, h, init_x, init_y);		//Muevo el puntero dos posiciones hasta donde esta guardado el valor del rojo, Voy llenando matrix acorde a lo que aparece en cuanto a colores.
	}
	else if (c == ' ') {
		rec_decomp(image, w, h, current_pos+1, init_x, init_y);
	}
}


unsigned char * Compresor::get_colours(unsigned char ** image, unsigned char *current_pos, unsigned int w, unsigned int h, unsigned int init_x, unsigned int init_y) {

	unsigned char RGB_T[4];			//arreglo con cada color y transparencia a partir del cual llenare TODOS los pixeles del cuadrante.
	int j = 0;
	bool received = false;
	bool finished_parsing = false;
	unsigned int colour = 0;
	uint i;					//aqu� me quedaran guardados los chars analizados para este bloque

	for ( i = 0; (i < 14) && (finished_parsing==false);  i++) {			//voy recorriendo el txt y voy cambiando mi posicion actual current_pos para luego devolverla.
		unsigned char c = current_pos[i];
		if ((c <= '9') && (c > '0')) {		//voy recibiendo los numeros de cada color segun vengan.
			received = true;
			colour = colour * 10 + (c-48);
		}
		else if (c == ' ') {
			if (received) {
				RGB_T[j] = colour;			//lleno el arreglo segun el color del txt.
				colour = 0;					//Reinicio el color
				j++;
			}
		}
		else if(j==3){
			RGB_T[3] = 0xff;				//completo para la transparencia.
			finished_parsing = true;
			break;
		}
	}
	current_pos += i; //Corro el puntero hacia el pr�ximo conjunto
	//lleno cada cuadrante.
	for ( i = init_y; i < init_y + h; i++)
		for (uint j = init_x * 4; j < (init_x + w * 4); j += 4)
		{
			image[i][j] = RGB_T[0];
			image[i][j + 1] = RGB_T[1];
			image[i][j + 2] = RGB_T[2];
			image[i][j + 3] = RGB_T[3];
		}

	return current_pos;		//devuelvo la posicion del txt en la que me encuentro ahora.
}


void Compresor::create_file(string name)
{
	string filename;
	string extension = ".eda";
	name.erase(name.end() - 4, name.end());
	filename += name + extension;

	this->filename = filename;
	std::ofstream outfile(filename);

	outfile.close();
}

template <typename t1> void Compresor::write_file(t1 a) {
	ofstream myfile;
	myfile.open(this->filename, ios::out | ios::app | ios::binary);
	myfile << a;
}
/*
void Compresor::write_file(char tobewritten) {
	ofstream myfile;
	myfile.open(this->filename, ios::out | ios::app | ios::binary);
	myfile << tobewritten;
}

void Compresor::write_file(uint tobewritten) {
	ofstream myfile;
	myfile.open(this->filename, ios::out | ios::app | ios::binary);
	myfile << tobewritten;
	myfile.close();

}
void Compresor::write_file(string tobewritten) {
	ofstream myfile;
	myfile.open(this->filename, ios::out | ios::app | ios::binary);
	myfile << tobewritten;
	myfile.close();

}*/



string Compresor::new_name(string my_image_path, string my_image_name) {

	string ext = ".png";
	string compre = "_decompress";
	string new_name;
	my_image_name.erase(my_image_name.end() - 4, my_image_name.end());

	new_name += my_image_path +'/'+ my_image_name + compre + ext;

	return new_name;
}

unsigned char * Compresor::allocate_file(image& my_image,uint * w, uint * h) {

	streampos size;
	char * memblock = NULL;
	uint32_t * mydimensions = NULL;

	ifstream file(this->complete_path, ios::in | ios::binary | ios::ate);
	if (file.is_open())
	{
		int i;
		size = file.tellg();
		memblock = new  char[size];
		file.seekg(0, ios::beg);
		file.read(memblock, size);
		file.close();

		cout << "the entire file content is in memory";

		*w = atoi(memblock + 1);//guardo los valores de w y h
		for ( i = 0; memblock[i] !=' '; i++)
		{

		}
		*h = atoi(memblock + ++i);
		

	}
	else cout << "Unable to open file";

	return (unsigned char *) (memblock+10); //Devuelvo el puntero donde empieza la codificaci�n, sin w y h
}