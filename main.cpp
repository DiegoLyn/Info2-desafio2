#include<iostream>
#include "usuario.h"
#include "huesped.h"
#include "globales.h"
#include <fstream>
using namespace std;
void seccionComo() {
    bool control = true;
    while (control) {


        cout << endl << "--- BIENVENIDO A UDEASTAY ---" << endl;
        cout << endl;
        cout << "Usuario: ";
        getline(cin, usuario);

        cout << endl << "Contrasena: ";
        getline(cin, contrasena);
        Usuario p1(usuario, contrasena);

        string rutacredenciales = "Desafio2/anfitrion/usuario/" + usuario + ".txt";
        ifstream archivo(rutacredenciales);
        string resultado;
        getline(archivo, resultado);
        if (resultado == usuario) {
            p1.loginAnfitrion();
        } else {
            string rutacredenciales = "Desafio2/huesped/usuario/" + usuario + ".txt";
            ifstream archivo2(rutacredenciales);
            string resultado2;
            getline(archivo2, resultado2);
            if (resultado2 == usuario) {
                p1.loginHuesped();
            } else {
                cout << "Usuario o contraseña incorrectas" << endl;
            }
        }

        // Agrega opción para salir
        string opcionSalir;
        cout << "Deseas intentar otro usuario o salir? (s = salir, otro = continuar): ";
        getline(cin, opcionSalir);
        if (opcionSalir == "s" || opcionSalir == "S" || opcionSalir == "salir" || opcionSalir == "Salir") {
            control = false;
        }
    }
}

int main (int argc, char *argv[]) {

    seccionComo();


}
