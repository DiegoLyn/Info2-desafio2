#ifndef USUARIO_H
#define USUARIO_H

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
	void reservar();
	
	
};
#endif
