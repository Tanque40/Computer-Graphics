#include <stdio.h>
#include <stdlib.h>

typedef struct direccion DIR;
typedef struct empleado EMP;

struct direccion{
	char calle[30];
	int numero;
	int codigo_postal;
	char ciudad[30];
	char pais[30];
};
struct empleado{
	int id_empleado;
	char nombre_empleado[30];
	char apellido_empleado[30];
	DIR direccion_empleado;
	float salario;
	char gender;
	char estado_civil;
	int numero_hijos;
	DIR *siguiente_empleado;
};

EMP *crear_empleado();
DIR nueva_direccion();
int insertar_empleado( EMP* lista_empleados );
int borrar_empleado( int id_empleado_to_delete, EMP *lista_empleados );
int num_empleados( EMP *lista_empleados );
char *mostrar_empleado(int id_empleado_to_show, EMP *lista_empleados);

int main(){

	EMP empleados;
	EMP *apt_empleados;
	empleados.siguiente_empleado = NULL;

	apt_empleados = &empleados;
	

	return 0;
}

int insertar_empleado( EMP *lista_empleados ){
	EMP *current_employee, *nuevo_empleado;
	
	current_employee = lista_empleados;

	nuevo_empleado = crear_empleado();
	if( nuevo_empleado == NULL ){
		return 0;
	}

	if( current_employee->siguiente_empleado == NULL ){

		current_employee->siguiente_empleado = nuevo_empleado;

	} else {

		EMP *next_employee = current_employee->siguiente_empleado;
		if( nuevo_empleado->id_empleado > next_employee->id_empleado ){

			next_employee->siguiente_empleado = next_employee;

		} else{

			EMP *temp;

			temp = next_employee;
			current_employee->siguiente_empleado = nuevo_empleado;
			current_employee = current_employee->siguiente_empleado;
			current_employee->siguiente_empleado = temp;

		}

	}

	return 1;

}

EMP *crear_empleado(){

	EMP nuevo_empleado;

	EMP *apt_nuevo_empleado;

	apt_nuevo_empleado = (EMP *)malloc(sizeof(EMP));
	if (apt_nuevo_empleado == NULL){
		return apt_nuevo_empleado; // ! Aquí hay que lanzar una excepción
	}

	

	printf("Ingresa la clave del empleado: ");
	scanf_s("%d", &nuevo_empleado.id_empleado);

	printf("Ingresa el nombre del empleado: ");
	scanf_s("%s", nuevo_empleado.nombre_empleado, 30);

	printf("Ingresa los apellidos del empleado: ");
	scanf_s("%s", nuevo_empleado.apellido_empleado, 30);

	nuevo_empleado.direccion_empleado = nueva_direccion();

	printf("Ingresa el estado civil del empleado: (s) Soltero - (c) Casado - (u) Union Libre - (n) Prefiero no decir");
	scanf_s("%s", &nuevo_empleado.estado_civil, 1);

	printf( "Número de hijos del empleado: " );
	scanf_s( "%d", &nuevo_empleado.numero_hijos );

	printf("Ingresa el genero del empleado: (m) Masculino - (f) Femenino - (n) Prefiero no decir");
	scanf_s("%s", &nuevo_empleado.gender, 1);

	printf("Ingresa el salario del empleado: $");
	scanf_s("%f", &nuevo_empleado.salario);

	nuevo_empleado.siguiente_empleado == NULL;

	apt_nuevo_empleado = &nuevo_empleado;

	return apt_nuevo_empleado;
}

int borrar_empleado( int id_empleado_to_delete, EMP *lista_empleados ){
	EMP *current_employee;
	
	current_employee = lista_empleados;
	if( current_employee->siguiente_empleado == NULL ){
		
		return 0;

	} else{

		int flag = 0;
		EMP *next_employee;

		next_employee = current_employee->siguiente_empleado;

		while( next_employee->siguiente_empleado != NULL ){

			if( next_employee->id_empleado == id_empleado_to_delete ){

				current_employee->siguiente_empleado = next_employee->siguiente_empleado;
				flag = 1;

			} else{

				current_employee = next_employee;
				next_employee = current_employee->siguiente_empleado;

			}

		}

		if( !flag || next_employee->siguiente_empleado == NULL ){

			if( next_employee->id_empleado == id_empleado_to_delete ){

				current_employee->siguiente_empleado = NULL;

			} else {

				return 0;

			}

		}

	}

	return 1;
}

int num_empleados( EMP *lista_empleados ){
	EMP *current_employee = lista_empleados;
	EMP	*temp;
	int cont = 0;
	
	while( current_employee->siguiente_empleado != NULL ){

		cont++;

		current_employee = current_employee->siguiente_empleado;

	}

	return cont;

}

char *mostrar_empleado( int id_empleado_to_show, EMP *lista_empleados ){

	char message[ 300 ];
	int flag = 0;
	EMP *current_employee = lista_empleados;

	while( !flag && current_employee->siguiente_empleado == NULL ){

	}
}


DIR nueva_direccion(){

	DIR direccion;

	printf( "Calle: " );
	scanf_s( "%s", direccion.calle, 30);

	printf( "Numero: " );
	scanf_s( "%d", &direccion.numero );

	printf( "Ciudad: " );
	scanf_s( "%s", direccion.ciudad, 30 );

	printf( "Codigo Postal: " );
	scanf_s( "%d", &direccion.codigo_postal );

	printf( "Pais: " );
	scanf_s( "%s", direccion.pais, 30 );


	return direccion;

}