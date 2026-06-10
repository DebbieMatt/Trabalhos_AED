#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Paciente.h"
#include "Medico.h"
#include "Consulta.h"
#include "Dados.h"

int main()
{
    LISTA atendimentos;
    inicializa(&atendimentos);

    PACIENTE *novoPaciente = NULL;
    MEDICO *novoMedico = NULL;

    int qtdePacientes = 0;
    int qtdeMedicos = 0;
    int op, aux_opc, aux_opc_edit;


    do
    {
        printf("\nSISTEMA DE PRONTO ATENDIMENTO\n");
        printf("1 - Cadastrar paciente/medico\n");
        printf("2 - Listar pacientes/medico\n");
        printf("3 - Gerenciar Atendimentos\n");
        printf("4 - Salvar ou Ler Arquivo\n");
        printf("5 - Ordenar atendimento\n");
        printf("6 - Busca\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        scanf("%d", &op);
        getchar(); // Limpa o buffer de entrada após o scanf

        switch (op)
        {
        case 1: //CADASTRO
            printf("1 - Cadastrar paciente\n");
            printf("2 - Cadastrar medico\n");
            printf("Digite uma opcao: ");
            scanf("%d", &aux_opc);
            getchar(); // Limpa o buffer

            switch (aux_opc)
            {
            case 1:
                // Cadastrar paciente
                if (qtdePacientes == 0)
                    novoPaciente = (PACIENTE *)malloc(sizeof(PACIENTE));
                else
                    novoPaciente = (PACIENTE *)realloc(novoPaciente, (qtdePacientes + 1) * sizeof(PACIENTE));
                if (novoPaciente == NULL)
                {
                    printf("Erro ao alocar memoria!\n");
                    break;
                }
                novoPaciente[qtdePacientes++] = *cadastrarPaciente();
                break;
            case 2:
                // Cadastrar médico
                if (qtdeMedicos == 0)
                    novoMedico = (MEDICO *)malloc(sizeof(MEDICO));
                else
                    novoMedico = (MEDICO *)realloc(novoMedico, (qtdeMedicos + 1) * sizeof(MEDICO));
                if (novoMedico == NULL)
                {
                    printf("Erro ao alocar memoria!\n");
                    break;
                }
                novoMedico[qtdeMedicos++] = *cadastrarMedico();
                break;
            default:
                break;
            }
            break;
        case 2: //LISTAGEM
            printf("1 - Listar Paciente\n");
            printf("2 - Listar Medico\n");
            printf("Digite uma opcao: ");
            scanf("%d", &aux_opc);

            switch (aux_opc)
            {
            case 1:
                listarPacientes(novoPaciente, qtdePacientes);
                break;
            case 2:
                listarMedicos(novoMedico, qtdeMedicos);
                break;
            default:
                printf("Opcao invalida.\n");
                break;
            }
            break;
        case 3: // GERENCIAR ATENDIMENTOS
            printf("1 - Realizar atendimento\n");
            printf("2 - Listar atendimento\n");
            printf("3 - Finalizar atendimento\n");
            printf("4 - Editar dados de atendimento\n");
            printf("Digite uma opcao: ");
            scanf("%d", &aux_opc);

            switch (aux_opc)
            {
            case 1: //realiza atendimento
                consulta(novoPaciente, qtdePacientes, novoMedico, qtdeMedicos, &atendimentos);
                break;
            case 2:
                listarAtendimentos(&atendimentos);
                break;
            case 3:
                encerrarConsulta(&atendimentos);
                break;
            case 4: // ALTERAR
                printf("\nQual destes tipos de dados vc quer alterar:\n");
                printf("1 - Editar Motivo da Consulta e Prioridade.\n");
                printf("2 - Editar Consulta já agendado com medico.\n");
                printf("Digite uma opcao: ");
                scanf("%d", &aux_opc_edit);
                switch (aux_opc_edit)
                {
                case 1:
                    editarAtendimento(&atendimentos);
                    break;
                case 2:
                    alterarMedicoAtendimento(&atendimentos, novoMedico, qtdeMedicos);
                    break;
                default:
                    printf("Opcao invalida.\n");
                    break;
                }
            default:
                printf("Opcao invalida\n");
                break;
            }
            break;
        case 4: // ARQUIVOS 
            printf("1 - Salvar em Arquivo\n");
            printf("2 - Ler este Arquivo\n");
            printf("Digite uma opcao: ");
            scanf("%d", &aux_opc);

            switch (aux_opc)
            {
            case 1:
                salvarAtendimentosEmArquivo(&atendimentos);
                break;
            case 2:
                imprimirConteudoDoArquivo(novoPaciente);
                break;
            default:
                printf("Opcao invalida\n");
                break;
            }
            break;
        case 5: // ordenacao
            printf("1 - Ordenar por Prioridade Crescente\n");
            printf("2 - Ordenada por Prioridade Decrescente.\n");
            printf("3 - Ordenar por Motivo alfabeticamente.\n");
            printf("Digite uma opcao: ");
            scanf("%d", &aux_opc);
            switch (aux_opc)
            {
            case 1:
                bubbleSortPrioridadeCrescente(&atendimentos);
                break;
            case 2:
                bubbleSortPrioridadeDecrescente(&atendimentos);
                break;
            case 3:
                // quickSortMotivo(&atendimentos, );
                break;
            default:
                printf("Opcao invalida.\n");
                break;
            }
            listarAtendimentos(&atendimentos);
            break;
        case 6:
            printf("1 - Busca sequencial por prioridade\n");
            printf("2 - Busca sequencial por motivo da consulta\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &aux_opc);

            switch (aux_opc)
            {
            case 1:
                printf("Digite a prioridade buscada: ");
                scanf("%d", &aux_opc_edit); // vou usar a msm variavel p/ economizar
                ITEM *auxil;
                auxil = buscaSequencialPrioridade(&atendimentos, aux_opc_edit);
                ATENDIMENTO *atendimento = (ATENDIMENTO *)auxil->chave;
                
                printf("O primeiro atendimento da lista da prioridade desejada\n");
                printf("\nPaciente: %s\n", atendimento->paciente->nome);
                printf("Medico: %s\t", atendimento->medico->nome);
                printf("Especialidade: %s\n", atendimento->medico->especialidade);
                printf("Motivo da consulta: %s\n", atendimento->motivo);
                printf("Prioridade: %s\n", (atendimento->prioridade == 1 ? "Leve" : (atendimento->prioridade == 2 ? "Moderada" : "Grave")));
                break;
            case 2:
                //busca sequencial pelo motivo da consulta
                getchar();
                printf("Digite o motivo da consulta a ser buscado: ");
                char motivo[50];
                fgets(motivo, sizeof(motivo), stdin);
                motivo[strcspn(motivo, "\n")] = '\0';
                auxil = buscaSequencialMotivo(&atendimentos, motivo);
                if (auxil != NULL)
                {
                    ATENDIMENTO *atendimento = (ATENDIMENTO *)auxil->chave;
                    printf("Atendimento encontrado por motivo: \n");
                    printf("\nPaciente: %s\n", atendimento->paciente->nome);
                    printf("Medico: %s\t", atendimento->medico->nome);
                    printf("Especialidade: %s\n", atendimento->medico->especialidade);
                    printf("Motivo da consulta: %s\n", atendimento->motivo);
                    printf("Prioridade: %s\n", (atendimento->prioridade == 1 ? "Leve" : (atendimento->prioridade == 2 ? "Moderada" : "Grave")));
                }
                break;
            default:
                printf("Opcao invalida!\n");
                break;
            }
        case 0:
            // Sair do programa
            liberarLista(&atendimentos);
            free(novoPaciente);
            free(novoMedico);
            printf("Saindo do sistema\n");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }

    } while (op != 0);

    return 0;
}
