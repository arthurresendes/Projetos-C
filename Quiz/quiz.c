#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int dificuldade;
    char pergunta[256];
    char opA[100];
    char opB[100];
    char opC[100];
    char opD[100];
    char result;
    char respostaCerta;
} Pergunta;

int pontos = 0;

void jogo();
void perguntas(Pergunta prg);

int main() {
    jogo();
    return 0;
}

void jogo() {
    int dificuldade;
    int continuar;

    do {
        printf("=======================\n");
        printf("1 - Nível fácil\n2 - Nível médio\n3 - Nível difícil\n4 - Nível avançado\n");
        printf("=======================\n");
        printf("Qual dos níveis de pergunta quer responder: ");
        scanf("%d", &dificuldade);
        getchar(); // Limpar o \n do buffer

        Pergunta prg;

        // Configura a pergunta de acordo com a dificuldade escolhida
        switch (dificuldade) {
            case 1:
                prg.dificuldade = 1;
                snprintf(prg.pergunta, sizeof(prg.pergunta), "Qual das opções representa corretamente uma estrutura de controle condicional em C?");
                snprintf(prg.opA, sizeof(prg.opA), "a) escolha-caso");
                snprintf(prg.opB, sizeof(prg.opB), "b) if-else");
                snprintf(prg.opC, sizeof(prg.opC), "c) quando-então");
                snprintf(prg.opD, sizeof(prg.opD), "d) condicional");
                prg.respostaCerta = 'b';
                break;
            case 2:
                prg.dificuldade = 2;
                snprintf(prg.pergunta, sizeof(prg.pergunta), "Qual a principal diferença entre float e double em C?");
                snprintf(prg.opA, sizeof(prg.opA), "a) float é mais preciso que double");
                snprintf(prg.opB, sizeof(prg.opB), "b) double ocupa menos memória que float");
                snprintf(prg.opC, sizeof(prg.opC), "c) double tem maior precisão e ocupa mais memória");
                snprintf(prg.opD, sizeof(prg.opD), "d) Não existe diferença; são sinônimos");
                prg.respostaCerta = 'c';
                break;
            case 3:
                prg.dificuldade = 3;
                snprintf(prg.pergunta, sizeof(prg.pergunta), "O que significa dizer que C permite manipulação de memória de baixo nível?");
                snprintf(prg.opA, sizeof(prg.opA), "a) Que C não usa memória");
                snprintf(prg.opB, sizeof(prg.opB), "b) Que C não pode alocar memória");
                snprintf(prg.opC, sizeof(prg.opC), "c) Que é possível acessar diretamente endereços de memória com ponteiros");
                snprintf(prg.opD, sizeof(prg.opD), "d) Que C usa apenas memória virtual");
                prg.respostaCerta = 'c';
                break;
            case 4:
                prg.dificuldade = 4;
                snprintf(prg.pergunta, sizeof(prg.pergunta), "Em C, qual das alternativas representa corretamente uma situação em que ocorre comportamento indefinido devido ao uso de variáveis em expressões com efeitos colaterais?");
                snprintf(prg.opA, sizeof(prg.opA), "a) Avaliar x = x++ + ++x; em uma única expressão");
                snprintf(prg.opB, sizeof(prg.opB), "b) Declarar uma variável global");
                snprintf(prg.opC, sizeof(prg.opC), "c) Usar uma função printf() com apenas um argumento");
                snprintf(prg.opD, sizeof(prg.opD), "d) Declarar uma variável int dentro da função main()");
                prg.respostaCerta = 'a';
                break;
            default:
                printf("Nível inválido. Tente novamente.\n");
                continue; // Vai para o próximo loop do jogo sem chamar perguntas
        }

        perguntas(prg);

        printf("\nDeseja jogar ainda? (1 - Sim, 0 - Não): ");
        scanf("%d", &continuar);
        getchar(); // limpar o buffer do enter
    } while (continuar == 1);
    printf("Obrigado por realizar o quiz , voce fez %d pontos" , pontos);
    exit(0);

}

void perguntas(Pergunta prg) {
    char resposta;

    printf("\n%s\n", prg.pergunta);
    printf("%s\n", prg.opA);
    printf("%s\n", prg.opB);
    printf("%s\n", prg.opC);
    printf("%s\n", prg.opD);

    printf("Sua resposta: ");
    scanf(" %c", &resposta);  // espaço antes do %c para ignorar lixo no buffer
    prg.result = resposta;
    pontos++;

}