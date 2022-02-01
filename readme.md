# Objetivo

<div style="font-size:18px">
O objetivo deste trabalho prático é permitir a avaliação do impacto causado pelo desempenho
dos algoritmos em sua execução real. Existem problemas e
algoritmos de complexidade exponencial, chamados de intratáveis. Nesses casos, os
programas, ao serem executados podem demorar uma quantidade de tempo não razoável para
encontrar uma solução, dependendo do tamanho da entrada. Vamos observar, portanto, como
isso ocorre na prática. Para tanto, essa será uma implementação para o Problema de
Roteamento de Veículos (PRV) – versão clássica. Esse é um problema intratável, pois sua
solução exata somente é possível através do cálculo e avaliação de todas as possíveis saídas, o
que chamamos de força bruta. Em seguida, essa implementação deverá ser executada para
diferentes valores de entrada N, e o tempo gasto para que o programa termine, em cada caso,
deverá ser medido por meio de comandos do sistema operacional.</div>

<br>

---

# O problema
<div style="font-size: 18px" >
O problema de roteamento de veículos (PRV) é um problema clássico da literatura que pode
ser definido como segue. Dado um conjunto de cidades, cada qual com uma demanda por um
produto, e um depósito com veículos de capacidade Qv
, encontrar as rotas para os veículos
minimizando as distâncias percorridas.
Em linhas gerais, esse problema recebe como entrada N cidades e um conjunto de distâncias
(não negativas) entre pares de cidades Ci e Cj (considere que a distância entre Ci e Cj representa
a existência de uma estrada entre elas, sendo que a distância entre Ci e Cj é a mesma daquela
entre Cj e Ci). As cidades são identificadas por números, que vão de 0 a N-1. Assim o conjunto
de cidades é dado por {C0
,C1
,C2
,...,CN-1}. A cidade C0 representa o depósito, sendo este a base de
uma frota de veículos idênticos de capacidade Qv
. Cada cidade Ci possui uma demanda não
negativa Qi e Q0=0. Desta forma, o problema também recebe como entrada um vetor Q de
tamanho N, contendo em cada i-ésima posição a demanda não negativa da cidade i. Neste
trabalho supõe-se que o somatório das demandas Qi de todas as cidades deve ser um múltiplo
da capacidade Qv de um caminhão. Dessa forma, o número de caminhões necessários para
atender às demandas de todas as cidades é dado pela divisão entre esse somatório e a
capacidade de um caminhão.
</div>