# Tarea 1

La tarea 1 cosnsitió en:

Escribir un programa en C o C++ para manipular una nómina de empelados. La información a almacenar por cada empleado es:

- Nombre de empleado. (*String*)
- Apellidos del empleado. (*String*)
- Identificación del empleado con número de ingreso. (*int*)
- Dirección. Este a la vez se estructura con:
    - Calle o avenida. (*String*)
    - Numero externo. (*int*)
    - Código postal. (*int*)
    - Ciudad. (*String*)
    - País. (*String*)
- Salario. (*float*)
- Genero. (*char*)
- Estado civil. (*char*)
- Número de hijos. (*int*)

*Aconsejable ocupar String.h*

Inicalmente la lista de empleados está vacía y se carga la información, de cada empleado, por teclado. Para ello debe haber un menú simple para interactuar con el usuario (sin interfaz gráfica).

Las funciones o procedimientos que deben escribirse son:

| Función            | Descripción               | 
|--------------------|---------------------------|
| crear_empleado     | Solicita el espacio necesario y almacena la información del empleado capturado por teclado. La función retorna un apuntador al empleado recién creado o un código de error si falla la habilitación  de  memoria.  Esta  función  debería  ser  llamada  por insertar_empleado. |
| insertar_empleado  | Agrega  un  nuevo  empleado  (ordenado  por  su  identificación).  El procedimiento recibe, al menos, el apuntador a la lista de empleados. Retorna error si no hay memoria disponible. |
| borrar_empleado    | Elimina un empleado por su identificación. Recibe como parámetro el identificador del empleado y la lista. Debe retorna código de error si el empleado no está en la lista. |
| num_empleados      | Retorna el número de empleados que contiene la lista. También como las demás funciones y procedimiento anteriores debe recibir parámetros |
| mostrar_empleado   | Muestra por pantalla la información de un empleado particular. Retorna un código de error si el empleado no está en la lista. |
| los_empleados      | Muestra por pantalla la información de todos los empleados. Retorna un código de error si la lista está vacía

## Análisis

Ocuparemos la librería `<string.h>` para apoyarnos en el manejo de Strings en cada uno de los casos que se ocupe.

Para facilitarnos el desarrollo de la tarea necesitamos una structura Dirección con todo lo que nos pide. 

~~~ C++

struct Direccion{

    std::string Calle;
    int NumeroExterno;
    int CodigoPostal;
    std::string Ciudad;
    std::string Pais;

}

~~~

