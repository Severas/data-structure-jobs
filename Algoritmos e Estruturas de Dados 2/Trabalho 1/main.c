#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define o tamanho das strings
#define MAX_LINE_SIZE 1034
#define MAX_NAME_SIZE 1001
#define MAX_ID_SIZE 31
#define MAX_AGE_SIZE 3

typedef enum TrieStatus TrieStatus;

enum TrieStatus { LIVRE, OCUPADO };

typedef struct Trie
{
    struct Trie *children[CHAR_MAX];
    TrieStatus status;
    int brandStruct;
}Trie;

// Lista de funcoes

//void removeKey(Trie*, unsigned char*);



Trie* searchTrieRecursive(Trie* T, unsigned char *key, int sizeKey, int lenghtTrie){
    printf("estou aqui\n");
    if (T == NULL)
        return 111;
    if(sizeKey == lenghtTrie){
        printf("%d", T->brandStruct);
        return T->brandStruct;
    }
    return searchTrieRecursive(T->children[key[lenghtTrie]], key, sizeKey,lenghtTrie+1);
}

Trie* createNoh(){
    int i;
    Trie* noh;
    noh = malloc(sizeof(Trie));
    noh->status = LIVRE;
    for ( i = 0; i < CHAR_MAX; i++)
    {
        noh->children[i] = NULL;
    }
    return noh;
}

void insertTrieRecursive(Trie **T, unsigned char *key, int brandStruct, int sizeKey, int lenghtTrie){
    if(*T == NULL)
        *T =  createNoh();
    if(sizeKey == lenghtTrie){// inserie o valor e marcar o ultimo caracter
        (*T)->brandStruct = brandStruct;
        (*T)->status = OCUPADO;
        return;
    }
    return insertTrieRecursive(&(*T)->children[key[lenghtTrie]],key,brandStruct,sizeKey,lenghtTrie+1);
}

void removeKeyRecursive(Trie **T, unsigned char *key, int sizeKey, int lenghtTrie){
    int i;

    if(*T == NULL)
        return;

    if(sizeKey == lenghtTrie)
        (*T)->status=LIVRE;
    else
        removeKeyRecursive(&(*T)->children[key[lenghtTrie]], key, sizeKey, lenghtTrie+1);

    if((*T)->status == OCUPADO)
        return;

    for ( i = 0; i < CHAR_MAX; i++) {
        if((*T)->children[i]!=NULL)
            return;
    }

    free(*T); //liberar
    *T = NULL; // apagar para o  pai nao apontar para ele
}

typedef struct  dataUser
{
    char id[MAX_ID_SIZE],
    name[MAX_NAME_SIZE],
    age[MAX_AGE_SIZE];
}dataUser;


void removeKey(Trie *T, unsigned char *key){
    return removeKeyRecursive(T,key,strlen(key),0);
}
/*povoa os noh da trie*/
void insertTrie(Trie **T, unsigned char *key, int brandStruct){
    return insertTrieRecursive(T, key, brandStruct, strlen(key), 0);
}

Trie* searchTrie(Trie* T, unsigned char *key){
    return searchTrieRecursive(T, key, strlen(key), 0);
}

int main()
{
    FILE* arq;
    char cod,tempLine[MAX_LINE_SIZE], *token,menu[MAX_ID_SIZE+1]="Come abacate, bem. faz bem!";
    int linhas=0,i=0,j=0,linhasSomando=0,seila;
    char sup2[MAX_LINE_SIZE],sup1[MAX_AGE_SIZE];
    Trie *T = NULL;
    Trie *Tsup = NULL;
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
            if(sup2[seila+1]=='\n') // caso a idade tnh apenas um digito
                sup1[1]=0;
            else
                sup1[1]=sup2[seila+1];
            //sup1 recebe os digitos referente a idade do usuario
            tempLine[seila]='\0';///atribui \0 onde comeca os numeros
            strcpy(data[i].age,sup1);//copia a idade do usuario para a struct
            token=strtok(tempLine," ");//divide a string em espacos em  branco
            
            while (token!=NULL)
            {
                if(j==0)
                    strcpy(data[i].id, token), j+=1;
                else
                    strcat(data[i].name, token),
                    strcat(data[i].name, " ");
                    //concatena os nomes para dentro da struct.
                token=strtok(NULL, " ");
            }
            printf("%d o i %s o id\n", i, data[i].age);
            if(i>0 && i<linhas){
                insertTrie(&T, &(data[i].id[0]), i);
            }
            j=0;
            i+=1;
        }

        //testar remove 
        seila=searchTrie(T, "dafd");
                printf("\nmarcacao %d\n", seila);
        // MENU
        while (menu[0]!='F')
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

