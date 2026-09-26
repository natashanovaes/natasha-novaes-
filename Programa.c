#include <stdio.h>

// Definicao de constantes para regras de negocio
#define TARIFA_DISTANCIA_KM 1.20
#define PROTECAO_VALOR 7.50
#define TENTATIVA_ADICIONAL_VALOR 4.00

// Prototipe das funcoes
double obter_valor_base_distancia(double distancia);
double obter_percentual_peso(double peso);
double obter_percentual_modalidade(int modalidade);
double calcular_valor_entrega(double distancia, double peso, int modalidade, int protecao, int tentativas);
void exibir_resumo(int total_entregas, double valor_total, int econ, int expr, int prio, double maior, double menor);

// Funcao para identificar a taxa fixa pela faixa de distancia
double obter_valor_base_distancia(double distancia) {
    if (distancia <= 5.0) {
        return 8.00;
    } else if (distancia <= 15.0) {
        return 12.00;
    } else if (distancia <= 30.0) {
        return 18.00;
    } else {
        return 25.00;
    }
}

// Funcao para identificar o percentual adicional por peso
double obter_percentual_peso(double peso) {
    if (peso <= 2.0) {
        return 0.0;
    } else if (peso <= 5.0) {
        return 0.05;
    } else if (peso <= 10.0) {
        return 0.10;
    } else {
        return 0.20;
    }
}

// Funcao para identificar o percentual adicional por modalidade
double obter_percentual_modalidade(int modalidade) {
    if (modalidade == 1) {
        return 0.0; // Economica
    } else if (modalidade == 2) {
        return 0.15; // Expressa
    } else if (modalidade == 3) {
        return 0.30; // Prioritaria
    }
    return 0.0;
}

// Funcao principal de calculo do valor de uma entrega individual
double calcular_valor_entrega(double distancia, double peso, int modalidade, int protecao, int tentativas) {
    double valor_base = obter_valor_base_distancia(distancia);
    double subtotal_inicial = valor_base + (distancia * TARIFA_DISTANCIA_KM);
    
    double adicional_peso = subtotal_inicial * obter_percentual_peso(peso);
    double adicional_modalidade = subtotal_inicial * obter_percentual_modalidade(modalidade);
    
    double valor_protecao = (protecao == 1) ? PROTECAO_VALOR : 0.0;
    double valor_tentativas = tentativas * TENTATIVA_ADICIONAL_VALOR;
    
    double valor_final = subtotal_inicial + adicional_peso + adicional_modalidade + valor_protecao + valor_tentativas;
    return valor_final;
}

// Funcao para exibir o resumo da sessao ao encerrar
void exibir_resumo(int total_entregas, double valor_total, int econ, int expr, int prio, double maior, double menor) {
    printf("\n=========================================\n");
    printf("           RESUMO DA SESSAO              \n");
    printf("=========================================\n");
    printf("Quantidade total de entregas: %d\n", total_entregas);
    printf("Valor total calculado: R$ %.2f\n", valor_total);
    
    if (total_entregas > 0) {
        printf("Valor medio por entrega: R$ %.2f\n", valor_total / total_entregas);
    } else {
        printf("Valor medio por entrega: R$ 0.00\n");
    }
    
    printf("Entregas Economicas: %d\n", econ);
    printf("Entregas Expressas: %d\n", expr);
    printf("Entregas Prioritarias: %d\n", prio);
    printf("Maior valor de entrega: R$ %.2f\n", maior);
    printf("Menor valor de entrega: R$ %.2f\n", menor);
    printf("=========================================\n");
}

int main() {
    // Variaveis de controle e acumuladores
    int total_entregas = 0;
    double valor_total_sessao = 0.0;
    
    int qtd_economica = 0;
    int qtd_expressa = 0;
    int qtd_prioritaria = 0;
    
    double maior_valor = 0.0;
    double menor_valor = 0.0;
    
    int continuar = 1;

    printf("=========================================\n");
    printf("    SIMULADOR DE ENTREGAS LOCAL          \n");
    printf("=========================================\n");

    while (continuar == 1) {
        double distancia = 0.0;
        double peso = 0.0;
        int modalidade = 0;
        int protecao = -1;
        int tentativas = -1;

        // Entradas e Validacoes
        do {
            printf("\nInforme a distancia em km (maior que 0): ");
            scanf("%lf", &distancia);
            if (distancia <= 0) {
                printf("Distancia invalida! Informe um valor maior que zero.\n");
            }
        } while (distancia <= 0);

        do {
            printf("Informe o peso em kg (maior que 0): ");
            scanf("%lf", &peso);
            if (peso <= 0) {
                printf("Peso invalido! Informe um valor maior que zero.\n");
            }
        } while (peso <= 0);

        do {
            printf("Informe a modalidade (1 - Economica, 2 - Expressa, 3 - Prioritaria): ");
            scanf("%d", &modalidade);
            if (modalidade < 1 || modalidade > 3) {
                printf("Modalidade invalida! Opcoes aceitas: 1, 2 ou 3.\n");
            }
        } while (modalidade < 1 || modalidade > 3);

        do {
            printf("Contratar servico de protecao? (1 - Sim, 0 - Nao): ");
            scanf("%d", &protecao);
            if (protecao != 0 && protecao != 1) {
                printf("Opcao invalida! Informe 1 para Sim ou 0 para Nao.\n");
            }
        } while (protecao != 0 && protecao != 1);

        do {
            printf("Quantidade de tentativas adicionais (>= 0): ");
            scanf("%d", &tentativas);
            if (tentativas < 0) {
                printf("Quantidade invalida! Informe um valor maior ou igual a zero.\n");
            }
        } while (tentativas < 0);

        // Processamento da entrega
        double valor_entrega = calcular_valor_entrega(distancia, peso, modalidade, protecao, tentativas);
        printf("\n-----------------------------------------\n");
        printf("Valor final da entrega: R$ %.2f\n", valor_entrega);
        printf("-----------------------------------------\n");

        // Atualizacao de estatisticas
        total_entregas++;
        valor_total_sessao += valor_entrega;

        if (modalidade == 1) qtd_economica++;
        else if (modalidade == 2) qtd_expressa++;
        else if (modalidade == 3) qtd_prioritaria++;

        if (total_entregas == 1) {
            maior_valor = valor_entrega;
            menor_valor = valor_entrega;
        } else {
            if (valor_entrega > maior_valor) maior_valor = valor_entrega;
            if (valor_entrega < menor_valor) menor_valor = valor_entrega;
        }

        // Pergunta de continuidade
        do {
            printf("\nDeseja registrar outra entrega? (1 - Sim, 0 - Nao): ");
            scanf("%d", &continuar);
            if (continuar != 0 && continuar != 1) {
                printf("Opcao invalida! Digite 1 para Sim ou 0 para Nao.\n");
            }
        } while (continuar != 0 && continuar != 1);
    }

    // Exibicao do resumo final
    exibir_resumo(total_entregas, valor_total_sessao, qtd_economica, qtd_expressa, qtd_prioritaria, maior_valor, menor_valor);

    return 0;
}
