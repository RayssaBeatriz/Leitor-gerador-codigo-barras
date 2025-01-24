//declaração das funções.
#ifndef COMANDO_H
#define COMANDO_H
#include <stdio.h>

int validar_identificador(int *ptr);// declaração da função para validação do digito verificador.

typedef struct{
    int espacamento_lat; //O espaçamento lateral do código na imagem (em pixels).
    int pixel_area; //A quantidade de pixels por área do código (em pixels).
    int altura; //A altura do código de barra (em pixels).
    char nome[100]; //O nome da imagem PBM a ser gerada.
}preferencias;


void converter_binario(char *ptr, int *ptroriginal, int espa); // função para converter de int para seu equivalente em binario na forma de string

int criarPBM(preferencias dados, char *ptr);

int existe(char *nome);

void head();

void loading();
#endif 