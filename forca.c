#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<locale.h>
#include<string.h>
typedef struct{
    char palavra[100];
    struct Palavra *prox;
}Palavra;
Palavra *primeiraPalavra;
Palavra *ultimaPalavra;
int tamanho;

void VerificaChances(int contador);
void MensagemVitoria(char tentativa);
void DesenhaForca(int contador,int flagInicio);
void MostrarLetrasErradas(int erro1,int erro2,int erro3,int erro4,int erro5,char tentativa,int contador);
void VerificaTentativa(char qtdCaracter,char tentativa,int *certo,int *contador,char resposta[]);
void CapturaLetra(char *tentativa);
void VerificaSeErrou(char frase[],int qtdCaracter,int *contador,char tentativa,int *erro1,int *erro2,int *erro3,int *erro4,int *erro5,int *n);
int MenurPrincipal();
char* BuscarPalavra(char nomeArquivo[]);
void CriarListaVazia();
void InseriNaLista(Palavra palavra);
int SorteiaPalavra(int faixa);
void limparLista();
int main ()
{
    setlocale(LC_ALL, "Portuguese");
    int i, contador, n, qtdCaracter, erro1, erro2, erro3, erro4, erro5, certo,opcao;
    char frase[100], resposta[100], tentativa, confirmar, continuar;
    do
    {
        MENU:
        system("cls");
        DesenhaForca(contador,1);

        opcao=MenuPrincipal();
        if(opcao==0)
        {
        exit(0);
        }
        else if(opcao==1)
        {
            strcpy(frase,BuscarPalavra("animais.txt"));
        }
        else if(opcao==2)
        {
            strcpy(frase,BuscarPalavra("profissoes.txt"));
        }
        else if(opcao==3)
        {
            strcpy(frase,BuscarPalavra("paises.txt"));
        }
        else if(opcao==4)
        {
            strcpy(frase,BuscarPalavra("filmes.txt"));
        }
        else if(opcao==5)
        {
            strcpy(frase,BuscarPalavra("seriados.txt"));
        }else{
            printf("\nOpcao Invalida tente Novamente");
           // system("cls");
            goto MENU;
        }

        confirmar = 'n';
        while(confirmar != 'S')
        {
            certo = 0;
            qtdCaracter=0;
            n = 0;
            i=0;
            contador = 0;
            erro1 = ' ';
            erro2 = ' ';
            erro3 = ' ';
            erro4 = ' ';
            erro5 = ' ';
            tentativa=' ';
            printf("O jogo sera iniciado...\n");
            system("PAUSE");
            system("CLS");
            for(i = 0; i < 100; i++)
            {
                resposta[i]='_';
            }
            while(contador < 6)
            {
                n=0;
                certo=0;
                DesenhaForca(contador,0);

                for(i=0; i < 100; i++)
                {
                    if(frase[i]=='\0')
                    {
                        qtdCaracter = i;
                        break;
                    }
                    else
                    {
                        if(frase[i]==' ')
                        {
                            resposta[i]=' ';
                            printf("%c", resposta[i]);
                        }
                        else
                        {
                            if(frase[i]==tentativa)
                            {
                                resposta[i]=frase[i];
                            }
                        }
                    }
                    printf("%c ", resposta[i]);
                }

                MostrarLetrasErradas(erro1,erro2,erro3,erro4,erro5,tentativa,contador);
                VerificaChances(contador);
                VerificaTentativa(qtdCaracter,tentativa,&certo,&contador,resposta);
                if(certo!=qtdCaracter)
                {
                    CapturaLetra(&tentativa);

                }
                VerificaSeErrou(frase,qtdCaracter,&contador,tentativa,&erro1,&erro2,&erro3,&erro4,&erro5,&n);

                system("cls");
            }


            if(contador==6)
            {
                DesenhaForca(contador,0);
                for(i = 0; i < qtdCaracter; i++)
                {
                    if(resposta[i]==frase[i])
                    {
                        printf("%c ", resposta[i]);
                    }
                    else
                    {
                        printf("(%c) ", frase[i]);
                    }
                }
                MostrarLetrasErradas(erro1,erro2,erro3,erro4,erro5,tentativa,contador);
                printf("\n\n\nVoçê Morreu !!!!\n");
                system("PAUSE");
            }
            if(contador==7)
            {
               MensagemVitoria(tentativa);
            }
            confirmar = 'S';
            printf("Deseja jogar novamente (S/N)? ");
            fflush(stdin);
            continuar = toupper(getchar());
        }
    }
    while(continuar=='S');
    system("PAUSE");
    return 0;
}

int MenuPrincipal()
{
    int opcao;
    printf("\n###############      MENU PRINCIPAL       ################");
    printf("\n#                                                        #");
    printf("\n#        Digite um comando para prosseguir:              #");
    printf("\n#                                                        #");
    printf("\n#        1 – Animais                                     #");
    printf("\n#        2 – Profissoes                                  #");
    printf("\n#        3 – Paises                                      #");
    printf("\n#        4 – Filmes                                      #");
    printf("\n#        5 – Seriados                                    #");
    printf("\n#        0 – Sair                                        #");
    printf("\n#                                                        #");
    printf("\n\n");
    scanf("%d",&opcao);
    return opcao;
}
void VerificaChances(int contador)
{
    switch(contador)
    {
    case 0:
        puts("\n\nVoce pode errar 5 vezes");
        break;
    case 1:
        puts("\n\nVoce pode errar 4 vezes");
        break;
    case 2:
        puts("\n\nVoce pode errar 3 vezes");
        break;
    case 3:
        puts("\n\nVoce pode errar 2 vezes");
        break;
    case 4:
        puts("\n\nVoce pode errar apenas mais uma vez");
        break;
    case 5:
        puts("\n\nSe errar agora voce morre!!!!");
    }

}
void MensagemVitoria(char tentativa)
{
printf("\n//////////////////////////////////////////////////////");
printf("\n***********          PARABENS            *************");
printf("\n***********            VOCE              *************");
printf("\n***********           VENCEU             *************");
printf("\n//////////////////////////////////////////////////////\n");

    tentativa='_';
}
void DesenhaForca(int contador,int flagInicio)
{
    if(flagInicio==0)
    {
        switch(contador)
        {
        case 0:
            printf("_____________   \n|.|         |   \n|.|        _|_\n|.|          \n|.|        \ \n|.|         \n|.| \n|.| \n|.| \n\n");
            break;

        case 1:
            printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|         \n|.|       \n|.| \n|.| \n|.| \n\n");
            break;

        case 2:
            printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|         |    \n|.|         \n|.| \n|.| \n|.| \n\n");
            break;

        case 3:
            printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|        /|    \n|.|         \n|.| \n|.| \n|.| \n\n");
            break;

        case 4:
            printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|        /|\\    \n|.|         \n|.| \n|.| \n|.| \n\n");
            break;

        case 5:
            printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|        /|\\    \n|.|        /  \n|.|  \n|.|  \n|.| \n\n");
            break;
        case 6:
            printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|        /|\\    \n|.|        / \\ \n|.|  \n|.|  \n|.| \n\n");
            break;
        }

    }
    else
    {
        puts("_____________ \n|.|         |   \n|.|        _|_\n|.|         O    \t JOGO DA FORCA \n|.|        /|\\   Trabalho de ProgramaçãoImperativa \n|.|        / \\     Universidade Federal de Goiás \n|.|       \t      Sistemas De Informação \n|.|     \t      Weliton Marcos P.Lima     \n|.| \n|.| \n|.| \n");
    }

}
void MostrarLetrasErradas(int erro1,int erro2,int erro3,int erro4,int erro5,char tentativa, int contador)
{
    if(contador==6)
    {
        printf("\n\n%c %c %c %c %c %c\n", erro1, erro2, erro3, erro4, erro5, tentativa);
    }
    else
    {
        printf("\n\n%c %c %c %c %c\n", erro1, erro2, erro3, erro4, erro5);
    }

}

void VerificaTentativa(char qtdCaracter,char tentativa,int *certo,int *contador,char resposta[])
{
    int i;
    for(i = 0; i <= qtdCaracter; i++)
    {
        if(tentativa!=' ')
        {
            if(resposta[i]!='_')
            {
                *certo=*certo+1;
                if(*certo==qtdCaracter)
                {
                    *contador=7;
                    break;
                }
            }
        }
    }

}
void CapturaLetra(char *tentativa)
{
    char tecla;
    printf("\n\nDigite uma letra: ");
    fflush(stdin);
    scanf("%c",&tecla);
    *tentativa=tecla;
    *tentativa = tolower(*tentativa);
}

void VerificaSeErrou(char frase[],int qtdCaracter,int *contador,char tentativa,int *erro1,int *erro2,int *erro3,int *erro4,int *erro5,int *n)
{
    int i;
    for(i = 0; i < qtdCaracter; i++)
    {
        if(tentativa!=frase[i])
        {
            *n=*n+1;
            if(*n==qtdCaracter)
            {
                *contador=*contador+1;
                if(*contador==1)
                {
                    *erro1 = tentativa;
                }
                if(*contador==2)
                {
                    *erro2 = tentativa;
                }
                if(*contador==3)
                {
                    *erro3 = tentativa;
                }
                if(*contador==4)
                {
                    *erro4 = tentativa;
                }
                if(*contador==5)
                {
                    *erro5 = tentativa;
                }
            }
        }
    }

}
char* BuscarPalavra(char nomeArquivo[])
{
    FILE *pont_arq;
    char linha[1024]; // variável do tipo string
    char palavraSorteada[100];
    Palavra palavra;
    pont_arq = fopen(nomeArquivo, "r");
    if(pont_arq == NULL)
    {
        printf("Erro na abertura do arquivo!");
        return 1;
    }
    int i=0;
    tamanho=0;
    CriarListaVazia();
    while(fscanf(pont_arq, " %[^\n]s",linha)!=EOF)
    {
        char *ptr;
        ptr=strtok(linha,";");
        strcpy(palavra.palavra,ptr);
        ptr=strtok(NULL,";");
        InseriNaLista(palavra);
        tamanho++;

    }
    fclose(pont_arq);

    Palavra lista[tamanho-1];
    Palavra *palavraAux;
    palavraAux=primeiraPalavra->prox;
    i=0;
    int numero=SorteiaPalavra(tamanho-1);
    while(palavraAux!= NULL){
        if(i==numero){
             strcpy( palavraSorteada,palavraAux->palavra);
        }
        palavraAux=palavraAux->prox;
        i++;
    }
    limparLista();
    return palavraSorteada;
}
void CriarListaVazia(){
    primeiraPalavra=(Palavra *)malloc(sizeof(Palavra));
    ultimaPalavra=primeiraPalavra;
}
void InseriNaLista(Palavra palavra){
    Palavra *palavraAux;
    palavraAux = (Palavra *)malloc(sizeof(Palavra));

    strcpy( palavraAux->palavra,palavra.palavra);

    ultimaPalavra->prox=palavraAux;
    ultimaPalavra=ultimaPalavra->prox;
    palavraAux->prox=NULL;
}
int SorteiaPalavra(int faixa){
    srand( (unsigned)time(NULL) );
    return  rand() % faixa;
}

void limparLista()//Remove todos os nós da Lista
{
    Palavra *no = primeiraPalavra, *aux;
    while (no != NULL)
    {
        aux = no;
        no = no->prox;
        free (aux);
    }
    primeiraPalavra = NULL;
    ultimaPalavra=NULL;
}
