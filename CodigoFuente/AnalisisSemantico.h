/*	Las sigientes dos lineas y la última del archivo, son instrucciones que evitan la 
	redefinición de las funciones y estructuras en caso de haber sido utilizadas con anterioridad
*/
#ifndef ANALISIS_SEMANTICO_H
#define ANALISIS_SEMANTICO_H

#include "TablaDeSimbolos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Definición de funciones prototipo
void AsignarValores();
void ConsultarTiposDeDatos(char Tipo[4], int num);
void TipoDatoId();
int VerificarTipos();

//FUNCIÓN PARA CONSULTAR TIPOS DE DATOS
void ConsultarTiposDeDatos(char Tipo[4], int num)
{
	//Limpiar la consola de salida
	//system("cls");
	aux = ini;
	if (ini == NULL)
	{
		printf("\n-------NO EXISTEN ELEMENTOS EN LA TABLA DE SIMBOLOS------\n\n");		
	}
	else
	{
		while(aux != NULL)
		{
			if (aux->index == num)
			{
				//Devuelve el tipo de dato
                //Si es un Numero entero
				if(strcmp(aux -> TipoId,"NumE")==0)
				{
					strcpy(Tipo,"NumE");
					break;
				}
                //Si no es un entero pero es un numero decimal
				else if(strcmp(aux -> TipoId,"NumD")==0)
				{
					strcpy(Tipo,"NumD");
					break;
				}
			}
			else
			{
				//Pasar al siguienyte elemento de la tabla de simbolos
				aux = aux->Sig;
			}
			
		}
	}
}

//FUNCIÓN PARA AGREGAR TIPO DE DATO DE LOS IDENTIFICADORES
void TipoDatoId()
{
	int numAux = 0;
	aux = ini;
	if (ini == NULL)
	{
		printf("\n-------NO EXISTEN ELEMENTOS EN LA TABLA DE SIMBOLOS------\n\n");		
	}
	else
	{
		printf("_________________________________________\n");
		while(aux != NULL)
		{
			//Si se encuentra un ID se pregunta qué tipo de dato es ese ID
			if(strcmp(aux -> TipTok,"ID") == 0)
			{
				printf("El identificador '%s' es un: \n", aux -> Lexema);
				printf("1. Numero Entero \n");
				printf("2. Numero Decimal \n");
				printf("Digita la opcion: ");
				fflush(stdin);
				scanf("%i",&numAux);
				printf("Numero leido: %i\n",numAux);
								
				if (numAux == 1)
				{
					strcpy(aux -> TipoId,"NumE");
				}
				else if (numAux == 2)
				{
					strcpy(aux ->TipoId,"NumD");
				}
				numAux = 0;
				printf("Tipo de dato asignado: %s\n\n", aux -> TipoId);
				aux = aux->Sig;
			}
            //Si no es un ID, pero es un Numero Entero se asigna el tipo de dato correspondiente
			else if(strcmp(aux -> TipTok,"NE")==0)
			{
                strcpy(aux -> TipoId,"NumE");
				aux = aux->Sig;
			}
            //Si no es un ID, pero es un Numero Decimal se asigna el tipo de dato correspondiente
            else if(strcmp(aux -> TipTok,"ND")==0)
            {
                strcpy(aux -> TipoId,"NumD");
                aux = aux->Sig;
            }
            /*Si no es ni un ID, ni un Numero Entero o Decimal, se pasa al siguiente 
            elemento de la tabla de simbolos. Se asume que es un operador*/
            else
            {
                strcpy(aux -> TipoId,"");
                aux = aux->Sig;
            }
            
		}
        printf("_________________________________________\n");
	}
	printf("Se ha ingresado el tipo de dato de los identificadores.\n");
	printf("_________________________________________\n");
}

//FUNCIÓN PARA VERIFICAR QUE LOS TIPOS DE DATOS DE LA OPERACIÓN SEAN VÁLIDOS
int VerificarTipos()
{
    char TipoPrincipal[4];
    char Tipo[4];
    int Index = 1;
    int Longitud = 0;
    int Error = 1;

    //Se obtiene el tipo de dato de la variable o ID principal
    ConsultarTiposDeDatos(TipoPrincipal,Index);
    Index = Index + 2;

    //Si el ID principal es un Numero Entero
    if (strcmp(TipoPrincipal,"NumE")==0)
    {
        //Obtiene la longitud de la tabla de simbolos
        Longitud = LongitudTS();
        //Consulta el tipo de dato de los siguientes elementos de la tabla de simbolos 
        while (Index <= Longitud)
        {
            ConsultarTiposDeDatos(Tipo, Index);
            //Si el tipo de los demás elementos es diferenete a Numero Entero, se marca un error
            if (strcmp(Tipo,"NumE")==0)
            {
                Index = Index + 2;
            }
            else
            {
                Error = -1;
                break;
            } 

        }   
        /*  Si Error es verdadero, significa que hay un error de tipos de datos en la operacion
            recordando que no se permite el estrechamiento de datos, es decir, no se puede
            asignar un valor decimal a una variable entera.
        */
        if (Error == -1)
        {
            printf("\nError: Los tipos de datos de la operacion no son validos.\n");
            printf("No se permite el estrechamiento de tipos de datos.\n");
            printf("_________________________________________\n\n");
            return 0;
        }
        //Si Error no es verdadero, entonces se sabe que los tipos de datos son adecuados para operar
        else
        {
            printf("=== LOS TIPOS DE DATOS SON VALIDOS ===\n");
            printf("_________________________________________\n");
            return 1;
        }
        
    }
    /*  Si el ID principal no es un Numero Entero pero es un Numero decimal
        Entonces se aceptara que una operacion contenga decimales y enteros,
        Pues se realiza un ensanchamiento de tipos de datos
    */
    else if (strcmp(TipoPrincipal,"NumD")==0)
    {
        printf("=== LOS TIPOS DE DATOS SON VALIDOS ===\n");
        printf("_________________________________________\n");
        return 1;
    }
}

//FUNCIÓN QUE SOLICITA EL VALOR DE LOS IDENTIFICADORES
void AsignarValores()
{
    int Index = 2;
    int Longitud = LongitudTS();
    aux = ini;
    if (aux != NULL)
    {
        strcpy(aux -> ValorId,"");
    }

    while(aux != NULL)
    {
        //Si el Indice es igual al Index, se inserta el dato
        if(aux -> index == Index)
        {
            //Si se trata de un ID, se pregunta el valor del ID
            if (strcmp(aux -> TipTok,"ID")==0)
            {
                printf("\nIngrese el valor del identificador '%s': ", aux -> Lexema);
                fflush(stdin);
                scanf("%s",&aux->ValorId);
                printf("Valor asignado: %s\n", aux->ValorId);
                Index += 1;
                //avanza al siguiente elemento 
                aux = aux->Sig;   
            }
            //Si no es un ID, se copia el lexema, asumiendo que es un Entero o un Decimal
            else if(strcmp(aux->TipTok,"NE")==0 || strcmp(aux->TipTok,"ND")==0)
            {
                strcpy(aux->ValorId, aux->Lexema);
                Index += 1;
                //avanza al siguiente elemento 
                aux = aux->Sig;   
            }
            else
            {
                strcpy(aux->ValorId, " ");
                Index += 1;
                aux = aux->Sig;
            }         
        }
        else
        {
            aux = aux->Sig;
        }
    }
 
}

#endif //ANALISIS_SEMANTICO_H