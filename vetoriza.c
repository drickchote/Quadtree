#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include <GL/glut.h>

#include "Ponto.h"
#include "winGL.h"
#include "arvore.h"
		
unsigned char* 	image = NULL;	// image file
int 			iHeight, 
				iWidth,
				iChannels;
tQuad * 		raiz;
bool 			desenha = true;
int 			nivelTeclado = 10;

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void negativaImage(unsigned char* img, int w, int h) {

	unsigned char 	aux;
	int 			i,
					j;
	
	if (img == NULL)
		return;

	for (j = 0 ; j < h ; j++) 
		for (i = 0 ; i < w ; i++) 
			img[j*w+i] = 255 - img[j*w+i]; 
}

// ***********************************************
// ******                                   ******
// ***********************************************

void desenhaArvore(tQuad *r, int nivel){
	
	if(r == NULL) {
		printf("saindo\n");	return;
	}
	printf("Estou no nivel %d, nivel pretendido: %d\n", r->nivel, nivel);
	if(r->nivel == nivel){
		desenhaQuadrante(r->pontoInicial,r->pontoFinal, r->cor);
		return;
	} else if(r->nivel < nivel && r->no1 != NULL && r->no2 !=NULL && r->no3 != NULL && r->no4 != NULL) {
		printf("Entrando no no 1\n");
		desenhaArvore(r->no1, nivel);
		printf("Entrando no no 2\n");
		desenhaArvore(r->no2, nivel);
		printf("Entrando no no 3\n");
		desenhaArvore(r->no3, nivel);
		printf("Entrando no no 4\n");
		desenhaArvore(r->no4, nivel);
	} else{
		return;
	}
}

void desenhaVetorizacao() {

	printf("Aqui eu vou desenhar o resultado da vetorizacao\n");
	
	// rotina que deve ser implementada para visualizacao da arvore
	// utilize a rotina desenhaQuadrante(p0, p1, cor)
	// fornecendo os pontos inicial e final do quadrante e a sua cor
	// funcao do valor do pixel ou da regiao que voce quer desenhar
	
	// tPonto p0, p1;
	 
	 desenhaArvore(raiz, nivelTeclado);
	// p0.x = p0.y = 0;

}
	
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void vetorizaImagem() {
	
	printf("Aqui eu vou construir a estrutura base para a vetorizacao\n");
	
	raiz = alocaNo(0,iWidth, 0, iHeight, 1);
	// printf("Tamanho: x: %d, y: %d", iWidth, iHeight)
	montaArvore(&raiz, image, iWidth, iHeight);
	// if(verificaBorda(raiz, image, iWidth, iHeight)){
	// 	printf("Tem borda");
	// } else {
	// 	printf("Tem borda não");
	// }
}
	
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void teclado(unsigned char key, int x, int y) {

	switch (key) {
		case 27		: 	exit(0);
						break;				
		case 'v'	:
		case 'V'	: 	vetorizaImagem();
						break;				
		case 'q'	:
		case 'Q'	: 	desenha = !desenha;
						break;	

		case 'r'	: 	
		case 'R'	: 	negativaImage(image, iHeight, iWidth);
						break;		
		case '0'	:   nivelTeclado = 0;
		break;	
		case '1'	:   nivelTeclado = 1;
						break;	
		case '2'	:   nivelTeclado = 2;
						break;	
		case '3'	:   nivelTeclado = 3;
						break;	
		case '4'	:   nivelTeclado = 4;
						break;	
		case '5'	:   nivelTeclado = 5;
						break;	
		case '6'	:   nivelTeclado = 6;
						break;	
		case '7'	:   nivelTeclado = 7;
						break;	
		case '8'	:   nivelTeclado = 8;
						break;	
		case '9'	:   nivelTeclado = 9;
						break;

		case 37		:
		case 40     : if(nivelTeclado>0)
						nivelTeclado--;	
						break;
		case 38		: 
		case 39     : if(nivelTeclado>0)
						nivelTeclado--;	
						break;
		}
	glutPostRedisplay();
}
		
/// ***********************************************************************
/// **
/// ***********************************************************************

void mouse(int button, int button_state, int x, int y ) {

	if 	(button_state == GLUT_DOWN ) {
		switch (button) {
			
			case GLUT_LEFT_BUTTON	: 	printf("botao esquerdo?\n");
										break;
	
			case GLUT_RIGHT_BUTTON	:	printf("botao direito?\n");
										break;
			}
		glutPostRedisplay();
		}
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void desenho(void) {

    glClear (GL_COLOR_BUFFER_BIT); 
    
    glColor3f (1.0, 1.0, 1.0);
    
    if (desenha)
    	desenhaVetorizacao();
    else
    	glDrawPixels( iWidth, iHeight, GL_LUMINANCE, GL_UNSIGNED_BYTE, image );
   	
    glutSwapBuffers ();
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

int main(int argc, char** argv) {
	
char* filename = "images/Twitter.png";

    if (argc > 1)
		filename = argv[1];

	image = leImagem(filename);
			
	criaJanela(argc, argv);

    initOpenGL();
    
    initEventos();
    
    return 0;   
}
