/*
 * Trabalho B1 - Logica de Programacao e Algoritmos
 * Simulador de Entregas
 *
 * Programa que processa solicitacoes de entrega, calcula o valor de
 * cada uma conforme as regras de negocio do roteiro e apresenta um
 * resumo da sessao ao final.
 */

#include <stdio.h>

/* ----------------------- Constantes do dominio ----------------------- */

#define TARIFA_POR_KM        1.20f
#define VALOR_PROTECAO       7.50f
#define VALOR_TENTATIVA      4.00f

#define BASE_ATE_5KM         8.00f
#define BASE_ATE_15KM        12.00f
#define BASE_ATE_30KM        18.00f
#define BASE_ACIMA_30KM      25.00f

#define PERC_PESO_FAIXA1     0.00f   /* ate 2 kg            */
#define PERC_PESO_FAIXA2     0.05f   /* acima de 2 ate 5 kg  */
#define PERC_PESO_FAIXA3     0.10f   /* acima de 5 ate 10 kg */
#define PERC_PESO_FAIXA4     0.20f   /* acima de 10 kg       */

#define PERC_MOD_ECONOMICA   0.00f
#define PERC_MOD_EXPRESSA    0.15f
#define PERC_MOD_PRIORITARIA 0.30f

#define MOD_ECONOMICA        1
#define MOD_EXPRESSA         2
#define MOD_PRIORITARIA      3

/* --------------------- Prototipos das funcoes ------------------------ */

float lerDistanciaValida(void);
float lerPesoValido(void);
int   lerModalidadeValida(void);
int   lerProtecaoValida(void);
int   lerTentativasValidas(void);
int   lerContinuarValido(void);

float obterValorBaseDistancia(float distancia);
float calcularSubtotalInicial(float distancia);
float obterPercentualPeso(float peso);
float obterPercentualModalidade(int modalidade);
float calcularValorFinal(float subtotal, float percentualPeso,
                          float percentualModalidade, int protecao,
                          int tentativasAdicionais);

void exibirResultadoEntrega(float subtotal, float valorFinal);
void exibirResumoFinal(int totalEntregas, float valorTotal, float valorMedio,
                        int qtdEconomica, int qtdExpressa, int qtdPrioritaria,
                        float maiorValor, float menorValor);

/* ------------------------------ main ---------------------------------- */

int main(void) {
    int continuar;

    int totalEntregas = 0;
    float valorTotalSessao = 0.0f;
    float maiorValor = 0.0f;
    float menorValor = 0.0f;

    int qtdEconomica = 0;
    int qtdExpressa = 0;
    int qtdPrioritaria = 0;

    printf("=== Simulador de Entregas ===\n\n");

    do {
        float distancia = lerDistanciaValida();
        float peso = lerPesoValido();
        int modalidade = lerModalidadeValida();
        int protecao = lerProtecaoValida();
        int tentativas = lerTentativasValidas();

        float subtotal = calcularSubtotalInicial(distancia);
        float percentualPeso = obterPercentualPeso(peso);
        float percentualModalidade = obterPercentualModalidade(modalidade);

        float valorFinal = calcularValorFinal(subtotal, percentualPeso,
                                               percentualModalidade,
                                               protecao, tentativas);

        exibirResultadoEntrega(subtotal, valorFinal);

        /* Atualiza contadores e acumuladores do resumo */
        totalEntregas = totalEntregas + 1;
        valorTotalSessao = valorTotalSessao + valorFinal;

        if (totalEntregas == 1) {
            maiorValor = valorFinal;
            menorValor = valorFinal;
        } else {
            if (valorFinal > maiorValor) {
                maiorValor = valorFinal;
            }
            if (valorFinal < menorValor) {
                menorValor = valorFinal;
            }
        }

        if (modalidade == MOD_ECONOMICA) {
            qtdEconomica = qtdEconomica + 1;
        } else if (modalidade == MOD_EXPRESSA) {
            qtdExpressa = qtdExpressa + 1;
        } else {
            qtdPrioritaria = qtdPrioritaria + 1;
        }

        printf("\n");
        continuar = lerContinuarValido();
        printf("\n");

    } while (continuar == 1);

    if (totalEntregas > 0) {
        float valorMedio = valorTotalSessao / totalEntregas;
        exibirResumoFinal(totalEntregas, valorTotalSessao, valorMedio,
                           qtdEconomica, qtdExpressa, qtdPrioritaria,
                           maiorValor, menorValor);
    } else {
        printf("Nenhuma entrega foi processada nesta sessao.\n");
    }

    return 0;
}

/* --------------------- Funcoes de leitura/validacao -------------------- */

float lerDistanciaValida(void) {
    float distancia;

    printf("Distancia (km): ");
    scanf("%f", &distancia);

    while (distancia <= 0.0f) {
        printf("Distancia invalida. Informe um valor maior que zero: ");
        scanf("%f", &distancia);
    }

    return distancia;
}

float lerPesoValido(void) {
    float peso;

    printf("Peso (kg): ");
    scanf("%f", &peso);

    while (peso <= 0.0f) {
        printf("Peso invalido. Informe um valor maior que zero: ");
        scanf("%f", &peso);
    }

    return peso;
}

int lerModalidadeValida(void) {
    int modalidade;

    printf("Modalidade (1-Economica, 2-Expressa, 3-Prioritaria): ");
    scanf("%d", &modalidade);

    while (modalidade != MOD_ECONOMICA && modalidade != MOD_EXPRESSA &&
           modalidade != MOD_PRIORITARIA) {
        printf("Modalidade invalida. Informe 1, 2 ou 3: ");
        scanf("%d", &modalidade);
    }

    return modalidade;
}

int lerProtecaoValida(void) {
    int protecao;

    printf("Servico de protecao (1-Sim, 0-Nao): ");
    scanf("%d", &protecao);

    while (protecao != 0 && protecao != 1) {
        printf("Valor invalido. Informe 0 ou 1: ");
        scanf("%d", &protecao);
    }

    return protecao;
}

int lerTentativasValidas(void) {
    int tentativas;

    printf("Quantidade de tentativas adicionais: ");
    scanf("%d", &tentativas);

    while (tentativas < 0) {
        printf("Valor invalido. Informe um numero maior ou igual a zero: ");
        scanf("%d", &tentativas);
    }

    return tentativas;
}

int lerContinuarValido(void) {
    int opcao;

    printf("Deseja processar outra entrega? (1-Sim, 0-Nao): ");
    scanf("%d", &opcao);

    while (opcao != 0 && opcao != 1) {
        printf("Valor invalido. Informe 0 ou 1: ");
        scanf("%d", &opcao);
    }

    return opcao;
}

/* --------------------------- Funcoes de calculo ------------------------ */

float obterValorBaseDistancia(float distancia) {
    if (distancia <= 5.0f) {
        return BASE_ATE_5KM;
    } else if (distancia <= 15.0f) {
        return BASE_ATE_15KM;
    } else if (distancia <= 30.0f) {
        return BASE_ATE_30KM;
    } else {
        return BASE_ACIMA_30KM;
    }
}

float calcularSubtotalInicial(float distancia) {
    float valorBase = obterValorBaseDistancia(distancia);
    return valorBase + (distancia * TARIFA_POR_KM);
}

float obterPercentualPeso(float peso) {
    if (peso <= 2.0f) {
        return PERC_PESO_FAIXA1;
    } else if (peso <= 5.0f) {
        return PERC_PESO_FAIXA2;
    } else if (peso <= 10.0f) {
        return PERC_PESO_FAIXA3;
    } else {
        return PERC_PESO_FAIXA4;
    }
}

float obterPercentualModalidade(int modalidade) {
    if (modalidade == MOD_ECONOMICA) {
        return PERC_MOD_ECONOMICA;
    } else if (modalidade == MOD_EXPRESSA) {
        return PERC_MOD_EXPRESSA;
    } else {
        return PERC_MOD_PRIORITARIA;
    }
}

float calcularValorFinal(float subtotal, float percentualPeso,
                          float percentualModalidade, int protecao,
                          int tentativasAdicionais) {
    float adicionalPeso = subtotal * percentualPeso;
    float adicionalModalidade = subtotal * percentualModalidade;
    float adicionalProtecao = (protecao == 1) ? VALOR_PROTECAO : 0.0f;
    float adicionalTentativas = tentativasAdicionais * VALOR_TENTATIVA;

    return subtotal + adicionalPeso + adicionalModalidade +
           adicionalProtecao + adicionalTentativas;
}

/* --------------------------- Funcoes de saida --------------------------- */

void exibirResultadoEntrega(float subtotal, float valorFinal) {
    printf("Subtotal inicial: R$ %.2f\n", subtotal);
    printf("Valor final da entrega: R$ %.2f\n", valorFinal);
}

void exibirResumoFinal(int totalEntregas, float valorTotal, float valorMedio,
                        int qtdEconomica, int qtdExpressa, int qtdPrioritaria,
                        float maiorValor, float menorValor) {
    printf("=== Resumo da sessao ===\n");
    printf("Total de entregas processadas: %d\n", totalEntregas);
    printf("Valor total da sessao: R$ %.2f\n", valorTotal);
    printf("Valor medio das entregas: R$ %.2f\n", valorMedio);
    printf("Entregas Economicas: %d\n", qtdEconomica);
    printf("Entregas Expressas: %d\n", qtdExpressa);
    printf("Entregas Prioritarias: %d\n", qtdPrioritaria);
    printf("Maior valor de entrega: R$ %.2f\n", maiorValor);
    printf("Menor valor de entrega: R$ %.2f\n", menorValor);
}
