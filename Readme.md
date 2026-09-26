# Trabalho B1 - Lógica de Programação e Algoritmos

## Descrição
Simulador de entregas em terminal (linguagem C). O programa solicita os
dados de cada entrega (distância, peso, modalidade, serviço de proteção e
tentativas adicionais), valida as entradas, calcula o valor final conforme
as regras de negócio e permite processar várias entregas na mesma sessão.
Ao final, apresenta um resumo com totais, médias, contagens por modalidade
e maior/menor valor.

## Funcionalidades
- Cálculo do valor-base por faixa de distância e tarifa por km.
- Adicional percentual por faixa de peso.
- Adicional percentual por modalidade (Econômica, Expressa, Prioritária).
- Serviço adicional de proteção (valor fixo).
- Tentativas adicionais de entrega (valor fixo por tentativa).
- Validação de todas as entradas de domínio, com nova solicitação em caso
  de valor inválido.
- Processamento de múltiplas entregas na mesma execução.
- Resumo final da sessão (total de entregas, valor total, valor médio,
  quantidade por modalidade, maior e menor valor).

## Organização da solução
O programa foi dividido em três grupos de funções, além da `main`, que
coordena o fluxo geral:
- **Leitura e validação**: `lerDistanciaValida`, `lerPesoValido`,
  `lerModalidadeValida`, `lerProtecaoValida`, `lerTentativasValidas`,
  `lerContinuarValido` — cada uma solicita um dado e repete a leitura
  enquanto o valor informado for inválido.
- **Cálculo**: `obterValorBaseDistancia`, `calcularSubtotalInicial`,
  `obterPercentualPeso`, `obterPercentualModalidade`, `calcularValorFinal`
  — funções puras (recebem parâmetros e retornam valores), sem
  entrada/saída, responsáveis por aplicar as regras de negócio na ordem
  definida no roteiro.
- **Apresentação**: `exibirResultadoEntrega`, `exibirResumoFinal` —
  responsáveis apenas por formatar e exibir os resultados.

A `main` chama essas funções em sequência, dentro de um laço `do-while`
que se repete enquanto o usuário quiser processar novas entregas, e
mantém os contadores/acumuladores usados no resumo final.

## Compilação
```
gcc -Wall -o simulador src/main.c
```

## Execução
```
./simulador
```

## Uso de Inteligência Artificial
[Preencha com a declaração correspondente ao seu caso real, conforme o
roteiro. Se você usou esta conversa como apoio, descreva a ferramenta,
a finalidade, o que foi aproveitado e o que você alterou/ajustou depois
de compreender o código.]

## Fontes consultadas

* Materiais e conteúdos disponibilizados pelo professor na disciplina de Lógica de Programação e Algoritmos.
* Documentação e materiais de referência sobre a linguagem C, quando necessário.
* Foi utilizado o Excel para realizar o teste de mesa de todos os cálculos.
