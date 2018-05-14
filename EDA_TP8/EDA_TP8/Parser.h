#pragma once
#include<iostream>
#include <string>

using namespace std;

enum { ERROR1 = -1, ERROR2 = -2, ERROR3 = -3 };
enum {COMPRESION, DESCOMPRESION};
const unsigned int NPARAMETERS = 0;
const unsigned int NKEYS =3 ;
const unsigned int NVALUES = 1;

typedef struct
{
	//char*  parameters[NPARAMETERS];
	char*  key[NKEYS];
	char*  value[NVALUES];

}parseData;

class Parser
{
public:
	Parser() { parseData.key[0] = (char*) "PATH"; parseData.key[1] = (char*) "MODO";  parseData.key[2] = (char*) "THRESHOLD"; error_fran = false; };
	~Parser();
	int Read(int argc, char *argv[]);

	string path;
	int modo;
	int threshold;
	bool getError();

private:
	void Do(char *key, char *value);
	parseData parseData;
	bool error_fran;
};

