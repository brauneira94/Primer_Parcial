#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "neira.h"
#include "clientes.h"
#define TAM 1000
int main()
{
    int elegirOpcion;
    int salirMenu = 0;
    int cantClientes = 0;
    eClientes eClientes[TAM];
    initClientes(eClientes, TAM);

    while(salirMenu == 0)
    {
        printf("MENU PRINCIPAL\n\n");
        printf("1. Alta cliente\n"
               "2. Modificar cliente\n"
               "3. Baja cliente\n"
               "4. Listado clientes\n"
               "5. Salir\n");
        elegirOpcion = 0;
        getEntero(&elegirOpcion, 5, "Seleccione una opcion\n", "", 0);
        switch(elegirOpcion)
        {
            case 1:
                if(!addClientes(eClientes, TAM))
                {
                    cantClientes++;
                }
                else
                {
                    printf("No se pudo dar de alta el cliente\n");
                }
                break;
            case 2:
                if(cantClientes != 0 && !modifyCliente(eClientes, TAM, 2))
                {
                    printf("Datos modificados con exito\n");
                }
                else
                {
                    printf("No se pudo modificar el cliente\n");
                }
                break;
            case 3:
                if(cantClientes != 0 && !removeCliente(eClientes, TAM, 2))
                {
                    cantClientes--;
                }
                else
                {
                    printf("No se pudo dar de baja el cliente\n");
                }
                break;
            case 4:
                if(cantClientes != 0)
                {

                            sortClientePorApellidoSexo(eClientes, TAM, 0);
                            printCliente(eClientes, TAM);


                    }

                else
                {
                    printf("No hay clientes cargados en el sistema\n");
                }
                break;
            case 5:
                salirMenu = 1;
                break;
            default:
                printf("Opcion Incorrecta\n");
                break;
        }
        printf("Pulse intro para continuar\n");
        fflush(stdin);
        getchar();
    }
}
