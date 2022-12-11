/*	Las sigientes dos lineas y la última del archivo, son instrucciones que evitan la 
	redefinición de las funciones y estructuras en caso de haber sido utilizadas con anterioridad
*/
#ifndef CODIGO_TRES_DIRECCIONES_H
#define CODIGO_TRES_DIRECCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include "TablaDeSimbolos.h"

//Funciones prototipo
int generarCodigoTresDirecciones();
void prioridad1() ;
void prioridad2();
void IdentificarOperacion();
void VerTemporales();


//variable global
int nTemp = 1;
char TempText[5] = "T";
char Num[3];

struct Temporales
{
    int nTemporal;
    char Operando1[10];
    char Operando2[10];
    char Operador[10];
    char NotacionPosfija[20];
    char TipoOperacion[4];
    struct Temporales *siguiente;    
};

struct Temporales *inicio = NULL, *final = NULL, *TempAux = NULL;

//Funcion para crear un nuevo temporal
void CrearTemporal(char OP1[5], char OP2[5],char OP[3] ,char Notacion[20],int nTemp)
{
    if(inicio==NULL)
    {
        inicio = malloc(sizeof(struct Temporales));
        inicio -> nTemporal = nTemp;
        strcpy(inicio -> Operando1,OP1);
        strcpy(inicio -> Operando2,OP2);
        strcpy(inicio -> Operador,OP);
        strcpy(inicio -> NotacionPosfija,Notacion);
        inicio -> siguiente = NULL;
        final = inicio;
    }
    else
    {
        TempAux = malloc(sizeof(struct Temporales));
        TempAux -> nTemporal = nTemp;
        strcpy(TempAux -> Operando1,OP1);
        strcpy(TempAux -> Operando2,OP2);
        strcpy(TempAux -> Operador,OP);
        strcpy(TempAux -> NotacionPosfija,Notacion);
        TempAux -> siguiente = NULL;
        final -> siguiente = TempAux;
        final = TempAux;
    }
}

//FUNCIÓN PARA IMPRIMRI LA TABLA DE TEMPORALES
void VerTemporales()
{
    TempAux = inicio;
    if(inicio == NULL)
    {
        printf("No hay temporales\n");
    }
    else
    {
        printf("\n\t------TABLA DE TEMPORALES------\n");
        printf("No. Temporal\t|Operando 1\t|Operando 2\t|Operador\t|Notacion Posfija |Operacion\n");
        printf("_____________________________________________________________________________________________\n");
        while (TempAux != NULL)
        {
            printf("%d\t\t|",TempAux->nTemporal);
            printf("%s\t\t|",TempAux->Operando1);
            printf("%s\t\t|",TempAux->Operando2);
            printf("%s\t\t|",TempAux->Operador);
            printf("%s\t\t  |",TempAux->NotacionPosfija);
            printf("%s\t\t\n",TempAux->TipoOperacion);

            //printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\n",TempAux->nTemporal,TempAux->Operando1,TempAux->Operando2,TempAux->Operador,TempAux->NotacionPosfija);
            TempAux = TempAux->siguiente;
        }
        
    }
}

//FUNCIÓN QUE IDENTIFICA EL TIPO DE OPERACIÓN
void IdentificarOperacion()
{
    TempAux = inicio;
    //Mientras no se llegue al final de la tabla de temporales hacer...
    while (TempAux != NULL)
    {
        /*Se busca el tipo de operador que tiene el temporal y se 
            asigan el tipo de operación correspondiente*/
        if(strcmp(TempAux->Operador,"*")==0)
        {
            strcpy(TempAux->TipoOperacion,"MUL");
            TempAux = TempAux->siguiente;
        }
        else if (strcmp(TempAux->Operador,"/")==0)
        {
            strcpy(TempAux->TipoOperacion,"DIV");
            TempAux = TempAux->siguiente;
        }
        else if (strcmp(TempAux->Operador,"+")==0)
        {
            strcpy(TempAux->TipoOperacion,"ADD");
            TempAux = TempAux->siguiente;
        }
        else if (strcmp(TempAux->Operador,"-")==0)
        {
            strcpy(TempAux->TipoOperacion,"SUB");
            TempAux = TempAux->siguiente;
        }
        else
        {
            printf("OCURRIÓ UN ERROR\n");
            break;
        }
    }
    
    
}


//FUNCIÓN QUE REALIZA LAS LLAMADAS A LAS FUNCIONES NECESARIAS PARA CREAR LOS TEMPORALES
int generarCodigoTresDirecciones()
{
    printf("GENERANDO TEMPORALES...\n");
    prioridad1();
    prioridad2();
    IdentificarOperacion();
    VerTemporales();
}

//FUNCIÓN QUE REALIZA UNA REVISIÓN DE LA TABLA DE SIMBOLOS BUSCANDO OPERADORES DE PRIORIDAD 1 (* | /)
void prioridad1()
{
    //printf("Entrando a prioridad 1\n");
    aux = ini;
    char Notacion [20];
    char Operando1[10];
    char Operando2[10];
    char Operador[10];
    while(aux != NULL)
    {
        //Se busca un operador de prioridad 1 (*, /)
        if(strcmp(aux->Lexema,"*")==0 || strcmp(aux->Lexema,"/")==0)
        {
            //printf("Encontrado operador de prioridad 1\n");
            /*Si se encuentra un operador de prioridad 1, los datos de ese lexema 
            se copian a los campos del temporal para generar una nueva tabla*/
            strcpy(Operando1,aux->Ant->ValorId);
            strcpy(Operando2,aux->Sig->ValorId);
            strcpy(Operador,aux->Lexema);
            strcpy(Notacion,Operando1);
            strcat(Notacion,Operando2);
            strcat(Notacion,Operador);
            //Realiza una concatenación para saber el Tn del temporal generado
            itoa(nTemp,Num,10);
            strcpy(TempText,"T");
            strcat(TempText,Num);
            printf("%s -> ",TempText);
            printf("%s\n",Notacion);
            //Se guardan los valores en la estructura de los temporales
            CrearTemporal(Operando1,Operando2,Operador,Notacion,nTemp);
            /*Cambia las referencias de los apuntadores para ignorar los
            valores ya utilizados*/
            if(aux->Ant->Ant != NULL)  
            {
                aux->Ant->Ant->Sig = aux;
                aux->Ant=aux->Ant->Ant;
            }
            else
            {
                aux->Ant=NULL;
                ini=aux;
            }
            if(aux->Sig->Sig != NULL)
            {
                aux->Sig->Sig->Ant = aux;
                aux->Sig=aux->Sig->Sig;
            }
            else
            {
                aux->Sig=NULL;
                fin=aux;
            }
            
            strcpy(aux->ValorId,TempText);
            nTemp++;
        }
        aux=aux->Sig;
    }
}

//FUNCIÓN QUE REALIZA UNA REVISIÓN DE LA TABLA DE SIMBOLOS BUSCANDO OPERADORES DE PRIORIDAD 2 (+ | -)
void prioridad2()
{
    //printf("Entrando a prioridad 2\n");
    aux = ini;
    char Notacion [20];
    char Operando1[5];
    char Operando2[5];
    char Operador[3];
    while (aux!=NULL)
    {
        if (strcmp(aux->Lexema,"+")==0 || strcmp(aux->Lexema,"-")==0)
        {
            //printf("Encontrado operador de prioridad 1\n");
            /*Si se encuentra un operador de prioridad 2, los datos de ese lexema 
            se copian a los campos del temporal para generar una nueva tabla*/
            strcpy(Operando1,aux->Ant->ValorId);
            strcpy(Operando2,aux->Sig->ValorId);
            strcpy(Operador,aux->Lexema);
            strcpy(Notacion,Operando1);
            strcat(Notacion,Operando2);
            strcat(Notacion,Operador);
            //Realiza una concatenación para saber el Tn del temporal generado
            itoa(nTemp,Num,10);
            strcpy(TempText,"T");
            strcat(TempText,Num);
            printf("%s -> ",TempText);
            printf("%s\n",Notacion);
            //Se guardan los valores en la estructura de los temporales
            CrearTemporal(Operando1,Operando2,Operador,Notacion,nTemp);
            /*Cambia las referencias de los apuntadores para ignorar los
            valores ya utilizados*/
            if(aux->Ant->Ant != NULL)  
            {
                aux->Ant->Ant->Sig = aux;
                aux->Ant=aux->Ant->Ant;
            }
            else
            {
                aux->Ant=NULL;
                ini=aux;
            }
            if(aux->Sig->Sig != NULL)
            {
                aux->Sig->Sig->Ant = aux;
                aux->Sig=aux->Sig->Sig;
            }
            else
            {
                aux->Sig=NULL;
                fin=aux;
            }
            strcpy(aux->ValorId,TempText);
            nTemp++;
        }
        aux=aux->Sig;        
    }
    
}

#endif // CODIGO_TRES_DIRECCIONES_H