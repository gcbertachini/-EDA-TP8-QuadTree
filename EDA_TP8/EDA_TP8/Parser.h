#pragma once
#include<iostream>
#include <string>

using namespace std;

enum { ERROR1 = -1, ERROR2 = -2, ERROR3 = -3 };
typedef enum {COMPRESION, DESCOMPRESION} modo_t;
const unsigned int NPARAMETERS = 0;
const unsigned int NKEYS =2 ;
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
	Parser() { parseData.key[0] = (char*) "PATH";  parseData.key[1] = (char*) "THRESHOLD"; error_do = false; };
	~Parser();
	int Read(int argc, char *argv[]);

	string path;
	modo_t modo;
	int threshold;
	bool getError();

private:
	void Do(char *key, char *value);
	parseData parseData;
	bool error_do;
};

