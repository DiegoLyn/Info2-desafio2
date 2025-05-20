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
	contrasenaBase.close();
}

void Usuario::loginHuesped(){
	string desicion;
	short veces=0;
	
	cout <<"Bienvenido a Udeastay - Huesped"<<endl;
	cout <<endl;
	cout <<"1. Reservar alojamiento"<<endl;
	cout <<"2. Anular reserva"<<endl;
	
	cout << "Respuesta: ";
	getline(cin,desicion);
	bool control = false;
	while(!control){
		veces=veces+1;
		if(veces>=2){
			control = true;
		}
		if (desicion!="1"&&desicion!="2"){
			cout <<"Opcion invalida, te quedan "<<3-veces<<" intentos"<<endl;
			cout << "Respuesta: ";
			getline(cin,desicion);
		}
		if (desicion=="1"){
			cout<<"Ingresando a reservar...";
			control = true;
		}
		else if(desicion=="2"){
			cout<<"Ingresando a Eliminar reserva...";
			control = true;
		}
		
	}
	
	
}

void Usuario::loginAnfitrion(){
	string desicion;
	short veces=0;
	
	cout <<"Bienvenido a Udeastay - Anfitrion"<<endl;
	cout <<endl;
	cout <<"1. Anular reserva"<<endl;
	cout <<"2. Consultar reservaciones"<<endl;
	cout <<"3. Actualizar historico"<<endl;
	
	cout << "Respuesta: ";
	getline(cin,desicion);
	bool control = false;
	while(!control){
		veces=veces+1;
		if(veces>=2){
			control = true;
		}
		if (desicion!="1"&&desicion!="2"&&desicion!="3"){
			cout <<"Opcion invalida, te quedan "<<3-veces<<" intentos"<<endl;
			cout << "Respuesta: ";
			getline(cin,desicion);
		}
		if (desicion=="1"){
			cout<<"Ingresando a reservar...";
			control = true;
		}
		else if(desicion=="2"){
			cout<<"Ingresando a Eliminar reserva...";
			control = true;
		}
		else if(desicion=="3"){
			cout<<"Ingresando a actualizar historico...";
			control = true;
		}
		
	}
	
}


