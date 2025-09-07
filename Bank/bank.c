//Bibliotecas para uso
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Constante esperar que funciona em diversos SO
#ifdef _WIN32
#include <windows.h>
#define esperar(segundos) Sleep((segundos) * 1000)
#else
#include <unistd.h>
#define esperar(segundos) sleep(segundos)
#endif

//Estrutura para cadastro de cliente
typedef struct {
    int codigo;
    char nome[50];
    char email[50];
    char cpf[20];
    char dataNascimento[20];
    char dataCadastro[20];
} Cliente;

//Estrutura para a conta do cliente
typedef struct {
    int numero;
    Cliente cliente; //Puxa informações do cliente
    float saldo;
    float limite;
    float saldoTotal;
} Conta;

void menu();
void infoCliente(const Cliente* cliente);
void infoConta(const Conta* conta);
void criarConta();
void efetuarSaque();
void efetuarDeposito();
void efetuarTransferencia();
void listarContas();
float atualizaSaldoTotal(const Conta* conta);
Conta* buscarContaPorNumero(int numero);
void sacar(Conta* conta, float valor);
void depositar(Conta* conta, float valor);
void transferir(Conta* conta_origem, Conta* conta_destino, float valor);
void limparBuffer();
void removeNovaLinha(char *str);

static Conta contas[50];
static int contador_contas = 0;
static int contador_clientes = 0;

int main() {
    while (1) {
        menu();
    }
    return 0;
}

void menu() {
    int opcao = 0;
    printf("============================\n");
    printf("========Bem-vindo(a)========\n");
    printf("============Bank============\n");
    printf("============================\n");

    printf("Selecione uma opcao abaixo: \n");
    printf("1- Criar conta\n");
    printf("2- Efetuar saque\n");
    printf("3- Efetuar deposito\n");
    printf("4- Efetuar transferencia\n");
    printf("5- Listar contas\n");
    printf("6- Sair\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    limparBuffer();

    switch (opcao) {
        case 1:
            criarConta();
            break;
        case 2:
            efetuarSaque();
            break;
        case 3:
            efetuarDeposito();
            break;
        case 4:
            efetuarTransferencia();
            break;
        case 5:
            listarContas();
            break;
        case 6:
            printf("Volte sempre!\n");
            esperar(2);
            exit(0);
        default:
            printf("Opcao invalida!\n");
            esperar(2);
            break;
    }
}

void removeNovaLinha(char *str) {
    str[strcspn(str, "\n")] = 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void infoCliente(const Cliente* cliente) {
    printf("Codigo: %d\nNome: %s\nData de Nascimento: %s\nCadastro: %s\n", 
        cliente->codigo, cliente->nome, cliente->dataNascimento, cliente->dataCadastro);
}

void infoConta(const Conta* conta) {
    printf("Numero da conta: %d\nCliente: %s\nData Nascimento: %s\nData cadastro: %s\nSaldo total: %.2f\n", 
        conta->numero, conta->cliente.nome, conta->cliente.dataNascimento, conta->cliente.dataCadastro, conta->saldoTotal);
}

void criarConta() {
    Cliente cliente;
    char dia[3], mes[3], ano[5];
    char data_cadastro[20];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(dia, "%02d", tm.tm_mday);
    sprintf(mes, "%02d", tm.tm_mon + 1);
    sprintf(ano, "%d", tm.tm_year + 1900);

    snprintf(data_cadastro, sizeof(data_cadastro), "%s-%s-%s", dia, mes, ano);
    strcpy(cliente.dataCadastro, data_cadastro);

    printf("Informe os dados do cliente.\n");
    cliente.codigo = contador_clientes + 1;

    printf("Nome: ");
    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    removeNovaLinha(cliente.nome);

    printf("E-mail: ");
    fgets(cliente.email, sizeof(cliente.email), stdin);
    removeNovaLinha(cliente.email);

    printf("CPF: ");
    fgets(cliente.cpf, sizeof(cliente.cpf), stdin);
    removeNovaLinha(cliente.cpf);

    printf("Data de nascimento: ");
    fgets(cliente.dataNascimento, sizeof(cliente.dataNascimento), stdin);
    removeNovaLinha(cliente.dataNascimento);

    contas[contador_contas].numero = contador_contas + 1;
    contas[contador_contas].cliente = cliente;
    contas[contador_contas].saldo = 0.0;
    contas[contador_contas].limite = 0.0;
    contas[contador_contas].saldoTotal = atualizaSaldoTotal(&contas[contador_contas]);

    printf("Conta criada com sucesso!\n\n");
    printf("Dados da conta criada:\n\n");
    infoConta(&contas[contador_contas]);
    contador_contas++;
    contador_clientes++;
    esperar(4);
}

void efetuarSaque() {
    if (contador_contas > 0) {
        int numero;
        printf("Digite o numero da conta: ");
        scanf("%d", &numero);
        limparBuffer();
        Conta* conta = buscarContaPorNumero(numero);
        if (conta != NULL) {
            float valor;
            printf("Informe o valor do saque: ");
            scanf("%f", &valor);
            limparBuffer();
            sacar(conta, valor);
        } else {
            printf("Nao foi encontrado uma conta com o numero %d\n", numero);
        }
    } else {
        printf("Ainda não existem contas para saque.\n");
    }
    esperar(2);
}

void efetuarDeposito() {
    if (contador_contas > 0) {
        int numero;
        printf("Digite o numero da conta: ");
        scanf("%d", &numero);
        limparBuffer();
        Conta* conta = buscarContaPorNumero(numero);
        if (conta != NULL) {
            float valor;
            printf("Informe o valor do deposito: ");
            scanf("%f", &valor);
            limparBuffer();
            depositar(conta, valor);
        } else {
            printf("Nao foi encontrado uma conta com o numero %d\n", numero);
        }
    } else {
        printf("Ainda não existem contas para deposito.\n");
    }
    esperar(2);
}

void efetuarTransferencia() {
    if (contador_contas > 0) {
        int numero_o, numero_d;
        printf("Informe o numero da sua conta: ");
        scanf("%d", &numero_o);
        limparBuffer();
        Conta* conta_o = buscarContaPorNumero(numero_o);
        if (conta_o != NULL) {
            printf("Informe o numero da conta de destino: ");
            scanf("%d", &numero_d);
            limparBuffer();
            Conta* conta_d = buscarContaPorNumero(numero_d);
            if (conta_d != NULL) {
                float valor;
                printf("Informe o valor da transferencia: ");
                scanf("%f", &valor);
                limparBuffer();
                transferir(conta_o, conta_d, valor);
            } else {
                printf("Conta de destino %d nao foi encontrada.\n", numero_d);
            }
        } else {
            printf("Conta com o numero %d nao foi encontrada.\n", numero_o);
        }
    } else {
        printf("Ainda não existem contas para transferencia.\n");
    }
    esperar(2);
}

void listarContas() {
    if (contador_contas > 0) {
        for (int i = 0; i < contador_contas; i++) {
            infoConta(&contas[i]);
            printf("\n");
            esperar(2);
        }
    } else {
        printf("Nao existem contas cadastradas.\n");
    }
    esperar(2);
}

float atualizaSaldoTotal(const Conta* conta) {
    return conta->saldo + conta->limite;
}

Conta* buscarContaPorNumero(int numero) {
    for (int i = 0; i < contador_contas; i++) {
        if (contas[i].numero == numero) {
            return &contas[i];
        }
    }
    return NULL;
}

void sacar(Conta* conta, float valor) {
    if (valor > 0 && conta->saldoTotal >= valor) {
        if (conta->saldo >= valor) {
            conta->saldo -= valor;
            conta->saldoTotal = atualizaSaldoTotal(conta);
            printf("Saque efetuado com sucesso\n");
        } else {
            float restante = valor - conta->saldo;
            conta->limite -= restante;
            conta->saldo = 0.0;
            conta->saldoTotal = atualizaSaldoTotal(conta);
            printf("Saque efetuado com sucesso usando o limite\n");
        }
    } else {
        printf("Saque indisponivel. Verifique o seu saldo!\n");
    }
}

void depositar(Conta* conta, float valor) {
    if (valor > 0) {
        conta->saldo += valor;
        conta->saldoTotal = atualizaSaldoTotal(conta);
        printf("Deposito efetuado com sucesso\n");
    } else {
        printf("Deposito indisponivel. Verifique o valor!\n");
    }
}

void transferir(Conta* conta_origem, Conta* conta_destino, float valor) {
    if (valor > 0 && conta_origem->saldoTotal >= valor) {
        if (conta_origem->saldo >= valor) {
            conta_origem->saldo -= valor;
            conta_destino->saldo += valor;
            conta_origem->saldoTotal = atualizaSaldoTotal(conta_origem);
            conta_destino->saldoTotal = atualizaSaldoTotal(conta_destino);
            printf("Transferencia realizada com sucesso!\n");
        } else {
            float restante = valor - conta_origem->saldo;
            conta_origem->limite -= restante;
            conta_origem->saldo = 0.0;
            conta_destino->saldo += valor;
            conta_origem->saldoTotal = atualizaSaldoTotal(conta_origem);
            conta_destino->saldoTotal = atualizaSaldoTotal(conta_destino);
            printf("Transferencia realizada com sucesso usando o limite!\n");
        }
    } else {
        printf("Transferencia indisponivel. Verifique o seu saldo!\n");
    }
}