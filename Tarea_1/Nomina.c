#include <stdio.h>
#include <stdlib.h>

//  ______                              _   _  _  _    _
//  | ___ \                            | | | |(_)| |  | |
//  | |_/ / _ __  _   _  _ __    ___   | | | | _ | |_ | |_   ___
//  | ___ \| '__|| | | || '_ \  / _ \  | | | || || __|| __| / _ \
//  | |_/ /| |   | |_| || | | || (_) | \ \_/ /| || |_ | |_ |  __/
//  \____/ |_|    \__,_||_| |_| \___/   \___/ |_| \__| \__| \___|
//
//

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
void mostrar_empleado(int id_empleado_to_show, EMP *lista_empleados);
void mostrar_direccion(EMP *empleado);
void los_empleados(EMP *lista_empleados);

int main() {
    EMP *apt_empleados = NULL;

    int ans = 1, id_empleado;

    printf("//  ______                              _   _  _  _    _               //\n");
    printf("//  | ___ \\                            | | | |(_)| |  | |              //\n");
    printf("//  | |_/ / _ __  _   _  _ __    ___   | | | | _ | |_ | |_   ___       //\n");
    printf("//  | ___ \\| '__|| | | || '_ \\  / _ \\  | | | || || __|| __| / _ \\      //\n");
    printf("//  | |_/ /| |   | |_| || | | || (_) | \\ \\_/ /| || |_ | |_ |  __/      //\n");
    printf("//  \\____/ |_|    \\__,_||_| |_| \\___/   \\___/ |_| \\__| \\__| \\___|      //\n");

    while (ans) {
        printf("\n\n\n\n¿Qué deseas hacer?\n");
        printf("\n\t1) Agniadir nuevo empleado.\n");
        printf("\n\t2) Borrar empleado (por clave).\n");
        printf("\n\t3) Mostrar empleado (por clave). \n");
        printf("\n\t4) Listar todos los empleados. \n");
        printf("\n\t5) Numero de empleados. \n");
        printf("\n\t0) SALIR\n");

        printf("\nTu respuesta: ");
        scanf("%d", &ans);

        switch (ans) {
            case 1:
                insertar_empleado(apt_empleados);
                break;
            case 2:
                printf("\nBorrar empleado. Ingresa la clave del empleado a borrar: ");
                scanf("%d", id_empleado);
                borrar_empleado(id_empleado, apt_empleados);
                break;
            case 3:
                printf("\nMostrar empleado. Ingresa la clave del empleado a mostrar: ");
                scanf("%d", id_empleado);
                mostrar_empleado(id_empleado, apt_empleados);
                break;
            case 4:
                los_empleados(apt_empleados);
                break;
            case 5:
                num_empleados(apt_empleados);
                break;
            case 0:
                ans = 0;
                break;
            default:
                printf("Valor fuera de rango");
                break;
        }
    }

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
        printf("Error in new empleado");
        return apt_nuevo_empleado;  // ! Aquí hay que lanzar una excepción
    }

    printf("Ingresa la clave del empleado: ");
    scanf("%d", &nuevo_empleado.id_empleado);

    printf("Ingresa el nombre del empleado: ");
    scanf("%s", nuevo_empleado.nombre_empleado);

    printf("Ingresa los apellidos del empleado: ");
    scanf("%s", nuevo_empleado.apellido_empleado);

    nuevo_empleado.direccion_empleado = nueva_direccion();

    printf("Ingresa el estado civil del empleado: (s) Soltero - (c) Casado - (u) Union Libre - (n) Prefiero no decir: ");
    scanf("%s", &nuevo_empleado.estado_civil, 1);

    printf("Número de hijos del empleado: ");
    scanf("%d", &nuevo_empleado.numero_hijos);

    printf("Ingresa el genero del empleado: (m) Masculino - (f) Femenino - (n) Prefiero no decir: ");
    scanf("%s", &nuevo_empleado.gender);

    printf("Ingresa el salario del empleado: $");
    scanf("%f", &nuevo_empleado.salario);

    nuevo_empleado.siguiente_empleado = NULL;

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

void mostrar_empleado(int id_empleado_to_show, EMP *lista_empleados) {
    int flag = 0;
    EMP *current_employee = lista_empleados;

    while (!flag && current_employee != NULL) {
        if (current_employee->id_empleado == id_empleado_to_show) {
            flag = 1;
        }
    }

    if (flag) {
        printf("Empelado: \t%s\n", current_employee->id_empleado);
        printf("Nombre: \t%s\n", current_employee->nombre_empleado);
        printf("Apellidos: \t%s\n", current_employee->apellido_empleado);
        printf("Salario: \t%f\n", current_employee->salario);
        printf("Genero: \t%s\n", current_employee->gender);
        printf("Estado Civil: \t%s\n", current_employee->estado_civil);
        printf("Numero de hijos: \t%d\n", current_employee->numero_hijos);
        mostrar_direccion(current_employee);
    } else {
        printf("No Se encontró el empleado");
    }
}

void los_empleados(EMP *lista_empleados) {
    EMP *current = lista_empleados;

    if (current->siguiente_empleado == NULL) {
        printf("No hay empleados");
    } else {
        while (current != NULL) {
            printf("\n__________________________________________________________________\n");
            mostrar_empleado(current->id_empleado, current);
            current = current->siguiente_empleado;
        }
    }
}

DIR nueva_direccion() {
    DIR direccion;

    printf("\nIngresa la direccion: \n\n");
    printf("\tCalle: ");
    scanf("%s", direccion.calle);

    printf("\tNumero: ");
    scanf("%d", &direccion.numero);

    printf("\tCiudad: ");
    scanf("%s", direccion.ciudad);

    printf("\tCodigo Postal: ");
    scanf("%d", &direccion.codigo_postal);

    printf("\tPais: ");
    scanf("%s", direccion.pais);

    printf("\n");

    return direccion;
}

void mostrar_direccion(EMP *empleado) {
    DIR direc = empleado->direccion_empleado;

    printf("Dirección:\n");
    printf("\tCalle: \t%s", direc.calle);
    printf("\tNumero: \t%d", direc.numero);
    printf("\tCodigo Postal: \t%d", direc.codigo_postal);
    printf("\tCiudad: \t%s", direc.ciudad);
    printf("\tPaís: \t%s", direc.pais);
}