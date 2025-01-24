
//implementação das funções
#include "comando.h"
#include <stdio.h>
#include <string.h>
int validar_identificador(int *ptr) {
    int soma = 0; 
    
    //laço para fazer a soma poderada de acordo com os indices.
    for (int i = 0; i < 7; i++) {
        if (i % 2 == 0) { // indice par, multiplicamos o valor por 3 e somamos na variável soma
            soma += ptr[i] * 3;
        } else {          // indice ímpar, apenassomamos na variável soma.
            soma += ptr[i];
        }
    }
    //calculando o digito verificador
    int digito = soma % 10;
    if (digito != 0) {
        digito = 10 - digito;
    }
    
    if (digito != ptr[7]) { //caso os valores não sejam iguais o digito vrificador informado não é válido.
        printf("\033[1;37;41mDigito verificador invalido!\033[0m\n");
        return 1;
    }
}


void converter_binario(char *ptr, int *ptroriginal, int espa){
    for(int i = 0; i<espa; i++){ // adicionando no array o espaçamento da esquerda
        strcat(ptr, "0");
    }
    
    strcat(ptr, "101"); //adicionando o limitador inicial do código

    for(int i = 0; i < 4; i++){
        switch (ptroriginal[i])
        {
        case 0:
            strcat(ptr, "0001101");
            break;
        case 1:
            strcat(ptr, "0011001");
            break;
        case 2:
            strcat(ptr, "0010011");
            break;
        case 3:
            strcat(ptr, "0111101");
            break;
        case 4:
            strcat(ptr, "0100011");
            break;
        case 5:
            strcat(ptr, "0110001");
            break;
        case 6:
            strcat(ptr, "0101111");
            break;
        case 7:
            strcat(ptr, "0111011");
            break;
        case 8:
            strcat(ptr, "0110111");
            break;
        case 9:
            strcat(ptr, "0001011");
            break;
        default:
            printf("Erro ao tentar converter para binário");
            break;
        }
    }

    strcat(ptr, "01010"); //adicionando o limitador de meio do código

    for(int i = 4; i < 8; i++){
        switch (ptroriginal[i])
        {
        case 0:
            strcat(ptr, "1110010");
            break;
        case 1:
            strcat(ptr, "1100110");
            break;
        case 2:
            strcat(ptr, "1101100");
            break;
        case 3:
            strcat(ptr, "1000010");
            break;
        case 4:
            strcat(ptr, "1011100");
            break;
        case 5:
            strcat(ptr, "1001110");
            break;
        case 6:
            strcat(ptr, "1010000");
            break;
        case 7:
            strcat(ptr, "1000100");
            break;
        case 8:
            strcat(ptr, "1001000");
            break;
        case 9:
            strcat(ptr, "1110100");
            break;
        default:
            printf("Erro ao tentar converter para binário");
            break;
        }
    }

    strcat(ptr, "101"); //adicionando o limitador final do código

    for(int i = 0; i<espa; i++){ // adicionando no array o espaçamento da esquerda
        strcat(ptr, "0");
    }     
}


int criarPBM(preferencias dados, char *ptr) {
    printf("Caminho completo: %s\n", dados.nome);
    FILE *arquivo = fopen(dados.nome, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir ou criar o arquivo!\n");
        return 1;
    }

    // Cabeçalho do arquivo PBM
    fprintf(arquivo, "P1\n");

    // Calculando dimensões da imagem
    int largura = strlen(ptr);
    int altura = dados.altura * dados.pixel_area + 2 * dados.espacamento_lat * dados.pixel_area;

    // Escrevendo as dimensões
    fprintf(arquivo, "%d %d\n", largura, altura);

    // Espaçamento superior 
    for (int i = 0; i < dados.espacamento_lat * dados.pixel_area; i++) {
        for (int j = 0; j < largura; j++) {
            fprintf(arquivo, "0");
            if (j < largura - 1) fprintf(arquivo, " "); 
        }
        fprintf(arquivo, "\n"); 
    }

    // Conteúdo principal com quebras de linha baseadas na largura
    for (int i = 0; i < dados.altura * dados.pixel_area; i++) {
        for (int j = 0; j < largura; j++) {
            fprintf(arquivo, "%c", ptr[j]);
            if (j < largura - 1) fprintf(arquivo, " "); // Espaço entre os pixels
        }
        fprintf(arquivo, "\n"); // Quebra de linha ao final de cada linha
    }

    // Espaçamento inferior (linhas completamente pretas)
    for (int i = 0; i < dados.espacamento_lat * dados.pixel_area; i++) {
        for (int j = 0; j < largura; j++) {
            fprintf(arquivo, "0");
            if (j < largura - 1) fprintf(arquivo, " "); // Espaço entre os pixels
        }
        fprintf(arquivo, "\n"); // Quebra de linha ao final
    }

    fclose(arquivo);
    return 0; // Indica sucesso
}





int existe(char *nome){
    int decisao = 1;
    FILE *arquivo = fopen(nome, "r");

    if (arquivo != NULL) {
        printf("\033[1;37mJa existe um arquivo com este nome\033[0m\n");
        printf("\033[1;36Deseja sobreescrever o arquivo?\033[0m\n");
        printf("1 - sim\n");
        printf("2 - nao\n");
        scanf("%d", &decisao);
        fclose(arquivo);
        return decisao;
    }
    else{
        return decisao;
    }
}

void head(){
    printf("\033[1;34m=======================================\033[0m\n");
    printf("\033[1;44m             Gerador EAN-8             \033[0m\n");
    printf("\033[1;34m=======================================\033[0m\n");
    printf("\033[1;34mSeja bem vindo ao nosso gerador EAN-8\033[0m\n");
}


