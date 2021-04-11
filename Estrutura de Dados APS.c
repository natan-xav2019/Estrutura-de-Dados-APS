#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#define MAX 10

typedef struct
{
	int inicio;		   // inicio da lista
	int final;		   // Final da lista
	int no;			   // posisao atual de busca do vetor
	int elemento[MAX]; //armazenamento das variaveis

} Lista;

void FormatarTexto(char texto[]);
void Iniciar(Lista *lista);
void Remover(Lista *lista);
void Apresentar(Lista *lista, char tipo[]);
void InsercaoLista(Lista *lista, char tipo[], int num);
void deletarFila(Lista *lista, char tipo[], int posisao);
void deletarLista(Lista *lista, char tipo[], int num);
void Ordenar(int prt_num[], int max);

void main(void)
{
	setlocale(LC_ALL, "");

	int tipoID, num;
	char comando[MAX], tipo[3][6];

	Lista *lista;

	lista = (Lista *)calloc(1, sizeof(Lista));

	strcpy(tipo[0], "lista");
	strcpy(tipo[1], "fila");
	strcpy(tipo[2], "pilha");
	Iniciar(lista);

	// Aqui escolhemos se queremos lista, filas ou pilhas
	printf("Escolha o tipo de organizacao de dados que deseja montar: lista, fila e pilha\n");
	do
	{
		scanf("%s", comando);
		FormatarTexto(comando);

	} while (strcmp(comando, tipo[0]) && strcmp(comando, tipo[1]) && strcmp(comando, tipo[2]));

	if (!strcmp(comando, tipo[0]))
	{
		//printf("Uma lista\n");
		tipoID = 0;
	}
	else
	{
		if (!strcmp(comando, tipo[1]))
		{
			//printf("Uma fila\n");
			tipoID = 1;
		}
		else
		{
			if (!strcmp(comando, tipo[2]))
			{
				//printf("Uma pilha\n");
				tipoID = 2;
			}
		}
	}

	do
	{
		printf("Escolha o comando para sua %s ou incerre o programa: fim, inserir e excluir\n", tipo[tipoID]);

		scanf("%s", comando);
		FormatarTexto(comando);

		if (!strcmp(comando, "inserir"))
		{
			printf("Digite o valor que deseja inserir:\n");
			scanf("%i", &num);
			switch (tipoID)
			{
			case 0:
				InsercaoLista(lista, tipo[tipoID], num);
				Ordenar(lista->elemento, lista->final);
				break;
			case 1:
				InsercaoLista(lista, tipo[tipoID], num);
				break;
			case 2:
				InsercaoLista(lista, tipo[tipoID], num);	
				break;
			}
		}
		else
		{
			if (!strcmp(comando, "excluir"))
			{

				switch (tipoID)
				{

				case 0:
					printf("Digite o valor que deseja excluir\n");
					scanf("%i", &num);
					deletarLista(lista, tipo[tipoID], num);	
					break;
				case 1:
					deletarFila(lista, tipo[tipoID], 1);
					break;
				case 2:
					deletarFila(lista, tipo[tipoID], lista->final + 1);
					break;
				}
			}
		}
		
		system("cls");
		Apresentar(lista, tipo[tipoID]);

	} while (strcmp(comando, "fim"));
}

/*
	Aqui estÃ£o as funÃ§Ãµes do projeto-------------------------------------------------------------------------------
*/

bool Cheia(Lista *lista)
{
	return (lista->final == MAX - 1) ? true : false;
}

//checar se a lista esta vazia
bool Vazio(Lista *lista)
{
	return (lista->final == -1) ? true : false;
}

void Iniciar(Lista *lista)
{
	lista->inicio = 0;
	lista->final = -1;
	lista->no = 0;
}

void InsercaoLista(Lista *lista, char tipo[], int num)
{
	if (Cheia(lista))
	{
		printf("A lista esta cheia nao pode ser inserido nenhum valor\n");
	}
	else
	{
		lista->final++;
		lista->elemento[lista->final] = num;
	}
}

void deletarLista(Lista *lista, char tipo[], int num)
{
	bool achou = false;

	if (Vazio(lista))
	{
		printf("A %s esta vazia nao pode ser deletado nenhum valor\n", tipo);
	}
	else
	{
		for (lista->no = 0; (lista->no <= lista->final) && achou == false; lista->no++)
		{
			if (lista->elemento[lista->no] == num)
			{
				achou = true;
			}
		}
		if (achou)
			Remover(lista);
		else
			printf("Nao encontado\n");
	}
}

void deletarFila(Lista *lista, char tipo[], int posisao)
{
	if (Vazio(lista))
	{
		printf("A %s esta vazia nao pode ser deletado nenhum valor\n", tipo);
	}
	else
	{
		lista->no = posisao;
		Remover(lista);
	}
}

void Remover(Lista *lista)
{
	while (lista->no <= lista->final)
	{
		printf("%i\n\n", lista->no);
		lista->elemento[lista->no - 1] = lista->elemento[lista->no];
		lista->no++;
	}
	lista->final--;
}
// transforma a palavra toda para letras minusculas para melhor tratamento das strings para comparasao

void FormatarTexto(char texto[])
{
	int quant = strlen(texto);
	int letra;

	for (letra = 0; letra < quant; letra++)
	{
		texto[letra] = tolower(texto[letra]);
	}
}

//apresenta lista, tabela e pilha
void Apresentar(Lista *lista, char tipo[])
{
	if (Vazio(lista))
	{
		printf("Lista vazia!\nRetornando as opicoes\n");
	}
	else
	{
		for (lista->no = 0; (lista->no <= lista->final); lista->no++)
		{
			if (lista->no == 0)
			{
				printf("=================================================\n");
				printf("\t\t%s\n", tipo);
				printf("=================================================\n");
				printf("\tPosicao %i valor %i\n", lista->no + 1, lista->elemento[lista->no]);
			}
			else{
				printf("\tPosicao %i valor %i\n", lista->no + 1, lista->elemento[lista->no]);
			}	
		}
	}
}

void Ordenar(int prt_num[], int max)
{
	int i, j = 0, aux;
	bool troca = true;

	while (troca)
	{
		troca = false;

		for (i = 0; i < max - j; i++)
		{
			if (prt_num[i] > prt_num[i + 1])
			{

				aux = prt_num[i];
				prt_num[i] = prt_num[i + 1];
				prt_num[i + 1] = aux;

				troca = true;
			}
		}
		j++;
	}
}
