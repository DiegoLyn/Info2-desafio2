#ifndef HERRAMIENTAS_H
#define HERRAMIENTAS_H

#include <iostream>
using namespace std;

class Herramientas{
public:
	static void buscarReservasPorMunicipio();
	static void buscarReservasPorNoches();
	static void buscarReservasDesdeFecha();
	static void buscarReservasCodigo();
	
	static string calcularFechaFin(string, int );
	static string nombreDiaSemana(int );
	static string generarCodigoReserva();
	static void guardarReservausuario(string,string);
	static string aMinusculas(string);
	static string formatearConPuntos(string numero);
	static string convertirAFechaClave(string);
	static int mesANumero(string);

};
#endif
