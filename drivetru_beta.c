#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int cod;
	char descr[20+1];
	float custo;
}CARDAPIO; //nome do tipo
//protótipo (pode chamar a função de onde quiser)
char menu (void);
void grava (CARDAPIO reg);
void cadastra (void);
void consulta (void);
void gerencia (char opc);

char menu (void){
	char opc;
	do{
	system("cls");
	printf("\n ======================= \n");
	printf("             MENU         ");
	printf("\n ======================= \n");
	printf("1- Cadastrar\n");
	printf("2- Consulta\n");
	printf("0 - Encerrar\n");
	printf("Escolha:");
	fflush(stdin);opc = getche();
	}while(opc<'0' || opc>'2');
		return (opc);
};
void cadastra (void){
	CARDAPIO prod;
	char op;
	do{
		system ("cls");
		printf("\nCodigo do produto: ");
		fflush(stdin); scanf ("%i", &prod.cod);
		
		system ("cls");
		printf("\nDescricao: ");
		fflush(stdin); gets (prod.descr);
		//gets - não da problema com espaço entre palavras
		system ("cls");
		printf("\nCusto: ");
		fflush(stdin); scanf ("%f", &prod.custo);
		//Grava no arquivo
		grava(prod);
		//gravar outro
		printf("\ngostaria de continuar? 0 - não");
		fflush(stdin); scanf ("%c", &op);
		
	}while(op!='0');
};
void grava(CARDAPIO reg){
	FILE *arq;// * pointer - endereço
	arq = fopen("prod.DAT","a");//abre ; w - grava como se fosse novo (reescreve); a - grava
	if(arq == NULL)
	{
		printf("\n erro ao abrir, my friend");
		getch();
		exit(0);
	}
	fwrite(&reg, sizeof(reg), 1, arq);//escreve
	fclose(arq);//fecha
	
	
};
void consulta (void){
	FILE *arq;
	CARDAPIO reg;
	arq = fopen("prod.DAT","r");//r - lê
	if(arq == NULL)
	{
		printf("\n erro ao abrir, my friend");
		getch();
		exit(0);
	}//(EOF) fim do arquivo - true ou false
	while(!feof(arq)){
		//lê arquivo
		fread(&reg, sizeof(reg), 1, arq);
		//testa se leu end of file
		if(!feof(arq)){
		//mostra
		printf ("\n %i \t %s \t R$%.2f",reg.cod,reg.descr,reg.custo);
		}
	}
	fclose(arq);
	printf("\nClique qualquer tecla para fechar");
	getch();
};
void gerencia (char opc){
	switch(opc){
		case '0' : exit(0); break;
		case '1' : cadastra(); break;
		case '2' : consulta(); break;
	};
};

int main(){
	char escolha;
	do{
	escolha = menu();//recebe
	gerencia(escolha);//não recebe
	} while(escolha != '0');
	return 0;
};
