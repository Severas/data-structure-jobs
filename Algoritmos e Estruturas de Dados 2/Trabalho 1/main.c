/**
*
*ATENCAO o valor "99999" aparece disversas vezes no codigo, utlizei dele paramelhorar meu controle sobre os erros.
* Verificar se o null eh obrigatorio com o professor ou se posso continuar com 99999
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_SIZE 1034
#define MAX_NAME_SIZE 1001
#define MAX_ID_SIZE 31
#define MAX_AGE_SIZE 3

typedef enum TrieStatus TrieStatus;
typedef struct Trie Trie;
typedef struct dataUser dataUser;

Trie* createNoh();
Trie* searchTrie(Trie *, unsigned char *);
Trie* searchTrieRecursive(Trie *, unsigned char *, int, int);
void insertTrie(Trie **, unsigned char *, int);
void insertTrieRecursive(Trie **, unsigned char *, int , int , int);
void setNameAge(Trie *, char *, dataUser *,int *, int *,int *);
void textProcessing(char *, char *);
void textProcessingTwo(char *);
void removeKey(Trie *, unsigned char *);
void removeKeyRecursive(Trie **, unsigned char *, int , int);


enum TrieStatus { LIVRE, OCUPADO };
struct Trie {
    struct Trie *children[CHAR_MAX];
    char data;
    TrieStatus status;
    int brandStruct;
};
struct dataUser {
    char id[MAX_ID_SIZE],
    name[MAX_NAME_SIZE],
    age[MAX_AGE_SIZE];
};

/*cria um novo noh*/
Trie* createNoh() {
    int i;
    Trie* noh;
    noh = malloc(sizeof(Trie));
    noh->status = LIVRE;
    for( i = 0; i < CHAR_MAX; i++) {
        noh->children[i] = NULL;
    }
    return noh;
}

/*reaper de busca na Trie*/
Trie* searchTrie(Trie *Trie, unsigned char *key) {
    return searchTrieRecursive(Trie, key, strlen(key), 0);
}

/**
 * Busca recursivamente na Trie por ate que confirme todos os elementos ou que se prove NULL.
 * Obs: retorna o indice do ponteiro que contem as informacoes correspondentes a chave.
*/
Trie* searchTrieRecursive(Trie* Trie, unsigned char *key, int sizeKey, int lenghtTrie) {
    if(Trie == NULL)
        return 99999; //inicialmente utilizei NULL como retorno, porem ao fazer nova pesquisa apos remover o id retornava NULL atribuia 0 (zero), dado essa peculiaridade atribui o  valor 99999 como "99999 Trie nao existente." 
    if(sizeKey == lenghtTrie) {
        return Trie->brandStruct;
    }
    return searchTrieRecursive(Trie->children[key[lenghtTrie]], key, sizeKey,lenghtTrie+1);
}

/*reaper de inserir chaves na Trie*/
void insertTrie(Trie **Trie, unsigned char *key, int brandStruct) {
    return insertTrieRecursive(Trie, key, brandStruct, strlen(key), 0);
}

/**
 * Insere recursivamente na Trie por ate que atribua todos os elementos.
 * Obs: Inserie o valor e marcar o ultimo caracter.
*/
void insertTrieRecursive(Trie **Trie, unsigned char *key, int brandStruct, int sizeKey, int lenghtTrie) {
    if(*Trie == NULL) {
        *Trie =  createNoh(key[lenghtTrie]);
        (*Trie)->brandStruct = 99999;
    }
    if(sizeKey == lenghtTrie) {
        (*Trie)->brandStruct = brandStruct;
        (*Trie)->status = OCUPADO;
        return;
    }
    (*Trie)->data = key[lenghtTrie];
    return insertTrieRecursive(&(*Trie)->children[key[lenghtTrie]],key,brandStruct,sizeKey,lenghtTrie+1);
}

/*Separa a Sring, insere os elementos na struct e o ID na arvore.*/
void setNameAge(Trie *Trie, char *tempLine, dataUser *data,int *i, int *j,int *lines) {
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
                while(token!=NULL) {
                    if(*j==0)
                        strcpy(data[*i].id, token), *j+=1;
                    else
                        strcat(data[*i].name, token),
                        strcat(data[*i].name, " ");
                        //concatena os nomes para dentro da struct.
                    token=strtok(NULL, " ");
                }
                if(*i>0 && *i<=lines)
                    insertTrie(Trie, &(data[*i].id[0]), *i);
                *j=0;
                *i+=1;
            
    
}
/*remove o \n da entrada de texto do usuario*/
void textProcessing(char *input, char *tempLine) {
    int x;
        for(x = 4; ; x++) {
            if (input[x] == ' ' || input[x] == '\n')
                break;
            tempLine[x-4] = input[x];
        }
        tempLine[x-4] = '\0';
}
/*substitui os caracteres especiais de entrada por espaco em branco*/
void textProcessingTwo(char *input) {
    input[0]=' ';
    input[1]=' ';
    input[2]=' ';
}

/*reaper de remover chaves da Trie*/
void removeKey(Trie *Trie, unsigned char *key){
    return removeKeyRecursive(Trie,key,strlen(key),0);
}

/*Faz a remocao dos noh recursivamente, liberando memoria e atribuindo null para evitar bugs posteriores com o noh pai.*/
void removeKeyRecursive(Trie **Trie, unsigned char *key, int sizeKey, int lenghtTrie) {
    int i;
    if(*Trie == NULL)
        return;

    if(sizeKey == lenghtTrie)
        (*Trie)->status=LIVRE;
    else
        removeKeyRecursive(&(*Trie)->children[key[lenghtTrie]], key, sizeKey, lenghtTrie+1);
    
    if((*Trie)->status == OCUPADO)
        return;

    for ( i = 0; i < CHAR_MAX; i++)
        if((*Trie)->children[i]!=NULL)
            return;
    
    ///(*Trie)->brandStruct=NULL;
    free(*Trie); //liberar
    *Trie = NULL; // apagar para o pai nao apontar para ele
}

int main() {
    FILE *arch;
    Trie *Trie = NULL;
    char cod, input[MAX_LINE_SIZE] = "Come abacate, bem. faz bem!", tempLine[MAX_LINE_SIZE];
    int assistant = 0, i = 0,j = 0, lines = 0;
    // open the banco.txt
    
    arch = fopen("banco.txt","r+");
    //verfica se existe erro na leitura
    if(arch == NULL) {
        printf("\nErro ao ler 'banco.txt'");
        return 1;
    }
    //faz a leitura do primeiro elemento do txt, o qual eh por informar o numero pix cadastrados
    cod = fgetc(arch);
    // faz conversao de  char para int
    lines = cod -'0';
    dataUser *data = (dataUser*) malloc((lines+1) * sizeof(dataUser));
    
    if(arch == NULL)
        printf("Erro, nao foi possivel abrir o archuivo\n");
    else
        while((fgets(tempLine, sizeof(tempLine), arch)) != NULL)
            setNameAge(&Trie, &tempLine, data, &i, &j, &lines); //faz o tratamento da string e armazena na struct data.
        // input
    while (input[0] != 'F') {
        fgets(input,MAX_LINE_SIZE,stdin);
        switch(input[2]){
            case '?':
                textProcessing(input, tempLine);//usar para remover \n
                assistant = searchTrie(Trie, tempLine);///retorna posicao de onde estara dentro da struct.
                if(assistant == 99999)
                    printf("ID %s nao encontrado.\n", tempLine);
                else
                    data[assistant].name[(strlen(data[assistant].name) - 1)] = '\0',
                    printf("(%s|%s|%s)\n", data[assistant].id, data[assistant].name, data[assistant].age);
                break;
            case '+':
                lines += 1;
                data = (dataUser*) realloc(data,(lines+1)*sizeof(dataUser));
                textProcessingTwo(input);//usar para remover > +
                setNameAge(&Trie, &input, data, &i, &j, &lines);
                textProcessing(input, tempLine);
                //verifica se o elemento foi inserido, e faz o printf.
                assistant = searchTrie(Trie, tempLine);
                data[assistant].name[(strlen(data[assistant].name) - 1)] = '\0',
                printf("Inserido (%s|%s|%s)\n", data[assistant].id, data[assistant].name, data[assistant].age);
                break;
            case '-':
                lines -= 1;
                textProcessingTwo(input);//usar para remover > +
                textProcessing(input, tempLine);
                assistant = searchTrie(Trie, tempLine);
                //utilizar funcao de busca para retornar onde esta a struct
                removeKey(&Trie, tempLine);
                printf("Removido (%s|%s|%s)\n", data[assistant].id, data[assistant].name, data[assistant].age);
                //************falta remover da struct**************
                //e reallocar apos remover da struct
                //*************************************************
                //data=(dataUser*) realloc(data,(lines+1)*sizeof(dataUser));
                break;
            case 'P':
                //perguntar ao professor como deletear um ponto da alocado dinamicamente
                for (i = 1; i <= lines ; i++){
                    assistant = searchTrie(Trie, data[i].id);
                    if(assistant != 99999)
                    //caso nao consiga apagar a struct da forma que quero,
                    // copiar os index validos para outra struct e reutilizar esta fun para salvar
                        data[i].name[(strlen(data[i].name) - 1)] = '\0',
                        printf("(%s|%s|%s)\n", data[i].id, data[i].name, data[i].age);
                }
                //printar e salvar em ordem alfabetica
                
                break;
            case 'S':
            //printar e salvar em ordem alfabetica
            //salvar alteracao em um novo txt
            //lines vai precisar de lines+1 o numero de linhas nao esta salvo
                break;
            case 'F':
            //finalizar a execucao do programa;

                break;
            default:
                printf("Desculpe, nao entendi sua resposta\n");
                break;
        }
    }
    /*verificar se existe necessidade de deixar fora do switch*/
    fclose(arch);// fechar archuivo
    free(data);//liberar memoria
    free(tempLine);
    return 0;
    
    
}

