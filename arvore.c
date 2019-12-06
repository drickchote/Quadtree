#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"
#include "vetoriza.h"
#include "Ponto.h"


int iHeigh, iWidth;
char * image;
/**Recebe as coordenadas do nó e retorna o nó*/
tQuad* alocaNo(int inicioX, int fimX, int inicioY, int fimY, int nivel){

    tQuad *no = malloc(sizeof(tQuad));
 
    no->nivel = nivel;
    // printf("alocando no do nivel %d\n", nivel);
    no->cor = image[inicioY*iWidth+inicioX];
    no->pontoInicial.x = inicioX;
    no->pontoInicial.y = inicioY;
    no->pontoFinal.x = fimX;
    no->pontoFinal.y = fimY;
    no->no1 = NULL;
    no->no2 = NULL;
    no->no3 = NULL;
    no->no4 = NULL;

    //  printf("%d ", no->pontoInicial.x);
    //  printf("%d ", no->pontoFinal.x);
    //  printf("%d ", no->pontoInicial.y);
    //  printf("%d\n\n",no->pontoFinal.y);
    return no;
};


/**Recebe um nó e preenche seus 4 filhos com a divisão das coordendas do pai*/
void split(tQuad **raiz){
    int inicioX = (*raiz)->pontoInicial.x;
    int inicioY = (*raiz)->pontoInicial.y;
    int fimX = (*raiz)->pontoFinal.x;
    int fimY = (*raiz)->pontoFinal.y;
    
     (*raiz)->no1 = alocaNo(inicioX, (inicioX+fimX)/2, (inicioY+fimY)/2, fimY, (*raiz)->nivel+1);
     (*raiz)->no2 = alocaNo((inicioX+fimX)/2, fimX, (inicioY+fimY)/2, fimY, (*raiz)->nivel+1);
     (*raiz)->no3 = alocaNo(inicioX, (inicioX+fimX)/2, inicioY, (inicioY+fimY)/2, (*raiz)->nivel+1);
     (*raiz)->no4 = alocaNo((inicioX+fimX)/2, fimX, inicioY, (inicioY+fimY)/2, (*raiz)->nivel+1);

    //  printf("%d ",(*raiz)->no3->pontoInicial.x);
    //  printf("%d ",(*raiz)->no3->pontoInicial.x);
    //  printf("%d ",(*raiz)->no3->pontoFinal.y);
    //  printf("%d\n\n",(*raiz)->no3->pontoFinal.y);
}

int verificaBorda(tQuad *no, unsigned char* img, int w, int h){
    // printf("Quadrado: ");
    // printf("x: %d - %d |", no->pontoInicial.x, no->pontoFinal.x);
    // printf("y: %d - %d\n\n", no->pontoInicial.y, no->pontoFinal.y);
    int inicioX = no->pontoInicial.x;
    int inicioY = no->pontoInicial.y;
    int fimX = no->pontoFinal.x;
    int fimY = no->pontoFinal.y;
    unsigned char aux = img[inicioY*w+inicioX]; //ver se isso tá certo.
    // printf("InicioX: %d\n", inicioX);
    // printf("InicioY: %d\n", inicioX);
    // printf("FimX: %d\n", fimX);
    // printf("FimY: %d\n", fimY);
    for(int i=inicioX; i<fimX; i++){
        for(int j=inicioY; j<fimY; j++){
            if(aux != img[j*w+i]){
               return 1;
            }
        }
    }
    // printf("%d\n", x);
    return 0;
}


void montaArvore(tQuad **raiz, unsigned char *img, int w, int h){
    // printf("Criei uma arvore\n\n");
    // printf("Eita!\n");
    image = img;
    iWidth = w;
    iHeigh = h;
    // if((*raiz)->pontoInicial.x == (*raiz)->pontoFinal.x){
    //     (*raiz)->cor = 100;
    //     return;
    // }
  
    if(verificaBorda(*raiz, img, w, h)){
        // printf("O no de nivel %d tem borda\n",(*raiz)->nivel);
        tPonto pontoInicial = (*raiz)->pontoInicial;
        // (*raiz)->cor = img[pontoInicial.y*w+pontoInicial.x];
        (*raiz)->cor = 66;
        split(raiz);
        montaArvore(&((*raiz)->no1), img, w, h);
        // printf("Vou começar a montar o segundo no\n\n");
        montaArvore(&((*raiz)->no2), img, w, h);
        // printf("Vou começar a montar o terceiro no\n\n");
        montaArvore(&((*raiz)->no3), img, w, h);
        // printf("Vou começar a montar o quarto no\n\n");
        montaArvore(&((*raiz)->no4), img, w, h);
    } else {
        return;
    }
}
