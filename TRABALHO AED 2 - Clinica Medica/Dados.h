#ifndef DADOS_H
#define DADOS_H

// Estrutura para uma lista encadeada
typedef struct ITEM
{
    void *chave;
    struct ITEM *prox;
} ITEM;

typedef struct
{
    ITEM *inicio;
    int qtde;
} LISTA;

void inicializa(LISTA *l);
void inserir(LISTA *l, void *chave);
void bubbleSortPrioridadeCrescente(LISTA *l);
void bubbleSortPrioridadeDecrescente(LISTA *l);
ITEM *buscaSequencialPrioridade(LISTA *atendimentos, int prioridade);
ITEM *buscaSequencialMotivo(LISTA *atendimento, const char *motivo);
void liberarLista(LISTA *l);


#endif
