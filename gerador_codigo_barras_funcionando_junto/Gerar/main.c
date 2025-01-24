#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comando.h" //biblioteca de funções locais.
int main() {
    preferencias dados; // inicializando um variável do tipo "preferencias".

    int numeros[8];  // Array para armazenar o identificador de tamanho 8
    char identificador[9];  // String para armazenar a entrada (8 números + '\0')
    int i;
    head();
    // Recebendo identificador sem espaços
    printf("\033[36mInsira o identificador abaixo:\033[0m\n");
    scanf("%8s", identificador); //recebendo a "string"


    for (i = 0; i < 8; i++) {
        // Verifica se o caractere é um dígito
        if (identificador[i] < '0' || identificador[i] > '9') {
            printf("\033[1;37mErro: O caractere '%c' e invalido. Apenas numeros de 0 a 9 sao permitidos.\033[0m\n", identificador[i]);
            system("pause");
            return 1;  // Encerra o programa em caso de erro
        }
        numeros[i] = identificador[i] - '0';  // Converte o caractere para número correpondete ASCII
    }
    
    // Verifica se o identificador tem exatamente 8 caracteres
    if (strlen(identificador) != 8) {
        printf("\033[1;37;41mErro: E preciso digitar exatamente 8 numeros.\033[0m\n");
        system("pause");
        return 1;  // Encerra o programa em caso de erro
    }

    int verifica = validar_identificador(&numeros[0]); // chamando a função para validar o digito verificador.
    if(verifica == 1){
        system("pause");
        return 1;
    }

    //valores padrões
    dados.espacamento_lat = 4;
    dados.pixel_area = 1;
    dados.altura = 50;
    strcpy(dados.nome, "codigo_de_barras.pbm");
    
    printf("\033[1;36minsira os dados opcionais(em Pixels),\033[0m\n");
    printf("\033[1;36mou tecle enter para pular.\033[0m\n");
    //pedindo as informações
    printf("\n");
    printf("\033[1;36mBorda lateral:\033[0m\n");
    
    char temp[100]; //podemos usar alocação dinâmica futuramente aqui --------
    
    getchar();//removendo \n do buffer
    
    fgets(temp, sizeof(temp), stdin); // recebendo como string
    
    temp[strcspn(temp, "\n")] = '\0';// retitando o ultimo caractere
    
    if(strlen(temp) != 0){//verificando se o usuario informou algum dado
        dados.espacamento_lat = atoi(temp); // podemos depois usar strtol para uma maior segurança --------
    }

    printf("\033[1;36mDensidade de pixels:\033[0m\n");

    fgets(temp, sizeof(temp), stdin);

    temp[strcspn(temp, "\n")] = '\0';

    if(strlen(temp) != 0){
        dados.pixel_area = atoi(temp);
    }

    printf("\033[1;36mAltura do codigo de barras:\033[0m\n");

    fgets(temp, sizeof(temp), stdin);

    temp[strcspn(temp, "\n")] = '\0';

    if(strlen(temp) != 0){
        dados.altura = atoi(temp);
    }

    printf("\033[1;36mNome do arquivo:\033[0m\n");

    fgets(temp, sizeof(temp), stdin);

    temp[strcspn(temp, "\n")] = '\0';

    if(strlen(temp) != 0){
        strcpy(dados.nome, temp); // copiando o arquivo da variável temp para a variável do tipo preferencias.
        strcat(dados.nome, ".pbm"); //concatenando para salvar o arquivo como .pbm
    }

    //ecaminhando para a pasta do extraidor do identificador
    char caminho[] = "C:\\Users\\joseg\\Documents\\projeto_itp\\gerador_codigo_barras\\Extrair\\";
    strcat(caminho, dados.nome);
    strcpy(dados.nome, caminho);

    //criando o código de barra
    char *codigo = calloc(67+(dados.espacamento_lat*2) + 1, sizeof(char));//alocação da linha do código de barra com espaçamento.
    converter_binario(codigo, &numeros[0], dados.espacamento_lat); // convertendo para ums string em binário

    //alocando memória para multiplicar os pixels 
    char *tamanhoPixel = calloc(strlen(codigo)*dados.pixel_area + 1, sizeof(char));

    //multiplicando o código pela quantidade de pixels

    int k = 0;
    for (int i = 0; i < strlen(codigo); i++) { // usando quantidade de caracteres total da string como parâmetro.
        for (int j = 0; j < dados.pixel_area; j++) { // usando os pixels informação como parâmetro para multiplicar
            tamanhoPixel[k++] = codigo[i]; //array com a quantidade total de pixel ja criada recebendo os caracteres n vezes da antiga
        }
    }
    tamanhoPixel[k] = '\0'; // colonado o \0 para finalizar a string de forma correta

    //verificando se já existe arquivo com este nome

    int result = existe(dados.nome); //chamando a função "existe" para verificar se há um arquivo de mesmo nome
    if(result == 1){
        // gerando o arquivo
        criarPBM(dados, tamanhoPixel);
    }
    if(result == 2){
        printf("\033[1;36mPrograma encerrado.\033[0m\n");
    }

    //limpando a memória depois da execução do programa.
    free(tamanhoPixel);
    free(codigo);
    system("pause");
    return 0;
}