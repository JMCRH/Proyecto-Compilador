/*	Las sigientes dos lineas y la última del archivo, son instrucciones que evitan la 
	redefinición de las funciones y estructuras en caso de haber sido utilizadas con anterioridad
*/
#ifndef ANALISIS_SINTACTICO_H
#define ANALISIS_SINTACTICO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include "TablaDeSimbolos.h"

//Definición de funciones
int Derivaciones(int num, char Tip[3], char Lex[20], char Derivacion[30], char Sustitucion[30]);
int GIC_OperacionesAritmeticas();

/*ESTRUCTURA DE LA GRAMATICA:
S->numOS | numUS | num | id | idOS | idUS
O-> *|/
U-> +|-
*/
int GIC_OperacionesAritmeticas()
{
	printf("\n DERIVACIONES \n");
	char Lex[20];
	char Tip[3];
	int num = 1;
	char Derivacion[50], Sustitucion[50];
	int bandera = 1;
	int longitud = LongitudTS();
	
	
	//Consulta la tabla de simbolos para saber qué lexema se encuentra en la posición num, se espera un 'ID'
	ConsultarTipTok(Tip,num);

	//El primer lexema debe ser un 'ID'
	if(num == 1)
	{
		//Si el primer lexema es un 'ID'
		if(strcmp(Tip,"ID") == 0)
		{
			//S->id
			strcpy(Derivacion,"S->id");
			strcpy(Sustitucion,"id");

			//Si el primer lexema es un 'ID', se aumenta el indice y consulta el siguiente lexema
			num++;
			ConsultarTipTok(Tip,num);
			//Se espera que el siguiente lexema sea el signo de asignacion
			if (strcmp(Tip,"AS") == 0)
			{
				printf("S");
				strcpy(Derivacion,Sustitucion);
				strcat(Derivacion,"AS");
				ConsultarLexema(Lex,num);
				strcat(Sustitucion,Lex);
				printf(" -> %s -> %sS \n",Derivacion, Sustitucion);
			}
			//Si no es el signo de asignacion, entonces se tiene un error de sintaxis
			else
			{
				printf("Error de sintaxis, se esperaba un signo de asignacion. \n\n");
				bandera = 0;
			}
		}
		//Si el primer lexema no es un ID, entonces se tiene un error de sintaxis
		else
		{
			printf("Error de sintaxis, se esperaba un ID en la asignacion. \n\n");
			bandera = 0;
		}
	}
	
	/*Si se encontró un ID seguido del signo de asignación, entonces se procede a 
	verificar si es una operación aritmética lo que le precede*/

	//Si bandera == 1, entonces no hay errores en sintaxis
	//si bandera == 0 entonces hay errores en sintaxis y finaliza
	while(bandera == 1)
	{
		num = num + 1;
		if(num <= longitud)
		{
			ConsultarTipTok(Tip,num);
			bandera = Derivaciones(num,Tip,Lex,Derivacion,Sustitucion);
		}
		//Si se trata de un número impar y es mayor a la longitud de la tabla de simbolos, puede ser válida
		else if(num > longitud && (num-1) % 2 != 0)
		{
			printf(" -> %s\n",Sustitucion);
			printf("\n LA CADENA ES VALIDA\n\n");
			bandera = 2;
		}
		//Si se trata de una longitud mayor a la tabla de simbolos y el indice es un numero par, entonces hay un error
		else if(num > longitud && (num-1) % 2 == 0)
		{
			printf(" -> %s\n",Sustitucion);
			printf("Error de sintaxis \n\n");
			bandera = 0;
		}
	}
	//Si la badera es 1, no hubo errores, si es 0, hubo errores
	if(bandera != 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

//fUNCIÓN QUE VERIFICA LAS DERIVACIONES Y REALIZA LAS SUSTITUCIONES
int Derivaciones(int num, char Tip[3], char Lex[20], char Derivacion[30], char Sustitucion[30])
{	
	//Si num es par, debe ser algún signo
	if(num % 2 == 0)
	{
		//OA1-> *|/
		if(strcmp(Tip,"OA1") == 0)
		{
			strcpy(Derivacion,Sustitucion);
			strcat(Derivacion,"OS");
			ConsultarLexema(Lex,num);
			//printf("%s",Lex);
			strcat(Sustitucion,Lex);
			printf(" -> %s -> %sS \n",Derivacion, Sustitucion);
		}
		//OA2-> +|-
		else if(strcmp(Tip,"OA2") == 0)
		{
			strcpy(Derivacion,Sustitucion);
			strcat(Derivacion,"US");
			ConsultarLexema(Lex,num);
			//printf("%s\n",Lex);
			strcat(Sustitucion,Lex);
			printf(" -> %s -> %sS \n",Derivacion, Sustitucion);
		}
		//Si no es ninguna de las anteriores, entonces es un error
		else
		{
			printf("Error de sintaxis\n\n");
			return 0;
		}
		return 1;
	}
	//Si no es par, se debe tratar de un num o un id
	else
	{
		if(strcmp(Tip,"NE") == 0 || strcmp(Tip,"ND") == 0)
		{
			strcpy(Derivacion,Sustitucion);
			strcat(Derivacion,"num");
			//ConsultarLexema(Lex,num);
			//printf("%s",Lex);
			strcat(Sustitucion,"num");			
		}
		else if(strcmp(Tip,"ID") == 0)
		{
			strcpy(Derivacion,Sustitucion);
			strcat(Derivacion,"id");
			//ConsultarLexema(Lex,num);
			//printf("%s",Lex);
			strcat(Sustitucion,"id");
		}
		else
		{
			printf("Error de sintaxis\n\n");
			return 0;
		}
		return 1;
	}
}

#endif //ANALISIS_SINTACTICO_H