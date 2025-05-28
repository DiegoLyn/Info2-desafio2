#include <iostream>
#include "usuario.h"
#include "anfitrion.h"
#include "huesped.h"
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

void Usuario::loginHuesped() {
    bool app = true;

    while (app) {
        cout << endl << "Bienvenido a Udeastay - Huesped" << endl << endl;
        cout << "1. Reservar alojamiento" << endl;
        cout << "2. Anular reserva" << endl;
        cout << "3. Salir" << endl;

        string desicion;
        short intentos = 0;
        bool opcionValida = false;

        while (!opcionValida && intentos < 3) {
            cout << "Respuesta: ";
            getline(cin, desicion);
            intentos++;

            if (desicion == "1") {
                cout << "Ingresando a reservar..." << endl;
                reservar();
                opcionValida = true;
            }
            else if (desicion == "2") {
                Huesped::anularReservaHuesped();
                opcionValida = true;
            }
            else if (desicion == "3") {
                cout << "Saliendo..." << endl;
                app = false;
                opcionValida = true;
            }
            else {
                cout << "Opcion invalida, te quedan " << 3 - intentos << " intentos" << endl;
                if (intentos == 3) {
                    cout << "Se agotaron los intentos. Regresando al menu principal." << endl;
                }
            }
        }
    }
}

void Usuario::loginAnfitrion(){
    bool app = true;
    while(app){
        string desicion;
        short veces=0;

        cout <<endl<<"Bienvenido a Udeastay - Anfitrion"<<endl;
        cout <<endl;
        cout <<"1. Anular reserva"<<endl;
        cout <<"2. Consultar reservaciones"<<endl;
        cout <<"3. Actualizar historico"<<endl;
        cout <<"4. Salir"<<endl;

        cout << "Respuesta: ";
        getline(cin,desicion);
        bool control = false;
        while(!control){
            veces=veces+1;
            if(veces>=2){
                control = true;
            }

            if (desicion=="1"){
                Anfitrion::anularReservaAnfitrion();

                control = true;
            }
            else if(desicion=="2"){
                Anfitrion::consultarReservaciones();
                control = true;
            }
            else if(desicion=="3"){
                Anfitrion::actualizarHistorico();
                control = true;
            }
            else if(desicion=="4"){
                cout<<"Saliendo..."<<endl;
                app=false;
                control = true;
            }
            else {
                cout << "Opcion invalida, te quedan " << 3 - veces << " intentos" << endl;
                if (veces == 3) {
                    cout << "Se agotaron los intentos. Regresando al menu principal." << endl;
                }
            }
        }

    }
}



void Usuario::reservar(){
	string fechausuario;
	string municipiousuario;
	string preciousuario;
	string desicion;
	short veces=0;
	
    cout <<endl<< "Buscar reservacion a partir de: "<<endl;
    cout <<"1. Fecha, Municipio y cantidad de noches"<<endl;
    cout <<"2. Precio"<<endl;
    cout <<"3. Puntuacion minima del anfitrion"<<endl;
    cout <<"4. Id"<<endl;
	
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
            Herramientas::buscarReservasPorFiltros();
			control = true;
		}

        else if(desicion=="2"){
			//precio
			control = true;
		}
        else if(desicion=="3"){
            //puntuacion del anfitrion
            float puntuacion;
            cout <<"Ingresa la puntuacion (Ej:4.5): ";
            cin>>puntuacion;

            Herramientas::puntuacionMinimaAnfitrion(puntuacion);
            control = true;
        }
        else if(desicion=="4"){
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





