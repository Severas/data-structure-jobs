/**
 * fazer comentario sobre char_max
*/

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define     MAX_AGE_SIZE         3
#define     MAX_ID_SIZE         31
#define     MAX_LINE_SIZE     1035
#define     MAX_NAME_SIZE     1001

typedef     enum        TrieStatus TrieStatus;
typedef     struct      Trie Trie;
typedef     struct      User User;

Trie*       createNoh               ();
User*       searchTrieRecursive     (Trie *, unsigned char *, int, int);
void        insertTrieRecursive     (Trie **, unsigned char *, User * , int , int);
void        setNameAge              (Trie *, char *, User *,int *, int *,int *);
void        textProcessing          (char *, char *);
void        textProcessingInputKey  (char *);
void        removeKeyRecursive      (Trie **, unsigned char *, int , int);


enum TrieStatus { LIVRE = 0, OCUPADO };

//declaracao da struct da trie
struct Trie {
    struct Trie *children[CHAR_MAX];
    TrieStatus status;
    User *brandStruct;
};

/*
* declaracao da struct do usuario, em relacao a idade optei por utilizar string,
* visto que nao vi muito sentido em armazenar como inteiro, ja que a variavel sofreria calculo sobre a idade.
*/
struct User {
    char id[MAX_ID_SIZE],
    name[MAX_NAME_SIZE],
    age[MAX_AGE_SIZE];
};

/*cria um novo noh*/
Trie* createNoh() {
    int i;

    //aloca  memoria para um novo noh
    Trie* noh = malloc(sizeof(Trie));

    //seta o status do noh como livre
    noh->status = LIVRE;

    //atribui null para os filhos
    for( i = 0; i < CHAR_MAX; i++)
        noh->children[i] = NULL;

    return noh;
}

/**
 * Busca recursivamente na Trie por ate que confirme todos os elementos ou que se prove NULL.
 * Obs: retorna o indice do ponteiro que contem as informacoes correspondentes a chave.
*/
User* searchTrieRecursive(Trie* Trie, unsigned char *key, int sizeKey, int lenghtTrie) {
    //verifica se eh nulo, caso seja retorna null
    if(Trie == NULL)
        return NULL;
    
    // percore a trie ate que ate completar a palavra, e retorna o endereco de memoria da struct onde esta
    if(sizeKey == lenghtTrie)
        return (Trie->brandStruct);

    return searchTrieRecursive(Trie->children[key[lenghtTrie]], key, sizeKey,lenghtTrie+1);
}

/**
 * Insere recursivamente na Trie por ate que atribua todos os elementos.
 * Obs: Insere o valor e marcar o ultimo caracter.
*/
void insertTrieRecursive(Trie **Trie, unsigned char *key, User *brandStruct, int sizeKey, int lenghtTrie) {
    //cria novo noh se for NULL
    if(*Trie == NULL)
        *Trie =  createNoh(key[lenghtTrie]);

    //se for ultimo caracter, marca como ocupado e salva o endereco de memoria da struct com as informacoes da chave.
    if(sizeKey == lenghtTrie) {
        (*Trie)->status = OCUPADO;
        (*Trie)->brandStruct = brandStruct;
        return;
    }
    
    return insertTrieRecursive(&(*Trie)->children[key[lenghtTrie]],key,brandStruct,sizeKey,lenghtTrie+1);
}

/*Separa a Sring, insere os elementos na struct e o ID na arvore.*/
void setNameAge(Trie *Trie, char *tempLine, User *data,int *i, int *j,int *lines) {
    char sup2[MAX_LINE_SIZE], sup1[2], *token;
    int assistant;

    //copia a string para facilitar a manipulacao
    strcpy(sup2,tempLine);
    // extrai ponto onde comecao os numeros
    assistant=strcspn(tempLine,"0123456789");
    sup1[0]=sup2[assistant];

    // caso a idade tnh apenas um digito, corta caracteres desnecessarios
    if(sup2[assistant+1]=='\n')
        sup1[1]=0;
    else
        sup1[1]=sup2[assistant+1];
    //corta caracteres desnecessarios, sup1 recebe os digitos referente a idade do usuario
    sup1[2]=0;

    //atribui \0 onde comeca os numeros
    tempLine[assistant]='\0';

    //copia a idade do usuario para a struct
    strcpy(data[*i].age, sup1);
    //divide a string em espacos em  branco
    token=strtok(tempLine, " ");

    while(token!=NULL) {
        if(*j==0)
            strcpy(data[*i].id, token), *j+=1;
        else {
            //concatena os nomes para dentro da struct.
            strcat(data[*i].name, token);
            strcat(data[*i].name, " ");
        }
        token=strtok(NULL, " ");
    }

    if(*i > 0 && *i < lines){
        printf("%s %s\n", data[*i].id,data[*i].name );
        insertTrieRecursive(Trie, &(data[*i].id[0]), &data[*i], strlen(&(data[*i].id[0])), 0);
    }
    // remove o " " do ultimo do nome do usuario
    data[*i].name[(strlen(data[*i].name) - 1)] = '\0';
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
void textProcessingInputKey(char *input) {
    input[0]=' ';
    input[1]=' ';
    input[2]=' ';
}

/*Faz a remocao dos noh recursivamente, liberando memoria e atribuindo null para evitar bugs posteriores com o noh pai.*/
void removeKeyRecursive(Trie **Trie, unsigned char *key, int sizeKey, int lenghtTrie) {
    int i;
    if(*Trie == NULL)
        return;

    //verifica se eh o ultimo elemento e atribui livre e modifica o endereco de memoria para 0.
    if(sizeKey == lenghtTrie){
        (*Trie)->status=LIVRE;
        (*Trie)->brandStruct = 0;
    }
        
    else
        removeKeyRecursive(&(*Trie)->children[key[lenghtTrie]], key, sizeKey, lenghtTrie+1);
    
    //verifica se algum noh ja esta ocupado, para nao remover por acidente.
    if((*Trie)->status == OCUPADO)
        return;

    for ( i = 0; i < CHAR_MAX; i++)
        if((*Trie)->children[i]!=NULL)
            return;
    
    //liberar memoria
    free(*Trie);

    // remover para o pai nao apontar para ele
    Trie = NULL;
}

int main() {
    
    FILE *arch;
    Trie *Trie = NULL;
    User *data;
    User *Sup;

    char cod, input[MAX_LINE_SIZE] = "Come abacate, bem. faz bem!", tempLine[MAX_LINE_SIZE];
    int assistant = 0, control = 0, i = 0, j = 0, k = 0, lines = 0, mark = 0;
    
    // open the banco.txt
    arch = fopen("banco.txt","r");

    //verfica se existe erro na leitura
    if(arch == NULL) {
        printf("\nErro ao ler 'banco.txt'\n");
        return -1;
    }

    //faz a leitura do primeiro elemento do txt, o qual eh por informar o numero pix cadastrados
    cod = fgetc(arch);
    // faz conversao de  char para int
    lines = cod - '0';
    control+=lines;
    data = (User*) malloc((lines+1) * sizeof(User));
    
    if(arch == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else
        while((fgets(tempLine, sizeof(tempLine), arch)) != NULL)
            //faz o tratamento da string e armazena na struct data.
            setNameAge(&Trie, &tempLine, data, &i, &j, &lines);

    // input
    while (input[0] != 'F') {

        fgets(input,MAX_LINE_SIZE,stdin);

        switch(input[2]){
            case '?':
                // tratar o texto e remover "\n"
                textProcessing(input, tempLine);

                //verifica se o elemento foi inserido na Trie e qual seu endereco.
                Sup = searchTrieRecursive(Trie, tempLine, strlen(tempLine), 0);

                if(Sup == NULL)
                    printf("ID %s nao encontrado.\n", tempLine);
                else
                    printf("(%s|%s|%s)\n", Sup->id, Sup->name, Sup->age);

                tempLine[0]=0;
                break;

            case '+':
                //usar para remover "> +"
                textProcessingInputKey(input);
                // tratar o texto e remover "\n"
                textProcessing(input, tempLine);

                //operacoes para controle e linhas e posicao
                i+=1;
                lines += 2;
                
                //faz o tratamento da string e armazena na struct data.
                setNameAge(&Trie, &input, data, &i, &j, &lines);
                control += 1;
                i-=1;

                //verifica se o elemento foi inserido, e faz o printf.
                Sup = searchTrieRecursive(Trie, tempLine, strlen(tempLine), 0);
                
                printf("Inserido (%s|%s|%s)\n", Sup->id, Sup->name, Sup->age);
                break;

            case '-':
                //usar para remover "> -"
                textProcessingInputKey(input);

                //verifica onde o elemtento inserido e qual sua posicao.
                textProcessing(input, tempLine);

                //utilizar funcao de busca para retornar onde esta a struct
                Sup = searchTrieRecursive(Trie, tempLine, strlen(tempLine), 0);
                if(Sup!= NULL){
                    //remove efetivamete a chave da trie
                    removeKeyRecursive(&Trie, Sup->id, strlen(Sup->id), 0);
                    printf("Removido (%s|%s|%s)\n", Sup->id, Sup->name, Sup->age);
                                
                    //realoca a struct na memoria com o novo tamanho.
                   // data=(User*) realloc(data,(control+1)*sizeof(User)); inicialmente tentava realocar a memoria, porem geravam diversos bugs na insercao, ao remover o realloc tudo
                    lines+=1;
                    control-=1;
                }else{
                    printf("ID %s nao encontrado.", tempLine);
                }
                break;

            case 'P':
                //faz a busca de todos os elementos que sao validos e printa
                for (k = 0; k <= lines ; k++) {
                    //verifica se o elemento foi inserido na Trie e qual seu endereco.
                    Sup = searchTrieRecursive(Trie, data[k].id, strlen(data[k].id), 0);

                    if(Sup->id != NULL) {
                        //printa os dados do usuario
                        printf("(%s|%s|%s)\n", Sup->id, Sup->name, Sup->age);
                    }
                }
                break;

            case 'S':
                //fecha o arquivo aberto com 'r' e abre com 'w'
                fclose(arch);
                arch=fopen("banco.txt", "w");
                //escreve no arquivo o numero de cadastros
                fprintf(arch,"%d\n", control);
                
                for (k = 0; k <= lines ; k++) {
                    //verifica se as chaves estao na trie
                    Sup = searchTrieRecursive(Trie, data[k].id, strlen(data[k].id), 0);

                    if(Sup->id == data[k].id) {
                        //escreve no txt
                        fprintf(arch,"%s %s %s\n", data[k].id, data[k].name, data[k].age);
                    }
                }
                printf("banco.txt salvo\n");

                //fecha o arquivo aberto com 'w' e abre com 'r+'
                fclose(arch);
                arch=fopen("banco.txt","r");
                break;

            case 'F':
                //finalizar a execucao do programa;
                fclose(arch);
                free(data);
                free(Trie);
                free(Sup);

                //encerra o menu.
                input[0] = 'F';
                break;

            default:
                printf("Desculpe, nao entendi sua resposta\n");
        }
    }
    return 0;
}

