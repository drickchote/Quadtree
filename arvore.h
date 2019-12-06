#ifndef __arvore_quaternaria__

#define __arvore_quaternaria__ 1
#include "Ponto.h"



typedef struct No{

    int nivel;
    int cor;
    tPonto pontoInicial;
    tPonto pontoFinal;
    /**Superior Esquerda */
    struct No * no1;
    /** Superior Direita */    
    struct No * no2;
    /**Inferior Esquerda */    
    struct No * no3;
    /**Inferior direita */    
    struct No * no4;

} tQuad;

tQuad* alocaNo(int inicioX, int fimX, int inicioY, int fimY, int nivel);

void split(tQuad **raiz);

/**Verifica se existe alguma mudança de cores em determinado nó*/
int verificaBorda(tQuad *no, unsigned char* img,  int w, int h);


void montaArvore(tQuad **raiz, unsigned char *img, int w, int h );



#endif












