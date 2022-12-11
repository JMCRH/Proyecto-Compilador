/*	Las sigientes dos lineas y la última del archivo, son instrucciones que evitan la 
	redefinición de las funciones y estructuras en caso de haber sido utilizadas con anterioridad
*/
#ifndef TABLA_SIMBOLOS
#define TABLA_SIMBOLOS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definición de funciones
void AgregarSimTS(char Lex[20], char Tip[3], int num);
void Imprimir();
void ConsultarLexema(char Lex[20], int num);
void ConsultarTipTok(char Tip[3], int num);
int LongitudTS();
void ConsultarTipos(char Tipo[4], int num);


//estructura para la tabla de simbolos
struct TS
{
	char Lexema [20];
	char TipTok [3];
	int Indice;
	char TipoId [8];
	char ValorId[10];
	int index;
	struct TS *Sig;
	struct TS *Ant;
};

//INICIALIZAR LA ESTRUCTURA
struct TS *ini = NULL, *fin = NULL, *aux = NULL, *aux2 = NULL;
int indexNum = 1;


//FUNCIÓN PARA AGREGAR NUEVOS SIMBOLOS A LA TABLA
void AgregarSimTS(char Lex[20], char Tip[3], int num)
{
	if(ini == NULL)
	{
		//ini = new(struct TS);
		ini = malloc(sizeof(struct TS));
		strcpy(ini -> Lexema,Lex);
		strcpy(ini -> TipTok,Tip);
		ini ->Indice = num;
		ini -> index = indexNum;
		ini -> Sig = NULL;
		ini -> Ant = NULL;
		fin = ini;
	}
	else
	{
		//aux = new (struct TS);
		aux = malloc(sizeof(struct TS));
		strcpy(aux -> Lexema,Lex);
		strcpy(aux -> TipTok,Tip);
		aux -> Indice = num;
		aux -> index = indexNum;
		aux -> Sig = NULL;
		aux -> Ant = fin;
		fin -> Sig = aux;
		fin = aux;
	}
	indexNum++;
}

//FUNCIÓN QUE IMPRIME LA TABLA DE SIMBOLOS
void Imprimir()
{
	aux = ini;
	if (ini == NULL)
	{
		printf("\n-------NO EXISTEN ELEMENTOS EN LA TABLA DE SIMBOLOS------\n\n");		
	}
	else
	{
		printf("\n\t------TABLA DE SIMBOLOS------\n");
		printf("\nLexema\t\t|TipTok\t\t|Indice\n");
		printf("_________________________________________\n");
		while(aux != NULL)
		{
			if (strlen(aux->Lexema)<=6)
			{
				printf("%s",aux->Lexema);
				printf(" \t\t|%s",aux->TipTok);
				printf(" \t\t|%d\n",aux->Indice);
				aux = aux->Sig;
			}
			else
			{
				printf("%s",aux->Lexema);
				printf(" \t|%s",aux->TipTok);
				printf(" \t\t|%d\n",aux->Indice);
				aux = aux->Sig;
			}
			
		}
	}
	printf("\n");
}
//**********************************************
//FUNCIÓN QUE IMPRIME LA TABLA DE SIMBOLOS COMPLETA
void ImprimirCompleta()
{
	aux = ini;
	if (ini == NULL)
	{
		printf("\n-------NO EXISTEN ELEMENTOS EN LA TABLA DE SIMBOLOS------\n\n");		
	}
	else
	{
		printf("\n\t------TABLA DE SIMBOLOS------\n");
		printf("\nLexema\t\t|TipTok\t\t|Indice\t\t|TipoDato\t|Valor\n");
		printf("_____________________________________________________________________________\n");
		while(aux != NULL)
		{
			if (strlen(aux->Lexema)<=6)
			{
				printf("%s",aux->Lexema);
				printf(" \t\t|%s",aux->TipTok);
				printf(" \t\t|%d",aux->Indice);
				printf(" \t\t|%s",aux->TipoId);
				printf(" \t\t|%s\n",aux->ValorId);
				aux = aux->Sig;
			}
			else
			{
				printf("%s",aux->Lexema);
				printf(" \t|%s",aux->TipTok);
				printf(" \t\t|%d",aux->Indice);
				printf(" \t\t|%s",aux->TipoId);
				printf(" \t\t|%s\n",aux->ValorId);
				aux = aux->Sig;
			}
		}
	}
	printf("\n");
}
//**********************************************


//fUNCIÓN PARA CONSULTAR LA LONGITUD DE LA TABLA DE SIMBOLOS
int LongitudTS()
{
	int cont = 0;
	aux = ini;
	while(aux != NULL)
	{
		cont++;
		aux = aux->Sig;
	}
	return cont;
}

//FUNCIÓN PARA CONSULTAR LEXEMAS
void ConsultarLexema(char Lex[20], int num)
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
				//Devuelve el lexema
				if(strcmp(aux -> Lexema,"+")==0)
				{
					strcpy(Lex,"+");
				}
				else if(strcmp(aux -> Lexema,"-")==0)
				{
					strcpy(Lex,"-");
				}
				else if(strcmp(aux -> Lexema,"/")==0)
				{
					strcpy(Lex,"/");
				}
				else if(strcmp(aux -> Lexema,"*")==0)
				{
					strcpy(Lex,"*");
				}
				else
				{
					strcpy(Lex,aux -> Lexema);
				}
				aux = aux->Sig;
			}
			else
			{
				//Pasar al siguienyte elemento de la tabla de simbolos
				aux = aux->Sig;
			}
			
		}
	}
}

//FUNCIÓN PARA CONSULTAR TIPOS DE TOKENS
void ConsultarTipTok(char Tip[3], int num)
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
				//Devuelve el TipTok
				strcpy(Tip,aux -> TipTok);
				aux = aux->Sig;
			}
			else
			{
				//Pasar al siguienyte elemento de la tabla de simbolos
				aux = aux->Sig;
			}
			
		}
	}
}



#endif	//TABLA_SIMBOLOS