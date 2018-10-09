#define CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED


typedef struct
{
    char nombre[51];
    char apellido[51];
    char sexo[1];
    int codigo;
    int telefono;
    int isEmpty;
}eClientes;


int initClientes(eClientes list[], int tam);
static int getNextId();
int searchFree(eClientes list[], int tam);
int addClientes(eClientes* array, int tam);
int findClienteById(eClientes list[], int tam, int id);
int printCliente(eClientes list[], int tam);
int modifyCliente(eClientes list[], int tam, int reintentos);
int removeCliente(eClientes* array, int tam, int reintentos);
int sortClientePorApellidoSexo(eClientes *array, int tam, int orden);
int compareApellidoSexo(eClientes* arrayUno, eClientes* arrayDos);
int ingresoManual(eClientes* array, int tam, char *nombre, char *apellido, float telefono, char sexo);

