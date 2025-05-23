#include <iostream>
#include "herramientas.h"
#include "usuario.h"
#include <random>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <algorithm> 
#include <ctime>

using namespace std;

int Herramientas::mesANumero(string mes) {
	if (mes == "Enero") return 1;
	if (mes == "Febrero") return 2;
	if (mes == "Marzo") return 3;
	if (mes == "Abril") return 4;
	if (mes == "Mayo") return 5;
	if (mes == "Junio") return 6;
	if (mes == "Julio") return 7;
	if (mes == "Agosto") return 8;
	if (mes == "Septiembre") return 9;
	if (mes == "Octubre") return 10;
	if (mes == "Noviembre") return 11;
	if (mes == "Diciembre") return 12;
	return 0;
}

void Herramientas::anularReserva(){
	string confirmar;
	string reservaEliminar;
	string reservamostrarantesdelete;
	cout<<"Ingresa el codigo de la reserva: ";
	getline(cin,reservaEliminar);
	
	string rutaeliminar = "Desafio2/reservas/usuariosconreservas/diego/"+ reservaEliminar+ ".txt";
	
	ifstream reservaencontrada(rutaeliminar);
	getline(reservaencontrada,reservamostrarantesdelete);
	if(reservaencontrada&&!reservamostrarantesdelete.empty()){
		cout<<endl <<"Reserva a eliminar: "<<endl;
		cout <<reservamostrarantesdelete<<endl;
		cout <<"Estas seguro: (s/n): ";
		getline(cin,confirmar);
		if(confirmar== "s"||confirmar== "S"||confirmar== "si"||confirmar== "Si"){
			ofstream guardarcambios(rutaeliminar);
			guardarcambios<<"";
			
			cout <<endl<<"Reserva eliminada con exito";
			
		}
		else{
			cout<<"Abordando opcion...";
			reservaencontrada.close();
		}
	}
	else{
		cout<<"Reserva "<<reservaEliminar<<" no encontrada";
		
	}

}

string Herramientas::nombreDiaSemana(int semanaday) {
	string dias[] = {"domingo","lunes","martes","miercoles","jueves","viernes","sabado"};
	if (semanaday < 0 || semanaday > 6) return "";
	return dias[semanaday];
}

string Herramientas::calcularFechaFin(string fechaInicio, int noches) {
	istringstream iss(fechaInicio);
	int dia, anio;
	string mesTexto;
	iss >> dia >> mesTexto >> anio;
	
	int mes = mesANumero(mesTexto);
	if (mes == 0) return "Mes inválido";
	
	tm fecha = {};
	fecha.tm_mday = dia + noches;
	fecha.tm_mon = mes - 1;
	fecha.tm_year = anio - 1900;
	mktime(&fecha);
	
	string mesFinal = mesTexto;
	for (char& c : mesFinal) c = tolower(c);
	
	string diaSemana = nombreDiaSemana(fecha.tm_wday);
	
	return diaSemana + ", " + to_string(fecha.tm_mday) + " de " + mesFinal + " del " + to_string(fecha.tm_year + 1900);
}


string Herramientas::convertirAFechaClave(string fechaTexto) {
	// Ejemplo de entrada: "31 Mayo 2025"
	istringstream ss(fechaTexto);
	string dia, mes, anio;
	ss >> dia >> mes >> anio;
	
	int numMes = mesANumero(mes);
	if (numMes == 0) return ""; // Fecha inválida
	
	// Asegurar formato de 2 dígitos para día y mes
	if (dia.length() == 1) dia = "0" + dia;
	string strMes = (numMes < 10) ? "0" + to_string(numMes) : to_string(numMes);
	
	return anio + strMes + dia; // "20250531"
}

string Herramientas::generarCodigoReserva(){
	static random_device rd;
	static mt19937 gen(rd());
	uniform_int_distribution<> dist(1000, 9999); // Números de 4 cifras
	
	int numero = dist(gen);
	return "RSV" + to_string(numero);
}

void Herramientas::guardarReservausuario(string id,string usuario){
	string rutafecha = "Desafio2/reservas/fecha/" + id + ".txt";
	string rutanoches = "Desafio2/reservas/noches/" + id + ".txt";
	string rutaprecio = "Desafio2/reservas/precio/" + id + ".txt";
	string rutamunicipio = "Desafio2/reservas/municipio/" + id + ".txt";
	
	ifstream archivoMunicipio(rutamunicipio);
	ifstream archivoFecha(rutafecha);
	ifstream archivoNoches(rutanoches);
	ifstream archivoPrecio(rutaprecio);
	
	string lafecha, nronoches, elprecio;
	getline(archivoFecha, lafecha);
	getline(archivoNoches, nronoches);
	getline(archivoPrecio, elprecio);
	string elmunicipio;
	getline(archivoMunicipio, elmunicipio);
	
	int nronochesentero = stoi(nronoches);
	string nombreusuarioguardar = "diego";
	
	cout <<endl<< "--- Reservacion exitosa ---"<<endl;
	cout << "Codigo de la reserva: "<< Herramientas::generarCodigoReserva()<<endl;
	cout <<"Nombre: "<<endl;
	cout <<"Codigo del alojamiento: "<<id<<endl;
	cout << "fecha inicio: "<<lafecha<<endl;
	cout << "fecha fin: "<<Herramientas::calcularFechaFin(lafecha,nronochesentero)<<endl;
	
	string rutaguardar = "Desafio2/reservas/usuariosconreservas/diego/"+ id+ ".txt";
	
	ofstream reservaUsuario(rutaguardar,ios::app);
	reservaUsuario << "Codigo: " << id
		<< " - Fecha: " << lafecha
		<< " - Municipio: " << elmunicipio
		<< " - Cantidad de noches: " << nronoches << " noches"
		<< " - Precio: " << Herramientas::formatearConPuntos(elprecio) << endl;
		reservaUsuario.close();
	
}

void Herramientas::buscarReservasPorMunicipio() {
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
				<< " - Precio: " << Herramientas::formatearConPuntos(elprecio) << endl;
			
			encontrada = true;
			
		}
	}
	
	if (!encontrada) {
		cout << "No se encontraron reservas en el municipio '" << palabra << "'." << endl;
	}
	
	cout <<endl;
	
	cout <<"Ingresa el codigo a reservar: ";
	string codigoreservarusuario;
	getline(cin,codigoreservarusuario);
	
	Herramientas::guardarReservausuario(codigoreservarusuario,"diego");
}

void Herramientas::buscarReservasPorNoches(){
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
				<< " - Precio: " << Herramientas::formatearConPuntos(elprecio) << endl;
			
			cout <<endl;
			
			cout <<"Ingresa el codigo a reservar: ";
			string codigoreservarusuario;
			getline(cin,codigoreservarusuario);
			
			Herramientas::guardarReservausuario(codigoreservarusuario,"diego");
			encontrada = true;
			
		}
	}
	
	if (!encontrada) {
		cout << "No se encontraron reservas de '" << dias << "'." << endl;
	}
	
}


void Herramientas::buscarReservasDesdeFecha() {
	string fechaUsuario;
	cout << "Ingresa la fecha a partir de la cual deseas ver reservas (ej: 15 Mayo 2025): ";
	getline(cin, fechaUsuario);
	
	string claveUsuario = convertirAFechaClave(fechaUsuario);
	if (claveUsuario.empty()) {
		cout << "Fecha no encontrada. Asegúrate de usar el formato correcto." << endl;
		return;
	}
	
	bool encontrada = false;
	
	for (int i = 1; i <= 99; ++i) {
		string id = (i < 10) ? "0" + to_string(i) : to_string(i);
		
		string rutaFecha = "Desafio2/reservas/fecha/" + id + ".txt";
		ifstream archivoFecha(rutaFecha);
		if (!archivoFecha.is_open()) continue;
		
		string fechaArchivo;
		getline(archivoFecha, fechaArchivo);
		archivoFecha.close();
		
		string claveActual = convertirAFechaClave(fechaArchivo);
		
		if (!claveActual.empty() && claveActual >= claveUsuario) {
			// Leer archivos asociados
			string rutaMunicipio = "Desafio2/reservas/municipio/" + id + ".txt";
			string rutaNoches   = "Desafio2/reservas/noches/"   + id + ".txt";
			string rutaPrecio   = "Desafio2/reservas/precio/"   + id + ".txt";
			
			ifstream archivoMunicipio(rutaMunicipio);
			ifstream archivoNoches(rutaNoches);
			ifstream archivoPrecio(rutaPrecio);
			
			string elmunicipio, nronoches, elprecio;
			getline(archivoMunicipio, elmunicipio);
			getline(archivoNoches, nronoches);
			getline(archivoPrecio, elprecio);
			
			cout << "Codigo: " << id
				<< " - Fecha: " << fechaArchivo
				<< " - Municipio: " << elmunicipio
				<< " - Cantidad de noches: " << nronoches << " noches"
				<< " - Precio: " << formatearConPuntos(elprecio) << endl;
			
			
			encontrada = true;
			
		}
	}
	
	if (!encontrada) {
		cout << "No se encontraron reservas a partir de la fecha '" << fechaUsuario << "'." << endl;
	}
	cout <<endl;
	
	cout <<"Ingresa el codigo a reservar: ";
	string codigoreservarusuario;
	getline(cin,codigoreservarusuario);
	
	Herramientas::guardarReservausuario(codigoreservarusuario,"diego");
}

void Herramientas::buscarReservasCodigo(){
	string idUsuario;
	cout << "Ingresa el Id: ";
	getline(cin, idUsuario);
	string rutaid = "Desafio2/reservas/noches/" + idUsuario + ".txt";
	ifstream archivoNoches(rutaid);
	

	
	if (archivoNoches.is_open()) {
		// Si hay coincidencia, leemos también los demás archivos de esa reserva
		string rutafecha = "Desafio2/reservas/fecha/" + idUsuario + ".txt";
		string rutamunicipio = "Desafio2/reservas/municipio/" + idUsuario + ".txt";
		string rutaprecio = "Desafio2/reservas/precio/" + idUsuario + ".txt";
		
		ifstream archivoFecha(rutafecha);
		ifstream archivoMunicipio(rutamunicipio);
		ifstream archivoPrecio(rutaprecio);
		
		string lafecha, municipio, elprecio;
		getline(archivoFecha, lafecha);
		getline(archivoMunicipio, municipio);
		getline(archivoPrecio, elprecio);
		string lasnoches;
		getline(archivoNoches, lasnoches);
		
		cout << "Codigo: " << idUsuario
			<< " - Fecha: " << lafecha
			<< " - Municipio: " << municipio
			<< " - Cantidad de noches: " << lasnoches << " noches"
			<< " - Precio: " << Herramientas::formatearConPuntos(elprecio) << endl;
		
		
	}
	else{
		cout <<"No se encontro archivo con ese id";
	}
	
	cout <<endl;
	
	cout <<"Ingresa el codigo a reservar: ";
	string codigoreservarusuario;
	getline(cin,codigoreservarusuario);
	
	Herramientas::guardarReservausuario(codigoreservarusuario,"diego");
}

	
	


string Herramientas::aMinusculas(string texto) {
	transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
	return texto;
}


string Herramientas::formatearConPuntos(string numero) {
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

