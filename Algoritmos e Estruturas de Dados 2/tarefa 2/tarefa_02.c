#include<stdio.h>
#include<stdlib.h>

void fSelect_Sort(int *pVetor,int nTamanho, int *passos)
{
    int vMenor, vAux, vTemp, vTroca;

    for(vAux=0; vAux < nTamanho-1; vAux++) 
    {
        vMenor = vAux; 

        for (vTemp=vAux+1; vTemp < nTamanho; vTemp++) 
        {
            if (pVetor[vTemp] < pVetor[vMenor]){
                vMenor = vTemp; 
                *passos+=1;
            }else{
                *passos+=1;
            }
        }

        if (vMenor != vAux){
            vTroca = pVetor[vAux];
            pVetor[vAux] = pVetor[vMenor];
            pVetor[vMenor] = vTroca;
        }
    }

}

void intercala(int p, int q, int r, int *pVetor, int *passos) 
{
   int *w;  
   w = malloc ((r-p) * sizeof (int));  
   int i = p, j = q, k = 0;  

    while (i < q && j < r) {  
        if (pVetor[i] <= pVetor[j]){
            w[k++] = pVetor[i++];  
        }else{ 
            w[k++] = pVetor[j++]; 
        }
        *passos+=1;
   }  
    while (i < q)
    {
      w[k++] = pVetor[i++];  
    }
    while (j < r)
    {
          w[k++] = pVetor[j++];
    }  
    for (i = p; i < r; ++i)
    {
      pVetor[i] = w[i-p]; 
    }
    free (w);  
}

void fMerge_Sort(int *pVetor,int nTamanho,int *passos)
{
   int b = 1;
   while (b < nTamanho) {
      int p = 0;
      while (p + b < nTamanho) {
         int r = p + 2*b;
         if (r > nTamanho){
            r = nTamanho;
            *passos+=1;
         }
         intercala(p, p+b, r, pVetor, passos);
         p = p + 2*b; 
         
      }
      
      b = 2*b;
   }
}

void mostrarVet(int *pVetor,int nTamanho){
    for (int i = 0; i < nTamanho; i++)
    {
        printf("%d ", pVetor[i]);
    }
}

int main()
{
    int nTamanho=0, i=0, *vetor, *vetorB, passosA=0, passosB=0;

    scanf("%d", &nTamanho);
    vetor = (int *)(malloc(nTamanho*sizeof(int)));
    vetorB = (int *)(malloc(nTamanho*sizeof(int)));

    for ( i = 0; i < nTamanho; i++)
    {   printf("manda a %d ", i);
        scanf("%d", (vetor+i));
        vetorB[i]=vetor[i];
    }

    // Grupo A 
    fSelect_Sort(vetor,nTamanho,&passosA);
    printf("\nSelectionSort\n");
    mostrarVet(vetor,nTamanho);
    printf("\n%d comparacoes\n",passosA);
    // Grupo B 
    fMerge_Sort(vetorB,nTamanho,&passosB);
    printf("\nMergeSort\n");
    mostrarVet(vetorB,nTamanho);
    printf("\n%d comparacoes\n",passosB);

    free(vetor);
    free(vetorB);
    return 0;
}
