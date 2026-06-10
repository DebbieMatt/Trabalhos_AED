#include<stdio.h>
#include<stdlib.h>

#include "Dados.h"
#include "Consulta.h"

// Inicializa a lista
void inicializa(LISTA *l)
{
    l->inicio = NULL;
    l->qtde = 0;
}

// Insere um elemento na lista
void inserir(LISTA *l, void *chave)
{
    ITEM *novoItem = (ITEM *)malloc(sizeof(ITEM));
    if (novoItem == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return;
    }

    novoItem->chave = chave;
    novoItem->prox = l->inicio;
    l->inicio = novoItem;
    l->qtde++;
}

void bubbleSortPrioridadeCrescente(LISTA *l)
{
    if (l == NULL || l->inicio == NULL)
    {
        printf("Lista vazia ou nao inicializada!\n");
        return;
    }

    int trocado;
    ITEM *atual;
    ATENDIMENTO *atendimentoAtual;
    void *temp;

    do
    {
        trocado = 0;
        atual = l->inicio;

        while (atual->prox != NULL)
        {
            ATENDIMENTO *atendimentoAtual = (ATENDIMENTO *)atual->chave;
            ATENDIMENTO *atendimentoProx = (ATENDIMENTO *)atual->prox->chave;

            if (atendimentoAtual->prioridade > atendimentoProx->prioridade)
            {
                // Troca os elementos na lista
                temp = atual->chave;
                atual->chave = atual->prox->chave;
                atual->prox->chave = temp;

                trocado = 1;
            }

            atual = atual->prox;
        }
    } while (trocado);
}

void bubbleSortPrioridadeDecrescente(LISTA *l)
{
    if (l == NULL || l->inicio == NULL)
    {
        printf("Lista vazia ou nao inicializada!\n");
        return;
    }

    int trocado;
    ITEM *atual;
    ATENDIMENTO *atendimentoAtual;
    void *temp;

    do
    {
        trocado = 0;
        atual = l->inicio;

        while (atual->prox != NULL)
        {
            ATENDIMENTO *atendimentoAtual = (ATENDIMENTO *)atual->chave;
            ATENDIMENTO *atendimentoProx = (ATENDIMENTO *)atual->prox->chave;

            if (atendimentoAtual->prioridade < atendimentoProx->prioridade) // Alteração aqui
            {
                // Troca os elementos na lista
                temp = atual->chave;
                atual->chave = atual->prox->chave;
                atual->prox->chave = temp;

                trocado = 1;
            }

            atual = atual->prox;
        }
    } while (trocado);
}

ITEM *buscaSequencialPrioridade(LISTA *atendimentos, int prioridade)
{
    if (atendimentos == NULL || atendimentos->inicio == NULL)
    {
        printf("Nenhum atendimento cadastrado!\n");
        return NULL;
    }

    ITEM *atual = atendimentos->inicio;
    while (atual != NULL)
    {
        ATENDIMENTO *atendimento = (ATENDIMENTO *)atual->chave;
        if (atendimento->prioridade == prioridade)
        {
            return atual;
        }
        atual = atual->prox;
    }

    printf("Atendimento com prioridade %d nao encontrado!\n", prioridade);
    return NULL;
}

ITEM *buscaSequencialMotivo(LISTA *atendimento, const char *motivo) 
{
    if (atendimento == NULL || atendimento->inicio == NULL)
    {
        printf("Nenhum atendimento cadastrado!\n");
        return NULL;
    }
    
    ITEM *atual = atendimento->inicio;
    while (atual != NULL)
    {
        ATENDIMENTO *atendimento = (ATENDIMENTO *)atual->chave;
        if (strcmp(atendimento->motivo, motivo) == 0)
        {
            return atual;
        }
        atual = atual->prox;
    }
    
    printf("Atendimento com o motivo '%s' nao encontrado no sistema!\n", motivo);
    return NULL;
}

// Libera a memória alocada para a lista de atendimentos
void liberarLista(LISTA *l)
{
    if (l == NULL)
        return;

    ITEM *atendimentoAtual = l->inicio;
    while (atendimentoAtual != NULL)
    {
        ATENDIMENTO *atendimento = (ATENDIMENTO *)atendimentoAtual->chave;
        free(atendimento->paciente); // Liberar a memória do paciente
        free(atendimento);           // Liberar o próprio atendimento
        ITEM *prox = atendimentoAtual->prox;
        free(atendimentoAtual); // Liberar o nó da lista
        atendimentoAtual = prox;
    }

    l->inicio = NULL;
    l->qtde = 0;
}
