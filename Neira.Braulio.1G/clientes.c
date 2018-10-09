#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "neira.h"

/**
* \brief  Esta funcion inicializa un array de tipo cliente, recorriendo el array y poniendo cada isEmpty en 1
* \param  list employee es el array que se recorre
* \param  tam es el limite de empleados
* \return Rotorna 1 si se realizo de manera correcta, de lo contrario devolvera 0
*/
int initClientes(eClientes list[], int tam)
{
    int retorno = -1;
    int i;
    if(list != NULL && tam > 0)
    {
        for(i=0;i<tam;i++)
        {
            list[i].isEmpty = 1;
        }
        retorno = 0;
    }
    return retorno;
}


/**
* \brief  Se utiliza esta funcion para obtener un nuevo id
* \return devuelve un id nuevo
*/
static int getNextId()
{
    static int ultimoId=-1;
    ultimoId++;
    return ultimoId;
}

/**
* \brief Se obtiene el primer lugar libre de un array de tipo cliente, recorre el array hasta encontrar un isEmpty en 1
* \param list es el array que se recorre
* \param tam es el limite de empleados que puede guardar el array
* \return devuelve el id de la posicion libre.
*/


int searchFree(eClientes list[], int tam)
{
    int id = -1;

    for(int i=0; i < tam; i++)
    {

        if( list[i].isEmpty == 1)
        {
            id = i;
            break;
        }
    }
    return id;
}

/**
* \brief Se utiliza esta funcion para dar de alta un cliente generando un id de manera automatica y el usuario introduce el resto de datos.
* \param Array es el array que se recorre
* \param tam es el limite de empleados que puede guardar el array
* \return El retorno es 0 si se realizo de manera correcta, si no el retorno es -1.
*/

int addClientes(eClientes* array, int tam)
{
    int retorno = -1;
    int indice;
    char nombre[51];
    char apellido[51];
    int telefono;
    char sexo[2];
    indice = searchFree(array,tam);
    if( array != NULL && tam > 0 && indice >= 0 &&
        indice < tam && array[indice].isEmpty &&
        !getNombre( nombre, 51,"Nombre cliente: \n",
                        "nombre invalido\nTiene que comenzar con mayuscula y el resto con minuscula \n",2) &&
        !getNombre( apellido, 51,"Apellido cliente: \n",
                        "apellido invalido\nTiene que comenzar con mayuscula y el resto con minuscula\n",2) &&
        !getEnteroSoloNumeros(&telefono,15, "Telefono cliente: \n","telefono invalido,\n ingrese solo numeros \n",2 ) &&

        !getTexto(&sexo, 4, "Sexo empleado: \n", "sexo invalido", 2) )
    {
        strncpy(array[indice].nombre, nombre,51);
        strncpy(array[indice].apellido, apellido, 51);
        array[indice].telefono = telefono;
        strncpy(array[indice].sexo, sexo,2);
        array[indice].isEmpty = 0;
        array[indice].codigo = getNextId();
        retorno = 0;
    }
    return retorno;
}


/**
* \brief Se utiliza para encontrar un cliente a través de un id
* \param list es el array que se recorre
* \param tam es el limite de empleados que puede guardar el array
* \param id es con lo que se compara cada dato del array
* \return retorna la direccion de la struct del empleado donde se encontro el id, si no el retorno es NULL.
*/


int findClienteById(eClientes list[], int tam, int id)
{
    eClientes* retorno = NULL;
    int i;
    if(list != NULL && tam > 0)
    {
        for(i=0;i<tam;i++)
        {
            if(!list[i].isEmpty && list[i].codigo == id)
            {
                retorno = &list[i];
                break;
            }
        }
    }
    return retorno;

}



/**
* \brief Con esta funcion para mostrar todos los datos de los clientes del array
* \param list es el array que se recorre
* \param tam es el limite de empleados que puede guardar el array
* \return El retorno es 0 si se mostraron los datos, si no el retorno es -1.
*/


int printCliente(eClientes list[], int tam)
{
    int retorno = -1;
    int i;
    if(list != NULL && tam > 0)
    {
        for(i=0;i<tam;i++)
        {
            if(!list[i].isEmpty)
            {
                printf("\nNombre: %s\nApellido: %s\nTelefono: %d\nSexo: %s\nID: %d\n\n",
                list[i].nombre, list[i].apellido, list[i].telefono, list[i].sexo, list[i].codigo);
            }
        }
        retorno = 0;
    }
    return retorno;
}



/**
* \brief Se utiliza esta funcion para modificar un cliente,el usuario elige por medio del menu
* \param list es el array que se recorre
* \param tam es el limite de empleados que puede guardar el array
* \param reintentos son veces que el usuario podra volver a introducir el id
* \return El retorno es 0 si se realizo de manera correcta, si no el retorno es -1.
*/
int modifyCliente(eClientes list[], int tam, int reintentos)
{
    int retorno = -1;
    eClientes *empleadoModificado = NULL;
    int elegirOpcion = 0;
    int id;
    int i;
    char nombre[51];
    char apellido[51];
    float telefono;
    char sexo;
    if(list != NULL && tam > 0 && reintentos >= 0)
    {
        printCliente(list, tam);
        for(i=0; i <= reintentos; i++)
        {
            if( !getEntero(&id, tam, "Introduzca el codigo de cliente que desea modificar: \n", "", 0) &&
                findClienteById(list, tam, id) != NULL)
            {
                empleadoModificado = findClienteById(list, tam, id);
                break;
            }
            else
            {
                printf("Codigo cliente invalido\n");
            }
        }
    }
    if(empleadoModificado != NULL)
    {
        printf("1. Modificar nombre\n"
               "2. Modificar apellido\n"
               "3. Modificar Telefono\n"
               "4. Modificar sexo\n"
               "5. Modificar todos los datos\n");
        getEnteroSoloNumeros(&elegirOpcion, 5, "Seleccione opcion: \n", "", 0);
        switch(elegirOpcion)
        {
            case 1:
                if( !getNombre(nombre, 51,"Nombre cliente: \n",
                    "nombre invalido\nTiene que comenzar con mayusculas y el resto en minuscula\n",2))
                {
                    strncpy(empleadoModificado->nombre, nombre, 51);
                    retorno = 0;
                }
                break;
            case 2:
                if( !getNombre( apellido, 51,"Apellido cliente: \n",
                    "apellido invalido\nTiene que comenzar con mayusculas y el resto en minuscula\n",2))
                {
                    strncpy(empleadoModificado->apellido, apellido, 51);
                    retorno = 0;
                }
                break;
            case 3:
                if(!getFloatPositivo(&telefono, 10,"Telefono empleado: \n","telefono invalido\n",2))
                {
                    empleadoModificado->telefono = telefono;
                    retorno = 0;
                }
                break;
            case 4:
                if(!getTexto(sexo, 1, "Sexo empleado: \n", "sexo invalido\n",2))
                {
                    strncpy(empleadoModificado->sexo, sexo, 1);
                    retorno = 0;
                }
                break;
            case 5:
                if( !getNombre( nombre, 51,"Nombre cliente: \n",
                    "nombre invalido\nTiene que comenzar con mayusculas y el resto en minuscula\n",2) &&
                    !getNombre( apellido, 51,"Apellido cliente: \n",
                    "apellido invalido\nTiene que comenzar con mayusculas y el resto en minuscula\n",2) &&
                    !getFloatPositivo(&telefono, 10,"Telefono empleado: \n","Telefono invalido\n",2) &&
                    !getTexto(sexo, 1, "Sexo empleado: \n", "sexo invalido", 2))
                {
                    strncpy(empleadoModificado->nombre, nombre, 51);
                    strncpy(empleadoModificado->apellido, apellido, 51);
                    empleadoModificado->telefono = telefono;
                    strncpy(empleadoModificado->sexo, sexo, 1);
                    retorno = 0;
                }
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    }
    return retorno;
}


/**
* \brief  Se utiliza esta funcion para dar de baja un cliente
* \param  el array es lo que se recorre
* \param  tam es el limite de clientes que puede guardar el array
* \param  reintentos son las veces que el usuario podra volver a introducir el id
* \return El retorno es 0 si se realizo de manera correcta, si no el retorno es -1.
*/

int removeCliente(eClientes* array, int tam, int reintentos)
{
    int retorno = -1;
    eClientes *modifyCliente;
    char confirmarBaja[10];
    int id;
    int i;
    if(array != NULL && tam > 0 && reintentos >= 0)
    {
        printCliente(array, tam);
        for(i=0; i<= reintentos; i++)
        {
            if( !getEntero(&id, tam, "Introduzca el codigo de cliente que desea dar de baja\n", "", 0) &&
                findClienteById(array, tam, id) != NULL)
            {
                modifyCliente = findClienteById(array, tam, id);
                printf("Se borrara el siguiente cliente\n");
                printCliente(modifyCliente, 1);
                if( !getTexto(confirmarBaja, 10, "Pulse 1 para confirmar\n", "Error\n", 2) &&
                    strcmp(confirmarBaja, "1") == 0)
                {
                    modifyCliente->isEmpty = 1;
                    retorno = 0;
                }
                break;
            }
            else
            {
                printf("Codigo cliente incorrecto\n");
            }
        }
    }
    return retorno;
}


/**
* \brief ordena un array de clientes por insercion, primero por apellido y en caso de coincidir, por sexo
* \param array se recorre
* \param tam es el limite de clientes que puede guardar el array
* \param el orden debe ser 0 si es ascendente o 1 descendente
* \return El retorno es 0 si se realizo el ordenamiento, si no el retorno es -1.
*/
int sortClientePorApellidoSexo(eClientes *array, int tam, int orden)
{

    eClientes auxiliar;
    int retorno=-1;
    int i;
    int j;
    if(array != NULL && tam > 0 && (orden == 0 || orden == 1))
    {
        for(i=1; i < tam; i++)
        {
            auxiliar = array[i];
            j = i - 1;
            if(orden == 0)
            {
                while ((j >= 0) && !compareApellidoSexo(&array[j], &auxiliar))
                {
                    array[j + 1] = array[j];
                    j--;
                }
                array[j + 1] = auxiliar;
            }
            if(orden == 1)
            {
                while ((j >= 0) && !compareApellidoSexo(&auxiliar, &array[j]))
                {
                    array[j + 1] = array[j];
                    j--;
                }
                array[j + 1] = auxiliar;
            }
        }
        retorno = 0;
    }
    return retorno;
}


/**
* \brief compara a los clientes por su apellido y luego por sexo
* \param arrayUno es el primer cliente que se va a comparar
* \param arrayDos es el segundo cliente que se va a comparar
* \return si el primero es mayor devuelve 0, si no -1
*/
int compareApellidoSexo(eClientes* arrayUno, eClientes* arrayDos)
{
    int retorno=-1;
    if(arrayUno != NULL && arrayDos != NULL)
    {
        if( strcmp(arrayUno->apellido, arrayDos->apellido) > 0 ||
            (strcmp(arrayUno->apellido, arrayDos->apellido) == 0 && arrayUno->sexo > arrayDos->sexo))
        {
            retorno = 0;
        }
    }
    return retorno;
}


/**
* \brief Se utiliza esta funcion para cargar los datos de un cliente del array, el id se genera de manera automatica
* \param el array que se recorre
* \param tam es el limite de cliente que puede guardar el array
* \return El retorno es 0 si se mostraron los datos, de lo contrario es -1.
*/
int ingresoManual(eClientes* array, int tam, char *nombre, char *apellido, float telefono, char sexo)
{
    int retorno = -1;
    int indice;
    indice = searchFree(array,tam);
    if( array != NULL && tam > 0 && nombre != NULL &&
        apellido != NULL && telefono > 0 && sexo > 0)
    {
        strncpy(array[indice].nombre, nombre, 51);
        strncpy(array[indice].apellido, apellido, 51);
        array[indice].telefono = telefono;
        strncpy(array[indice].sexo, sexo, 1);
        array[indice].isEmpty = 0;
        retorno = 0;
    }
    return retorno;
}

