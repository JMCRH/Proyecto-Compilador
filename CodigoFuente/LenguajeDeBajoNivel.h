/*	Las sigientes dos lineas y la última del archivo, son instrucciones que evitan la 
	redefinición de las funciones y estructuras en caso de haber sido utilizadas con anterioridad
*/
#ifndef LENGUAJE_DE_BAJO_NIVEL_H
#define LENGUAJE_DE_BAJO_NIVEL_H

#include "CodigoTresDirecciones.h"

//Funciones prototipo
void Encabezado();
void MUL();
void DIV();
void ADD();
void SUB();
int buscarT1();
int buscarT2();
void CadResultado();
void MostrarResultado();

//Variables globales
const char* NombreArchivo = "Compilador.asm";
FILE *ASM;
int NumDeTemp;
//Se crear una variable del tipo Temporal como auxiliar
struct Temporales *Aux;

//FUNCIÓN QUE CREA EL ARCHIVO *.ASM
void CrearArchivoASM()
{
    //Crear el archivo ASM con el nombre "Compilador.asm" en modo escritura
    ASM = fopen(NombreArchivo,"w");

    Encabezado();
    //ConsultaTemporal(Aux,Index);
    TempAux = inicio;
	
	while (TempAux != NULL)
	{		
		//Duplica el temporal en una variable global
		Aux = TempAux;
		//Si el tipo de operación es una multiplicacion...
		if(strcmp(TempAux->TipoOperacion,"MUL")==0)
		{
			printf("Multiplicacion\n");
			//Llama a la función que carga una multiplicación en el ASM
			MUL();
			TempAux = TempAux->siguiente;
		}
		else if(strcmp(TempAux->TipoOperacion,"DIV")==0)
		{
			printf("Division\n");
			//Llama a a la función que carga una división en el ASM
			DIV();
			TempAux = TempAux->siguiente;
		}
		else if(strcmp(TempAux->TipoOperacion,"ADD")==0)
		{
			printf("Suma\n");
			//Llama a la función que carga una suma en el ASM
			ADD();
			TempAux = TempAux->siguiente;
		}
		else if(strcmp(TempAux->TipoOperacion,"SUB")==0)
		{
			printf("Resta\n");
			//Llama a la función que carga una resta en el ASM
			SUB();
			TempAux = TempAux->siguiente;
		}
	}
	//Confirmar que las operaciones se cargaron correctamente
	printf("\nOperaciones cargadas correctamente\n");
	//Copia el archivo que muestra una cadena para el resultado
	CadResultado();
	//Abriri el archivo ASM en modo de "Escritura y Adición"
	ASM = fopen(NombreArchivo,"a");
	//Mueve el valor del último resultado generado al registro AL
	fprintf(ASM,"\nMOV AL, r%i\n",nTemp-1);
	//cerrar el archivo ASM
	fclose(ASM);
	//Copia el archivo para el final del programa
	MostrarResultado();
	//Muestra un mensaje de confirmación
	printf("\nArchivo ** %s **  creado con exito\n\n",NombreArchivo);
}
//FUNCIÓN QUE CARGA LOS VALORES Y LA OPERACIÓN DE MULTIPLICACIÓN EN EL ARCHIVO *.ASM
void MUL()
{
	//Abriri el archivo ASM en modo de "Escritura y Adición"
	ASM = fopen(NombreArchivo,"a");
	fprintf(ASM,"\n;MULTIPLICACION\n");
	//Si el primer operando es un temporal...
	if(buscarT1()==0)
	{
		//Utiliza el temporal como primer operando (en el asm llevará el número de resultado)
		fprintf(ASM,"MOV AL, r%i\n",NumDeTemp);
	}
	else
	{
		//Si no, utiliza el valor del primer operando
		fprintf(ASM,"MOV AL, %s\n",Aux->Operando1);
	}
	//Si el segundo operando es un temporal...
	if(buscarT2()==0)
	{
		//Utiliza el temporal como segundo operando (en el asm llevará el número de resultado)
		fprintf(ASM,"MOV BL, r%i\n",NumDeTemp);
	}
	else
	{
		//Si no, utiliza el valor del segundo operando
		fprintf(ASM,"MOV BX, %s\n",Aux->Operando2);
	}
	//Realiza la multiplicación
	fprintf(ASM,"MUL BL\n");
	fprintf(ASM,"MOV r%d,AL\n",Aux->nTemporal);
	//Cerrar el archivo ASM
	fclose(ASM);
}

//FUNCIÓN QUE CARGA LOS VALORES Y LA OPERACIÓN DE DIVISIÓN EN EL ARCHIVO *.ASM
void DIV()
{
	//Abriri el archivo ASM en modo de "Escritura y Adición"
	ASM = fopen(NombreArchivo,"a");
	//Si el primer operando es un temporal...
	fprintf(ASM,"\n;DIVISION\n");
	if(buscarT1()==0)
	{
		//Utiliza el temporal como primer operando (en el asm llevará el número de resultado)
		fprintf(ASM,"MOV AL, r%i\n",NumDeTemp);
	}
	else
	{
		//Si no, utiliza el valor del primer operando
		fprintf(ASM,"MOV AL, %s\n",Aux->Operando1);
	}
	
	//Si el segundo operando es un temporal...
	if(buscarT2()==0)
	{
		//Utiliza el temporal como segundo operando (en el asm llevará el número de resultado)
		fprintf(ASM,"MOV BL, r%i\n",NumDeTemp);
	}
	else
	{
		//Si no, utiliza el valor del segundo operando
		fprintf(ASM,"MOV BL, %s\n",Aux->Operando2);
	}
	//Realiza la división
	//Abre la plantilla de división
	fprintf(ASM,"DIV BL\n");
	fprintf(ASM,"MOV r%d,AL\n",Aux->nTemporal);
	//Cerrar el archivo ASM
	fclose(ASM);
}

//FUNCIÓN QUE CARGA LOS VALORES Y LA OPERACIÓN DE SUMA EN EL ARCHIVO *.ASM
void ADD()
{
	//Abriri el archivo ASM en modo de "Escritura y Adición"
	ASM = fopen(NombreArchivo,"a");
	fprintf(ASM,"\n;SUMA\n");
	//Si el primer operando es un temporal...
	if(buscarT1()==0)
	{
		//Utiliza el temporal como primer operando (en el asm llevará el número de resultado)
		fprintf(ASM,"MOV AL, r%i\n",NumDeTemp);
	}
	else
	{
		//Si no, utiliza el valor del primer operando
		fprintf(ASM,"MOV AL, %s\n",Aux->Operando1);
	}

	//Si el segundo operando es un temporal...
	if(buscarT2()==0)
	{
		//Utiliza el temporal como segundo operando (en el asm llevará el número de resultado)
		fprintf(ASM,"MOV BL, r%i\n",NumDeTemp);
	}
	else
	{
		//Si no, utiliza el valor del segundo operando
		fprintf(ASM,"MOV BL, %s\n",Aux->Operando2);
	}
	//Realiza la suma
	fprintf(ASM,"ADD AL,BL\n");
	fprintf(ASM,"MOV r%d,AL\n",Aux->nTemporal);
	//Cerrar el archivo ASM
	fclose(ASM);
}

//FUNCIÓN QUE CARGA LOS VALORES Y LA OPERACIÓN DE RESTA EN EL ARCHIVO *.ASM
void SUB()
{
	//Abriri el archivo ASM en modo de "Escritura y Adición"
	ASM = fopen(NombreArchivo,"a");
	fprintf(ASM,"\n;RESTA\n");
	//Si el primer operando es un temporal...
	if(buscarT1()==0)
	{
		//Utiliza el temporal como primer operando (en el asm llevará el número de resultado)
		fprintf(ASM,"MOV AL, r%i\n",NumDeTemp);
	}
	else
	{
		//Si no, utiliza el valor del primer operando
		fprintf(ASM,"MOV AL, %s\n",Aux->Operando1);
	}

	//Si el segundo operando es un temporal...
	if(buscarT2()==0)
	{
		//Utiliza el temporal como segundo operando (en el asm llevará el número de resultado)
		fprintf(ASM,"MOV BL, r%i",NumDeTemp);
	}
	else
	{
		//Si no, utiliza el valor del segundo operando
		fprintf(ASM,"MOV BL, %s\n",Aux->Operando2);
	}
	//Realiza la resta
	fprintf(ASM,"SUB AL,BL\n");
	fprintf(ASM,"MOV r%d,AL\n",Aux->nTemporal);
	//Cerrar el archivo ASM
	fclose(ASM);
}

//FUNCIÓN QUE BUSCA SI EL PRIMER OPERANDO ES UN TEMPORAL
int buscarT1()
{
	int i = 1;
	int bandera = 0;
	char cadAux[10] = "T";
	char Numero[3];
	for(i = 0; i < nTemp; i++)
	{
		itoa(i,Numero,10);
		strcat(cadAux,Numero);
		if (strcmp(cadAux,Aux->Operando1)==0)
		{
			NumDeTemp = i;
			return 0;
		}
		else
		{
			strcpy(cadAux,"T");
		}
	}
	if (bandera == 1)
	{
		return 1;
	}
	
}

//FUNCIÓN QUE BUSCA SI EL SEGUNDO OPERANDO ES UN TEMPORAL
int buscarT2()
{
	int i = 1;
	int bandera = 0;
	char cadAux[10] = "T";
	char Numero[3];
	for(i = 0; i < nTemp; i++)
	{
		itoa(i,Numero,10);
		strcat(cadAux,Numero);
		if (strcmp(cadAux,Aux->Operando2)==0)
		{
			NumDeTemp = i;
			return 0;
		}
		else
		{
			strcpy(cadAux,"T");
		}
	}
	if (bandera == 1)
	{
		return 1;
	}
}

//FUNCIÓN QUE CARGA EL ENCABEZADO DEL PROGRAMA EN EL ARCHIVO *.ASM
void Encabezado()
{
	//Puntero para abriri el archivo de encabezado
	FILE *INI_ASM;
	//Datos que se pueden leer por pasada
	char DatosLeidos[200]; 
	int cantidad;


	//Abre el archivo que contiene el encabezado en modo lectura
	INI_ASM = fopen("Encabezado.txt","r");
	//verifica si el archivo se abre correctamente
	if(!INI_ASM)
	{
		perror("OCURRIO UN ERROR AL ABRIR EL ARCHIVO DEL ENCABEZADO");
		exit(EXIT_FAILURE);
	}
	//Lee el contenido del archivo Encabazado.txt
	while(feof(INI_ASM) == 0)
	{
		fgets(DatosLeidos,200,INI_ASM);
		fprintf(ASM,DatosLeidos);
	}
	fclose(INI_ASM);
	//Cierra el archivo ASM
	fclose(ASM);
	printf("\nEncabezado.txt cargado correctamente\n");
}

//FUNCION QUE COPIA EL ARCHIVO PARA IMPRIMIR LA CADENA DE RESULTADOS
void CadResultado()
{
	//Abrir el archivo ASM en modo de "Escritura y Adición"
	ASM = fopen(NombreArchivo,"a");
	//Puntero para abriri el archivo de cadena de resultados
	FILE *CAD_RESULTADOS;
	//Datos que se pueden leer por pasada
	char DatosLeidos[200]; 
	int cantidad;

	//Abre el archivo que contiene el procedimiento en modo lectura
	CAD_RESULTADOS = fopen("Cadena.txt","r");
	//verifica si el archivo se abre correctamente
	if(!CAD_RESULTADOS)
	{
		perror("OCURRIO UN ERROR AL ABRIR EL ARCHIVO DE CADENA DE RESULTADOS");
		exit(EXIT_FAILURE);
	}
	//Lee el contenido del archivo Cadena.txt
	while(feof(CAD_RESULTADOS) == 0)
	{
		fgets(DatosLeidos,200,CAD_RESULTADOS);
		fprintf(ASM,DatosLeidos);
	}
	//cierra el archivo Cadena.txt
	fclose(CAD_RESULTADOS);
	//Cierra el archivo ASM
	fclose(ASM);
	printf("Cadena.txt cargada correctamente\n");
}

//FUNCION QUE COPIA EL ARCHIVO QUE MUESTRA EL RESULTADO DE LAS OPERACIONES
void MostrarResultado()
{
	//Abrir el archivo ASM en modo de "Escritura y Adición"
	ASM = fopen(NombreArchivo,"a");
	//Puntero para abriri el archivo de impresión de resultados
	FILE *PRINT;
	//Datos que se pueden leer por pasada
	char DatosLeidos[200]; 
	int cantidad;

	//Abre el archivo que contiene el procedimiento en modo lectura
	PRINT = fopen("ImprimirEnteros.txt","r");
	//verifica si el archivo se abre correctamente
	if(!PRINT)
	{
		perror("OCURRIO UN ERROR AL ABRIR EL ARCHIVO DE IMPRESION DE RESULTADOS");
		exit(EXIT_FAILURE);
	}
	//Lee el contenido del archivo ImprimirEnteros.txt
	while(feof(PRINT) == 0)
	{
		fgets(DatosLeidos,200,PRINT);
		fprintf(ASM,DatosLeidos);
	}
	//cierra el archivo ImprimirEnteros.txt
	fclose(PRINT);
	//Cierra el archivo ASM
	fclose(ASM);
	printf("ImprimirEnteros.txt cargada correctamente\n");
}

#endif //LENGUAJE_DE_BAJO_NIVEL_H