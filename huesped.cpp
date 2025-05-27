#include <iostream>
#include "huesped.h"
#include <fstream>
#include <string>
using namespace std;


void Huesped::anularReserva(){
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
