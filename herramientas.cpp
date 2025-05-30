#include <iostream>
#include "herramientas.h"
#include "usuario.h"
#include "estadisticas.h"
#include "globales.h"
#include <filesystem>
#include <random>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <algorithm> 
#include <ctime>

namespace fs = std::filesystem;
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



string Herramientas::nombreDiaSemana(int semanaday) {
	string dias[] = {"domingo","lunes","martes","miercoles","jueves","viernes","sabado"};
	if (semanaday < 0 || semanaday > 6) return "";
	return dias[semanaday];
}

bool Herramientas::comprobarSitieneReservas(string usuario, string id){
    string idExistente=id+".txt";
    string datosBd;
    string rutaarchivo = "Desafio2/reservas/usuariosconreservas/"+ usuario+ "/"+id+".txt";
    ifstream archivo(rutaarchivo);
    getline(archivo,datosBd);

    if(datosBd.empty()){
        return false;
    }
    else{
        return true;
    }
}


string Herramientas::calcularFechaFin(string fechaInicio, int noches) {
	istringstream iss(fechaInicio);
	int dia, anio;
	string mesTexto;
	iss >> dia >> mesTexto >> anio;
	
	int mes = mesANumero(mesTexto);
	if (mes == 0) return "Mes inv�lido";
	
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
	if (numMes == 0) return ""; // Fecha inv�lida
	
	// Asegurar formato de 2 d�gitos para d�a y mes
	if (dia.length() == 1) dia = "0" + dia;
	string strMes = (numMes < 10) ? "0" + to_string(numMes) : to_string(numMes);
	
	return anio + strMes + dia; // "20250531"
}

string Herramientas::generarCodigoReserva(){
	static random_device rd;
	static mt19937 gen(rd());
	uniform_int_distribution<> dist(1000, 9999); // N�meros de 4 cifras
	
	int numero = dist(gen);
	return "RSV" + to_string(numero);
}

void Herramientas::guardarReservausuario(string id,string usuario){

    //estas rutas son para mostrar en el recibo, van a buscar la reserva asociada con ese admmin
    string rutafecha = "Desafio2/reservas/anfitrionesReservas/admin/fecha/" + id + ".txt";
    string rutanoches = "Desafio2/reservas/anfitrionesReservas/admin/noches/" + id + ".txt";
    string rutaprecio = "Desafio2/reservas/anfitrionesReservas/admin/precio/" + id + ".txt";
    string rutamunicipio = "Desafio2/reservas/anfitrionesReservas/admin/municipio/" + id + ".txt";
	
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

    int nronochesentero = 0;
    try {
        nronochesentero = stoi(nronoches);
    } catch (const invalid_argument& e) {
        cerr << "Error: No es un numero valido: " << nronoches << endl;
        return;
    } catch (const out_of_range& e) {
        cerr << "Error: numero de noches fuera de rango: " << endl;
        return;
    }


    bool verdad = Herramientas::comprobarSitieneReservas(usuario,id);

    if(verdad==false){
        string doc;
        cout <<"Ingresa tu documento: ";
        getline(cin,doc);

        string metodoPago;
        cout <<"Ingresa el metodo de pago (1.PSE 2.TCredito): ";
        getline(cin,metodoPago);
        if(metodoPago=="1"){
            metodoPago="PSE";
        }
        else if(metodoPago=="2"){
            metodoPago="TCredito";
        }
        else{
            metodoPago="No aplica";
        }

        string monto;
        cout <<"Ingresa el monto: ";
        getline(cin,monto);

        string anotacion;
        cout <<"Anadir anotacion (1000 caracteres): ";
        getline(cin,anotacion);


        if (anotacion.length() > 1000) {
            cout << "Error: El texto excede el l�mite de 1000 caracteres." << endl;
        } else {
            string rutaGAnotacion = "Desafio2/reservas/anfitrionesReservas/admin/anotacionesUsers/"+id+".txt";
            ofstream archivoAn(rutaGAnotacion);
            archivoAn<<anotacion;
            archivoAn.close();

            cout <<endl<< "--- Reservacion exitosa ---"<<endl;
            cout << "Codigo de la reserva: "<< Herramientas::generarCodigoReserva()<<endl;
            cout <<"Nombre: "<<usuario<<endl;
            cout <<"Documento: "<<doc<<endl;
            cout <<"Metodo de pago: "<<metodoPago<<endl;
            cout <<"Monto: "<<monto<<endl;
            cout <<"Fecha de Pago: "<<lafecha<<endl;
            cout <<"Codigo del alojamiento: "<<id<<endl;
            cout << "fecha inicio: "<<lafecha<<endl;
            cout << "fecha fin: "<<Herramientas::calcularFechaFin(lafecha,nronochesentero)<<endl;


        }


        string rutanewcarpeta= "Desafio2/reservas/usuariosconreservas/"+ usuario+"/";

        string rutaguardar = "Desafio2/reservas/usuariosconreservas/"+ usuario+ "/"+id+".txt";
        try {
            if (fs::create_directory(rutanewcarpeta)) {
                cout << "Carpeta creada exitosamente: "<< endl;
            }
        } catch (fs::filesystem_error& e) {
            cerr << "Error al crear carpeta: " << e.what() << endl;
        }

        ofstream reservaUsuario(rutaguardar,ios::app);
        reservaUsuario << "Codigo: " << id
                       << " - Fecha: " << lafecha // aca se estan usando las rutas  de arriba
                       << " - Municipio: " << elmunicipio
                       << " - Cantidad de noches: " << nronoches << " noches"
                       << " - Precio: " << Herramientas::formatearConPuntos(elprecio) << endl;
        reservaUsuario.close();
    }else{
        cout <<"Ya tienes esa reserva"<<endl;
    }


}

void Herramientas::buscarReservasPorFiltros() {
    string fechaUsuario, municipioUsuario, nochesUsuario;

    cout <<endl<< "Ingresa la fecha a partir de la cual deseas ver reservas (ej: 15 Mayo 2025): ";
    getline(cin, fechaUsuario);
    string claveUsuario = convertirAFechaClave(fechaUsuario);
    if (claveUsuario.empty()) {
        cout << "Fecha no v�lida o formato incorrecto." << endl;
        return;
    }

    cout << "Ingresa el municipio a buscar: ";
    getline(cin, municipioUsuario);
    if (!municipioUsuario.empty()) {
        municipioUsuario[0] = toupper(municipioUsuario[0]);
    }

    cout << "Ingresa el n�mero de noches a buscar: ";
    getline(cin, nochesUsuario);
    // Ajustar formato para comparar, por si en archivo hay "3 noches"
    string nochesConTexto = nochesUsuario + " noches";

    bool encontrada = false;

    for (int i = 1; i <= 99; ++i) {
        string id = (i < 10) ? "0" + to_string(i) : to_string(i);

        // Leer fecha
        string rutaFecha = "Desafio2/reservas/anfitrionesReservas/admin/fecha/" + id + ".txt";
        ifstream archivoFecha(rutaFecha);
        if (!archivoFecha.is_open()) continue;
        string fechaArchivo;
        getline(archivoFecha, fechaArchivo);
        archivoFecha.close();

        string claveActual = convertirAFechaClave(fechaArchivo);
        if (claveActual.empty() || claveActual < claveUsuario) {
            continue; // fecha menor a la buscada
        }

        // Leer municipio
        string rutaMunicipio = "Desafio2/reservas/anfitrionesReservas/admin/municipio/" + id + ".txt";
        ifstream archivoMunicipio(rutaMunicipio);
        if (!archivoMunicipio.is_open()) continue;
        string municipioArchivo;
        getline(archivoMunicipio, municipioArchivo);
        archivoMunicipio.close();
        if (municipioArchivo != municipioUsuario) {
            continue; // municipio no coincide
        }

        // Leer noches
        string rutaNoches = "Desafio2/reservas/anfitrionesReservas/admin/noches/" + id + ".txt";
        ifstream archivoNoches(rutaNoches);
        if (!archivoNoches.is_open()) continue;
        string nochesArchivo;
        getline(archivoNoches, nochesArchivo);
        archivoNoches.close();

        // comparar noches: puede ser "3" o "3 noches"
        if (nochesArchivo != nochesUsuario && nochesArchivo != nochesConTexto) {
            continue; // noches no coincide
        }

        // Leer precio
        string rutaPrecio = "Desafio2/reservas/anfitrionesReservas/admin/precio/" + id + ".txt";
        ifstream archivoPrecio(rutaPrecio);
        if (!archivoPrecio.is_open()) continue;
        string precioArchivo;
        getline(archivoPrecio, precioArchivo);
        archivoPrecio.close();
        //nombre
        string rutaNombre = "Desafio2/reservas/anfitrionesReservas/admin/nombre/" + id + ".txt";
        ifstream archivoNombre(rutaNombre);
        if (!archivoNombre.is_open()) continue;
        string nombreArchivo;
        getline(archivoNombre, nombreArchivo);
        archivoNombre.close();

        //Departamento

        string rutadepar = "Desafio2/reservas/anfitrionesReservas/admin/departamento/" + id + ".txt";
        ifstream archivoDepar(rutadepar);
        if (!archivoDepar.is_open()) continue;
        string deparArchivo;
        getline(archivoDepar, deparArchivo);
        archivoDepar.close();

        //direccion

        string rutadirec = "Desafio2/reservas/anfitrionesReservas/admin/direccion/" + id + ".txt";
        ifstream archivoDirec(rutadirec);
        if (!archivoDirec.is_open()) continue;
        string direcArchivo;
        getline(archivoDirec, direcArchivo);
        archivoDirec.close();

        //amenidades

        string rutaAmeni = "Desafio2/reservas/anfitrionesReservas/admin/amenidades/" + id + ".txt";
        ifstream archivoAmeni(rutaAmeni);
        if (!archivoAmeni.is_open()) continue;
        string ameniArchivo;
        getline(archivoAmeni, ameniArchivo);
        archivoAmeni.close();

        // Mostrar reserva que cumple criterios
        cout <<endl<< "Nombre: " << nombreArchivo
             << " - Codigo: " << id
             << " - Fecha: " << fechaArchivo
             << " - Departamento: " << deparArchivo
             << " - Municipio: " << municipioArchivo
             << endl<<" - Direccion: " << direcArchivo
             << " - Cantidad de noches: " << nochesArchivo
             << " - Amenidades: " << ameniArchivo
             << " - Precio: " << Herramientas::formatearConPuntos(precioArchivo) << endl;

        encontrada = true;
    }

    if (!encontrada) {
        cout << "No se encontraron reservas que coincidan con los criterios ingresados." << endl;
        return;
    }

    cout << "\nIngresa el codigo a reservar: ";
    string codigoReservar;
    getline(cin, codigoReservar);

    Herramientas::guardarReservausuario(codigoReservar, usuario);
}

void Herramientas::buscarReservasCodigo(){
    string idUsuario;
    cout << "Ingresa el Id: ";
    getline(cin, idUsuario);
    string rutaid = "Desafio2/reservas/anfitrionesReservas/admin/noches/" + idUsuario + ".txt";
    ifstream archivoNoches(rutaid);



    if (archivoNoches.is_open()) {
        // Si hay coincidencia, leemos tambi�n los dem�s archivos de esa reserva
        string rutafecha = "Desafio2/reservas/anfitrionesReservas/admin/fecha/" + idUsuario + ".txt";
        string rutamunicipio = "Desafio2/reservas/anfitrionesReservas/admin/municipio/" + idUsuario + ".txt";
        string rutaprecio = "Desafio2/reservas/anfitrionesReservas/admin/precio/" + idUsuario + ".txt";

        ifstream archivoFecha(rutafecha);
        ifstream archivoMunicipio(rutamunicipio);
        ifstream archivoPrecio(rutaprecio);

        string lafecha, municipio, elprecio;
        getline(archivoFecha, lafecha);
        getline(archivoMunicipio, municipio);
        getline(archivoPrecio, elprecio);
        string lasnoches;
        getline(archivoNoches, lasnoches);

        //nombre
        string rutaNombre = "Desafio2/reservas/anfitrionesReservas/admin/nombre/" + idUsuario + ".txt";
        ifstream archivoNombre(rutaNombre);
        string nombreArchivo;
        getline(archivoNombre, nombreArchivo);
        archivoNombre.close();

        //Departamento

        string rutadepar = "Desafio2/reservas/anfitrionesReservas/admin/departamento/" + idUsuario + ".txt";
        ifstream archivoDepar(rutadepar);
        string deparArchivo;
        getline(archivoDepar, deparArchivo);
        archivoDepar.close();

        //direccion

        string rutadirec = "Desafio2/reservas/anfitrionesReservas/admin/direccion/" + idUsuario + ".txt";
        ifstream archivoDirec(rutadirec);
        string direcArchivo;
        getline(archivoDirec, direcArchivo);
        archivoDirec.close();

        //amenidades

        string rutaAmeni = "Desafio2/reservas/anfitrionesReservas/admin/amenidades/" + idUsuario + ".txt";
        ifstream archivoAmeni(rutaAmeni);
        string ameniArchivo;
        getline(archivoAmeni, ameniArchivo);
        archivoAmeni.close();

        // Mostrar reserva que cumple criterios
        cout <<endl<< "Nombre: " << nombreArchivo
             << " - Codigo: " << idUsuario
             << " - Fecha: " << lafecha
             << " - Departamento: " << deparArchivo
             << " - Municipio: " << municipio
             <<endl<< " - Direccion: " << direcArchivo
             << " - Cantidad de noches: " << lasnoches
             << " - Amenidades: " << ameniArchivo
             << " - Precio: " << Herramientas::formatearConPuntos(elprecio) << endl;


        cout <<endl;

        cout <<"Ingresa el codigo a reservar: ";
        string codigoreservarusuario;
        getline(cin,codigoreservarusuario);

        Herramientas::guardarReservausuario(codigoreservarusuario,usuario);
    }
    else{
        cout <<"No se encontro archivo con ese id"<<endl;
    }


}

void Herramientas::buscarPorPrecioNoche(){
    string precioStr;
    cout << "Ingresa el precio maximo de una noche: ";
    getline(cin, precioStr);

    string precioLimpioUsuario = "";
    for(char c : precioStr) {
        if (isdigit(c)) {
            precioLimpioUsuario += c;
        }
    }

    int precioMaximo;
    try {
        precioMaximo = stoi(precioLimpioUsuario);  // Convertimos a int
    } catch (invalid_argument& e) {
        cout << "Error: El precio ingresado no es v�lido." << endl;
        return;
    }

    int numero = 1;
    bool control = true;
    int intentosFallidos = 0;  // Contador de intentos fallidos

    while (control) {

        string id = to_string(numero);
        string rutacodigo = "Desafio2/reservas/anfitrionesReservas/admin/codigos/" + id + ".txt";
        ifstream losids(rutacodigo);
        string ide;
        if (getline(losids, ide)) {  // Si el archivo existe y contiene algo
            intentosFallidos = 0;  // Reinicia los fallos porque se encontr� uno v�lido

            string rutafecha = "Desafio2/reservas/anfitrionesReservas/admin/fecha/" + ide + ".txt";
            string rutanoches = "Desafio2/reservas/anfitrionesReservas/admin/noches/" + ide + ".txt";
            string rutaprecio = "Desafio2/reservas/anfitrionesReservas/admin/precio/" + ide + ".txt";
            string rutamunicipio = "Desafio2/reservas/anfitrionesReservas/admin/municipio/" + ide + ".txt";

            ifstream archivoFecha(rutafecha);
            ifstream archivoNoches(rutanoches);
            ifstream archivoPrecio(rutaprecio);
            ifstream archivoMunicipio(rutamunicipio);

            string lafecha, nronoches, elprecioStr, elmunicipio;
            getline(archivoFecha, lafecha);
            getline(archivoNoches, nronoches);
            getline(archivoPrecio, elprecioStr);
            getline(archivoMunicipio, elmunicipio);

            // Si el precio tiene puntos, eliminarlos antes de convertir a int
            string precioLimpio = "";
            for(char c : elprecioStr) {

                if (isdigit(c)) {
                    precioLimpio += c;
                }
            }

            int precioActual;
            try {
                precioActual = stoi(precioLimpio);
            } catch (invalid_argument& e) {

                numero++;
                continue;
            }
            string puntuacionA;
            string rutaPuntuacion = "Desafio2/anfitrion/usuario/adminPuntuacion.txt";
            ifstream  pA (rutaPuntuacion);
            getline(pA,puntuacionA);
            if(precioActual <= precioMaximo){
                //nombre
                string rutaNombre = "Desafio2/reservas/anfitrionesReservas/admin/nombre/" + ide + ".txt";
                ifstream archivoNombre(rutaNombre);
                string nombreArchivo;
                getline(archivoNombre, nombreArchivo);
                archivoNombre.close();

                //Departamento

                string rutadepar = "Desafio2/reservas/anfitrionesReservas/admin/departamento/" + ide + ".txt";
                ifstream archivoDepar(rutadepar);
                string deparArchivo;
                getline(archivoDepar, deparArchivo);
                archivoDepar.close();

                //direccion

                string rutadirec = "Desafio2/reservas/anfitrionesReservas/admin/direccion/" + ide + ".txt";
                ifstream archivoDirec(rutadirec);
                string direcArchivo;
                getline(archivoDirec, direcArchivo);
                archivoDirec.close();

                //amenidades

                string rutaAmeni = "Desafio2/reservas/anfitrionesReservas/admin/amenidades/" + ide + ".txt";
                ifstream archivoAmeni(rutaAmeni);
                string ameniArchivo;
                getline(archivoAmeni, ameniArchivo);
                archivoAmeni.close();

                // Mostrar reserva que cumple criterios
                cout <<endl<< "Nombre: " << nombreArchivo
                     << " - Codigo: " << ide
                     << " - Fecha: " << lafecha
                     << " - Departamento: " << deparArchivo
                     << " - Municipio: " << elmunicipio
                     <<endl<< " - Direccion: " << direcArchivo
                     << " - Cantidad de noches: " << nronoches
                     << " - Amenidades: " << ameniArchivo
                     << " - Precio: " << Herramientas::formatearConPuntos(elprecioStr) << endl;


            }

            numero++;


        } else {
            intentosFallidos++;
            if (intentosFallidos >= 10) {
                control = false;  // Si lleva 10 intentos fallidos seguidos, salir del bucle
            } else {
                numero++;  // Seguir probando el siguiente n�mero
            }
        }

    }

    cout << endl;
    cout << "Ingresa el codigo a reservar: ";
    string codigoreservarusuario;
    getline(cin, codigoreservarusuario);  // No necesitas cin.ignore() aqu� porque getline anterior ya consumi� el '\n'

    Herramientas::guardarReservausuario(codigoreservarusuario, usuario);


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

void Herramientas::puntuacionMinimaAnfitrion(float puntuacionHuesped){
    string puntosAnfitrion;

    string rutaPuntosAnfitrion = "Desafio2/anfitrion/usuario/adminPuntuacion.txt";

    ifstream archivopuntuacionAnfitrion(rutaPuntosAnfitrion);
    getline(archivopuntuacionAnfitrion,puntosAnfitrion);

    float puntosFloat = stof(puntosAnfitrion);


    if(puntosFloat>=puntuacionHuesped){
        int numero = 1;
        bool control = true;
        int intentosFallidos = 0;  // Contador de intentos fallidos


        while (control) {

            string identificador = to_string(numero);
            string rutacodigos = "Desafio2/reservas/anfitrionesReservas/admin/codigos/" + identificador + ".txt";

            ifstream codigos(rutacodigos);
            string id;
            if (getline(codigos, id)) {  // Si el archivo existe y contiene algo
                intentosFallidos = 0;  // Reinicia los fallos porque se encontr� uno v�lido

                string rutaFecha = "Desafio2/reservas/anfitrionesReservas/admin/fecha/" + id + ".txt";
                ifstream archivoFecha(rutaFecha);
                if (!archivoFecha.is_open()) continue;
                string fechaArchivo;
                getline(archivoFecha, fechaArchivo);
                archivoFecha.close();



                // Leer municipio
                string rutaMunicipio = "Desafio2/reservas/anfitrionesReservas/admin/municipio/" + id + ".txt";
                ifstream archivoMunicipio(rutaMunicipio);
                if (!archivoMunicipio.is_open()) continue;
                string municipioArchivo;
                getline(archivoMunicipio, municipioArchivo);
                archivoMunicipio.close();


                // Leer noches
                string rutaNoches = "Desafio2/reservas/anfitrionesReservas/admin/noches/" + id + ".txt";
                ifstream archivoNoches(rutaNoches);
                if (!archivoNoches.is_open()) continue;
                string nochesArchivo;
                getline(archivoNoches, nochesArchivo);
                archivoNoches.close();


                // Leer precio
                string rutaPrecio = "Desafio2/reservas/anfitrionesReservas/admin/precio/" + id + ".txt";
                ifstream archivoPrecio(rutaPrecio);
                if (!archivoPrecio.is_open()) continue;
                string precioArchivo;
                getline(archivoPrecio, precioArchivo);
                archivoPrecio.close();
                //nombre
                string rutaNombre = "Desafio2/reservas/anfitrionesReservas/admin/nombre/" + id + ".txt";
                ifstream archivoNombre(rutaNombre);
                if (!archivoNombre.is_open()) continue;
                string nombreArchivo;
                getline(archivoNombre, nombreArchivo);
                archivoNombre.close();

                //Departamento

                string rutadepar = "Desafio2/reservas/anfitrionesReservas/admin/departamento/" + id + ".txt";
                ifstream archivoDepar(rutadepar);
                if (!archivoDepar.is_open()) continue;
                string deparArchivo;
                getline(archivoDepar, deparArchivo);
                archivoDepar.close();

                //direccion

                string rutadirec = "Desafio2/reservas/anfitrionesReservas/admin/direccion/" + id + ".txt";
                ifstream archivoDirec(rutadirec);
                if (!archivoDirec.is_open()) continue;
                string direcArchivo;
                getline(archivoDirec, direcArchivo);
                archivoDirec.close();

                //amenidades

                string rutaAmeni = "Desafio2/reservas/anfitrionesReservas/admin/amenidades/" + id + ".txt";
                ifstream archivoAmeni(rutaAmeni);
                if (!archivoAmeni.is_open()) continue;
                string ameniArchivo;
                getline(archivoAmeni, ameniArchivo);
                archivoAmeni.close();

                // Mostrar reserva que cumple criterios
                cout <<endl<< "Nombre: " << nombreArchivo
                     << " - Codigo: " << id
                     << " - Fecha: " << fechaArchivo
                     << " - Departamento: " << deparArchivo
                     << " - Municipio: " << municipioArchivo
                     <<endl<< " - Direccion: " << direcArchivo
                     << " - Cantidad de noches: " << nochesArchivo
                     << " - Amenidades: " << ameniArchivo
                     << " - Precio: " << Herramientas::formatearConPuntos(precioArchivo) << endl;
                numero++;  // Avanza al siguiente c�digo
            } else {
                intentosFallidos++;
                if (intentosFallidos >= 10) {
                    control = false;  // Si lleva 10 intentos fallidos seguidos, salir del bucle
                } else {
                    numero++;  // Seguir probando el siguiente n�mero
                }
            }
        }
        //cin.ignore();

        cout <<endl;

        cout <<"Ingresa el codigo a reservar: ";
        string codigoreservarusuario;

        getline(cin,codigoreservarusuario);
        Herramientas::guardarReservausuario(codigoreservarusuario,usuario);

    }else{
        cout << "El anfitrion no cumple con la puntuacion minima requerida (" << puntuacionHuesped << ")." << endl;
    }

}


