#include <iostream>
#include "usuario.h"

#include "herramientas.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <algorithm> 
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
			cout<<"Ingresando a reservar..."<<endl;
			reservar();
			
			control = true;
		}
		else if(desicion=="2"){
			cout<<"Ingresando a anular reserva...";
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
			cout<<"Ingresando a anular reservar...";
			
			control = true;
		}
		else if(desicion=="2"){
			cout<<"Ingresando a consultar reserva..."<<endl;
			control = true;
		}
		else if(desicion=="3"){
			cout<<"Ingresando a actualizar historico...";
			control = true;
		}
		
	}
	
}


void Usuario::reservar(){
	string fechausuario;
	string municipiousuario;
	string preciousuario;
	string desicion;
	short veces=0;
	
	cout << "Buscar reservacion a partir de: "<<endl;
	cout <<"1. Fecha"<<endl;
	cout <<"2. Municipio"<<endl;
	cout <<"3. Cantidad de noches"<<endl;
	cout <<"4. Precio"<<endl;
	cout <<"5. Id"<<endl;
	
	cout << "Respuesta: ";
	getline(cin,desicion);
	bool control = false;
	while(!control){
		veces=veces+1;
		if(veces>=2){
			control = true;
		}
		if (desicion!="1"&&desicion!="2"&&desicion!="3"&&desicion!="4"&&desicion!="5"){
			cout <<"Opcion invalida, te quedan "<<3-veces<<" intentos"<<endl;
			cout << "Respuesta: ";
			getline(cin,desicion);
		}
		if (desicion=="1"){
			Herramientas::buscarReservasDesdeFecha();
			control = true;
		}
		else if(desicion=="2"){
			Herramientas::buscarReservasPorMunicipio();
			control = true;
		}
		else if(desicion=="3"){
			Herramientas::buscarReservasPorNoches();
			control = true;
		}
		else if(desicion=="4"){
			//precio
			control = true;
		}
		else if(desicion=="5"){
			Herramientas::buscarReservasCodigo();
			control = true;
		}
		
		
	}
	string rutafecha = "Desafio2/reservas/fecha/01.txt";
	ifstream fecha(rutafecha);
	string lafecha;
	getline(fecha,lafecha);
	
	string rutamunicipio = "Desafio2/reservas/municipio/01.txt";
	ifstream municipio(rutamunicipio);
	string elmunicipio;
	getline(municipio,elmunicipio);
	
	
	string rutanoches = "Desafio2/reservas/noches/01.txt";
	ifstream noche(rutanoches);
	string nronoches;
	getline(noche,nronoches);
	
	string rutaprecio = "Desafio2/reservas/precio/01.txt";
	ifstream precio(rutaprecio);
	string elprecio;
	getline(precio,elprecio);
	
	
	
//	cout <<endl;
//	cout << "Reservaciones disponibles: "<<endl;
//	cout <<endl;
	
}





