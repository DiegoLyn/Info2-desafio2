#include <iostream>
#include "anfitrion.h"
#include "herramientas.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <filesystem>
#include <algorithm> 
#include <ctime>

using namespace std;

void Anfitrion::consultarReservaciones() {
    int numero = 1;
    bool control = true;
    int intentosFallidos = 0;  // Contador de intentos fallidos

    string admin;
    cout<<"Ingresa nombre administrador: ";
    getline(cin,admin);

    while (control) {
        string identificador = to_string(numero);
        string rutacodigos = "Desafio2/reservas/anfitrionesReservas/"+admin+"/codigos/" + identificador + ".txt";

        ifstream codigos(rutacodigos);
        string id;
        if (getline(codigos, id)) {  // Si el archivo existe y contiene algo
            intentosFallidos = 0;  // Reinicia los fallos porque se encontró uno válido

            string rutafecha = "Desafio2/reservas/anfitrionesReservas/admin/fecha/" + id + ".txt";
            string rutanoches = "Desafio2/reservas/anfitrionesReservas/admin/noches/" + id + ".txt";
            string rutaprecio = "Desafio2/reservas/anfitrionesReservas/admin/precio/" + id + ".txt";
            string rutamunicipio = "Desafio2/reservas/anfitrionesReservas/admin/municipio/" + id + ".txt";

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

            numero++;  // Avanza al siguiente código
        } else {
            intentosFallidos++;
            if (intentosFallidos >= 10) {
                control = false;  // Si lleva 10 intentos fallidos seguidos, salir del bucle
            } else {
                numero++;  // Seguir probando el siguiente número
            }
        }
    }
}




namespace fs = std::filesystem;

void Anfitrion::actualizarHistorico() {
    string fechaCorte;
    cout << "Ingrese la fecha de corte (YYYY-MM-DD): ";
    cin >> fechaCorte;

    // Asegúrate de crear la carpeta si no existe
    string rutaHistorico = "Desafio2/reservas/historico/";
    if (!fs::exists(rutaHistorico)) {
        fs::create_directories(rutaHistorico);
    }

    int numero = 1;
    while (true) {
        string id = to_string(numero);
        string rutacodigo = "Desafio2/reservas/codigos/" + id + ".txt";

        ifstream archivoCodigo(rutacodigo);
        if (!archivoCodigo.is_open()) {
            break;  // No hay más reservaciones
        }

        string codigo;
        getline(archivoCodigo, codigo);
        archivoCodigo.close();

        // Leer la fecha de la reserva
        string rutaFecha = "Desafio2/reservas/fecha/" + codigo + ".txt";
        ifstream archivoFecha(rutaFecha);
        if (!archivoFecha.is_open()) {
            numero++;
            continue;
        }

        string fechaReserva;
        getline(archivoFecha, fechaReserva);
        archivoFecha.close();

        if (fechaReserva < fechaCorte) {
            // Mover archivos al histórico
            string rutaOrigenes[] = {
                "Desafio2/reservas/codigos/" + id + ".txt",
                "Desafio2/reservas/fecha/" + codigo + ".txt",
                "Desafio2/reservas/noches/" + codigo + ".txt",
                "Desafio2/reservas/precio/" + codigo + ".txt",
                "Desafio2/reservas/municipio/" + codigo + ".txt"
            };
            for (const string& origen : rutaOrigenes) {
                if (fs::exists(origen)) {
                    string destino = rutaHistorico + fs::path(origen).filename().string();
                    fs::rename(origen, destino);
                }
            }
        }

        numero++;
    }

    // Mostrar el rango habilitado
    int year, month, day;
    sscanf(fechaCorte.c_str(), "%d-%d-%d", &year, &month, &day);
    month += 12;
    year += (month - 1) / 12;
    month = (month - 1) % 12 + 1;
    printf("Reservaciones futuras habilitadas hasta: %04d-%02d-%02d\n", year, month, day);
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
