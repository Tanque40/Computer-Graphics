#include "Nomina.h"
#include <iostream>

Nomina::Nomina(){

	NumEmpleados = 0;

}

Nomina::~Nomina(){

	ListaEmpleados = NULL;

}

Empleado *Nomina::crear_empleado(){
	std::string Nombre;
	std::string Apellidos;
	int Numero_Identificacion;
	Direccion *Direccion_Empleado;
	float Salario;
	// (M) Masculino, (F) Femenino, (O) Otro.
	char Genero;
	// (C) Casado, (U) Unión Libre, (S) Soltero, (D) Divorciado, (V) Viudo, (O) Otro.
	char Estado_Civil;
	int Numero_Hijos;

	std::cout << "Ingresa Numero de Identificacion: " << std::endl;
	std::cin >> Numero_Identificacion;
	std::cout << "Ingresa Nombre: " << std::endl;
	std::cin >> Nombre;
	std::cout << "Ingresa Apellidos: " << std::endl;
	std::cin >> Apellidos;

	Direccion_Empleado = Create_Direccion();

	std::cout << "Ingresa Salario: " << std::endl;
	std::cin >> Salario;
	std::cout << "Ingresa Genero (M) Masculino, (F) Femenino, (O) Otro: " << std::endl;
	std::cin >> Genero;
	std::cout << "Ingresa Estado Civil (C) Casado, (U) Unión Libre, (S) Soltero, (D) Divorciado, (V) Viudo, (O) Otro: " << std::endl;
	std::cin >> Estado_Civil;
	std::cout << "Ingresa Numero de Hijos: " << std::endl;
	std::cin >> Numero_Hijos;

	Empleado emp( Nombre, Apellidos, Numero_Identificacion, Direccion_Empleado, Salario, Genero, Estado_Civil, Numero_Hijos );
	
	return &emp;	
}

int Nomina::insertar_empelado(){
	Empleado *Empleado_A_Insertar = crear_empleado();

	if( ListaEmpleados == NULL ){

		ListaEmpleados = Empleado_A_Insertar;
		return 1;

	} else {



	}

	return 0;
}

int Nomina::borrar_empleado( int Id_Empleado ){
	return 0;
}

int Nomina::num_empleados(){
	return 0;
}

std::string Nomina::mostrar_empleado( int Id_Empleado ){
	return std::string();
}

std::string Nomina::To_String(){
	return std::string();
}

Direccion *Nomina::Create_Direccion(){

	std::string Calle;
	int NumeroExterno;
	int CodigoPostal;
	std::string Ciudad;
	std::string Pais;

	std::cout << "Introduzca Calle:" << std::endl;
	std::cin >> Calle;

	std::cout << "Introduzca Numero Externo:" << std::endl;
	std::cin >> NumeroExterno;

	std::cout << "Introduzca Codigo Postal:" << std::endl;
	std::cin >> CodigoPostal;

	std::cout << "Introduzca Ciudad:" << std::endl;
	std::cin >> Ciudad;

	std::cout << "Introduzca Pais:" << std::endl;
	std::cin >> Pais;

	Direccion dir( Calle, NumeroExterno, CodigoPostal, Ciudad, Pais );

	return &dir;

}
