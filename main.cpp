#include<iostream>
#include "usuario.h"
using namespace std;

int main (int argc, char *argv[]) {
	Usuario p1("diego","12345");
	bool ella = p1.validacionCredenciales();
	if (ella){
		cout <<"Holaaa";
	}
	else{
		cout <<"No coincidieron";
	}
	return 0;
}

