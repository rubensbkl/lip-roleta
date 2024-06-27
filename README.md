# Projeto de Cassino com Arduino

Este projeto foi desenvolvido por Gustavo Tadeu, Otoniel Goulart e Rubens Dias sob a orientação do professor João Paulo Aramuni na PUC Minas. O objetivo do projeto é simular uma roleta de cassino utilizando um Arduino, LEDs e um display LCD para representar um sistema de apostas.

## Descrição do Projeto

O projeto consiste em um jogo de apostas onde o jogador pode escolher uma cor (verde, vermelho ou amarelo) e definir um valor de aposta. Após confirmar a aposta, a roleta é "girada" e um número aleatório entre 0 e 36 é sorteado. Se o número sorteado corresponder à cor escolhida pelo jogador, ele ganha de acordo com as regras da roleta:

- Verde: Números pares
- Vermelho: Números ímpares
- Amarelo: Número zero (0)

O display LCD mostra as instruções e resultados do jogo, enquanto os LEDs indicam a cor escolhida e os resultados das apostas.

## Hardware Utilizado

- Arduino UNO
- Display LCD 16x2
- LEDs (verde, vermelho, amarelo)
- Botões
- Resistores
- Protoboard e fios de conexão

## Código

O código do projeto foi escrito em C++ e utiliza a biblioteca LiquidCrystal para controlar o display LCD. O jogo é estruturado em funções que controlam as etapas de entrada de dados, sorteio e exibição de resultados.

## Esquema de Montagem

![Tinkercad](imgs/planta.png)

## Como Jogar

1. O jogador inicia com um saldo de R$100.
2. Selecione a cor da aposta utilizando os botões.
3. Defina o valor da aposta (mínimo de R$10).
4. Confirme a aposta e aguarde o resultado.
5. O saldo é atualizado conforme o resultado da aposta.

## Integrantes do Projeto

- Gustavo Tadeu Melgaço Valeriano
- Otoniel Goulart Damasceno Filho
- Rubens Dias Bicalho

## Professor Orientador

- João Paulo Carneiro Aramuni

## Faculdade

- Pontifícia Universidade Católica De Minas Gerais - PUC Minas
  
