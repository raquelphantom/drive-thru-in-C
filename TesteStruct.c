/* BIBLIOTECAS */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

/* TIPOS PRÉ-DEFINIDOS PELO PROGRAMADOR */
typedef  struct 
{
	int		codprod;
	char	descrprod[20+1];
	float	custoprod;
}
CARDAPIO;

/* PROTÓPIPOS DE FUNÇÕES */
void consulta (void);
void cadastra(void);
void gerencia (char  opc);
char menu (void);
void gravaArq (CARDAPIO reg);

/* CONSTRUÇÃO DAS FUNÇÕES */
char menu (void)
{	char  opc;
	do
	{	system ("cls");
		printf("\n===============");
		printf("\n   M E N U     ");
		printf("\n===============");
		printf("\n 1. Cadastra   ");
		printf("\n 2. Consulta   ");
		printf("\n 0. ENCERRAR   ");
		printf("\n===============");
		printf("\n Escolha: ");
		fflush(stdin); opc = getche();
	}while (opc<'0' || opc>'2');
	return (opc);
}

void gerencia (char  opc)
{
	switch ( opc )	
	{
		case '0': exit(0); 		break;
		case '1': cadastra();	break;
		case '2': consulta();	break;
	}
}

void cadastra(void)
{	CARDAPIO   c;	
	char      op;
	do
	{	/* Captura os dados que serão gravados */
		system ("cls");
		printf ("\nCodigo do produto   : "); 
		fflush(stdin); scanf ("%i", &c.codprod);
		printf ("\nDescricao do produto: "); 
		fflush(stdin); gets(c.descrprod);
		printf ("\nCusto do produto    : "); 
		fflush(stdin); scanf ("%f", &c.custoprod);
		/* Grava os dados no arquivo */
		gravaArq(c);
		/* Deseja cadastrar outro produto? */
		printf ("\nDeseja cadastrar outro produto? [0=NAO]:");
		op = getche();
	}while ( op!='0' );
}

void gravaArq (CARDAPIO reg)
{	FILE *Arq;
	/* Abre o arquivo */
	Arq = fopen ("PRODUTOS.DAT", "w");
	if (Arq == NULL)
	{
		printf ("\nERRO AO ABRIR O PRODUTOS.DAT");
		getch();
		exit(0);
	}
	/* Grava no arquivo */
	fwrite ( &reg, sizeof(reg), 1, Arq );
	/* Fecha o arquivo */
	fclose(Arq);
}

void consulta (void)
{
	
}

/* CORPO DO PROGRAMA */
int main()
{   char escolha;
	do
	{
		escolha = menu();
		gerencia(escolha);
	}
	while ( escolha != '0' );
	return 0;
}
