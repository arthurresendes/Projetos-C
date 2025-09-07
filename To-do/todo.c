#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tarefa { // Estrutura para armazenar as tarefas
    char descricao[100]; //Descrição da tarefa
};

void bordaMenu() {
    printf("====================================\n"); //Borda do menu
}

int main() { //Inicializador do programa
    struct tarefa *lista = NULL; //Ponteiro para armazenar as posições das tarefas
    int i, quantidade = 0, totalTarefas = 0, opcao; //Variaveis para uso do programa

    do {  //Inicio de um loop
        bordaMenu(); 
        printf("Bem-vindo ao To-Do List\n");
        printf("1 -- Anotar tarefas\n");
        printf("2 -- Remover tarefas\n");
        printf("3 -- Mostrar tarefas\n");
        printf("0 -- Sair\n"); //Opções do menui
        bordaMenu();

        printf("Escolha uma opção: "); 
        scanf("%d", &opcao);
        getchar();  //Limpa o buffer de entrada

        switch (opcao) {
            case 1:
                printf("Quantas tarefas deseja adicionar? "); 
                scanf("%d", &quantidade);
                getchar(); 

                lista = realloc(lista, (totalTarefas + quantidade) * sizeof(struct tarefa)); //Realoco espaço na memoria
                if (lista == NULL) { //Verifica se o espaço foi alocado
                    printf("Erro ao alocar memória!\n");
                    return 1; //Volta erro ao alocar a memoria
                }

                for (i = 0; i < quantidade; i++) { //Inicio de um loop
                    printf("Digite a tarefa %d: ", totalTarefas + 1); 
                    fgets(lista[totalTarefas].descricao, 100, stdin); 
                    lista[totalTarefas].descricao[strcspn(lista[totalTarefas].descricao, "\n")] = '\0';
                    totalTarefas++; //Adiciona um numero para cada tarefa
                }
                break; 

            case 2:
                if (totalTarefas == 0) {
                    printf("Nenhuma tarefa para remover.\n");
                    break;
                }

                printf("Tarefas atuais:\n");
                for (i = 0; i < totalTarefas; i++) {
                    printf("%d. %s\n", i + 1, lista[i].descricao);
                } //Mostra as tarefas atuais

                int remover;
                printf("Digite o número da tarefa que deseja remover: ");
                scanf("%d", &remover);
                getchar();

                if (remover < 1 || remover > totalTarefas) {
                    printf("Número inválido.\n");
                } else {
                    // Move os elementos para "tapar o buraco"
                    for (i = remover - 1; i < totalTarefas - 1; i++) { //i=remover - 1 (como começa o vetor do 0 subtrai 1 para achar a tarefa correta) , i < totalTarefas - 1: evita ultrapassar o fim do vetor (último índice válido é totalTarefas - 1).
                        lista[i] = lista[i + 1]; //a tarefa atual (i) recebe o conteúdo da próxima (i + 1), mudando a posição na hora de imprimir as tarefas novamente.
                    }
                    totalTarefas--; //Diminui o contador de tarefas

                    // Realoca para reduzir o tamanho
                    lista = realloc(lista, totalTarefas * sizeof(struct tarefa));
                    printf("Tarefa removida com sucesso!\n");
                }
                break;

            case 3:
                if (totalTarefas == 0) {
                    printf("Nenhuma tarefa cadastrada.\n");
                } else {
                    printf("\nTarefas:\n");
                    for (i = 0; i < totalTarefas; i++) {
                        printf("%d. %s\n", i + 1, lista[i].descricao);
                    }
                }
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    free(lista); //Libera a memória que foi alocada dinamicamente com malloc(), calloc() ou realloc().
    return 0;
}
