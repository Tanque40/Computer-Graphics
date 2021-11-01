#pragma once

#include <string>

struct Direccion{

    std::string Calle;
    int NumeroExterno;
    int CodigoPostal;
    std::string Ciudad;
    std::string Pais;

    /**
     * Constructor
     */
    Direccion( std::string Calle, int NumeroExterno, int CodigoPostal, std::string Ciudad, std::string Pais ){
        this->Calle = Calle;
        this->NumeroExterno = NumeroExterno;
        this->CodigoPostal = CodigoPostal;
        this->Ciudad = Ciudad;
        this->Pais = Pais;
    }

    /**
     * @return Todo el contenido de la estructura de Direccion.
     */
    std::string To_String(){
        return (
            "\n\tCalle: " + Calle + "\n" + 
            "\tNumero Externo: " + std::to_string( NumeroExterno ) + " \n" +
            "\tCodigo Postal: " + std::to_string( CodigoPostal ) + " \n" +
            "\tCiudad: " + Ciudad + " \n" +
            "\tPais: " + Pais + " \n"
            );
    }

};

struct Empleado{

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
    Empleado *Siguiente_Empleado = NULL;

    /**
     * Constructor
     */
    Empleado( std::string Nombre, std::string Apellidos, int Numero_Identificacion, Direccion *Direccion_Empleado, float Salario, char Genero, char Estado_Civil, int Numero_Hijos ){
        this->Nombre = Nombre;
        this->Apellidos = Apellidos;
        this->Numero_Identificacion = Numero_Identificacion;
        this->Direccion_Empleado = Direccion_Empleado;
        this->Salario = Salario;
        this->Genero = Genero;
        this->Estado_Civil = Estado_Civil;
        this->Numero_Hijos = Numero_Hijos;
    }

    /**
     * Push empleado
     *
     * Inserta el siguiente empeado.
     * Si ya hay un valor recorre las posisiones.
     *
     * @param Apuntador con el nuevo empleado
     * @return void
     */
    void Push( Empleado *Nuevo_Empleado ){
        
        if( Siguiente_Empleado == NULL ){

            Siguiente_Empleado = Nuevo_Empleado;

        } else{

            Empleado *temp = Siguiente_Empleado;

            Siguiente_Empleado = Nuevo_Empleado;
            Nuevo_Empleado->Siguiente_Empleado = temp;

        }

    }

    /**
     * Delete_Next empleado
     *
     * Borra el empleado siguiente.
     * Si hay más empleados los recorre a la posición de Siguiente_Empelado
     *
     * @return 1 si el empleado fue borrado correctamente
     * @return 0 si hubo error al borrar empleado
     */
    int Delete_Next(){

        if( Siguiente_Empleado->Siguiente_Empleado == NULL ){

            Siguiente_Empleado = NULL;
            return 1;

        } else{

            Empleado *temp = Siguiente_Empleado->Siguiente_Empleado;

            Siguiente_Empleado = temp;

            return 1;

        }
        
        return 0;

    }

    /**
     * To_String()
     *
     * @return String todos los datos del empleado.
     */
    std::string To_String(){

        std::string res = "";

        res += "Numero de identificación: " + std::to_string( Numero_Identificacion );
        res += "Nombre: " + Nombre;
        res += "Apellidos: " + Apellidos;
        res += "Salario: " + std::to_string( Salario );
        res += "Genero: " + Genero;
        res += "Estado Civil: " + Estado_Civil;
        res += "Numero de Hijos: " + std::to_string( Numero_Hijos );
        res += "Direccion: " + Direccion_Empleado->To_String();

    }

};


class Nomina{

    int NumEmpleados;
    Empleado *ListaEmpleados = NULL;

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
    int borrar_empleado( int Id_Empleado );

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
    std::string mostrar_empleado( int Id_Empleado );

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


};