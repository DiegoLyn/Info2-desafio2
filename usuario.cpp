#include <iostream>
#include "usuario.h"
#include <fstream>
#include <string>
using namespace std;

Usuario::Usuario(string _usuario, string _contrasena){
	usuario = _usuario;
	contrasena=_contrasena;
	
}

bool Usuario::validacionCredenciales(string usuario, string contrasena){
	string codigo;
	
	cout << "Ingresa tu codigo de usuario: ";
	getline(cin,codigo);
	
	string nombreArchivo = "Desafio2/huesped/usuario/"+codigo+".txt";
	
	ifstream usuarioBase(nombreArchivo);
	
	string linea;
	getline(usuarioBase,linea);
	
	cout << "esto hay en el archivo: "<< linea;
	
	usuarioBase.close();
	
}
