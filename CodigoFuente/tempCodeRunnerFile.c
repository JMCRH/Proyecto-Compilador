#include <stdio.h>
#include <stdlib.h>
#include "TablaDeSimbolos.h"
#include "AnalisisLexico.h"
#include "AnalisisSintactico.h"
#include "AnalisisSemantico.h"
#include "CodigoTresDirecciones.h"
#include "LenguajeDeBajoNivel.h"

//FUNCION QUE VERIFICA SI EL PROGRAMA SE EJECUTA SIN ERRORES
void VerificarStatus(int bandera)
{
	if (bandera == 0)
	{
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[])
{
	//system("cls");
	int op = 0, bandera = 0;
	int nTemp = 1;
	char Cadena[50];

	//Despliegue de opciones
	printf("\tCALCULADORA COMPILADA \n");
	printf("Escriba la cadena: ");
	fflush(stdin);
	gets(Cadena);
	LeerCadena(Cadena);
	bandera = Analizar();
	VerificarStatus(bandera);

	//Mostrar trabla de simbolos
	printf("\n");
	Imprimir();

	//Verificar gramática
	bandera = GIC_OperacionesAritmeticas();
	VerificarStatus(bandera);

	//Ingreso de tipos de datos para los IDs
	TipoDatoId();

	//Verificacion de tipos de datos asignados
	bandera = VerificarTipos();
	VerificarStatus(bandera);

	//Asignacion de valores en los IDs
	AsignarValores();
	printf("\n");

	//mostrar tabla de simbolos completa
	printf("\n");
	ImprimirCompleta();

	//Gerenar codigo intermedio
	printf("\n");
	generarCodigoTresDirecciones();
	system("pause");
	
	//Se genera el archivo ASM
	CrearArchivoASM();
	//printf("Compilador.asm creado exitosamente. \n");
	system("pause");
	return 0;
}