# data-structure

//APLICAÇÃO DO QUICKSORT  
/*
DESCRIÇÃO DO PROBLEMA: O Quicksort é um algoritmo considerado muito rápido para a maioria das situações.  Considere o algoritmo do 
Quicksort, em que o pivô escolhido como uma mediana de 3 valores, onde esses três valores devem ser definidos como: a) primeiro 
elemento do intervalo considerado do vetor, b) o elemento na posição do meio e c) o último elemento.

Você deve implementar um programa que leia da entrada um conjunto de informações sobre N pessoas contendo o nome de cada pessoa com até 
15 caracteres e a sua idade. O seu programa deverá utilizar o algoritmo do Quicksort com escolha do pivo por mediana de 3, conforme 
indicado acima, e que ordene-os de forma crescente por idade. Posteriormente deve-se verificar se o resultado da ordenação é estável, 
ou seja, se pessoas com a mesma idade foram mantidas na mesma ordem relativa da entrada. Após a ordenação, você deve imprimir uma região
indicada da lista ordenada. 

ENTRADA:
A primeira linha da entrada contém o número N (2 ≤ N ≤ 105.000) de pessoas a serem ordenadas. Nas próximas N linhas são apresentados, 
em cada linha, um nome de até 15 caracteres e um inteiro representando a idade. A linha seguinte contém dois números P (1 ≤ P ≤ N) da 
posição do primeiro nome a ser impresso e o número M (1 ≤ M ≤ N-P+1) de pessoas a serem impressas partir do P-éssimo nome.

SAÍDA: 
Na primeira linha da saída, imprima “yes” se a ordenação for estável, ou “no”, caso contrário. Nas próximas M linhas, imprima os M nomes
e idades presentes a partir da Péssima posição da lista ordenada, uma pessoa a cada linha. 

Exemplos de entrada e saída ao final.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 16 //Tamanho máximo do nome (15 caracteres ocupáveis)

typedef struct { //Estrutura dos dados a serem recebidos, nome e idade
    char nome[MAX];
    int idade;
} TCelula;

void swap(TCelula *A, int x, int y) { //Troca a posição das idades e nomes nas respectivas posições
    int aux1;
    aux1 = A[x].idade;
    A[x].idade = A[y].idade;
    A[y].idade = aux1;
   
    char aux2[MAX];
    strcpy(aux2, A[x].nome);
    strcpy(A[x].nome, A[y].nome);
    strcpy(A[y].nome, aux2);
}

void encontraMediana(TCelula *A, int p, int ult) { //Encontra a mediana de 3 para uma escolha melhorada do pivô
    int meio, a, b, c, medianaIndice;
     
    meio = (p+ult)/2;
    a = A[p].idade;
    b = A[meio].idade;
    c = A[ult].idade;
    medianaIndice = 0;
     
    if (a < b)
        if (b < c)
            medianaIndice = meio;
        else
            if (a < c)
                medianaIndice = ult;
            else
                medianaIndice = p;
               
    else
        if (c < b)
            medianaIndice = meio;
        else
            if (c < a)
                medianaIndice = ult;
            else
                medianaIndice = p;
       
    if(medianaIndice != ult)
        swap(A, medianaIndice, ult); //Troca que coloca a mediana na última possição do arranjo para o quicksort
}

int partition(TCelula *A, int p, int ult) { //Partição dos dados
    int x, i;
    x = A[ult].idade;
    i = p-1;
    for(int j=p; j<=ult-1; j++)
        if(A[j].idade<=x) {
            i++;
            swap(A, i, j);
        }
    swap(A, i+1, ult);
    return(i+1);
}

void quicksort(TCelula *A, int p, int ult) { //Ordena os dados através do Quicksort
    int q, aux;
    if(p<ult) {
        encontraMediana(A, p, ult); //Chamada da função para encontrar a mediana e colocá-la na última posição do arranjo
        q = partition(A, p, ult); //Reparte o arranjo em dois com o uso do pivô
        quicksort(A, p, q-1); //Chama recursivamente a função para valores menores que o pivô
        quicksort(A, q+1, ult); //Chama recursivamente a função para valores maiores que o pivô
    }
}

char* retorna_nome(int idade, TCelula *Inicio, int ult) { //Função utilizada para casos em que possuem duas pessoas com mesma idade
    int i;
    for(i=0; i<=ult; i++)
        if(Inicio[i].idade == idade) //É utilizado o arranjo de início na comparação
            return Inicio[i].nome; //Retorna o nome que aparece primeiro no arranjo inicial
}

int EhEstavel(TCelula *A, int p, int ult, TCelula *Inicio) { //Verifica se a ordenação é estável
    int i, j, cont=0, aux=1;
               
    for(i=0; i<ult; i++)
        for(j=i+1; j<=ult; j++) //É utilizado o arranjo final nas comparações
            if(A[i].idade == A[j].idade) { //Compara se há duas pessoas com mesma idade
                cont++; //Contador para saber se existe ou não idades iguais
                if(strcmp(retorna_nome(A[i].idade, Inicio, ult), A[i].nome))
                    /* Em caso afirmativo, Verifica se o nome que aparece primeiro no arranjo final
                    é o mesmo que aparece prmeiro no arranjo inicial, se a resposta for negativa, aux recebe 0 */
                    aux = 0;
            }
           
    if(aux==0 || cont==0) //Imprime se é instável ou não
        printf("no");
    else
        printf("yes");
       
    return 1;
}


int main(void) {
    int medianaIndice, n, i, p=0, ult, num, x;
    TCelula *lista, *Inicio;
   
    //printf("Digite o número de pessoas a serem ordenadas: ");
    scanf("%d", &n);

    ult = n-1; //Definindo a última posição do arranjo

    lista = (TCelula*)malloc(n*sizeof(TCelula)); //Aloca dinamicamente um vetor de estruturas com os nomes e idades
    for(i=0; i<n; i++)
        scanf("%s %d", lista[i].nome, &lista[i].idade);
   
    Inicio = (TCelula*)malloc(n*sizeof(TCelula)); //Guarda os dados iniciais também de forma dinâmica
    for(i=0; i<n; i++) {
        strcpy(Inicio[i].nome, lista[i].nome);
        Inicio[i].idade = lista[i].idade;
    }

    //printf("Digite a posição do primeiro nome a ser impresso e o número de nomes a serem impressos: ");
    scanf("%d %d", &x, &num);
   
    quicksort(lista, p, ult);
    EhEstavel(lista, p, ult, Inicio);
   
    for(i=x-1; i<x+num-1; i++) //Imprime os dados no intervalo determinado pelo usuário
        printf("\n%s %d", lista[i].nome, lista[i].idade);
       
    free(lista); //Libera a memória alocada
    free(Inicio);
}

/*
Exemplo de Entrada 1
4
Alex 20
Gabriel 20
Joana 18
Rodrigo 18
1 4

Exemplo de Saída 1
no
Rodrigo 18
Joana 18
Alex 20
Gabriel 20
_______________________

Exemplo de Entrada 2
5
Daniel 25
Ana 21
Jose 22
Silvia 25
Joao 23
3 2

Exemplo de Saída 2
yes
Joao 23
Daniel 25
*/
