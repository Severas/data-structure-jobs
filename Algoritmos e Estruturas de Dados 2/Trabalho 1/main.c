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
    char data;
    TrieStatus status;
    int brandStruct;
}Trie;

// Lista de funcoes

//void removeKey(Trie*, unsigned char*);



Trie* searchTrieRecursive(Trie* T, unsigned char *key, int sizeKey, int lenghtTrie){
    if (T == NULL)
        return 99999; //inicialmente utilizei NULL como retorno, porem ao fazer nova pesquisa apos remover o id retornava NULL atribuia 0 (zero), dado essa peculiaridade atribui o  valor 99999 como "99999 Trie nao existente." 
    if(sizeKey == lenghtTrie){
        return T->brandStruct;
    }

    return searchTrieRecursive(T->children[key[lenghtTrie]], key, sizeKey,lenghtTrie+1);
}

Trie* createNoh(){
    int i;
    Trie* noh;
    noh = malloc(sizeof(Trie));
    noh->status = LIVRE;
    //noh->data=data;
    for ( i = 0; i < CHAR_MAX; i++)
    {
        noh->children[i] = NULL;
    }
    return noh;
}

void insertTrieRecursive(Trie **T, unsigned char *key, int brandStruct, int sizeKey, int lenghtTrie){
    if(*T == NULL){
        *T =  createNoh(key[lenghtTrie]);
        (*T)->brandStruct = 99999;// valor para atribuir a noh sem dono, para facilitar o menu
    }
    if(sizeKey == lenghtTrie){// inserie o valor e marcar o ultimo caracter
        (*T)->brandStruct = brandStruct;
        (*T)->status = OCUPADO;
        //(*T)->data = key[lenghtTrie];
        //printf("%c - ", key[lenghtTrie]);
        return;
    }
    (*T)->data = key[lenghtTrie];
    
    //printf("%c - ",(*T)->data);
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
    ///(*T)->brandStruct=NULL;
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

Trie* searchTrie(Trie *T, unsigned char *key){
    return searchTrieRecursive(T, key, strlen(key), 0);
}
/*Separa a Sring, insere os elementos na struct e o ID na arvore.*/
void setNameAge(Trie *T, char *tempLine, dataUser *data,int *i, int *j,int *lines){
    char sup2[MAX_LINE_SIZE], sup1[2], *token;
    int assistant;
                strcpy(sup2,tempLine);//copia a string para facilitar a manipulacao
                assistant=strcspn(tempLine,"0123456789");// extrai ponto onde comecao os numeros
                
                sup1[0]=sup2[assistant];
                if(sup2[assistant+1]=='\n') // caso a idade tnh apenas um digito
                    sup1[1]=0;//corta caracteres desnecessarios
                else
                    sup1[1]=sup2[assistant+1];
                sup1[2]=0;//corta caracteres desnecessarios
                //sup1 recebe os digitos referente a idade do usuario
                tempLine[assistant]='\0';///atribui \0 onde comeca os numeros
    
                strcpy(data[*i].age,sup1);//copia a idade do usuario para a struct
                token=strtok(tempLine," ");//divide a string em espacos em  branco
                while (token!=NULL)
                {
                    if(*j==0)
                        strcpy(data[*i].id, token), *j+=1;
                    else
                        strcat(data[*i].name, token),
                        strcat(data[*i].name, " ");
                        //concatena os nomes para dentro da struct.
                    token=strtok(NULL, " ");
                }
                if(*i>0 && *i<=lines)
                    insertTrie(T, &(data[*i].id[0]), *i);
                *j=0;
                *i+=1;
            
    
}

void textProcessing(char *menu, char *tokenn){
    int x;
        for (x = 4; ; x++) {
            if (menu[x] == ' ' || menu[x] == '\n')
                break;
            tokenn[x-4] = menu[x];
        }
        tokenn[x-4] = '\0';
}
void textProcessingTwo(char *menu){
    menu[0]=' ';
    menu[1]=' ';
}

int main()
{
    FILE *arq;
    char cod,tempLine[MAX_LINE_SIZE], *token, tokenn[1000],menu[MAX_ID_SIZE+1]="Come abacate, bem. faz bem!";
    int lines=0,i=0,j=0,linhasSomando=0,assistant;
    Trie *T = NULL;
    // open the arquivo.txt
    arq= fopen("banco.txt","r+");
    //verfica se  existe erro na leitura
    if(arq==NULL){
        printf("\nErro ao ler 'banco.txt'");
        return 1;
    }
    //faz a leitura do primeiro elemento do txt, o qual eh por informar o numero pix cadastrados
    cod = fgetc(arq);
    // faz conversao de  char para int
    lines=cod-'0';
    linhasSomando+=lines;
    dataUser *data = (dataUser*) malloc((lines+1)*sizeof(dataUser));
    
    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else
        while( (fgets(tempLine, sizeof(tempLine), arq))!=NULL )
            printf("%s\n", tempLine),
            setNameAge(&T,&tempLine,data,&i,&j,&lines); //faz o tratamento da string e armazena na struct data.

        // MENU
        while (menu[0]!='F')
        {
            fgets(menu,MAX_LINE_SIZE,stdin);
            switch(menu[2]){
                case '?':
                    textProcessing(menu,tokenn);//usar para remover \n
                    assistant=searchTrie(T, tokenn);///retorna posicao de onde estara dentro da struct.
                    if(assistant==99999)
                        printf("ID %s nao encontrado.\n",tokenn);
                    else
                        data[assistant].name[(strlen(data[assistant].name)-1)]='\0',
                        printf("(%s|%s|%s)\n", data[assistant].id,data[assistant].name,data[assistant].age);
                    break;
                case '+':
                    lines+=1;
                    menu[2]=' ';
                    data=(dataUser*) realloc(data,(lines+1)*sizeof(dataUser));
                    textProcessingTwo(menu);//usar para remover > +
                    setNameAge(&T,&menu,data,&i,&j,&lines);
                    textProcessing(menu,tokenn);
                    
                    assistant=searchTrie(T, tokenn);
                    data[assistant].name[(strlen(data[assistant].name)-1)]='\0',
                    printf("Inserido (%s|%s|%s)\n", data[assistant].id,data[assistant].name,data[assistant].age);
                    break;
                case '-':
                // remover da arvore

                    
                    //utilizar funcao de busca para retornar onde esta a struct
                    removeKey(&T, token[1]);
                    
                    break;
                case 'P':

                    
                    break;
                case 'S':
                //salvar alteracao em um novo txt
                //lines vai precisar de lines+1 o numero de linhas nao esta salvo
                    break;
                case 'F':
                //finalizar a execucao do programa;
                    break;
                default:
                    printf("Desculpe, nao entendi sua resposta");
                    break;
        }
    }
    
    fclose(arq);// fechar arquivo
    free(data);//liberar memoria
    free(tokenn);
    return 0;
    
    
}

