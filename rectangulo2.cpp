#include "rectangulo2.h"
#include <iostream>

using namespace std;

Rectangulo::Rectangulo(float _ancho, float _largo){
	ancho = _ancho;
	largo = _largo;
}

void Rectangulo::perimetro(){
	float _perimetro;
	_perimetro = (2*ancho)+(2*largo);
	
	cout << "Este es el perimetro: "<<_perimetro;
}
