#include <iostream>
#include "anfitrion.h"
#include "herramientas.h"
#include <fstream>

#include <string>
#include <cctype>

#include <ctime>


using namespace std;



void Anfitrion::consultarReservaciones() {
    int numero = 1;
    bool control = true;
    int intentosFallidos = 0;
    bool algunaReservaImpresion = false;

    string admin;
    cout << "Ingresa nombre administrador: ";
    getline(cin, admin);

    while (control) {
        string identificador = to_string(numero);
        string rutacodigos = "Desafio2/reservas/anfitrionesReservas/" + admin + "/codigos/" + identificador + ".txt";

        ifstream codigos(rutacodigos);
        string id;
        if (getline(codigos, id)) {
            intentosFallidos = 0;

            string rutafecha = "Desafio2/reservas/anfitrionesReservas/" + admin + "/fecha/" + id + ".txt";
            string rutanoches = "Desafio2/reservas/anfitrionesReservas/" + admin + "/noches/" + id + ".txt";
            string rutaprecio = "Desafio2/reservas/anfitrionesReservas/" + admin + "/precio/" + id + ".txt";
            string rutamunicipio = "Desafio2/reservas/anfitrionesReservas/" + admin + "/municipio/" + id + ".txt";

            ifstream archivoFecha(rutafecha);
            ifstream archivoNoches(rutanoches);
            ifstream archivoPrecio(rutaprecio);
            ifstream archivoMunicipio(rutamunicipio);

            string lafecha, nronoches, elprecio, elmunicipio;

            if (getline(archivoFecha, lafecha)) {
                getline(archivoNoches, nronoches);
                getline(archivoPrecio, elprecio);
                getline(archivoMunicipio, elmunicipio);

                cout << endl << "--- Reserva " << id << " ---" << endl;
                cout << "Codigo: " << id
                     << " - Fecha: " << lafecha
                     << " - Municipio: " << elmunicipio
                     << " - Cantidad de noches: " << nronoches << " noches"
                     << " - Precio: " << Herramientas::formatearConPuntos(elprecio) << endl;
                algunaReservaImpresion = true;
            }

            numero++;  // Avanza siempre para evitar quedar atascado

        } else {
            intentosFallidos++;
            if (intentosFallidos >= 10) {

                control = false;
            } else {
                numero++;
            }
        }
    }
    if (algunaReservaImpresion==false) {
        cout << "No tienes reservas asociadas." << endl;
    }

}


void Anfitrion::actualizarHistorico() {
    string dia, mes, anio;
    cout << "Ingresa la fecha de corte (dia=6 mes=6 anio=2025)" << endl;
    cout << "Dia: "; getline(cin, dia);
    cout << "Mes: "; getline(cin, mes);
    cout << "Año: "; getline(cin, anio);

    string admin;
    cout<<"Ingresa nombre administrador: ";
    getline(cin,admin);

    string fechaCorte = dia  + mes + anio;

    int numero = 1;
    int intentosFallidos = 0;
    bool control = true;

    string rutaHistorico = "Desafio2/historico/historico.txt";
    ofstream guardarH(rutaHistorico, ios::app);
    if (!guardarH) {
        cout << "Error al abrir el archivo historico." << endl;
        return;
    }

    while (control) {
        string id = (numero < 10) ? "0" + to_string(numero) : to_string(numero);
        string rutafecha = "Desafio2/reservas/anfitrionesReservas/"+admin+"/fecha/" + id + ".txt";
        string rutacodigo = "Desafio2/reservas/anfitrionesReservas/"+admin+"/codigos/" + id + ".txt";
        string rutanoches = "Desafio2/reservas/anfitrionesReservas/"+admin+"/noches/" + id + ".txt";
        string rutaprecio = "Desafio2/reservas/anfitrionesReservas/"+admin+"/precio/" + id + ".txt";
        string rutamunicipio = "Desafio2/reservas/anfitrionesReservas/"+admin+"/municipio/" + id + ".txt";

        ifstream archivoFecha(rutafecha);


        string lafecha;
        if (getline(archivoFecha, lafecha)) {
            intentosFallidos = 0; // Reiniciar intentos


            string ide, nronoches, elprecio, elmunicipio;
            ifstream archivoCod(rutacodigo);
            ifstream archivoNoches(rutanoches);
            ifstream archivoPrecio(rutaprecio);
            ifstream archivoMunicipio(rutamunicipio) ;

            string rutafechaconpa = "Desafio2/reservas/anfitrionesReservas/"+admin+"/fechaComparar/" + id + ".txt";
            ifstream archivoComparar(rutamunicipio) ;
            string fechaComparar;
            getline(archivoComparar,fechaComparar);

            if (lafecha < fechaComparar) {


                getline(archivoCod, ide);
                getline(archivoNoches, nronoches);
                getline(archivoPrecio, elprecio);
                getline(archivoMunicipio, elmunicipio);

                // Escribir en historico
                guardarH << "Codigo: " << id
                         << " - Fecha: " << lafecha
                         << " - Municipio: " << elmunicipio
                         << " - Noches: " << nronoches
                         << " - Precio: " << Herramientas::formatearConPuntos(elprecio)
                         << endl;
                ofstream archivoCodigoG(rutacodigo);
                ofstream archivoNochesG(rutanoches);
                ofstream archivoPrecioG(rutaprecio);
                ofstream archivoMunicipioG(rutamunicipio) ;
                ofstream archivoFechaG(rutafecha);

                archivoMunicipioG<<"";
                archivoCodigoG<<"";
                archivoNochesG<<"";
                archivoPrecioG<<"";
                archivoNochesG<<"";


            }
            numero++; // Muy importante: avanzar al siguiente número
        } else {
            intentosFallidos++;
            if (intentosFallidos >= 10) control = false; // Terminar si no hay más archivos
            else numero++;
        }
    }

    guardarH.close();
    cout << "Actualizacion de historico completada." << endl;
}


void Anfitrion::anularReservaAnfitrion(){
    string confirmar;
    string reservaEliminar;
    string reservamostrarantesdelete;
    string usuarioReserva;
    string admin;


    cout<<"Ingresa el codigo de la reserva: ";
    getline(cin,reservaEliminar);

    cout<<"Ingresa el usuario asociado a esa reserva: ";
    getline(cin,usuarioReserva);

    cout<<"Ingresa nombre administrador: ";
    getline(cin,admin);

    string rutaeliminar = "Desafio2/reservas/usuariosconreservas/"+usuarioReserva+"/"+ reservaEliminar+ ".txt";

    string rutacodigos = "Desafio2/reservas/anfitrionesReservas/"+admin+"/fecha/" + reservaEliminar + ".txt";
    ifstream reservaencontrada(rutaeliminar);
    getline(reservaencontrada,reservamostrarantesdelete);

    ifstream reservaencontradaenAnfitrion(rutacodigos);

    if(reservaencontradaenAnfitrion){
        if(reservaencontrada&&!reservamostrarantesdelete.empty()){
            cout<<endl <<"Reserva a eliminar: "<<endl;
            cout <<reservamostrarantesdelete<<endl;
            cout <<"Estas seguro: (s/n): ";
            getline(cin,confirmar);
            if(confirmar== "s"||confirmar== "S"||confirmar== "si"||confirmar== "Si"){
                ofstream guardarcambios(rutaeliminar);
                guardarcambios<<"";

                cout <<endl<<"Reserva eliminada con exito"<<endl;

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

}
