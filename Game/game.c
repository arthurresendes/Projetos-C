#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Struct com typedef chamado de Calcular com os suas variaveis dentro
typedef struct {
    int dificuldade;
    int valor1;
    int valor2;
    int operacao;
    int resultado;
} Calcular;

void jogar();
void mostrarInfo(Calcular calc);
int somar(int resposta, Calcular calc);
int diminuir(int resposta, Calcular calc);
int multiplicar(int resposta, Calcular calc);
int dividir(int resposta, Calcular calc);

//Quantidade de pontos quando o usuario acerta
int pontos = 0;

int main() {
    srand(time(NULL));
    jogar();
    return 0;
}

void jogar() {
    //Calcular agora se chama calc
    Calcular calc;
    //Variaveis dificuldade e recomecar
    int dificuldade, recomecar = 1;

    //Quando recomecar for igual a 1 ele volta o jogo
    while (recomecar == 1) {
        //Loop para o usuario informar a dificuldade
        do {
            printf("\nInforme a dificuldade do jogo [1, 2, 3 ou 4]: ");
            scanf("%d", &dificuldade);
        } while (dificuldade > 4 || dificuldade < 1);

        //Passando a resposta da int dificuldade para o calc.dificuldade(esta na struct)
        calc.dificuldade = dificuldade;

        //Se calc.dificuldade for igual a 1 , ira gerar numero aleatorio para valor 1 e 2 de 0 ate 100 
        if (calc.dificuldade == 1) {
            calc.valor1 = rand() % 101;
            calc.valor2 = rand() % 101;
        //Se nao se calc.dificuldade for igual a 2 , ira gerar numero aleatorio para valor 1 e 2 de 0 ate 1000 
        } else if (calc.dificuldade == 2) {
            calc.valor1 = rand() % 1001;
            calc.valor2 = rand() % 1001;
        //Se nao se calc.dificuldade for igual a 3 , ira gerar numero aleatorio para valor 1 e 2 de 0 ate 10000 
        } else if (calc.dificuldade == 3) {
            calc.valor1 = rand() % 10001;
            calc.valor2 = rand() % 10001;
        //Se nao calc.dificuldade for igual a 4 , ira gerar numero aleatorio para valor 1 e 2 de 0 ate 100000 
        } else {
            calc.valor1 = rand() % 100001;
            calc.valor2 = rand() % 100001;
        }

        
        calc.operacao = rand() % 4;

        // Evitar divisão por zero
        if (calc.operacao == 3 && calc.valor2 == 0) {
            calc.valor2 = 1;
        }

        mostrarInfo(calc);

        int resposta;
        printf("Informe o resultado da seguinte operacao:\n");

        if (calc.operacao == 0) {
            printf("%d + %d = ", calc.valor1, calc.valor2);
            scanf("%d", &resposta);
            if (somar(resposta, calc)) {
                pontos++;
                printf("Voce tem %d ponto(s).\n", pontos);
            }
        } else if (calc.operacao == 1) {
            printf("%d - %d = ", calc.valor1, calc.valor2);
            scanf("%d", &resposta);
            if (diminuir(resposta, calc)) {
                pontos++;
                printf("Voce tem %d ponto(s).\n", pontos);
            }
        } else if (calc.operacao == 2) {
            printf("%d * %d = ", calc.valor1, calc.valor2);
            scanf("%d", &resposta);
            if (multiplicar(resposta, calc)) {
                pontos++;
                printf("Voce tem %d ponto(s).\n", pontos);
            }
        } else if (calc.operacao == 3) {
            printf("%d / %d = ", calc.valor1, calc.valor2);
            scanf("%d", &resposta);
            if (dividir(resposta, calc)) {
                pontos++;
                printf("Voce tem %d ponto(s).\n", pontos);
            }
        } else {
            printf("Operacaoo desconhecida.\n");
        }

        printf("\nDeseja continuar o jogo? (1 - Sim / 0 - Nao): ");
        scanf("%d", &recomecar);
    }

    printf("\nVocê finalizou com %d ponto(s).\n", pontos);
    printf("Ate a próxima!\n");
}

void mostrarInfo(Calcular calc) {
    char op[25];
    if (calc.operacao == 0) {
        sprintf(op, "Somar");
    } else if (calc.operacao == 1) {
        sprintf(op, "Diminuir");
    } else if (calc.operacao == 2) {
        sprintf(op, "Multiplicar");
    } else if (calc.operacao == 3) {
        sprintf(op, "Dividir");
    } else {
        sprintf(op, "Operação desconhecida");
    }

    printf("\n------ Informacoes ------\n");
    printf("Valor 1: %d\n", calc.valor1);
    printf("Valor 2: %d\n", calc.valor2);
    printf("Dificuldade: %d\n", calc.dificuldade);
    printf("Operacao: %s\n", op);
    printf("-------------------------\n");
}

int somar(int resposta, Calcular calc) {
    int resultado = calc.valor1 + calc.valor2;
    calc.resultado = resultado;
    int certo = 0;

    if (resposta == calc.resultado) {
        printf("Resposta correta!\n");
        certo++;
    } else {
        printf("Resposta errada!\n");
    }

    printf("Resultado: %d + %d = %d\n", calc.valor1, calc.valor2, calc.resultado);
    return certo;
}

int diminuir(int resposta, Calcular calc) {
    int resultado = calc.valor1 - calc.valor2;
    calc.resultado = resultado;
    int certo = 0;

    if (resposta == calc.resultado) {
        printf("Resposta correta!\n");
        certo++;
    } else {
        printf("Resposta errada!\n");
    }

    printf("Resultado: %d - %d = %d\n", calc.valor1, calc.valor2, calc.resultado);
    return certo;
}

int multiplicar(int resposta, Calcular calc) {
    int resultado = calc.valor1 * calc.valor2;
    calc.resultado = resultado;
    int certo = 0;

    if (resposta == calc.resultado) {
        printf("Resposta correta!\n");
        certo++;
    } else {
        printf("Resposta errada!\n");
    }

    printf("Resultado: %d * %d = %d\n", calc.valor1, calc.valor2, calc.resultado);
    return certo;
}

int dividir(int resposta, Calcular calc) {
    int resultado = calc.valor1 / calc.valor2;
    calc.resultado = resultado;
    int certo = 0;

    if (resposta == calc.resultado) {
        printf("Resposta correta!\n");
        certo++;
    } else {
        printf("Resposta errada!\n");
    }

    printf("Resultado: %d / %d = %d\n", calc.valor1, calc.valor2, calc.resultado);
    return certo;
}
