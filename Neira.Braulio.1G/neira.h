#define NEIRA_H_INCLUDED
#define NEIRA_H_INCLUDED
typedef struct
{
    char nombre[50];
    char apellido[50];
    char DNI[20];
}utnEmpleado;

static void myFpurge();
static int getString(char *pBuffer, int limite);
int getNombre(char *pNombre, int limite, char *mensaje, char *mensajeError, int reintentos);
int getEnteroSoloNumeros(int *pEntero, int limite, char *mensaje, char *mensajeError, int reintentos);
int getFloatPositivo(float *pFloat, int limite, char *mensaje,char *mensajeError, int reintentos);
int getEntero(int *pEntero, int limite, char *mensaje, char *mensajeError, int reintentos);
int getTexto(char *pTexto, int limite, char *mensaje, char *mensajeError, int reintentos);
int validInteger(char *pBuffer, int limite);
int validText(char *pBuffer, int limite);
int validFloatPositive(char *pBuffer, int limite);
int validIntegerOnlyNumber(char *pBuffer, int limite);
int validName(char *pBuffer, int limite);
static int isValidTelefonoFijo(char *pBuffer, int limite);
