#ifndef MEDICO_H
#define MEDICO_H

typedef struct
{
    char nome[40];
    char especialidade[50];
} MEDICO;

MEDICO *cadastrarMedico();
int compararMedicos(const void *a, const void *b);
void listarMedicos(MEDICO *m, int quantidade);

#endif
