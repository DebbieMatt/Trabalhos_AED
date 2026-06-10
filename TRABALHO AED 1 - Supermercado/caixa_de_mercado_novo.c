// Alunas: Débora Mateus e Maria Vittória Sousa
// Turma VE2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int estoque[10];
float divida_cliente[10];

void consultar_debitos()
{
    int cliente;
    printf("\n");
    printf("\nDigite  o codigo do cliente: ");
    printf("(se deseja cancelar digite um codigo invalido) ");
    scanf("%d", &cliente);
    if ((cliente >= 0) && (cliente < 10)) // se ele digitar um vetor valido
    {
        printf("Voce digitou um codigo valido. ");
        printf("Divida do cliente %d = R$%.2f ", cliente, divida_cliente[cliente]);
    }
    else
    {
        printf("Voce nao digitou um codigo valido. ");
    }
}

void perdoar_divida()
{
    int cliente_sorteado, cliente_tem_debito = 1, existe_cliente_com_divida = 0;
    // fazer for
    for (int i = 0; i < 10; i++)
    {
        if (divida_cliente[i] != 0)
        {
            existe_cliente_com_divida++; // existe alguem com divida
        }
        else
        {
            // nao existe ninguem com divida
        }
    }
    if (existe_cliente_com_divida > 0) // se existir cliente com divida
    {
        do
        {
            srand(time(0));
            cliente_sorteado = rand() % 10;
            printf("\nNumero sorteado: %d", cliente_sorteado);

            if (divida_cliente[cliente_sorteado] != 0) // se ele tiver divida
            {
                printf("\nDivida anterior: %.2f", divida_cliente[cliente_sorteado]);
                divida_cliente[cliente_sorteado] = 0;
                cliente_tem_debito = 0;
                printf("\nDivida zerada. valor atual: %.2f", divida_cliente[cliente_sorteado]);
                break;
            }
            else
            {
                printf("\nCliente não possui debito.");
            }
        } while (cliente_tem_debito == 1);
    }
    else
    {
        printf("\nNao existe clientes com divida. ");
    }
}

void consultar_estoque()
{
    int item;
    printf("\n");
    printf("\nQual item deseja ver: ");
    printf("(se deseja cancelar digite um codigo invalido) ");
    scanf("%d", &item);

    if ((item >= 0) && (item < 10)) // se ele digitar um vetor valido
    {
        printf("Voce digitou um codigo valido. ");
        printf("\nEstoque: %d \n", estoque[item]);
    }
    else
    {
        printf("Voce nao digitou um codigo valido. ");
    }
}

void diminui_estoque(int item, int quantidade)
{
    estoque[item] -= quantidade;
}

int verifica_estoque(int item, int quantidade)
{
    if (estoque[item] >= quantidade)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void prencher_estoque()
{
    int item, quant;
    printf("\n");
    printf("\nQual item deseja preencher:\n ");
    printf("(se deseja cancelar digite um codigo invalido) ");
    scanf("%d", &item);

    if ((item >= 0) && (item < 10)) // se ele digitar um vetor valido
    {
        printf("Voce digitou um codigo valido. ");

        printf("\nQual a quantidade deseja aumentar: ");
        scanf("%d", &quant);

        printf("\nEstoque antigo: %d", estoque[item]);
        estoque[item] += quant;
        printf("\nNovo estoque atualizado: %d \n", estoque[item]);
    }
    else
    {
        printf("Voce nao digitou um codigo valido. ");
    }
}

void compra()
{
    int item, quant, cliente, retorno_estoque, metodo_de_pagamento;
    float valor_total;
    valor_total = 0; // reiniciar a variavel valor

    do
    {
        printf("\n");
        printf("\nPor favor digite o item de nossa nosso supermercado, que deseja levar: ");
        printf("\n(Caso queira finalizar a compra digite -1) ");
        scanf("%d", &item);

        if (item == -1) // finaliza compra
        {
            break;
        }
        if ((item < 0) || (item >= 10)) // se ele digitar um vetor de item não valido valido
        {
            printf(" Voce digitou um codigo de item invalido. ");
        }
        else
        {
            printf(" Voce digitou um item valido. ");
            printf("\n");
            printf("Digite a quantidade: ");
            scanf("%d", &quant);

            if (quant > 0) // se digitar uma quantidade maior que 0
            {
                retorno_estoque = verifica_estoque(item, quant);
                // se retorno estoque = 1 é pq tem estoque disponivel
                // se retorno estoque = 0 nao tem estoque disponivel
                // printf("%d", retorno_estoque);

                if (retorno_estoque == 1)
                {
                    // completo as opcoes de compra

                    switch (item)
                    {
                    case 0:

                        if (quant >= 3) // atacado
                        {
                            valor_total += 1.95 * quant;
                            printf("\nVoce esta levando %i quantidade(s) pasta de dente(s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        else // varejo
                        {
                            valor_total += 2.10 * quant;
                            printf("\nVoce esta levando %i quantidade(s) pasta de dente(s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        break;

                    case 1:

                        if (quant >= 3) // atacado
                        {
                            valor_total += 8.20 * quant;
                            printf("\nVoce esta levando %i quantidade(s) pão hot dog(s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        else // varejo
                        {
                            valor_total += 9.40 * quant;
                            printf("\nVoce esta levando %i quantidade(s) pão hot dog(s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        break;

                    case 2:

                        if (quant >= 4) // atacado
                        {
                            valor_total += 4 * quant;
                            printf("\nVoce esta levando %i quantidade(s) yakisoba(s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        else // varejo
                        {
                            valor_total += 4.20 * quant;
                            printf("\nVoce esta levando %i quantidade(s) yakisoba(s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        break;

                    case 3:

                        if (quant >= 3) // atacado
                        {
                            valor_total += 4.80 * quant;
                            printf("\nVoce esta levando %i quantidade(s) massa de lasanha(s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        else // varejo
                        {
                            valor_total += 5 * quant;
                            printf("\nVoce esta levando %i quantidade(s) massa de lasanha(s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        break;

                    case 4:

                        if (quant >= 2) // atacado
                        {
                            valor_total += 19.85 * quant;
                            printf("\nVoce esta levando %i quantidade(s) carne de porco(s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        else // varejo
                        {
                            valor_total += 21 * quant;
                            printf("\nVoce esta levando %i quantidade(s) carne de porco(s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        break;

                    case 5:

                        if (quant >= 5) // atacado
                        {
                            valor_total += 5.55 * quant;
                            printf("\nVoce esta levando %i quantidade(s) feijão preto(s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        else // varejo
                        {
                            valor_total += 5.99 * quant;
                            printf("\nVoce esta levando %i quantidade(s) feijão preto(s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        break;

                    case 6:

                        if (quant >= 7) // atacado
                        {
                            valor_total += 2 * quant;
                            printf("\nVoce esta levando %i quantidade(s) ervilha (s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        else // varejo
                        {
                            valor_total += 2.20 * quant;
                            printf("\nVoce esta levando %i quantidade(s) ervilha (s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        break;

                    case 7:

                        if (quant >= 5) // atacado
                        {
                            valor_total += 3.20 * quant;
                            printf("\nVoce esta levando %i quantidade(s) detergente (s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        else // varejo
                        {
                            valor_total += 4 * quant;
                            printf("\nVoce esta levando %i quantidade(s) detergente (s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        break;

                    case 8:

                        if (quant >= 3) // atacado
                        {
                            valor_total += 10 * quant;
                            printf("\nVoce esta levando %i quantidade(s) caixa de chocolate(s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        else // varejo
                        {
                            valor_total += 11 * quant;
                            printf("\nVoce esta levando %i quantidade(s) caixa de chocolate(s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        break;

                    case 9:

                        if (quant >= 6) // atacado
                        {
                            valor_total += 4.99 * quant;
                            printf("\nVoce esta levando %i quantidade(s) banana(s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        else // varejo
                        {
                            valor_total += 5.75 * quant;
                            printf("\nVoce esta levando %i quantidade(s) banana(s). \n", quant);
                            diminui_estoque(item, quant);
                            printf("Lhe custara R$ %.2f \n", valor_total);
                        }
                        break;

                    default:
                        printf("Opcao nao disponivel. ");
                        break;
                    }
                }
                else
                {
                    printf("Quantidade nao disponivel no estoque. ");
                }
            }
            else
            {
                printf("Voce nao digitou uma quantidade valida, por favor digite uma quantidade maior que 0. ");
            }
        }

    } while (item != -1);

    if (valor_total == 0)
    {
        printf("Nao comprou nada. ");
    }
    else
    {
        // metodo de pagamento
        printf("\n");
        printf("\nDigite 1 - pix");
        printf("\nDigite 2 - Cartao credito ou debito");
        printf("\nDigite 3 - Dinheiro");
        printf("\nDigite 4 - Crediario");

        // completo as opcoes de pagamento a baixo

        do
        {
            printf("\n");
            printf("\nQual o metodo de pagamento: ");
            scanf("%d", &metodo_de_pagamento);
            switch (metodo_de_pagamento)
            {
            case 1: // pix 5% desconto
                valor_total = valor_total * 0.95;
                printf("Valor a pagar: %.2f", valor_total);
                valor_total = 0;
                break;

            case 2: // cartao credito/debito
                printf("Valor a pagar: %.2f", valor_total);
                valor_total = 0;
                break;

            case 3: // dinheiro
                valor_total = valor_total * 0.98;
                printf("Valor a pagar: %.2f", valor_total);
                valor_total = 0;
                break;

            case 4: // crediario
                printf("Digite o codigo do cliente: ");
                scanf("%d", &cliente);
                if ((cliente >= 0) && (cliente < 10)) // se ele digitar um vetor valido
                {
                    printf("Voce digitou um codigo valido. ");
                    divida_cliente[cliente] = divida_cliente[cliente] + valor_total;
                    printf("Divida atual do cliente %d: R$%.2f", cliente, divida_cliente[cliente]);
                    valor_total = 0;
                }
                else
                {
                    printf(" Voce nao digitou um codigo valido. ");
                }

                break;
            default:
                printf("\nOpcao de pagamento invalida.");
                break;
            }
        } while (valor_total != 0); // para garantir q o valor será pago
        printf("\nPagamento efetuado com sucesso.");
    }
}

void pagar_debito_crediario()
{
    int codigo_cliente;
    float valor;
    printf("\nDigite o codigo do cliente: \n");
    printf("(se deseja cancelar digite um codigo invalido) ");
    scanf("%d", &codigo_cliente);

    if ((codigo_cliente >= 0) && (codigo_cliente < 10)) // se ele digitar um vetor valido
    {
        printf("Voce digitou um codigo valido. ");
        printf("\nDigite o valor que deseja pagar: ");
        scanf("%f", &valor);

        if (divida_cliente[codigo_cliente] == 0) // se o cliente não deve nada
        {
            printf("\nCliente não tem divida");
        }
        else if (divida_cliente[codigo_cliente] < valor) // se o cliente quis pagar mais do que sua divida
        {
            printf("\nValor a pagar maior do que a divida atual");
        }
        else if ((divida_cliente[codigo_cliente] > 0) && (divida_cliente[codigo_cliente] >= valor)) // valor possivel de pagar
        {
            printf("\nEh possivel pagar sua divida. Divida anterior: %.2f", divida_cliente[codigo_cliente]);
            divida_cliente[codigo_cliente] -= valor;
            printf("\nDivida atual: %.2f", divida_cliente[codigo_cliente]);
        }
    }
    else
    {
        printf(" Voce nao digitou um codigo valido. ");
    }
}

int main()
{
    int codigo_menu;
    for (int i = 0; i < 10; i++) // para zerar os vetores e eles nao comecarem com lixo de memoria
    {
        divida_cliente[i] = 0; // zerar 
        estoque[i] = 0;        // zerar 
    }

    do
    {
        printf("\n");
        printf("\n1 - simular compra");                                               // completo
        printf("\n2 - consultar debitos de clientes do crediario");                   // feito
        printf("\n3 - preencher estoque");                                            // feito
        printf("\n4 - consultar estoque");                                            //(estoque inicia vazio)               // feito
        printf("\n5 - pagar debitos de clientes do cediario (total ou parcial)");     // feito
        printf("\n6 - sortear um cliente que tera sua dívida do crediário perdoada"); // feito
        printf("\n(-1 codigo de parada)");                                            // feito
        printf("\nDigite sua opcao: ");
        scanf("%d", &codigo_menu);

        if (codigo_menu == -1)
        {
            break;
        }
        switch (codigo_menu)
        {
        case 1:
            compra();
            break;
        case 2:
            consultar_debitos();
            break;
        case 3:
            prencher_estoque();
            break;
        case 4:
            consultar_estoque();
            break;
        case 5:
            pagar_debito_crediario();
            break;
        case 6:
            perdoar_divida();
            break;
        default:
            break;
        }

    } while (codigo_menu != -1);

    return 0;
}
