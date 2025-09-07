#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#define esperar(segundos) Sleep((segundos) * 1000)
#else
#include <unistd.h>
#define esperar(segundos) sleep(segundos)
#endif

void menu(char *name);
void borda();
void questionaFuncionario();
void questionaLimpeza();

int main(){
    char nome[200];
    menu(nome);
    return 0;
}

void menu(char *name){
    int opcao;

    printf("Ola, qual seu nome?\n");
    fgets(name, 200, stdin);
    name[strcspn(name, "\n")] = '\0';

    borda();
    printf("\nBem-vindo ao questionario da empresa, %s\n", name);
    printf("--Escolha uma das opções a seguir:\n");
    printf("1-- Questionario sobre funcionarios\n");
    printf("2-- Questionario sobre limpeza\n");
    printf("3-- Sair\n");
    esperar(2);

    printf("Sua resposta -> ");
    if(scanf("%d", &opcao) != 1){
        // Entrada inválida
        printf("Entrada inválida! Tente novamente.\n");
        while(getchar() != '\n'); // limpa buffer
        menu(name);
        return;
    }
    while(getchar() != '\n'); // limpa buffer para fgets futuras

    switch(opcao){
        case 1:
            questionaFuncionario();
            break;
        case 2:
            questionaLimpeza();
            break;
        case 3: 
            printf("Fique a vontade para voltar!!\n");
            esperar(3);
            exit(0);
        default:
            printf("Opção irreconhecida!!\n");
            menu(name);
    }
}

void borda(){
    printf("\n=====================\n");
}

void questionaLimpeza(){
    char resposta[100];

    printf("1. Com que frequencia a area e limpa? ");
    fgets(resposta, sizeof(resposta), stdin);
    resposta[strcspn(resposta, "\n")] = '\0';

    printf("2. Quais produtos de limpeza sao utilizados? ");
    fgets(resposta, sizeof(resposta), stdin);
    resposta[strcspn(resposta, "\n")] = '\0';

    printf("3. Ha um responsavel pela supervisao da limpeza? ");
    fgets(resposta, sizeof(resposta), stdin);
    resposta[strcspn(resposta, "\n")] = '\0';
}

void questionaFuncionario(){
    char resposta[100];

    printf("1. Qual o nome do funcionario? ");
    fgets(resposta, sizeof(resposta), stdin);
    resposta[strcspn(resposta, "\n")] = '\0';

    printf("2. Ha quanto tempo ele trabalha na empresa? ");
    fgets(resposta, sizeof(resposta), stdin);
    resposta[strcspn(resposta, "\n")] = '\0';

    printf("3. Quais sao as principais funcoes dele? ");
    fgets(resposta, sizeof(resposta), stdin);
    resposta[strcspn(resposta, "\n")] = '\0';
}
