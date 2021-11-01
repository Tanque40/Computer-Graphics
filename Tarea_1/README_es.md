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

Generaremos una clase Nomina que nos permitirar el manejo de los los Empleados, la obtención de los datos y la inserción de los mismos. Esto apoyado de las funciones que permitan el manejo de la lista enlazada de los empleados. Y un `To_String()` que devuelva los datos de todos los empleados de la empresa. En este caso como creamos la clase nomina no es necesario que las funciones reciban como parámetro el apuntador de los empleados.

La clase y las structuras irán dentro del header `Nomina.h` y la declaración de las funciones estará dentro de `Nomina.cpp`. 

Ocuparemos la librería `<string.h>` para apoyarnos en el manejo de Strings en cada uno de los casos que se ocupe.

Para facilitarnos el desarrollo de la tarea necesitamos una structura Dirección con todo lo que nos pide. Indicaremos un contructor que asigne los valores necesarios y un `To_String()` que devuelva todos los valores de manera más cómoda. 

~~~ C++

struct Direccion {

    std::string Calle;
    int NumeroExterno;
    int CodigoPostal;
    std::string Ciudad;
    std::string Pais;

    /**
     * Constructor
     */ 
    Direccion(std::string Calle, int NumeroExterno, int CodigoPostal, std::string Ciudad, std::string Pais);

    /**
     * @return Todo el contenido de la estructura de Direccion.
     */
    std::string To_String();

}

~~~

También necesitamos la estructura empleado, la cual contendrá los datos solicitados, un constructor para aasignar todos los datos, un `To_String()` para mostrar todo el contenido de la estructura y finalmente un par de funciones para la inserción de los nuevos Empleados y el manejo de la lista ligada con los punteros.

~~~ C++

struct Empleado {

    std::string Nombre;
    std::string Apellidos;
    int Numero_Identificacion;
    Direccion Direccion_Empleado; 
    float Salario;
    // (M) Masculino, (F) Femenino, (O) Otro.
    char Genero;
    // (C) Casado, (U) Unión Libre, (S) Soltero, (D) Divorciado, (V) Viudo, (O) Otro.
    char Estado_Civil;
    int Numero_Hijos;
    Empleado *Siguiente_Empleado = NULL;    

    /**
     * Constructor
     */
    Empelado(std::string Nombre, std::string Apellidos, int Numero_Identificacion, Direccion Direccion_Empleado, float Salario, char Genero, char Estado_Civil, int Numero_Hijos);

    /**
     * Push empleado
     * 
     * Inserta el siguiente empeado.
     * Si ya hay un valor recorre las posisiones.
     * 
     * @param Apuntador con el nuevo empleado
     * @return void 
     */
    void Push(Empleado *Nuevo_Empleado);

    /**
     * Delete_Next empleado
     * 
     * Borra el empleado siguiente.
     * Si hay más empleados los recorre a la posición de Siguiente_Empelado
     * 
     * @return 1 si el empleado fue borrado correctamente
     * @return 0 si hubo error al borrar empleado
     */
    int Delete_Next();

    /**
     * To_String()
     * 
     * @return String todos los datos del empleado.
     */
    std::string To_String();

}

~~~

Finalmente declaramos la clase Nomina con las fuciones para crear empleado, insertar empleados, borrar empleado, numero de empleados, mostrar un empleado y el `To_String()` que mostrará todos los empleados.

~~~ C++

class Nomina{

    int NumEmpleados;
    Empleado ListaEmpleados = NULL;

public:
    
    /**
     * Contructor
     *
     * Inicializa el numero de empleados en 0.
     * La lista de empleados se modificará hasta la inserción de un empleado. 
     */
    Nomina();
    
    /**
     * Destructor
     * Vacía los datos de la lista para liberar espacio.
     */
    ~Nomina();

    /**
     * crear_empleado 
     *
     * Pide los datos necesarios para crear un empleado.
     *
     * @return Un apuntador con los datos del nueco empleado
     */
    Empleado *crear_empleado();

    /**
     * insertar_empleado
     *
     * Llama a la funcion crear_empleado para tener un nuevo empleado,
     * lo inserta en orden dependiendo de la clave del empleado.
     *
     * @return 1 si el empleado fue añadido correctamente.
     * @return 0 si hubo un error al insertar el empleado.
     */
    int insertar_empelado();

    /**
     * borrar_empleado
     * 
     * Busca el empleado anterior al que queremos borrar, identificado con el Id_Empleado,
     * aplica la función Delete_Next() de la estructura empleado.
     *
     * @param[ in ] Id_Empleado el Identificador del empleado a borrar.
     *
     * @return 1 si el empleado fue borrado correctamente.
     * @return 0 si el empleado no se encontró o hubo un error al borrar.  
     */
    int borrar_empleado(int Id_Empleado);
    
    /**
     * num_empleados
     *
     * @return numero de empleados en la nómina.
     */
    int num_empleados();

    /**
     * mostrar_empleado
     *
     * Busca el empelado por su clave y muestra sus datos
     * 
     * @param[ in ] Id_Empleado el empleado a buscar
     *
     * @return El To_String() del empleado.
     */
    std::string mostrar_empleado(int Id_Empleado);

    /**
     * To_String();
     * 
     * @return Un string con los strings de todos los empleados.
     */
    std::string To_String();

private:

    /**
     * Create_Direccion()
     *
     * Pide los datos necesarios para crear un apuntador de Direccion
     * 
     * @return Apuntador de la estructura dirección
     */
    Direccion *Create_Direccion();

}

~~~

Finalmente nuestro main del programa entrará en un bucle en el que se mostarará un menú con las opciones disponibles para hacer con la nómina. Se pedirán los datos necesarios en cada caso y si se mete la opción 0 o cualquier diferente a las opciones del menú el programa acabará.