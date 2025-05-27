#include <iostream>
#include "anfitrion.h"
#include "herramientas.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <algorithm> 
#include <ctime>

using namespace std;

void Anfitrion::consultarReservaciones() {
	int numero = 1;
	bool control = true;
	
	while(control) {
		string identificador = to_string(numero);
		string rutacodigos = "Desafio2/reservas/codigos/" + identificador + ".txt";
		
		ifstream codigos(rutacodigos);
		string id;
		if (getline(codigos, id)) {  // Si el archivo existe y contiene algo
			
			string rutafecha = "Desafio2/reservas/fecha/" + id + ".txt";
			string rutanoches = "Desafio2/reservas/noches/" + id + ".txt";
			string rutaprecio = "Desafio2/reservas/precio/" + id + ".txt";
			string rutamunicipio = "Desafio2/reservas/municipio/" + id + ".txt";
			
			ifstream archivoFecha(rutafecha);
			ifstream archivoNoches(rutanoches);
			ifstream archivoPrecio(rutaprecio);
			ifstream archivoMunicipio(rutamunicipio);
			
			string lafecha, nronoches, elprecio, elmunicipio;
			getline(archivoFecha, lafecha);
			getline(archivoNoches, nronoches);
			getline(archivoPrecio, elprecio);
			getline(archivoMunicipio, elmunicipio);
			
			cout << endl << "--- Reserva " << id << " ---" << endl;
			cout << "Codigo: " << id
				<< " - Fecha: " << lafecha
				<< " - Municipio: " << elmunicipio
				<< " - Cantidad de noches: " << nronoches << " noches"
				<< " - Precio: " << Herramientas::formatearConPuntos(elprecio) << endl;
			
			numero++;  // Pasa al siguiente código
		} else {
			control = false;  // No hay más archivos, sal del bucle
		}
	}
}
