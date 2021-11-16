#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>


struct lista
{
    int Tamanho;
    int inicio;
    int fim;
    int lock;
    int* list;
};

void inserir(struct lista* Lista);
void remover(struct lista* Lista );

int main ()
{   

    /* Alocando Memoria compartilhada */
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANON;

    int estruturaLista = sizeof(struct lista);
    int tamLista = 200; /// 200 posicoes
    
    /*Alocando lista********************/
    
    struct lista* Lista = (struct lista*) mmap(NULL, estruturaLista, protection, visibility, 0, 0);
    if((long int)Lista == -1)
    {
        printf("Erro de alocacao! \n");
        return 0;
    }else
    { 
        
        printf("\nEstrutura da lista alocada com Sucesso!\n");
    }

    Lista->list = mmap(NULL, sizeof(int)*tamLista, protection, visibility, 0, 0);
    if((long int)Lista->list  == -1)
    {
        printf("Erro de alocacao! \n");
        return 0;
    }else
    { 

        printf("\nVetor de interiros da lista alocada com Sucesso!\n");

        // Iniciando Estrutura
        Lista->fim = -1;
        Lista->inicio = -1;
        Lista->Tamanho = tamLista;
        Lista->lock = 0;

    }
    /* Processos ****************/
    pid_t childpid;
    childpid = fork();
    printf("o childpid eh %i\n",childpid);

    if (childpid == 0)
    { //filho    
        int true = 10;
        do
        {
            Lista->lock = 1;
            while (Lista->lock)
            {
                remover(Lista);
                Lista->lock = 0;
            }
            
        } while (true--);
        
    } 
    else 
    {
        int true = 50;
        do
        {
            Lista->lock = 1;
            while (Lista->lock)
            {
                inserir(Lista);
                Lista->lock = 0;
            }
            
        } while (true--);
        

    }

    /*Imprimindo lista **//*
    printf("\n Lista Fim -> %i\n", Lista->fim);
    for (int i = 0; i< Lista->fim; i++)
    {
        printf(" %i ", Lista->list[i]);
    }*/


}
void inserir(struct lista* Lista)
{// Inserir 1 elemento aleatorio na lista
    printf("\nInserir");
    if (Lista->fim == -1 && Lista->inicio == -1)
    {
        Lista->inicio = 0;
        Lista->fim = 0;
        Lista->list[Lista->fim] = rand()%100;
    }
    if(Lista->fim < Lista->Tamanho)
    {
        Lista->fim++;
        Lista->list[Lista->fim] = rand()%100;
        
    }
    
}
void remover(struct lista* Lista )
{ // Remove 1 elemento no final da lista.
    printf(" \n Remover");
    if(Lista->fim != -1 && Lista->inicio != -1)
    {
        if ((Lista->fim-1) == -1)
        {
            Lista->fim = -1;
            Lista->inicio = -1;
        }else
        {
            Lista->fim = Lista->fim - 1;
        }
    }
    
}
