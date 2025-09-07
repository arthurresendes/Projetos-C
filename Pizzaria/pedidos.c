#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

// Permite apenas números
int apenasNumeros(const char *str) {
    for (int i = 0; str[i] != '\0'; i++)
        if (!isdigit((unsigned char)str[i]))
            return 0;
    return 1;
}

// Permite apenas letras e espaços
int apenasLetras(const char *str) {
    for (int i = 0; str[i] != '\0'; i++)
        if (!isalpha((unsigned char)str[i]) && str[i] != ' ')
            return 0;
    return 1;
}

// Permite emails válidos (simplificado)
int apenasEmail(const char *str) {
    int arroba = 0, ponto = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '@') arroba = 1;
        if (arroba && str[i] == '.') ponto = 1;
    }
    return arroba && ponto;
}

// Limpa buffer de entrada
void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Limpa tela
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

typedef struct {
    char email[50];
    char senha[50];
} Usuario;

#define MAX_ITENS 100

int main() {
    int menu;
    Usuario usuario = {"", ""};
    char menustr[10];

    // Agora até MAX_ITENS de cada tipo
    char nomePizza[MAX_ITENS][50], nomeBebida[MAX_ITENS][50], nomeDoce[MAX_ITENS][50];
    int escolhaPizza[MAX_ITENS], quantidadePizza[MAX_ITENS];
    int escolhaBebida[MAX_ITENS], quantidadeBebida[MAX_ITENS];
    int escolhaDoce[MAX_ITENS], quantidadeDoce[MAX_ITENS];
    float precoPizza[MAX_ITENS], precoBebida[MAX_ITENS], precoDoce[MAX_ITENS];
    char email[50], senha[50], confirma[50];
    char complemento[50], cep[10], cpf[15];
    char quantidadeStr[16];
    int querSalgada = 2, querBebida = 2, querDoce = 2, pagamento = 0;
    char nomePagamento[50];
    float total = 0.0;
    int i, n_pizza = 0, n_bebida = 0, n_doce = 0;

    while (1) {
        // Menu principal
        do {
            printf("----------------- \n");
            printf("| 1-Cadastro    | \n");
            printf("| 2-Login       | \n");
            printf("| 3-Cardapio    | \n");
            printf("| 4-Sair        | \n");
            printf("----------------- \n");
            printf("Escolha uma opcao: ");
            fgets(menustr, sizeof(menustr), stdin);
            menustr[strcspn(menustr, "\n")] = '\0';
        } while (!apenasNumeros(menustr) || strlen(menustr) == 0);
        menu = atoi(menustr);

        switch (menu) {
        case 1: // Cadastro
            limparTela();
            // E-mail
            do {
                printf("Digite seu e-mail: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = '\0';
                if (!apenasEmail(email) || strlen(email) == 0)
                    printf("Email inválido! Tente novamente.\n");
            } while (strlen(email) == 0 || !apenasEmail(email));
            strcpy(usuario.email, email);

            // CPF
            do {
                printf("Digite seu CPF (11 digitos): ");
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = '\0';
                if (strlen(cpf) != 11 || !apenasNumeros(cpf))
                    printf("CPF inválido! Tente novamente.\n");
            } while (strlen(cpf) != 11 || !apenasNumeros(cpf));

            // CEP
            do {
                printf("Digite seu CEP (8 digitos sem traço): ");
                fgets(cep, sizeof(cep), stdin);
                cep[strcspn(cep, "\n")] = '\0';
                if (strlen(cep) != 8 || !apenasNumeros(cep))
                    printf("CEP inválido! Tente novamente.\n");
            } while (strlen(cep) != 8 || !apenasNumeros(cep));

            // Complemento
            do {
                printf("Digite complemento do endereço (pontos populares): ");
                fgets(complemento, sizeof(complemento), stdin);
                complemento[strcspn(complemento, "\n")] = '\0';
                if (strlen(complemento) == 0 || !apenasLetras(complemento))
                    printf("Complemento inválido! Apenas letras e espaços.\n");
            } while (strlen(complemento) == 0 || !apenasLetras(complemento));

            // Senha e confirmação
            do {
                printf("Digite sua senha: ");
                fgets(senha, sizeof(senha), stdin);
                senha[strcspn(senha, "\n")] = '\0';
                printf("Confirme sua senha: ");
                fgets(confirma, sizeof(confirma), stdin);
                confirma[strcspn(confirma, "\n")] = '\0';
                if (strcmp(senha, confirma) != 0 || strlen(senha) == 0 || strlen(confirma) == 0)
                    printf("Senhas diferentes ou campo vazio. Tente novamente.\n\n");
            } while (strcmp(senha, confirma) != 0 || strlen(senha) == 0);
            strcpy(usuario.senha, senha);

            printf("Cadastro realizado com sucesso! Bem-vindo ao PizzaControl, %s!\n", usuario.email);
            break;

        case 2: // Login e pedido
            limparTela();
            // Login
            do {
                printf("Digite seu e-mail: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = '\0';
            } while (strlen(email) == 0);

            do {
                printf("Digite sua senha: ");
                fgets(senha, sizeof(senha), stdin);
                senha[strcspn(senha, "\n")] = '\0';
            } while (strlen(senha) == 0);

            // Validação simples (apenas um usuário em memória)
            if (strcmp(usuario.email, email) != 0 || strcmp(usuario.senha, senha) != 0) {
                printf("Email ou senha inválidos! Faça o cadastro ou tente novamente.\n");
                break;
            }
            printf("Bom ter voce de volta ao PizzaControl, %s!\n", usuario.email);

            // Escolha de pizzas salgadas (quantas quiser)
            n_pizza = 0;
            do {
                do {
                    printf("Deseja adicionar uma pizza salgada? (1-Sim / 2-Nao): ");
                    fgets(menustr, sizeof(menustr), stdin);
                    menustr[strcspn(menustr, "\n")] = '\0';
                } while (!apenasNumeros(menustr) || (atoi(menustr) != 1 && atoi(menustr) != 2));
                querSalgada = atoi(menustr);
                if (querSalgada == 1) {
                    printf("---------------------------- \n");
                    printf("| 1-Frango catupiry--50 R$ | \n");
                    printf("| 2-Calabresa--50 R$       | \n");
                    printf("| 3-Mussarela--50 R$       | \n");
                    printf("| 4-Quatro queijos--50 R$  | \n");
                    printf("| 5-Portuguesa--50 R$      | \n");
                    printf("---------------------------- \n");
                    do {
                        printf("Escolha sua pizza salgada: ");
                        fgets(menustr, sizeof(menustr), stdin);
                        menustr[strcspn(menustr, "\n")] = '\0';
                        escolhaPizza[n_pizza] = atoi(menustr);
                    } while (escolhaPizza[n_pizza] < 1 || escolhaPizza[n_pizza] > 5 || !apenasNumeros(menustr));
                    switch (escolhaPizza[n_pizza]) {
                        case 1: strcpy(nomePizza[n_pizza], "Frango com catupiry"); break;
                        case 2: strcpy(nomePizza[n_pizza], "Calabresa"); break;
                        case 3: strcpy(nomePizza[n_pizza], "Mussarela"); break;
                        case 4: strcpy(nomePizza[n_pizza], "Quatro queijos"); break;
                        case 5: strcpy(nomePizza[n_pizza], "Portuguesa"); break;
                    }
                    do {
                        printf("Quantas %s voce deseja? ", nomePizza[n_pizza]);
                        fgets(quantidadeStr, sizeof(quantidadeStr), stdin);
                        quantidadeStr[strcspn(quantidadeStr, "\n")] = '\0';
                    } while (strlen(quantidadeStr) == 0 || !apenasNumeros(quantidadeStr));
                    quantidadePizza[n_pizza] = atoi(quantidadeStr);
                    precoPizza[n_pizza] = 50.0 * quantidadePizza[n_pizza];
                    n_pizza++;
                }
            } while (querSalgada == 1 && n_pizza < MAX_ITENS);

            // Escolha de bebidas (quantas quiser)
            n_bebida = 0;
            do {
                do {
                    printf("Deseja adicionar uma bebida? (1-Sim / 2-Nao): ");
                    fgets(menustr, sizeof(menustr), stdin);
                    menustr[strcspn(menustr, "\n")] = '\0';
                } while (!apenasNumeros(menustr) || (atoi(menustr) != 1 && atoi(menustr) != 2));
                querBebida = atoi(menustr);
                if (querBebida == 1) {
                    printf("----------------------------- \n");
                    printf("| 1-Coca-Cola--12 R$        | \n");
                    printf("| 2-Guarana--11 R$          | \n");
                    printf("| 3-Suco de laranja--10 R$  | \n");
                    printf("| 4-Agua--8 R$              | \n");
                    printf("----------------------------- \n");
                    do {
                        printf("Escolha sua bebida: ");
                        fgets(menustr, sizeof(menustr), stdin);
                        menustr[strcspn(menustr, "\n")] = '\0';
                        escolhaBebida[n_bebida] = atoi(menustr);
                    } while (escolhaBebida[n_bebida] < 1 || escolhaBebida[n_bebida] > 4 || !apenasNumeros(menustr));
                    switch (escolhaBebida[n_bebida]) {
                        case 1: strcpy(nomeBebida[n_bebida], "Coca-Cola"); precoBebida[n_bebida] = 12.0; break;
                        case 2: strcpy(nomeBebida[n_bebida], "Guarana"); precoBebida[n_bebida] = 11.0; break;
                        case 3: strcpy(nomeBebida[n_bebida], "Suco de laranja"); precoBebida[n_bebida] = 10.0; break;
                        case 4: strcpy(nomeBebida[n_bebida], "Agua"); precoBebida[n_bebida] = 8.0; break;
                    }
                    do {
                        printf("Quantas %s voce deseja? ", nomeBebida[n_bebida]);
                        fgets(quantidadeStr, sizeof(quantidadeStr), stdin);
                        quantidadeStr[strcspn(quantidadeStr, "\n")] = '\0';
                    } while (strlen(quantidadeStr) == 0 || !apenasNumeros(quantidadeStr));
                    quantidadeBebida[n_bebida] = atoi(quantidadeStr);
                    precoBebida[n_bebida] = precoBebida[n_bebida] * quantidadeBebida[n_bebida];
                    n_bebida++;
                }
            } while (querBebida == 1 && n_bebida < MAX_ITENS);

            // Escolha de doces (quantas quiser)
            n_doce = 0;
            do {
                do {
                    printf("Deseja adicionar uma pizza doce? (1-Sim / 2-Nao): ");
                    fgets(menustr, sizeof(menustr), stdin);
                    menustr[strcspn(menustr, "\n")] = '\0';
                } while (!apenasNumeros(menustr) || (atoi(menustr) != 1 && atoi(menustr) != 2));
                querDoce = atoi(menustr);
                if (querDoce == 1) {
                    printf("----------------------------- \n");
                    printf("| 1-Chocolate--50 R$        | \n");
                    printf("| 2-Prestigio--55 R$        |\n");
                    printf("| 3-RomeuJulieta--55 R$     | \n");
                    printf("| 4-Brigadeiro--50 R$       |\n");
                    printf("----------------------------- \n");
                    do {
                        printf("Escolha sua pizza doce: ");
                        fgets(menustr, sizeof(menustr), stdin);
                        menustr[strcspn(menustr, "\n")] = '\0';
                        escolhaDoce[n_doce] = atoi(menustr);
                    } while (escolhaDoce[n_doce] < 1 || escolhaDoce[n_doce] > 4 || !apenasNumeros(menustr));
                    switch (escolhaDoce[n_doce]) {
                        case 1: strcpy(nomeDoce[n_doce], "Chocolate"); precoDoce[n_doce] = 50.0; break;
                        case 2: strcpy(nomeDoce[n_doce], "Prestigio"); precoDoce[n_doce] = 55.0; break;
                        case 3: strcpy(nomeDoce[n_doce], "RomeuJulieta"); precoDoce[n_doce] = 55.0; break;
                        case 4: strcpy(nomeDoce[n_doce], "Brigadeiro"); precoDoce[n_doce] = 50.0; break;
                    }
                    do {
                        printf("Quantas %s voce deseja? ", nomeDoce[n_doce]);
                        fgets(quantidadeStr, sizeof(quantidadeStr), stdin);
                        quantidadeStr[strcspn(quantidadeStr, "\n")] = '\0';
                    } while (strlen(quantidadeStr) == 0 || !apenasNumeros(quantidadeStr));
                    quantidadeDoce[n_doce] = atoi(quantidadeStr);
                    precoDoce[n_doce] = precoDoce[n_doce] * quantidadeDoce[n_doce];
                    n_doce++;
                }
            } while (querDoce == 1 && n_doce < MAX_ITENS);

            if ((n_pizza == 0) && (n_bebida == 0) && (n_doce == 0)) {
                printf("Nenhum pedido registrado.\n");
                break;
            }

            // Pagamento
            do {
                printf("Metodo de pagamento\n");
                printf("---------------- \n");
                printf("| 1--Credito   | \n");
                printf("| 2--Debito    | \n");
                printf("| 3--PIX       | \n");
                printf("| 4--Dinheiro  | \n");
                printf("---------------- \n");
                fgets(menustr, sizeof(menustr), stdin);
                menustr[strcspn(menustr, "\n")] = '\0';
                pagamento = atoi(menustr);
            } while (pagamento < 1 || pagamento > 4 || strlen(menustr) == 0 || !apenasNumeros(menustr));
            switch (pagamento) {
                case 1: strcpy(nomePagamento, "Credito"); break;
                case 2: strcpy(nomePagamento, "Debito"); break;
                case 3: strcpy(nomePagamento, "PIX"); break;
                case 4: strcpy(nomePagamento, "Dinheiro"); break;
            }

            // Resumo
            printf("\n--- RESUMO DO PEDIDO ---\n");
            printf("Email: %s\n", usuario.email);
            total = 0;
            for (i = 0; i < n_pizza; i++)
                printf("Pizza salgada: %d %s, preco = %.2f\n", quantidadePizza[i], nomePizza[i], precoPizza[i]), total += precoPizza[i];
            if (n_pizza == 0) printf("Sem pizza salgada.\n");
            for (i = 0; i < n_bebida; i++)
                printf("Bebida: %d %s, preco = %.2f\n", quantidadeBebida[i], nomeBebida[i], precoBebida[i]), total += precoBebida[i];
            if (n_bebida == 0) printf("Sem bebida.\n");
            for (i = 0; i < n_doce; i++)
                printf("Pizza doce: %d %s, preco = %.2f\n", quantidadeDoce[i], nomeDoce[i], precoDoce[i]), total += precoDoce[i];
            if (n_doce == 0) printf("Sem pizza doce.\n");
            printf("Total do pedido: %.2f\n", total);
            printf("Metodo de pagamento: %s\n", nomePagamento);
            printf("------------------------\n");
            break;

        case 3:
            printf("Pizza salgada: \n");
            printf("---------------------------- \n");
            printf("| 1-Frango catupiry--50 R$ | \n");
            printf("| 2-Calabresa--50 R$       | \n");
            printf("| 3-Mussarela--50 R$       | \n");
            printf("| 4-Quatro queijos--50 R$  | \n");
            printf("| 5-Portuguesa--50 R$      | \n");
            printf("---------------------------- \n");
            printf("Pizza doce: \n");
            printf("----------------------------- \n");
            printf("| 1-Chocolate--50 R$        | \n");
            printf("| 2-Prestigio--55 R$        |\n");
            printf("| 3-RomeuJulieta--55 R$     | \n");
            printf("| 4-Brigadeiro--50 R$       |\n");
            printf("----------------------------- \n");
            printf("Bebidas: \n");
            printf("----------------------------- \n");
            printf("| 1-Coca-Cola--12 R$        | \n");
            printf("| 2-Guarana--11 R$          | \n");
            printf("| 3-Suco de laranja--10 R$  | \n");
            printf("| 4-Agua--8 R$              | \n");
            printf("----------------------------- \n");
            printf("Esse é nosso cardápio, se quiser fazer o pedido faça login ou se cadastre-se. (1-Menu para pedido / 2-Sair)\n");
            fgets(menustr, sizeof(menustr), stdin);
            if (atoi(menustr) != 1) {
                printf("Obrigado por visitar a PizzaControl!\n");
                return 0;
            }
            break;

        case 4:
            printf("Obrigado por visitar a PizzaControl!\n");
            return 0;
        default:
            printf("Opção inválida.\n");
        }
    }
    return 0;
}