#ifndef INGRESO_H
#define INGRESO_H

#include <iostream>
using namespace std;

class Usuario{
private:
	string usuario;
	string contrasena;
public:
	Usuario(string,string);
	bool validacionCredenciales();
	void loginHuesped();
	void loginAnfitrion();
	
};
#endif
