#include<stdio.h>>
#include<stdlib.h>

typedef enum trieEstado
{//marcacao para o ultimo caracter de informacao valida
    LIVRE,
    OCUPADO
}trieEstado;

typedef struct user
{
    char id[MAX_STRING_SIZ]
    name[MAX_STRING_SIZE],
    age[MAX_STRING_SIZE];
}user;

int main(int argc, char const *argv[])
{
    FILE* arq;
    char cod,tempLine[MAX_LINE_SIZE];
    int linhas=0,i=0,j=0,aux,linhasSomando=0;
    
    // open the arquivo.txt
    arq= fopen("banco.txt","r+");
    // verfica se  existe erro na leitura
    if(arq==NULL){
        printf("\nErro ao ler 'banco.txt'");
        return 1;
    }
    // faz a leitura do primeiro elemento do txt, o qual eh por informar o numero pix cadastrados
    cod = fgetc(arq);
    // faz conversao de char para int
    linhas = cod - '0';


    return 0;
}
