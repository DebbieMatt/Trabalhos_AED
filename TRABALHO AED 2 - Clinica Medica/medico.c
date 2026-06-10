#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Medico.h"
#include "Dados.h"

// Função para cadastrar médico
MEDICO *cadastrarMedico()
{
    MEDICO *novoMedico = (MEDICO *)malloc(sizeof(MEDICO)); // Alocando memória
    if (novoMedico == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return NULL;
    }

    printf("\nCADASTRO DE MEDICO\n");
    printf("Nome: ");
    fgets(novoMedico->nome, sizeof(novoMedico->nome), stdin);
    novoMedico->nome[strcspn(novoMedico->nome, "\n")] = '\0';

    printf("Especialidade: ");
    fgets(novoMedico->especialidade, sizeof(novoMedico->especialidade), stdin);
    novoMedico->especialidade[strcspn(novoMedico->especialidade, "\n")] = '\0';

    return novoMedico;
}

// Função de comparação para qsort
int compararMedicos(const void *a, const void *b)
{
    MEDICO *medicoA = (MEDICO *)a;
    MEDICO *medicoB = (MEDICO *)b;

    // Primeiro, compare os nomes
    int nomeComparacao = strcmp(medicoA->nome, medicoB->nome);
    if (nomeComparacao != 0)
    {
        return nomeComparacao; // Se os nomes são diferentes, retorne o resultado da comparação de nomes
    }

    // Se os nomes são iguais, compare as especialidades
    return strcmp(medicoA->especialidade, medicoB->especialidade);
}

// Função para listar os médicos cadastrados
void listarMedicos(MEDICO *m, int quantidade)
{
    if (m == NULL || quantidade == 0)
    {
        printf("Nenhum medico cadastrado!\n");
        return;
    }

    printf("\nMedicos Cadastrados:\n");
    for (int i = 0; i < quantidade; i++)
    {
        printf("Nome: %s\n", m[i].nome);
        printf("Especialidade: %s\n", m[i].especialidade);
    }
}
