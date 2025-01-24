#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Variáveis globais
int **matriz;
int largura, altura;

//Cabeçalho
void head(){
    printf("\033[1;34m======================================\033[0m\n");
    printf("\033[1;44m             Leitor EAN-8             \033[0m\n");
    printf("\033[1;34m======================================\033[0m\n");
    printf("\033[1;34mSeja bem vindo ao nosso leitor EAN-8\033[0m\n");
}

void ler_arquivo(char arquivo[100]){
    char tipo[3], formato[4];

    FILE *file = fopen(arquivo, "r");
    
    //Verificar se o arquivo é valido
    int tam = strlen(arquivo);
    strncpy(formato, &arquivo[tam - 3], 3);
    formato[3] = '\0';

    if (!file || strcmp(formato, "pbm") != 0) {
        perror("Erro ao abrir o arquivo. O arquivo é inválido.");
        exit(1);
    }else{
        printf("Arquivo válido\n");
    }
    

    //Ler tipo, altura e largura
    fscanf(file, "%s", tipo);
    fscanf(file, "%d %d", &largura, &altura);

    //Alocar memória para a matriz
    matriz = (int**)malloc(sizeof(int*) * altura);
    for(int i = 0; i < altura; i++){
        matriz[i] = (int*)malloc(sizeof(int) * largura);
    }
    
    //Gerar matriz
    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            fscanf(file, "%d", &matriz[i][j]);
        }
    }

   /*
    //Imprimir matriz
    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    */

    //Fechar arquivo
    fclose(file);
    
}

void extrai_identificador(){
    //Identificar bordas
    int comp = 0, k = 0;
    int borda_superior, borda_lateral;
    
    for(int i = 0; i < altura; i++){
        if(comp == 1){
            break;
        }
        for(int j = 0; j < largura; j++){
            comp = matriz[i][j];
            if(comp == 1){
                break;
            }else{
                k++;
            }
        }   
    }
    borda_superior = k / largura;
    borda_lateral = k % largura;

    //Identificar área
    int area = 0;
    for(int i = borda_lateral; i < largura; i++){
        if(matriz[borda_superior][i] == 0){
            break;
        }else{
            area++;
        }
    }

    printf("Identificador do código de barras: ");
    
    //Identificar dígitos da esquerda
    int l_code[10] = {1101, 11001, 10011, 111101, 100011, 110001, 101111 , 111011, 110111, 1011};
    int m = 0, num;
    char numero[10] = "";
    char temp[3]; 

    //Percorrer as primeiras areas
    for(int i = borda_lateral + (3 * area); i <= borda_lateral + (31 * area); i = i + area){
        //Separar de 7 em 7
        if(m < 7){
            sprintf(temp, "%d" , matriz[borda_superior][i]);
            strcat(numero, temp);
            num = atoi(numero);
            m++;
        }
        //Identificar número correspondente    
        else{
            for(int n = 0; n < 10; n++){
                if(num == l_code[n]){
                    printf("%d", n);
                    break;
                }
            }
            numero[0] = '\0';
            temp[0] = '\0';
            i = i - area;
            m = 0;
        }
    }

    //Identificar dígitos da direita
    int r_code[10] = {1110010, 1100110, 1101100, 1000010, 1011100, 1001110, 1010000, 1000100, 1001000, 1110100};
    int m1 = 0, num1;
    char numero1[10] = "";
    char temp1[3]; 

    //Percorrer as areas restantes
    for(int i = borda_lateral + (36 * area); i <= largura - borda_lateral; i = i + area){
        //Separar de 7 em 7
        if(m1 < 7){
            sprintf(temp1, "%d" , matriz[borda_superior][i]);
            strcat(numero1, temp1);
            num1 = atoi(numero1);
            m1++;    
        }
        //Identificar número correspondente
        else{
            for(int n = 0; n < 10; n++){
                if(num1 == r_code[n]){
                    printf("%d", n);
                    break;
                }
            }
            numero1[0] = '\0';
            temp1[0] = '\0';
            i = i - area;
            m1 = 0;
        }
    }
    
    //Liberar memória
    for (int i = 0; i < altura; i++) {
    free(matriz[i]);
    }
    free(matriz);
}

int main()
{
    char arquivo[100];

    head();

    scanf("%s", arquivo);
    ler_arquivo(arquivo);
    extrai_identificador();
    printf("\n");
    system("pause");
    return 0;
}
