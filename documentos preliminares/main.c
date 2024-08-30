#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>

#define NUM_MAX_CAD 10

typedef struct{

    int ocupado ;

    char nome[256];

    char tipo[256];

    char celular[13];

    int idade;

    char sexo ;

}Animal ;


Animal vetor_animal[NUM_MAX_CAD];
int total_animal = 0;


char caminho_arquivo_animal[256];



void cadastro_inicializar();

int cadastro_verificar_capacidade_maxima();

void cadastro_inserir_animal(Animal animal);

Animal cadastro_pesquisar_animal(char *celular);

int cadastro_remover_animal(char *celular);


//ARQUIVOS

void cadastro_inicializar_arquivo();

void cadastro_carregar_dados_arquivo();

void cadastro_salvar_dados_arquivo();


//TELAS

int Menu();

void Cadastrar();

void Pesquisar();

void Remover();

void Relatorio();

int Sair();


void ler_nome(char *str);

void ler_tipo(char *str);

int ler_idade();

char ler_sexo();

void ler_celular(char *str);





int main () {


    setlocale(LC_ALL, "Portuguese");

    int sair = 0;

    int opcao;

    cadastro_inicializar();

    cadastro_inicializar_arquivo();

    cadastro_carregar_dados_arquivo();



do
    {
        opcao = Menu();

        switch(opcao)
        {
            case 1:
                Cadastrar();

            break;

            case 2:
                Pesquisar();

            break;

            case 3:
                Remover();

            break;

            case 4:

                Relatorio();

            break;

            case 5:

                sair = Sair();

            break;

            default:

                printf("\nCARACTER INVALIDO !!! \n");
                system("pause");
        }

    }while(sair == 0);




    cadastro_salvar_dados_arquivo();

    system("cls");
    printf("\n!!! FIM !!!\n");

    return 0;
}

int Menu()
{

    int opcao;

    system("cls");
    printf("MENU DE OPÇÕES \n");
    printf("==========================\n");
    printf("1 - Cadastrar um animal \n");
    printf("2 - Pesquisar um animal \n");
    printf("3 - Remover um animal \n");
    printf("4 - Cadastros Salvos \n");
    printf("5 - Sair \n");
    printf("==========================\n");


    printf("Escolha uma opção: ");
    int erro = scanf("%d", &opcao);

    if(erro != 1) {

        fflush(stdin);

        opcao = -1;
    }

    return opcao;

}

void Cadastrar()
{
    int continuar;

    Animal animal;

    do {
        system("cls");
        printf("CADASTRAR :  \n");


        if(cadastro_verificar_capacidade_maxima() == 1)
        {
            printf("\nErro: O cadastro j  atingiu sua capacidade m xima!\n");
            system("pause");
        }

        ler_nome(animal.nome);

        ler_tipo(animal.tipo);

        ler_celular(animal.celular);

        animal.idade = ler_idade();

        animal.sexo = ler_sexo();

        cadastro_inserir_animal(animal);

        continuar = tela_mensagem("\nCADASTRAR OUTRO ANIMAL?");

    } while(continuar == 1);
}


void Pesquisar()

{
    int continuar;

    char celular[13];

    do{

        system("cls");
        printf("PESQUISAR : \n");

        ler_celular(celular);

        Animal animalDados = cadastro_pesquisar_animal(celular);

        if(animalDados.ocupado == 1)
        {
            printf("\nANIMAL ENCONTRADO: \n");
            printf("NOME:     %s\n", animalDados.nome);
            printf("TIPO:    %s\n", animalDados.tipo);
            printf("TELEFONE:   %s\n", animalDados.celular);
            printf("IDADE:       %d\n",animalDados.idade);
            printf("Sexo:    %c\n", animalDados.sexo);
            system("pause");
        }else{
            printf("\nNENHUM ANIMAL REGISTRADO NESSE TELEFONE!\n\n");
            system("pause");
        }



        continuar = tela_mensagem("\nPESQUISAR OUTRO ANIMAL ?");

    }while(continuar==1);

}

void Remover()
{

    int continuar;


    char celular[13];

    do
    {
        system("cls");
        printf("3 - REMOVER \n\n");


        ler_celular(celular);


        int rs = cadastro_remover_animal(celular);

        if(rs == 1)
        {
            printf("\nCADASTRO REMOVIDO!\n");
        }
        else
        {
            printf("\nNAO FOI POSSIVEL REMOVER ESTE CADASTRO!\n");
        }

        system("pause");



        continuar = tela_mensagem("\nGOSTARIA DE REMOVER OUTRO CADASTRO?");

    }while(continuar);
}


void Relatorio()
{
    system("cls");
    printf("RELAORIO : \n\n");

    printf("TOTAL DE ANIMAIS CADASTRADOS : %d\n\n", total_animal);

    for(int i=0; i<NUM_MAX_CAD; i++){

        if(vetor_animal[i].ocupado == 1)
        {
            printf("%s\n", vetor_animal[i].nome);
            printf("%s\n", vetor_animal[i].tipo);
            printf("%s\n", vetor_animal[i].celular);
            printf("%d\n", vetor_animal[i].idade);
            printf("%c\n", vetor_animal[i].sexo);

        }
    }

    system("pause");
}


int Sair()
{
    int sair;
    system("cls");
    printf("5 - Sair \n\n");


    sair = tela_mensagem("\nDESEJA MESMO ENCERRAR O PROGRAMA??");

    return sair;
}


int cadastro_remover_animal(char *celular)
{

    int idxPesquisa = -1;


    for(int i = 0; i < NUM_MAX_CAD; i++) {

        if(vetor_animal[i].ocupado == 1)
        {
            if(strcmp(vetor_animal[i].celular, celular) == 0){

                total_animal = total_animal - 1;

                vetor_animal[i].ocupado = 0;

                idxPesquisa = i;


                break;
            }
        }
    }


    if(idxPesquisa != -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


Animal cadastro_pesquisar_animal(char *celular)

{
    int idxPesquisa = -1;

    for(int i = 0 ; i<NUM_MAX_CAD ; i++){


        if(vetor_animal[i].ocupado == 1)
        {
            if(strcmp(vetor_animal[i].celular,celular) == 0 ) {

                idxPesquisa = i;

                break;
            }
        }
    }

    if(idxPesquisa != -1)
    {

        return vetor_animal[idxPesquisa];

    }
    else {

        Animal animalSemDados = {" "," "," ",0,' '};

        return animalSemDados;

    }
}



void ler_nome(char *str)
{
    int erro;


    do
    {
        erro = 0;

        printf("\nDIGITE O NOME DO ANIMAL: ");
        scanf(" %255[^\n]", str);


        fflush(stdin);



        if(strlen(str) > 254)
        {
            erro = 1;
            printf("!!ERRO!! MAXIMO DE CARACTERES EXCEDIDO \n");
        }
        if(strlen(str) < 3) {
            erro = 1;
            printf("ERRO!! NOME DEVE TER PELO MENOS 3 CARACTERES \n");
        }

    } while(erro == 1);
}

void ler_tipo(char *str)
{
    int erro;

    do{
        erro = 0 ;


        printf("QUAL O ANIMAL : ");
        scanf("%255[^\n]",str);

        fflush(stdin);



        if(strlen(str) > 254)
        {
            erro = 1 ;
            printf("EXCEDEU O NUMERO DE CARACTERES '254'");

        }

        if(strlen(str)<3)
        {
            erro = 1;
            printf("!ERRO!DEVE CONTER PELO MENOS 3 CARACTERES ");

        }

    }while(erro ==1);

}

void ler_celular(char *str)
{
    int erro;

    do
    {
        erro = 0;

        printf("DIGITE O NUMERO DE TELEFONE: ");
        scanf(" %12s", str);

        fflush(stdin);

        if(strlen(str) != 12)
        {
            erro = 1;
            printf("!ERRO! O NUMERO DE TELEFONE DEVE TER 12 DIGITOS.\n");
        }

    } while(erro == 1);
}

int ler_idade()
{
    int erro;

    int idade;

    do
    {
        printf("DIGITE A IDADE DO ANIMAL: ");
        //
        erro = scanf("%d", &idade);


        fflush(stdin);


        if(erro != 1)
        {
            printf("ERRO: DIGITE UM VALOR VALIDO (>=1) \n");
        }

        else if(idade < 1 || idade > 14)
        {
            erro = -1;
            printf("!ERRO! DIGITE UMA IDADE ENTRE 1 E 14\n");
        }

    }while(erro != 1);

    return idade;
}

char ler_sexo()
{
    int erro;

    char sexo;

    char strSexo[3];

    do
    {
        erro = 0;

        printf("DIGITE O SEXO DO ANIMAL : (M / F): ");


        scanf(" %2[^\n]", strSexo);


        fflush(stdin);


        if(strlen(strSexo) == 1)
        {

            sexo = toupper(strSexo[0]);
        }
        else
        {
            erro = 1;
        }


        if( !(sexo == 'M' || sexo == 'F') || erro == 1 )
        {
            erro = 1;
            printf("!ERRO! M' ou 'F'!\n");
        }

    }while(erro == 1);

    return sexo;

}

int tela_mensagem(char *mensagem)
{
    char ch;
    char texto[256] = "";
    int erro;

    strcat(texto, mensagem);
    strcat(texto, " (s/n): ");

    do {

        erro = 0;


        printf(texto);


        scanf(" %c", &ch);


        fflush(stdin);


        ch = toupper(ch);


        if( !(ch == 'S' || ch == 'N') )
        {
            erro = 1;
            printf("ERRO!!!! 'S' ou 'N'!\n");
        }


    } while(erro);


    if(ch == 'S') return 1;
    else return 0;
}


void cadastro_inicializar()
{

    total_animal = 0;


    for(int i=0; i < NUM_MAX_CAD; i++)
    {

        vetor_animal[i].ocupado = 0;
    }
}

int cadastro_verificar_capacidade_maxima()
{

    if(total_animal >= NUM_MAX_CAD)
    {

        return 1;
    }
    else
    {

        return 0;
    }
}


void cadastro_inserir_animal(Animal animal)
{
    if(cadastro_verificar_capacidade_maxima() == 1)
    {
        printf("Erro: Capacidade máxima atingida!\n");
        return;
    }

    for(int i = 0; i < NUM_MAX_CAD; i++)
    {
        if(vetor_animal[i].ocupado == 0)
        {
            vetor_animal[i] = animal;
            vetor_animal[i].ocupado = 1;
            total_animal++;
            break;
        }
    }
}




void cadastro_inicializar_arquivo()
{

	strcpy(caminho_arquivo_animal, "Animais.txt");


	FILE *fp = fopen(caminho_arquivo_animal, "r");


	if(fp == NULL)
    {

		fp = fopen(caminho_arquivo_animal, "w");


		fprintf(fp, "%d\n", total_animal);


		fclose(fp);

	}

	else
    {

		fclose(fp);
	}
}

void cadastro_carregar_dados_arquivo()
{

	FILE *fp = fopen (caminho_arquivo_animal, "r");


	if(fp == NULL){
		printf("!!! ERRO !!!");
		exit(EXIT_FAILURE);
	}


	fscanf(fp, "%d ", &total_animal);

	int i;

	for(i=0; i < total_animal; i++){

		Animal animal;


		fscanf(fp, "%255[^\n] ", animal.nome);
		fscanf(fp, "%255[^\n] ", animal.tipo);
		fscanf(fp, "%13[^\n] ", animal.celular);
		fscanf(fp, "%d ", &animal.idade);
		fscanf(fp, "%c ", &animal.sexo);

		animal.ocupado = 1;

		vetor_animal[i] = animal;

	}


	fclose(fp);
}



void cadastro_salvar_dados_arquivo()
{

	FILE *fp = fopen (caminho_arquivo_animal, "w");


	if(fp == NULL){
		printf("!!! ERRO !!!");
		exit(EXIT_FAILURE);
	}


	fprintf(fp, "%d\n", total_animal);


	for(int i=0; i < NUM_MAX_CAD; i++)
    {

        if(vetor_animal[i].ocupado == 1)
        {

            fprintf(fp, "%s\n", vetor_animal[i].nome);
            fprintf(fp, "%s\n", vetor_animal[i].tipo);
            fprintf(fp, "%s\n", vetor_animal[i].celular);
            fprintf(fp, "%d\n", vetor_animal[i].idade);
            fprintf(fp, "%c\n", vetor_animal[i].sexo);

        }
    }


	fclose(fp);
}
