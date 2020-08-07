//Pesquisa Interna - Hashing com Encadeamento

#include <stdio.h>
#include <stdlib.h>

typedef struct SCelula *TCelula; //Define TCelula como um ponteiro para uma célula

typedef struct SCelula { //Estrutura de cada célula
    TCelula ant, prox; //Ponteiros pras células anterior e próxima
    int chave; //Item a ser armazenada
} TLista;

TCelula Inicia(TCelula Celula) { //Inicializa a Celula
    Celula = (TCelula)malloc(sizeof(TLista));
    Celula->prox = NULL;
    Celula->ant = NULL;
}
 
void Insere(TCelula *Celula, int chave){ //Insere um novo elemento
    TCelula Novo, Aux;
    Aux = (*Celula);
    Novo = (TCelula)malloc(sizeof(TLista));
    Novo->chave = chave;
    Novo->prox = NULL;
    while(Aux->prox != NULL)
        Aux = Aux->prox;
    Aux->prox = Novo;
    Novo->ant = Aux;
   
}

void Remove(TCelula *Celula) { //Remove um elemento
    TCelula Aux;
    (*Celula)->ant->prox = (*Celula)->prox;
    if((*Celula)->prox != NULL)
        (*Celula)->prox->ant = (*Celula)->ant;
    Aux = (*Celula);
    free(Aux);
}

int FunctionHash(int k, int tam) { //Retorna o resultado da Função Hash de divisão
    if(k>0) return(k%tam);
    else return 0;
}

void Imprime(TCelula *Lista, int indice){ //Imprime
    TCelula Aux;
    printf("\n[%d] ", indice);
    if((*Lista)->prox != NULL){
        Aux = (*Lista)->prox;
        while(Aux != NULL){
            printf("%d ", Aux->chave);
            Aux = Aux->prox;
        }
    }  
}

TCelula BuscaChave(TCelula *Lista, int chave) { //Busca um determinado elemento
    if((*Lista)->ant==NULL && (*Lista)->prox==NULL)
        return NULL;
       
    if((*Lista)->chave == chave)
        return (*Lista);
       
    if((*Lista)->prox != NULL)
        return BuscaChave(&(*Lista)->prox, chave);
   
    return NULL;
}


int main() {
    TCelula Pesquisa, Aux;
    TCelula *Hash;
    int tam, quant, num, chaveBusca, indice;
   
    printf("Entre com o tamanho da tabela Hash: ");
    scanf("%d", &tam);
   
    Hash = (TCelula*)malloc(tam*sizeof(TCelula)); //Inicializa a Tabela Hash, uma lista de listas
   
    for(int j=0; j<tam; j++)
        Hash[j] = Inicia(Aux); //Inicializa cada uma das listas da tabela
   
    printf("Entre com a quantidade de números de entrada: ");
    scanf("%d", &quant);
   
    for(int i=0; i<quant; i++) {
        scanf("%d", &num);
        Insere(&Hash[FunctionHash(num, tam)], num); //Insere os elementos lidos na tabela
    }
   
    printf("Entre com a chave a ser pesquisada na tabela: ");
    scanf("%d", &chaveBusca);
   
    indice = FunctionHash(chaveBusca, tam);
    Pesquisa = BuscaChave(&Hash[indice], chaveBusca); //Verifica se a chave de busca foi encontrada na tabela
   
    if(Pesquisa!=NULL)
        Remove(&Pesquisa); //Caso seja encontrada, a chave é removida da tabela
    else
        Insere(&Hash[indice], chaveBusca); //Caso não seja encontrada, a chave é inserida na tabela

    for(int i=0; i<tam; i++)
        Imprime(&Hash[i], i); //Imprime a Tabela Hash final
}
