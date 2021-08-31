#include <stdio.h>
#include <stdlib.h>

typedef struct direccion DIR;
typedef struct empleado EMP;

struct direccion {
    char calle[30];
    int numero;
    int codigo_postal;
    char ciudad[30];
    char pais[30];
};
struct empleado {
    int id_empleado;
    char nombre_empleado[30];
    char apellido_empleado[30];
    DIR direccion_empleado;
    float salario;
    char gender;
    char estado_civil;
    int numero_hijos;
    EMP *siguiente_empleado;
};

EMP *crear_empleado();
DIR nueva_direccion();
int insertar_empleado(EMP *lista_empleados);
int borrar_empleado(int id_empleado_to_delete, EMP *lista_empleados);
int num_empleados(EMP *lista_empleados);
char *mostrar_empleado(int id_empleado_to_show, EMP *lista_empleados);
char *mostrar_direccion(EMP *empleado);
char *los_empleados(EMP *lista_empleados);

int main() {
    EMP empleados;
    EMP *apt_empleados;
    empleados.siguiente_empleado = NULL;

    apt_empleados = &empleados;

    return 0;
}

int insertar_empleado(EMP *lista_empleados) {
    EMP *current_employee, *nuevo_empleado;

    current_employee = lista_empleados;

    nuevo_empleado = crear_empleado();
    if (nuevo_empleado == NULL) {
        return 0;
    }

    if (current_employee->siguiente_empleado == NULL) {
        current_employee->siguiente_empleado = nuevo_empleado;
    } else {
        EMP *next_employee = current_employee->siguiente_empleado;

        while (nuevo_empleado->id_empleado > next_employee->id_empleado) {
            current_employee = next_employee;
            next_employee = current_employee;
        }

        EMP *temp;

        temp = next_employee;
        current_employee->siguiente_empleado = nuevo_empleado;
        current_employee = current_employee->siguiente_empleado;
        current_employee->siguiente_empleado = temp;
    }

    return 1;
}

EMP *crear_empleado() {
    EMP nuevo_empleado;

    EMP *apt_nuevo_empleado;

    apt_nuevo_empleado = (EMP *)malloc(sizeof(EMP));
    if (apt_nuevo_empleado == NULL) {
        return apt_nuevo_empleado;  // ! Aquí hay que lanzar una excepción
    }

    printf("Ingresa la clave del empleado: ");
    scanf("%d", &nuevo_empleado.id_empleado);

    printf("Ingresa el nombre del empleado: ");
    scanf("%s", nuevo_empleado.nombre_empleado);

    printf("Ingresa los apellidos del empleado: ");
    scanf("%s", nuevo_empleado.apellido_empleado);

    nuevo_empleado.direccion_empleado = nueva_direccion();

    printf("Ingresa el estado civil del empleado: (s) Soltero - (c) Casado - (u) Union Libre - (n) Prefiero no decir");
    scanf("%s", &nuevo_empleado.estado_civil, 1);

    printf("Número de hijos del empleado: ");
    scanf("%d", &nuevo_empleado.numero_hijos);

    printf("Ingresa el genero del empleado: (m) Masculino - (f) Femenino - (n) Prefiero no decir");
    scanf("%s", &nuevo_empleado.gender);

    printf("Ingresa el salario del empleado: $");
    scanf("%f", &nuevo_empleado.salario);

    nuevo_empleado.siguiente_empleado == NULL;

    apt_nuevo_empleado = &nuevo_empleado;

    return apt_nuevo_empleado;
}

int borrar_empleado(int id_empleado_to_delete, EMP *lista_empleados) {
    EMP *current_employee;

    current_employee = lista_empleados;
    if (current_employee->siguiente_empleado == NULL) {
        return 0;
    } else {
        int flag = 0;
        EMP *next_employee;

        next_employee = current_employee->siguiente_empleado;

        while (next_employee->siguiente_empleado != NULL) {
            if (next_employee->id_empleado == id_empleado_to_delete) {
                current_employee->siguiente_empleado = next_employee->siguiente_empleado;
                flag = 1;
            } else {
                current_employee = next_employee;
                next_employee = current_employee->siguiente_empleado;
            }
        }

        if (!flag || next_employee->siguiente_empleado == NULL) {
            if (next_employee->id_empleado == id_empleado_to_delete) {
                current_employee->siguiente_empleado = NULL;
            } else {
                return 0;
            }
        }
    }

    return 1;
}

int num_empleados(EMP *lista_empleados) {
    EMP *current_employee = lista_empleados;
    EMP *temp;
    int cont = 0;

    while (current_employee != NULL) {
        cont++;

        current_employee = current_employee->siguiente_empleado;
    }

    return cont;
}

char *mostrar_empleado(int id_empleado_to_show, EMP *lista_empleados) {
    char *message;
    int flag = 0;
    EMP *current_employee = lista_empleados;

    while (!flag && current_employee == NULL) {
        if (current_employee->id_empleado == id_empleado_to_show) {
            flag = 1;
        }
    }

    if (flag) {
        message = (char *)malloc(sizeof("Empleado: " + current_employee->id_empleado +
                                        "\nNombre: " + current_employee->nombre_empleado +
                                        "\nApellidos: " + current_employee->apellido_empleado +
                                        "\nDireccion" + mostrar_direccion(current) +
                                        "\nSalario: " + current_employee->salario +
                                        "\nGenero: " + current_employee->salario +
                                        "\nEstado Civil: " + current_employee->estado_civil +
                                        "\nNumero de hijos: " + current_employee->numero_hijos));
        message = "Empleado: " + current_employee->id_empleado +
                  "\nNombre: " + current_employee->nombre_empleado +
                  "\nApellidos: " + current_employee->apellido_empleado +
                  "\nDireccion" + mostrar_direccion(current) +
                  "\nSalario: " + current_employee->salario +
                  "\nGenero: " + current_employee->salario +
                  "\nEstado Civil: " + current_employee->estado_civil +
                  "\nNumero de hijos: " + current_employee->numero_hijos;
    } else {
        message = (char *)malloc(sizeof("No Se encontró el empleado"));
        message = "No Se encontró el empleado";
    }

    return message;
}

char *los_empleados(EMP *lista_empleados) {
    char *lista, *empleado;

    EMP *current = lista_empleados;

    if (current->siguiente_empleado == NULL) {
        lista = (char *)malloc(sizeof("No hay empleados"))
    } else {
        while (current != NULL) {
            empleado = (char *)malloc(sizeof(mostrar_empleado(current->id_empleado, current)));
            empleado = mostrar_empleado(current->id_empleado, current);
            lista = (char *)malloc(sizeof(lista + "\n ------- \n " + empleado));
            lista = lista + "\n ------- \n " + empleado;
        }
    }

    return lista;
}

DIR nueva_direccion() {
    DIR direccion;

    printf("Calle: ");
    scanf("%s", direccion.calle);

    printf("Numero: ");
    scanf("%d", &direccion.numero);

    printf("Ciudad: ");
    scanf("%s", direccion.ciudad);

    printf("Codigo Postal: ");
    scanf("%d", &direccion.codigo_postal);

    printf("Pais: ");
    scanf("%s", direccion.pais);

    return direccion;
}

char *mostrar_direccion(EMP *empleado) {
    char *direccion;
    DIR *direc = empleado->direccion_empleado;

    direccion = (char *)malloc(sizeof(
        "\t\nCalle: " + direc->calle +
        "\t\nNumero: " + direc->numero +
        "\t\nCodigo postal: " + direc->codigo_postal +
        "\t\nCiudad: " + direc->ciudad +
        " \t\nPaís: " + direc->pais));

    direccion = "\t\nCalle: " + direc->calle +
                "\t\nNumero: " + direc->numero +
                "\t\nCodigo postal: " + direc->codigo_postal +
                "\t\nCiudad: " + direc->ciudad +
                " \t\nPaís: " + direc->pais;

    return direccion
}