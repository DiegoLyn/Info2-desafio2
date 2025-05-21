#include<iostream>
#include "usuario.h"
#include "huesped.h"
using namespace std;

int main (int argc, char *argv[]) {
	
	
	Usuario p1("diego","12345");
	

	string desicion;
	short veces=0;
	
	cout << "--- BIENVENIDO A UDEASTAY ---"<<endl;
	cout<<endl;
	cout <<"1. Ingresar como huesped"<<endl;
	cout <<"2. Ingresar como anfitrion"<<endl;
	
	cout << "Respuesta: ";
	getline(cin,desicion);
	bool control = false;
	while(!control){
		veces=veces+1;
		if(veces>=2){
			control = true;
		}
		if (desicion!="1"&&desicion!="2"){
			cout <<"Opcion invalida, te quedan "<<3-veces<<" intentos"<<endl;
			cout << "Respuesta: ";
			getline(cin,desicion);
		}
		if (desicion=="1"){
			p1.loginHuesped();
			
			control = true;
		}
		else if(desicion=="2"){
			p1.loginAnfitrion();
			control = true;
		}
	}	
}

//	bool ella = p1.validacionCredenciales();
//	if (ella){
//		cout <<"Holaaa";
//	}
//	else{
//		cout <<"No coincidieron";
//	}
//	return 0;
//}

