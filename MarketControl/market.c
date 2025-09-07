// Bibliotecas padrão utilizadas
#include <stdio.h>      // Entrada e saída padrão (printf, scanf, etc.)
#include <stdlib.h>     // Funções utilitárias (exit, malloc, etc.)
#include <string.h>     // Manipulação de strings (fgets, strlen, etc.)

// Verifica se o sistema operacional é Windows
#ifdef _WIN32
#include <windows.h>                                // Necessário para usar Sleep() no Windows
#define esperar(segundos) Sleep((segundos) * 1000)  // Define a função esperar() com Sleep
#else
#include <unistd.h>                                 // Para sistemas Unix/Linux/MacOS
#define esperar(segundos) sleep(segundos)           // Define a função esperar() com sleep
#endif

// Struct Produto armazena os dados de um produto
typedef struct {
    int codigo;         // Código identificador do produto
    char nome[30];      // Nome do produto
    float preco;        // Preço do produto
} Produto;

// Struct Carrinho armazena um produto e sua quantidade no carrinho
typedef struct {
    Produto produto;    // Produto adicionado ao carrinho
    int quantidade;     // Quantidade desse produto
} Carrinho;

// Protótipos das funções utilizadas
void infoProduto(Produto prod);       // Mostra informações de um produto
void menu();                          // Exibe o menu principal
void cadastrarProduto();              // Permite cadastrar um novo produto
void listarProdutos();                // Lista todos os produtos cadastrados
void comprarProduto();                // Adiciona um produto ao carrinho
void visualizarCarrinho();            // Mostra os itens no carrinho
Produto pegarProdutoPorCodigo(int codigo);  // Retorna um produto pelo código
int *temNoCarrinho(int codigo);            // Verifica se produto já está no carrinho
void fecharPedido();                 // Finaliza o pedido e mostra total

// Variáveis globais estáticas
static int contador_produto = 0;     // Conta quantos produtos foram cadastrados
static int contador_carrinho = 0;    // Conta quantos itens estão no carrinho
static Carrinho carrinho[50];        // Vetor de carrinho com até 50 itens
static Produto produtos[50];         // Vetor de produtos com até 50 produtos

// Função principal do programa
int main() {
    menu();     // Inicia o menu principal
    return 0;   // Retorna 0 para indicar que o programa terminou corretamente
}

// Mostra na tela as informações de um produto passado como parâmetro
void infoProduto(Produto prod) {
    printf("Codigo: %d \nNome: %s \nPreco: %.2f\n", prod.codigo, prod.nome, prod.preco);
}

// Exibe o menu principal com as opções disponíveis ao usuário
void menu() {
    printf("============================\n");
    printf("========Bem-vindo(a)========\n");
    printf("=======Market Control=======\n");
    printf("============================\n");

    printf("Selecione uma opcao abaixo: \n");
    printf("1- Cadastrar produto\n");
    printf("2- Listar produto\n");
    printf("3- Comprar produto\n");
    printf("4- Visualizar carrinho\n");
    printf("5- Fechar pedido\n");
    printf("6- Sair\n");

    int opcao;
    scanf("%d", &opcao);   // Lê a opção do usuário
    getchar();             // Limpa o buffer do teclado

    // Direciona para a função correspondente à opção escolhida
    switch (opcao) {
        case 1:
            cadastrarProduto();
            break;
        case 2:
            listarProdutos();
            break;
        case 3:
            comprarProduto();
            break;
        case 4:
            visualizarCarrinho();
            break;
        case 5:
            fecharPedido();
            break;
        case 6:
            printf("Volte sempre!\n");
            esperar(2);
            exit(0);       // Encerra o programa
        default:
            printf("Opcao invalida!\n");
            esperar(2);
    }

    menu(); // Volta para o menu após a execução de cada opção
}

// Cadastra um novo produto no vetor de produtos
void cadastrarProduto() {
    printf("Cadastro de produto\n");
    printf("===================\n");

    // Lê o nome do produto
    printf("Informe o nome do produto: \n");
    fgets(produtos[contador_produto].nome, 30, stdin);
    produtos[contador_produto].nome[strcspn(produtos[contador_produto].nome, "\n")] = '\0'; // Remove o \n do final

    // Lê o preço do produto
    printf("Informe o preco do produto: \n");
    scanf("%f", &produtos[contador_produto].preco);
    getchar(); // Limpa o buffer

    // Define o código do produto como sendo o índice + 1
    produtos[contador_produto].codigo = contador_produto + 1;

    // Confirma o cadastro
    printf("O produto %s foi cadastrado com sucesso.\n", produtos[contador_produto].nome);
    contador_produto++; // Incrementa o número de produtos
    esperar(2);
}

// Lista todos os produtos cadastrados
void listarProdutos() {
    if (contador_produto > 0) {
        printf("Listagem de produtos.\n");
        printf("---------------------\n");
        for (int i = 0; i < contador_produto; i++) {
            infoProduto(produtos[i]);
            printf("---------------------\n");
            esperar(1);
        }
    } else {
        printf("Nao temos registro de produtos cadastrados.\n");
    }
    esperar(2);
}

// Permite ao usuário adicionar um produto ao carrinho
void comprarProduto() {
    if (contador_produto > 0) {
        printf("Informe o codigo do produto que deseja adicionar ao carrinho.\n");
        printf("===== Produtos disponiveis =====\n");

        // Mostra os produtos disponíveis
        for (int i = 0; i < contador_produto; i++) {
            infoProduto(produtos[i]);
            printf("---------------------\n");
            esperar(1);
        }

        int codigo;
        scanf("%d", &codigo);
        getchar();

        int tem_mercado = 0;

        // Verifica se o código informado existe
        for (int i = 0; i < contador_produto; i++) {
            if (produtos[i].codigo == codigo) {
                tem_mercado = 1;

                // Verifica se o carrinho já tem produtos
                if (contador_carrinho > 0) {
                    int *retorno = temNoCarrinho(codigo);
                    if (retorno[0] == 1) {
                        // Já está no carrinho: aumenta a quantidade
                        carrinho[retorno[1]].quantidade++;
                        printf("Aumentei a quantidade do produto %s ja existente no carrinho.\n", carrinho[retorno[1]].produto.nome);
                    } else {
                        // Adiciona novo item ao carrinho
                        Produto p = pegarProdutoPorCodigo(codigo);
                        carrinho[contador_carrinho].produto = p;
                        carrinho[contador_carrinho].quantidade = 1;
                        contador_carrinho++;
                        printf("O produto %s foi adicionado ao carrinho.\n", p.nome);
                    }
                } else {
                    // Carrinho está vazio, adiciona o primeiro produto
                    Produto p = pegarProdutoPorCodigo(codigo);
                    carrinho[contador_carrinho].produto = p;
                    carrinho[contador_carrinho].quantidade = 1;
                    contador_carrinho++;
                    printf("O produto %s foi adicionado ao carrinho.\n", p.nome);
                }

                esperar(2);
                return; // Sai da função após adicionar
            }
        }

        if (!tem_mercado) {
            printf("Nao foi encontrado produto com o codigo %d\n", codigo);
            esperar(2);
        }

    } else {
        printf("Nenhum produto cadastrado.\n");
        esperar(2);
    }
}

// Mostra todos os produtos atualmente no carrinho
void visualizarCarrinho() {
    if (contador_carrinho > 0) {
        printf("Produtos no carrinho.\n");
        printf("---------------------\n");
        for (int i = 0; i < contador_carrinho; i++) {
            infoProduto(carrinho[i].produto);
            printf("Quantidade: %d\n", carrinho[i].quantidade);
            printf("---------------------\n");
            esperar(1);
        }
    } else {
        printf("Nao temos produto no carrinho.\n");
    }
    esperar(2);
}

// Retorna um produto com base no seu código
Produto pegarProdutoPorCodigo(int codigo) {
    for (int i = 0; i < contador_produto; i++) {
        if (produtos[i].codigo == codigo) {
            return produtos[i]; // Produto encontrado
        }
    }
    // Se não encontrar, retorna um produto vazio
    Produto p = {0, "", 0.0};
    return p;
}

// Verifica se o produto com determinado código já está no carrinho
int *temNoCarrinho(int codigo) {
    static int retorno[] = {0, 0}; // retorno[0] = existe (0/1), retorno[1] = índice
    retorno[0] = 0;
    retorno[1] = 0;

    for (int i = 0; i < contador_carrinho; i++) {
        if (carrinho[i].produto.codigo == codigo) {
            retorno[0] = 1; // Produto encontrado
            retorno[1] = i; // Índice no carrinho
            break;
        }
    }
    return retorno; // Retorna ponteiro para vetor com resultado
}

// Finaliza o pedido, mostra o total e limpa o carrinho
void fecharPedido() {
    if (contador_carrinho > 0) {
        float valorTotal = 0.0;
        printf("Produtos carrinho\n");
        printf("---------------------\n");
        for (int i = 0; i < contador_carrinho; i++) {
            Produto p = carrinho[i].produto;
            int quantidade = carrinho[i].quantidade;
            valorTotal += p.preco * quantidade;
            infoProduto(p);
            printf("Quantidade: %d\n", quantidade);
            printf("---------------------\n");
            esperar(1);
        }

        printf("Sua fatura eh R$ %.2f\n", valorTotal);

        contador_carrinho = 0; // Limpa o carrinho após finalizar
        printf("Obrigado pela preferencia\n");
        esperar(5);
    } else {
        printf("Sem produtos no carrinho.\n");
        esperar(3);
    }
}
