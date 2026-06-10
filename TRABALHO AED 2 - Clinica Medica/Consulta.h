#ifndef CONSULTA_H
#define CONSULTA_H

#include "Paciente.h"
#include "Medico.h"
#include "Dados.h"

typedef struct
{
    PACIENTE *paciente;
    MEDICO *medico;
    char motivo[50];
    int prioridade;
} ATENDIMENTO;

void consulta(PACIENTE *p, int qtdeP, MEDICO *m, int qtdeM, LISTA *l);
void listarAtendimentos(LISTA *l);
void editarAtendimento(LISTA *atendimentos);
void alterarMedicoAtendimento(LISTA *atendimentos, MEDICO *medicos, int qtdeMedicos);
void encerrarConsulta(LISTA *atendimentos);
void salvarAtendimentosEmArquivo(LISTA *atendimentos);
void imprimirConteudoDoArquivo(PACIENTE *novoPaciente);
void salvarAtendimentosEmArquivo(LISTA *atendimentos);
void imprimirConteudoDoArquivo(PACIENTE *novoPaciente);

#endif
