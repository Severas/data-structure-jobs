#include<stdio.h>
#include<stdlib.h>

int buscaLinear(int *vetor, int vProcurado , int tamVet){
    int i;
    for ( i=0; i < tamVet; i++ ){
        if ( vProcurado == vetor[i])
            return i;
    }
    return i;
}

int buscaBinaria(int *vetor, int vProcurado, int tamVet, int *passos){
    int i, inicio = 0, fim = tamVet - 1;

    while (inicio <= fim) {
        *passos+=1;
        i = (inicio + fim) / 2;

        if (vetor[i] == vProcurado)
            return i;
        else if (vProcurado< vetor[i])
            fim=i-1;
        else if(vProcurado>vetor[i])
            inicio=i+1;
    }
    return tamVet+1;
}

int main(){
    int xProcurado=0, nTamanho=0, i=0, *vetor, numPosicao=0, passosBinarios=0, eleEh=0,existeNum=0;
    printf("Insira o tamanho do vetor");
    scanf("%d", &nTamanho);
    vetor = (int *)(malloc(nTamanho*sizeof(int)));
    
    for ( i = 0; i < nTamanho; i++)
        scanf("%d", (vetor+i));
    printf("valorque procuramos");
    scanf("%d", &xProcurado);
    
    numPosicao=buscaLinear(vetor, xProcurado, nTamanho);

    if (numPosicao<nTamanho)
        printf("\nBusca Linear:\n%d esta na posicao %d\nTotal: %d Passos",xProcurado,numPosicao,numPosicao+1);
    
    else
        printf("\nBusca Linear:\n%d nao encontrado\nTotal: %d Passos",xProcurado,numPosicao);
    

    for (i = 0; i < nTamanho; i++)
    {
        if (vetor[i]>vetor[i+1]&&i+1!=nTamanho)
            eleEh+=1;
    }

    if(eleEh<1){
        numPosicao=buscaBinaria(vetor, xProcurado, nTamanho, &passosBinarios);

        if (numPosicao<nTamanho)
            printf("\n\nBusca Binaria:\n%d esta na posicao %d\nTotal: %d Passos",xProcurado,numPosicao,passosBinarios); 
        else
            printf("\n\nBusca Binaria:\n%d nao encontrado\nTotal: %d Passos",xProcurado,passosBinarios); 
    }else{
        printf("\n\nVetor nao ordenado");
    }

    free(vetor);
    return 0;
}