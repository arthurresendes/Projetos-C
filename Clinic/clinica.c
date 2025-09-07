#include <stdio.h>
#include <string.h>
#include <stdio.h>

//Uma estrtura que guarda as informações de cadastro de pessoas
struct cadastrosP
{
    char nomeP[200];
    int idade;
    char cpf[12];
    char convenio[50];
    int telefone;
} p;


//Uma estrtura que guarda as informações de cadastro de medicos
struct cadastrosM
{
    char nomeM[10][30];
    char crm[10][10]; // corrigido para 10 strings
    char especialidade[10][50];
} M;

//Cadastro da pessoa
void pessoa()
{
    printf("Cadastre você na clinica control\n");
    printf("Digite seu nome: ");
    fgets(p.nomeP, sizeof(p.nomeP), stdin);
    p.nomeP[strcspn(p.nomeP, "\n")] = '\0';

    printf("Digite sua idade: ");
    scanf("%d", &p.idade);
    getchar(); // Limpa o \n do buffer

    printf("Digite seu CPF: ");
    fgets(p.cpf, sizeof(p.cpf), stdin);
    p.cpf[strcspn(p.cpf, "\n")] = '\0';

    printf("Digite seu convênio: ");
    fgets(p.convenio, sizeof(p.convenio), stdin);
    p.convenio[strcspn(p.convenio, "\n")] = '\0';

    printf("Digite seu telefone (Apenas números): ");
    scanf("%d", &p.telefone);
    getchar();
}

//Mostrar informações da pessoa
void mostrar()
{
    printf("\nCadastro concluido!!\n");
    printf("Suas informacoes:\n Nome: %s\n Idade: %d\n CPF: %s\n Convenio: %s\n Telefone: %d\n", p.nomeP, p.idade, p.cpf, p.convenio, p.telefone);
}

//Menu inicial
void menu()
{
    printf("============== Menu =============\n");
    printf("[1] Cadastre-se\n");
    printf("[2] Ver listagem de médicos\n");
    printf("[3] Agendar consulta\n");
    printf("[4] Consulta marcada\n");
    printf("[5] Cancelar consulta\n");
    printf("[0] Sair\n");
    printf("=================================\n");
}

int main()
{
    //Criacao de dois inteiros , um como opcao para que o usuario decida oq fzr e outra para listagem que seria qual medico ira escolher e depois mostrar(comeca com -1 pois vetor comeca do 0)
    int opcao;
    int listagem = -1; // variável para armazenar o médico selecionado (agenda)

    // Inicializando dados médicos
    strcpy(M.nomeM[0], "Arthur");
    strcpy(M.nomeM[1], "Gustavo");
    strcpy(M.nomeM[2], "Henrique");
    strcpy(M.nomeM[3], "Jose");
    strcpy(M.nomeM[4], "Lucas");
    strcpy(M.nomeM[5], "Ana");
    strcpy(M.nomeM[6], "Beatriz");
    strcpy(M.nomeM[7], "Carlos");
    strcpy(M.nomeM[8], "Giovanna");
    strcpy(M.nomeM[9], "Gabriel");

    strcpy(M.crm[0], "12345-SP");
    strcpy(M.crm[1], "67890-RJ");
    strcpy(M.crm[2], "54321-MG");
    strcpy(M.crm[3], "98765-RS");
    strcpy(M.crm[4], "11223-DF");
    strcpy(M.crm[5], "44556-BA");
    strcpy(M.crm[6], "77889-PE");
    strcpy(M.crm[7], "33445-CE");
    strcpy(M.crm[8], "99001-PR");
    strcpy(M.crm[9], "55667-SC");

    strcpy(M.especialidade[0], "Cardiologia");
    strcpy(M.especialidade[1], "Neurologia");
    strcpy(M.especialidade[2], "Pediatria");
    strcpy(M.especialidade[3], "Dermatologia");
    strcpy(M.especialidade[4], "Ortopedia");
    strcpy(M.especialidade[5], "Endocrinologia");
    strcpy(M.especialidade[6], "Psiquiatria");
    strcpy(M.especialidade[7], "Ginecologia");
    strcpy(M.especialidade[8], "Oftalmologia");
    strcpy(M.especialidade[9], "Otorrinolaringologia");

    menu();

    do
    {
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer do teclado

        switch (opcao)
        {
        case 1:
            pessoa();
            mostrar();
            menu();
            break;

        case 2:
            printf("Lista de médicos cadastrados:\n");
            for (int i = 0; i < 10; i++)
            {
                printf("%d - %s | CRM: %s | Especialidade: %s\n",
                    i + 1, M.nomeM[i], M.crm[i], M.especialidade[i]);
            }
            menu();
            break;

        case 3:
            printf("Lista de médicos disponíveis para agendamento:\n");
            for (int i = 0; i < 10; i++)
            {
                printf("%d - %s | CRM: %s | Especialidade: %s\n",
                    i + 1, M.nomeM[i], M.crm[i], M.especialidade[i]);
            }
            printf("Qual medico quer passar (numero da listagem): ");
            scanf("%d", &listagem);
            getchar();
            //Se a listagem for menor que 1 ou maior que 10 , mostra numero invalido
            if (listagem < 1 || listagem > 10)
            {
                printf("Número inválido! Por favor, escolha um número entre 1 e 10.\n");
                listagem = -1; // resetar seleção inválida
            }
            //Se nao mostra a consulta que foi agendada de acordo com sua escolha
            else
            {
                printf("Consulta agendada com:\n");
                printf("Nome: %s\n", M.nomeM[listagem - 1]);
                printf("CRM: %s\n", M.crm[listagem - 1]);
                printf("Especialidade: %s\n", M.especialidade[listagem - 1]);
            }
            menu();
            break;
        case 4:
            //Se a consulta permanecer como -1 diz que nao tem consulta
            if (listagem == -1)
            {
                printf("Nenhuma consulta agendada ainda.\n");
            }
            //Se nao criamos um inteiro idx que vai ser igual a listagem - 1 e depois mostra os profisisonais
            else
            {
                int idx = listagem - 1;
                printf("Consulta marcada:\n");
                printf("Paciente: %s\n", p.nomeP);
                printf("Médico: %s\n", M.nomeM[idx]);
                printf("CRM: %s\n", M.crm[idx]);
                printf("Especialidade: %s\n", M.especialidade[idx]);
            }
            menu();
            break;

        case 5:
            if (listagem == -1)
            {
                printf("Nenhuma consulta agendada para cancelar.\n");
            }
            else
            {
                printf("Consulta com %s cancelada.\n", M.nomeM[listagem - 1]);
                listagem = -1;
            }
            menu();
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida! Tente novamente.\n");
            menu();
            break;
        }
    } while (opcao != 0);

    return 0;
}
