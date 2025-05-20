#include <iostream>
#include "usuario.h"
#include <fstream>
#include <string>
using namespace std;

Usuario::Usuario(string _usuario, string _contrasena){
	usuario = _usuario;
	contrasena=_contrasena;
	
}

bool Usuario::validacionCredenciales(){
	string codigo;
	
	cout << "Ingresa tu codigo de usuario: ";
	getline(cin,codigo);
	
	string nombreArchivoUsuario = "Desafio2/huesped/usuario/"+codigo+".txt";
	
	ifstream usuarioBase(nombreArchivoUsuario);
	
	string usuariodb;
	getline(usuarioBase,usuariodb);
	
	//Recuperando la constraseña de la base de datos
	
	string nombreArchivoContrasena = "Desafio2/huesped/contrasena/"+codigo+".txt";
	
	ifstream contrasenaBase(nombreArchivoContrasena);
	
	string contrasenadb;
	getline(contrasenaBase,contrasenadb);
	
	if (usuariodb==usuario && contrasenadb == contrasena){
		return true;
	}
	else{
		return false;
	}
	
	usuarioBase.close();
	
}
