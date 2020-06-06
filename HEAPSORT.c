# data-structure

//APLICAÇÃO DO HEAPSORT
/*
Implemente o algoritmo de ordenação HeapSort. Escreva um procedimento separado para as seguintes operações: a) maxheapfy(...), 
b) build-max-heap(…), c) heap-extract-max(…) e d)heapSort(…).

ENTRADA:
A entrada consiste de duas linhas, sendo a primeira contendo um número inteiro N (1 ≤ N ≤ 10.000) que especifica a quantidade de valores
do arranjo original a serem ordenados. A segunda linha contém uma sequência de números inteiros separados por espaços, onde cada número 
inteiro Ai pode estar na faixa: 0 ≤ Ai ≤ 10.000, correspondendo ao arranjo original a ser ordenado.

SAÍDA:
A saída consiste de duas linhas, sendo a primeira o vetor rearranjado após chamada a rotina build-max-heap(…). A segunda linha 
corresponde ao vetor final devidamente ordenado. 

Exemplos de entradas e saídas no final
*/

#include <stdio.h>
#include <stdlib.h>
#define MAXTAM 10000 //Tamanho máximo de um array

//Troca dois elementos do array de lugar
int swap(int *x, int *y) {
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;
}

//Encontra o maior elemento do heap
void MAX_HEAPFY(int A[], int i, int tam) {
    int max, l, r;
    l = 2*i;
    r = 2*i+1;
   
    if(l<=tam && A[l]>A[i])
        max = l;
    else max = i;
    if(r<=tam && A[r]>A[max])
        max = r;
   
    if(max!=i) {
        swap(&A[i], &A[max]);
        MAX_HEAPFY(A, max, tam);
    }
}

//Constrói um heap máximo
void BUILD_MAX_HEAP(int A[], int tam) {
    int n;
    n = tam;
    for(int i=n/2; i>0; i--)
        MAX_HEAPFY(A, i, tam);
}

//Retira o maior elemento do array e decrementa seu tamanho
int HEAP_EXTRACT_MAX(int A[], int tam) {
    int max, last;
    if(tam<1)
        return 0;
    max = A[1];
    last = tam;
    A[1] = A[last];
    tam--;
    MAX_HEAPFY(A, 1, tam);
    return max;
}

//Imprime o array quando necessário
void ImprimeVetor(int A[], int tam) {
    for(int j=1; j<tam+1; j++)
        printf("%d ", A[j]);
    printf("\n");
}

//Método de ordenação interna HEAPSORT
void HEAPSORT(int A[], int tam) {
    BUILD_MAX_HEAP(A, tam);
    ImprimeVetor(A, tam); //Imprime o array após a construção o heap
    int n = tam;
    int V[n+1];
    while (n>0) {
        V[n] = HEAP_EXTRACT_MAX(A, n);
        n--;
    }
    ImprimeVetor(V, tam); //Imprime o vetor já ordenado
}

int main(void) {
    int vet[MAXTAM], n;
   
    //printf("Digite a quantidade de valores do vetor: ");
    scanf("%d", &n);
   
    for(int i=1; i<n+1; i++) //Lê os n valores do array lado a lado
        scanf("%d", &vet[i]);
   
    HEAPSORT(vet, n);
}

/*
Exemplo de Entrada 1 
4
8 5 6 7

Exemplo de Saída 1
8 7 6 5
5 6 7 8
____________________
Exemplo de Entrada 2 
10
10 2 4 5 8 5 6 7 11 20

Exemplo de Saída 2
20 11 6 10 8 5 4 7 5 2
2 4 5 5 6 7 8 10 11 20
*/
