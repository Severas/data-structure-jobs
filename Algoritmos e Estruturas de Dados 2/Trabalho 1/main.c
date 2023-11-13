#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
// Define o tamanho do caractere
#define MAX_LINE_SIZE 1034
#define MAX_NAME_SIZE 1001
#define MAX_ID_SIZE 31
#define MAX_AGE_SIZE 3


typedef struct  dataUser
{
    char id[MAX_ID_SIZE],
    name[MAX_NAME_SIZE],
    age[MAX_AGE_SIZE];
}dataUser;

int main()
{
    FILE* arq;
    char cod,tempLine[MAX_LINE_SIZE], *token,menu[MAX_ID_SIZE+1]="Come abacate, bem. faz bem!";
    int linhas=0,i=-1,j=0,linhasSomando=0,seila;
    char sup2[MAX_LINE_SIZE],sup1[MAX_AGE_SIZE];
    // open the arquivo.txt
    arq= fopen("banco.txt","r+");
    //verfica se  existe erro na leitura
    if(arq==NULL){
        printf("\nErro ao ler 'banco.txt'");
        return 1;
    }
    //faz a leitura do primeiro elemento do txt, o qual eh por informar o numero pix cadastrados
    cod = fgetc(arq);
    // faz conversao de char para int
    linhas=cod-'0';
    linhasSomando+=linhas;
    dataUser *data=(dataUser*)malloc((linhas+1)*sizeof(dataUser));
    
    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else
        while( (fgets(tempLine, sizeof(tempLine), arq))!=NULL )
        {
            strcpy(sup2,tempLine);//copia a string para facilitar a manipulacao
            seila=strcspn(tempLine,"0123456789");// extrai posicao onde comecao os numeros
            //printf("%s\n e o seila %d", sup2,seila);
            sup1[0]=sup2[seila];
            sup1[1]=sup2[seila+1];
            //sup1 recebe os digitos referente a idade do usuario
            tempLine[seila]='\0';///atribui \0 onde comeca os numeros
            strcpy(data[i].age,sup1);//copia a idade do usuario para a struct
            token=strtok(tempLine," ");//divide a string em espacos em  branco
            
            while (token!=NULL)
            {
                if(j==0)
                    strcpy(data[i].id,token), j+=1;
                else
                    strcat(data[i].name,token),
                    strcat(data[i].name," ");
                    //concatena os nomes para dentro da struct.
                
                token=strtok(NULL," ");
            }
            printf("%s\n", data[i].id);
            j=0;
            i+=1;
        }
        // MENU
        while (menu[0]!="F")
        {
            fgets(menu,MAX_LINE_SIZE,stdin);
            switch(menu[0]){
                case '?':
                    break;
                case '+':
                    break;
                case '-':
                    break;
                case 'P':
                    break;
                case 'S':
                    break;
                case 'F':
                    break;
                default:
                    printf("Desculpe, nao entendi sua resposta");
                    break;
        }
    }
        
    fclose(arq);// fechar arquivo
    free(data);//liberar memoria
    return 0;
    
}

