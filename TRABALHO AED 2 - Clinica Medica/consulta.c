#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Paciente.h"
#include "Medico.h"
#include "Consulta.h"
#include "Dados.h"

void consulta(PACIENTE *p, int qtdeP, MEDICO *m, int qtdeM, LISTA *l)
{
    if (p == NULL || qtdeP == 0 || m == NULL || qtdeM == 0 || l == NULL)
    {
        printf("Nao ha nenhum cadastro no sistema!\n");
        return;
    }

    char paciente[40];
    char medico[40];
    char motivo[50];
    char especialidade[50];
    int prioridade, opPaciente, opMedico;

    printf("\nRealizar atendimento\n");

    printf("\nPacientes cadastrados:\n");
    for (int i = 0; i < qtdeP; i++)
    {
        printf("%d - %s\n", i + 1, p[i].nome);
    }

    printf("Informe o paciente: ");
    scanf("%d", &opPaciente);
    getchar();

    if (opPaciente < 1 || opPaciente > qtdeP)
    {
        printf("Opcao invalida!\n");
        return;
    }
    strcpy(paciente, p[opPaciente - 1].nome);

    // Listar médicos cadastrados
    printf("Medicos cadastrados:\n");
    for (int i = 0; i < qtdeM; i++)
    {
        printf("%d - %s - %s\n", i + 1, m[i].nome, m[i].especialidade);
    }

    printf("Informe o medico: ");
    scanf("%d", &opMedico);
    getchar();

    if (opMedico < 1 || opMedico > qtdeM)
    {
        printf("Opcao invalida!\n");
        return;
    }
    strcpy(medico, m[opMedico - 1].nome);

    printf("Motivo da consulta: ");
    fgets(motivo, sizeof(motivo), stdin);
    motivo[strcspn(motivo, "\n")] = '\0';

    printf("Prioridade (1 - Leve, 2 - Moderada, 3 - Grave): ");
    scanf("%d", &prioridade);
    getchar();

    //inicia um novo atendimento
    ATENDIMENTO *novo = (ATENDIMENTO *)malloc(sizeof(ATENDIMENTO));
    if (novo == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return;
    }

    // Alocar memória para um novo paciente e copia os dados
    novo->paciente = (PACIENTE *)malloc(sizeof(PACIENTE));
    if (novo->paciente == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        free(novo);
        return;
    }

    memcpy(novo->paciente, &p[opPaciente - 1], sizeof(PACIENTE)); //copia os dados do paciente para o novo atendimento
    
    novo->medico = (MEDICO *)malloc(sizeof(MEDICO));
    if (novo->medico == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return;
    }
    // Copia os dados do médico selecionado para a estrutura alocada dinamicamente
    strcpy(novo->medico->nome, m[opMedico - 1].nome);
    strcpy(novo->medico->especialidade, m[opMedico - 1].especialidade);

    strcpy(novo->motivo, motivo);
    novo->prioridade = prioridade;

    //insere o atendimento na lista
    inserir(l, novo);

    // exibe as informações do atendimento
    printf("Atendimento:\n");
    printf("Paciente: %s\n", paciente);
    printf("Medico: %s %s\n", medico, especialidade);
    printf("Motivo da consulta: %s\n", motivo);
    printf("Prioridade: %s\n", (prioridade == 1 ? "Leve" : (prioridade == 2 ? "Moderada" : "Grave")));
}

void listarAtendimentos(LISTA *l)
{
    if (l == NULL || l->inicio == NULL)
    {
        printf("Nenhum atendimento realizado ainda!\n");
        return;
    }

    printf("\nLista de Atendimentos Realizados:\n");
    ITEM *atual = l->inicio;
    while (atual != NULL)
    {
        ATENDIMENTO *atendimento = (ATENDIMENTO *)atual->chave;
        if (atendimento != NULL)
        {
            printf("Paciente: %s\n", atendimento->paciente->nome); // Agora acessa a cópia independente do paciente
            printf("Medico: %s\n", atendimento->medico->nome);
            printf("Especialidade: %s\n", atendimento->medico->especialidade);
            printf("Motivo: %s\n", atendimento->motivo);
            printf("Prioridade: %s\n", (atendimento->prioridade == 1 ? "Leve" : (atendimento->prioridade == 2 ? "Moderada" : "Grave")));
            printf("\n");
            atual = atual->prox;
        }
    }
}

void editarAtendimento(LISTA *atendimentos)
{
    int id;
    printf("Digite o ID do atendimento que deseja editar: ");
    scanf("%d", &id);
    getchar(); // Limpa o buffer

    if (id < 1 || id > atendimentos->qtde)
    {
        printf("ID inválido!\n");
        return;
    }

    // Encontre o atendimento correspondente na lista
    ITEM *atual = atendimentos->inicio;
    for (int i = 1; i < id; i++)
    {
        atual = atual->prox;
    }

    ATENDIMENTO *atendimento = (ATENDIMENTO *)atual->chave;

    printf("Motivo atual: %s\n", atendimento->motivo);
    printf("Digite o novo motivo: ");
    fgets(atendimento->motivo, sizeof(atendimento->motivo), stdin);
    atendimento->motivo[strcspn(atendimento->motivo, "\n")] = '\0';

    printf("Prioridade atual: %d\n", atendimento->prioridade);
    printf("Digite a nova prioridade: ");
    scanf("%d", &atendimento->prioridade);
    getchar(); // Limpa o buffer
}

void alterarMedicoAtendimento(LISTA *atendimentos, MEDICO *medicos, int qtdeMedicos)
{
    if (atendimentos == NULL || atendimentos->inicio == NULL)
    {
        printf("Nenhum atendimento cadastrado!\n");
        return;
    }

    // Exibe todos os atendimentos para o usuário escolher
    printf("Atendimentos:\n");
    ITEM *atual = atendimentos->inicio;
    for (int i = 1; i <= atendimentos->qtde; i++)
    {
        ATENDIMENTO *atendimento = (ATENDIMENTO *)atual->chave;
        printf("%d - Paciente: %s, Medico: %s\n", i, atendimento->paciente->nome, atendimento->medico->nome);
        atual = atual->prox;
    }

    printf("Digite o número do atendimento que deseja alterar o medico: ");
    int id;
    scanf("%d", &id);
    getchar(); // Limpa o buffer

    if (id < 1 || id > atendimentos->qtde)
    {
        printf("Número de atendimento inválido!\n");
        return;
    }

    // Encontre o atendimento correspondente na lista
    atual = atendimentos->inicio;
    for (int i = 1; i < id; i++)
    {
        atual = atual->prox;
    }

    ATENDIMENTO *atendimento = (ATENDIMENTO *)atual->chave;

    // Exibe todos os médicos para o usuário escolher
    printf("Medicos:\n");
    for (int i = 0; i < qtdeMedicos; i++)
    {
        printf("%d - Nome: %s, Especialidade: %s\n", i + 1, medicos[i].nome, medicos[i].especialidade);
    }

    printf("Digite o número do novo medico: ");
    int idMedico;
    scanf("%d", &idMedico);
    getchar(); // Limpa o buffer

    if (idMedico < 1 || idMedico > qtdeMedicos)
    {
        printf("Número de medico inválido!\n");
        return;
    }

    atendimento->medico = &medicos[idMedico - 1];
    printf("O medico do atendimento foi alterado com sucesso!\n");
}

void encerrarConsulta(LISTA *atendimentos)
{
    int id;
    printf("Digite o ID do atendimento que deseja encerrar: ");
    scanf("%d", &id);
    getchar(); // Limpa o buffer

    if (id < 1 || id > atendimentos->qtde)
    {
        printf("ID inválido!\n");
        return;
    }

    // Encontre o atendimento correspondente na lista
    ITEM *atual = atendimentos->inicio;
    ITEM *anterior = NULL;
    for (int i = 1; i < id; i++)
    {
        anterior = atual;
        atual = atual->prox;
    }

    // Remova o atendimento da lista
    if (anterior == NULL)
    {
        atendimentos->inicio = atual->prox;
    }
    else
    {
        anterior->prox = atual->prox;
    }

    // Libere a memória alocada para o atendimento
    free(atual->chave);
    free(atual);

    atendimentos->qtde--;

    printf("Atendimento encerrado com sucesso!\n");
}

void salvarAtendimentosEmArquivo(LISTA *atendimentos)
{
    FILE *arq = fopen("atendimentos.txt", "w"); // abre ou cria um arquivo txt para escrita.

    if (arq)
    {
        ITEM *atual = atendimentos->inicio;
        while (atual != NULL)
        {
            ATENDIMENTO *atendimento = (ATENDIMENTO *)atual->chave;
            fprintf(arq, "Paciente: %s\n", atendimento->paciente->nome);
            fprintf(arq, "Idade: %d\n", atendimento->paciente->idade);
            fprintf(arq, "Medico: %s\n", atendimento->medico->nome);
            fprintf(arq, "Especialidade: %s\n", atendimento->medico->especialidade);
            fprintf(arq, "Motivo: %s\n", atendimento->motivo);
            fprintf(arq, "Prioridade: %d\n\n", atendimento->prioridade);
            atual = atual->prox;
        }
        fclose(arq); // fecha o arquivo.
    }
    else
    {
        printf("ERRO: nao é possivel abrir o arquivo.");
    }
}

void imprimirConteudoDoArquivo(PACIENTE *novoPaciente)
{
    FILE *arq = fopen("atendimentos.txt", "r"); // Abre o arquivo em modo de leitura

    if (arq == NULL)
    {
        printf("ERRO: nao é possível abrir o arquivo.\n");
        return;
    }

    char linha[100]; // Buffer para armazenar cada linha do arquivo

    // Lê cada linha do arquivo até o final
    while (fgets(linha, sizeof(linha), arq) != NULL)
    {
        printf("%s", linha); // Imprime a linha
    }

    fclose(arq); // Fecha o arquivo
}
