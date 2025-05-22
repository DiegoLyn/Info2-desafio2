#ifndef HERRAMIENTAS_H
#define HERRAMIENTAS_H

#include <iostream>
using namespace std;

class Herramientas{
public:
	static void buscarReservasPorMunicipio();
	static void buscarReservasPorNoches();
	static void buscarReservasDesdeFecha();
	static string aMinusculas(string);
	static string formatearConPuntos(string numero);
	static string convertirAFechaClave(string);
	static int mesANumero(string);

};
#endif
