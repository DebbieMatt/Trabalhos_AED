#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct
{
    char nome[50];
    int idade;
} PACIENTE;

PACIENTE *cadastrarPaciente();
int compararPacientes(const void *a, const void *b);
void listarPacientes(PACIENTE *p, int quantidade);

#endif
