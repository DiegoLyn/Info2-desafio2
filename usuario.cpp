#include <iostream>
#include "usuario.h"
#include "huesped.h"
#include <fstream>
#include <string>
#include <cctype>
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

string Usuario::formatearConPuntos(string numero) {
	/*
	Esta funcion da formato al saldo al momento de mostralo al usuario
	cuando va a consultar o retirar.
	Agrega puntos despues de tres numeros y retorna el saldo con puntos de mil
	*/
	
	string resultado = "";
	int contador = 0;
	
	for (int i = numero.length() - 1; i >= 0; i--) {
		resultado = numero[i] + resultado;
		contador++;
		
		if (contador == 3 && i != 0) {
			resultado = '.' + resultado;
			contador = 0;
		}
	}
	
	return resultado;
}

void Usuario::buscarReservasPorMunicipio() {
	string palabra;
	cout << "Ingresa el municipio a buscar: ";
	getline(cin, palabra);
	
	// Asegurarse de capitalizar la primera letra como en los archivos
	if (!palabra.empty()) {
		palabra[0] = toupper(palabra[0]);
	}
	
	bool encontrada = false;
	
	// Asumimos que hay hasta 99 archivos, puedes ajustar el límite si lo sabes
	for (int i = 1; i <= 99; ++i) {
		string id = (i < 10) ? "0" + to_string(i) : to_string(i);
		
		string rutamunicipio = "Desafio2/reservas/municipio/" + id + ".txt";
		ifstream archivoMunicipio(rutamunicipio);
		if (!archivoMunicipio.is_open()) {
			continue;
		}
		
		string elmunicipio;
		getline(archivoMunicipio, elmunicipio);
		archivoMunicipio.close();
		
		if (elmunicipio == palabra) {
			// Si hay coincidencia, leemos también los demás archivos de esa reserva
			string rutafecha = "Desafio2/reservas/fecha/" + id + ".txt";
			string rutanoches = "Desafio2/reservas/noches/" + id + ".txt";
			string rutaprecio = "Desafio2/reservas/precio/" + id + ".txt";
			
			ifstream archivoFecha(rutafecha);
			ifstream archivoNoches(rutanoches);
			ifstream archivoPrecio(rutaprecio);
			
			string lafecha, nronoches, elprecio;
			getline(archivoFecha, lafecha);
			getline(archivoNoches, nronoches);
			getline(archivoPrecio, elprecio);
			
			cout << "Codigo: " << id
				<< " - Fecha: " << lafecha
				<< " - Municipio: " << elmunicipio
				<< " - Cantidad de noches: " << nronoches << " noches"
				<< " - Precio: " << formatearConPuntos(elprecio) << endl;
			
			encontrada = true;
		}
	}
	
	if (!encontrada) {
		cout << "No se encontraron reservas en el municipio '" << palabra << "'." << endl;
	}
}

void Usuario::buscarReservasPorNoches(){
	string dias;
	cout << "Ingresa el numero de dias a buscar: ";
	getline(cin, dias);
	
	
	
	
	bool encontrada = false;
	
	// Asumimos que hay hasta 99 archivos, puedes ajustar el límite si lo sabes
	for (int i = 1; i <= 99; ++i) {
		string id = (i < 10) ? "0" + to_string(i) : to_string(i);
		
		string rutadias = "Desafio2/reservas/noches/" + id + ".txt";
		ifstream archivoNoches(rutadias);
		if (!archivoNoches.is_open()) {
			continue;
		}
		
		string lasnoches;
		getline(archivoNoches, lasnoches);
		archivoNoches.close();
		
		string numeroynoches=dias+" noches";
		
		if (lasnoches == dias || lasnoches==numeroynoches) {
			// Si hay coincidencia, leemos también los demás archivos de esa reserva
			string rutafecha = "Desafio2/reservas/fecha/" + id + ".txt";
			string rutamunicipio = "Desafio2/reservas/municipio/" + id + ".txt";
			string rutaprecio = "Desafio2/reservas/precio/" + id + ".txt";
			
			ifstream archivoFecha(rutafecha);
			ifstream archivoMunicipio(rutamunicipio);
			ifstream archivoPrecio(rutaprecio);
			
			string lafecha, municipio, elprecio;
			getline(archivoFecha, lafecha);
			getline(archivoMunicipio, municipio);
			getline(archivoPrecio, elprecio);
			
			cout << "Codigo: " << id
				<< " - Fecha: " << lafecha
				<< " - Municipio: " << municipio
				<< " - Cantidad de noches: " << dias << " noches"
				<< " - Precio: " << formatearConPuntos(elprecio) << endl;
			
			encontrada = true;
		}
	}
	
	if (!encontrada) {
		cout << "No se encontraron reservas en el municipio '" << dias << "'." << endl;
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
	
	cout << "Respuesta: ";
	getline(cin,desicion);
	bool control = false;
	while(!control){
		veces=veces+1;
		if(veces>=2){
			control = true;
		}
		if (desicion!="1"&&desicion!="2"&&desicion!="3"&&desicion!="4"){
			cout <<"Opcion invalida, te quedan "<<3-veces<<" intentos"<<endl;
			cout << "Respuesta: ";
			getline(cin,desicion);
		}
		if (desicion=="1"){
			cout<<"Ingresa la fecha: ";
			getline(cin,fechausuario);
			control = true;
		}
		else if(desicion=="2"){
			buscarReservasPorMunicipio();
			control = true;
		}
		else if(desicion=="3"){
			buscarReservasPorNoches();
			control = true;
		}
		else if(desicion=="4"){
			//precio
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





