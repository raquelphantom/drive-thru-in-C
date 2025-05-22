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
void imprimeRelat(void);

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
	Arq = fopen ("PRODUTOS.DAT", "a");
	if (Arq == NULL)
	{	printf ("\nERRO AO ABRIR O PRODUTOS.DAT");
		printf ("\nEndereco lido: %p", Arq);
		getch();
		exit(0);
	}
	printf ("\nEndereco de PRODUTOS.DAT: %p", Arq);
	/* Grava no arquivo */
	fwrite ( &reg, sizeof(reg), 1, Arq );
	/* Fecha o arquivo */
	fclose(Arq);
}

void consulta (void)
{	FILE *Arq;
	CARDAPIO reg;
	char	 opc;
    /* Abre o arquivo para leitura "r" */
	Arq = fopen ("PRODUTOS.DAT", "r");
	if (Arq == NULL)
	{	printf ("\nERRO AO LER PRODUTOS.DAT");
		printf ("\nEndereco lido: %p", Arq);
		getch();
		exit(0);
	}
	/* Enquanto não for fim de arquivo (EOF)...*/
	system ("cls");
	printf ("\nCod\tDescricao\tCusto");
	printf ("\n---------------------");
	while ( !feof(Arq) )
	{	/*... leio do arquivo */
		fread ( &reg, sizeof(reg), 1, Arq );
		/* Testa se foi lido EOF */
		if (!feof(Arq))
		{	/* Depois, mostra na tela o conteúdo lido */	
			printf ("\n%i\t%s\t R$%.2f", 
			reg.codprod, reg.descrprod, reg.custoprod);
		}
	}
	/* Fecha o arquivo */
	fclose(Arq);
	printf("\nDeseja imprimir o relatório? [1=Sim]");
	fflush(stdin); opc=getche();
	if ( opc=='1')
		imprimeRelat();
	getch();
}

void imprimeRelat(void)
{   FILE *Arq, *Relat;
	CARDAPIO reg;
    /* Abre o arquivo para leitura "r" */
	Arq = fopen ("PRODUTOS.DAT", "r");
	if (Arq == NULL)
	{	printf ("\nERRO AO LER PRODUTOS.DAT");
		printf ("\nEndereco lido: %p", Arq);
		getch();
		exit(0);
	}	
	/* Criar o arquivo RELAT.TXT */
	Relat = fopen ("RELAT.TXT", "w");
	if (Relat == NULL)
	{	printf ("\nERRO AO GERAR RELAT.TXT");
		printf ("\nEndereco lido: %p", Arq);
		getch();
		exit(0);
	}	
	/* Enquanto não for fim de arquivo (EOF)...*/
	fprintf ( Relat, "\nRELATORIO DE PRODUTOS");
	fprintf ( Relat, "\nCod\tDescricao\tCusto");
	fprintf ( Relat, "\n---------------------");
	while ( !feof(Arq) )
	{	/*... leio do arquivo */
		fread ( &reg, sizeof(reg), 1, Arq );
		/* Testa se foi lido EOF */
		if (!feof(Arq))
		{	/* Depois, gravo no Relat o conteúdo lido */	
			fprintf ( Relat, "\n%i\t%s\t R$%.2f", 
			reg.codprod, reg.descrprod, reg.custoprod);
		}
	}
	/* Fecha os arquivos */
	fclose(Arq);
	fclose(Relat);
	printf ("\nArquivo RELAT.TXT gerado com sucesso!");
	getch();
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
