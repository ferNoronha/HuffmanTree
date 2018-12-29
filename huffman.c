#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include "conio2.h"

struct TpNo
{
	struct TpNo *dir, *esq;
	char letra;
	float frequencia;
};
typedef struct TpNo No;

struct TpLetra
{
	char letra, cod[5];
	int quantidade;
};
typedef struct TpLetra Letra;

void exibe(No *raiz, int dist, int x, int y)
{
	if(raiz != NULL)
	{
		gotoxy(x, y);
		if(raiz->letra == '\0')
			printf("*");
		else
			printf("%c", raiz->letra);
		
		if(raiz->esq != NULL)
		{
			gotoxy(x-dist/2, y+1);
			printf("/");
		}
		if(raiz->dir != NULL)
		{
			gotoxy(x+dist/2, y+1);
			printf("\\");
		}
		
		exibe(raiz->esq, dist*0.4, x - dist, y+2);
		exibe(raiz->dir, dist*0.4, x + dist, y+2);
	}
}

No *CriaNo(char info, No *esq, No *dir, float frequencia)
{
	No *nova = (No *) malloc(sizeof(No));
	nova->dir=dir;
	nova->esq=esq;
	nova->letra=info;
	nova->frequencia=frequencia;
	return nova;
}

int buscaLista(Letra vetLetra[], int tl, char letra)
{
	int i,flag =-1;
	
	for(i=0;i<tl && flag<0;i++)
	{
		if(vetLetra[i].letra==letra)
			flag=i;
	}
	
	return flag;
}

void geraCod(Letra vetLetra[], int tl, No *raiz, char aux[], int *tlaux)
{
	int i=0;
	int ax;
	
	if(raiz!=NULL)
	{
		if(raiz->letra!='\0')
		{
			ax=buscaLista(vetLetra,tl,raiz->letra);
			for(i=0;i<*tlaux;i++)	
				vetLetra[ax].cod[i]=aux[i];
			vetLetra[ax].cod[i]='\0';
			(*tlaux)--;
			
		
		}
		else
		{
			aux[(*tlaux)++]='0';
			//aux[(*tlaux)]='\0';
			
			geraCod(vetLetra,tl,raiz->esq,aux,&(*tlaux));
			aux[(*tlaux)++]='1';
			//aux[(*tlaux)]='\0';
				
			geraCod(vetLetra,tl,raiz->dir,aux,&(*tlaux));
			(*tlaux)--;
		}
	}
}

void Ordena(No *vet[], int tl)
{
	No *aux=NULL;
	int i, j, menor;
	float fre;
	
	for( i = 0; i < tl; i++)
	{
		fre = vet[i]->frequencia;
		menor = i;
		for( j = i+1; j < tl; j++)
		{
			if(vet[j]->frequencia > fre)
			{
				fre = vet[j]->frequencia;
				menor = j;
			}
		}
		
		aux = vet[i];
		vet[i] = vet[menor];
		vet[menor] = aux;
	}
}

void percorreVet(No *vet[], int tl)
{
	int i=0;
	float fr;
	No *aux=NULL;

	while(tl>1)
	{
		fr=vet[tl-1]->frequencia+vet[tl-2]->frequencia;
		aux=CriaNo('\0',vet[tl-1], vet[tl-2],fr);
		tl--;
		vet[tl-1]=aux;		
		Ordena(&*vet,tl);
	}
}

void LePalavra(No *vet[],char palavra[], int *TL)
{
	Letra vetLetra[strlen(palavra)];
	int i=0,j=0;
	int T= strlen(palavra);
	char aux[5];
	int tlaux=0;
	
	for(i=0; i<strlen(palavra);i++)
	{
		j = buscaLista(vetLetra, *TL, palavra[i]);
		if( j >= 0)
			vetLetra[j].quantidade++;
		else
		{
			vetLetra[*TL].letra=palavra[i];
			vetLetra[*TL].quantidade=1;
			(*TL)++;
		}
	}
	
	for(i=0;i<*TL;i++)
	{
		vet[i]=CriaNo(vetLetra[i].letra,NULL,NULL,(vetLetra[i].quantidade*100)/T);
	}

	Ordena(&*vet,*TL);
	
	percorreVet(vet,*TL);
	geraCod(vetLetra,*TL,vet[0],aux,&tlaux);
	
	exibe(vet[0], 40, 70 , 1);
	printf("\n\n\n");
	
	for(i=0; i<*TL; i++)
	{
		printf("%c",vetLetra[i].letra);
		printf("   %s\n",vetLetra[i].cod);
	}
	getch();	
	
	printf("\n\n\nCodificacao da palavra utilizando Huffman:");
	for(i= 0 ; i< strlen(palavra); i++)
	{
		j=0;
		
		while(j < *TL)
		{
			
			if(vetLetra[j].letra == palavra[i])
			{
				printf(" %s", vetLetra[j].cod);
			}
			j++;
		}
	}	
}

int numBin(int numero){
    int i;
    int result=numero;
    int bin[5];
    for(i=0;i<5;i++)
        bin[i]=0;
    for(i=0;result!=0;i++){
        bin[i]=result%2;
        result=(result - bin[i])/2;
    }
    printf(" ");
    for(i=4;i>=0;i--)
        printf("%d", bin[i]);
}

int main()
{
	int tl=0;
	int i=0;
	char palavra[100];
	
	printf("Digite a palavra: ");
	fflush(stdin);
	gets(palavra);
	No *vet[strlen(palavra)];
	LePalavra(&vet,palavra,&tl);
	
	printf("\n");
	printf("Codificacao da palavra utilizando binario:");
	for(i= 0 ; i< strlen(palavra); i++)
	{
		numBin(palavra[i]);
	}

	getch();
}
