#include<iostream>
#include "usuario.h"
using namespace std;

int main (int argc, char *argv[]) {
	Usuario p1("diego","123");
	p1.validacionCredenciales("diego","123");
	return 0;
}

