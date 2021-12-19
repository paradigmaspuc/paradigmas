#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>


int main()
{
  /*o processo pai e o processo filho compartilhem uma variável simples (por exemplo, inteiro - valor 1)*/
  pid_t childpid;
  int shm_id,i,soma;
  int *p; 
  int * shrd;
  int *comp;// mesma coisa da sua variavel shrd

  shm_id = shmget(IPC_PRIVATE, 1200*4  , IPC_CREAT |  0660);
  if (shm_id < 0)
  {
    printf("shmget error\n");
  }
 
 int *d;// mesma coisa da sua variavel p
 comp = (int*)shmat(shm_id, NULL, 0);
 d=comp;



  //supostamente setando onde começa cada coisa na memoria compartilhada 
  int *qt=d;
  int *inicio=d+4;
  int *fim=d+8;
  int *lock=d+12;
  int *fila=d+16;
  //inicializando cada coisa
  *qt=0;
  *inicio=0;
  *fim=0;
  *lock=0;


    /*o processo pai imprime o valor inicial dessa variável; em seguida, cria o processo filho e espera-o*/
    childpid = fork();
    printf("o childpid eh %i\n",childpid);
    /*o processo filho acessa esta variável, realiza uma operação (por exemplo, adição - valor 2, totalizando 3), modificando o valor; em seguida, o processo filho termina*/
    if (childpid == 0)//filho    
    { 
      do
      {
        while(lock)
        {
          *lock = 1;
          int z=0;
          while( z<1000)
          {
            int randola=1+rand() % 1000; //numero aleatorio 
            *qt=z+1;//incrementando a contidade
            if(*qt==1) 
            {
               inicio=fila;
              fim=inicio;
            }else
            {
              fim=fila;
            }
            *fila=randola; //coloca o rand na fila
            //std:: cout << *fila<<","; //(TESTE) imprimo tudo que esta na fila para comparar com a saída 
            fila=fila + 4;//pula pra proxima posicao 
            z++;
          }
        }
        *lock=0;  
       
      }while (*lock==1);
    
    }
    else
    {
     
      wait (NULL); 
      int z=0;
     // std:: cout << "\n\n///////////////////////////\n\n " ;//(TESTE) separa o teste do que o pai imprimir
  
      while( z<1000)
      {
        std:: cout << "," <<*comp;
        comp=comp+4;//aqui vejo q só esta imprimindo partes(ate a posicao 512) dos valores que estão na fila o resto sai lixos de memoria
        z++;
      }
    }
    
}
   