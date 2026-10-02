# Sistema Meteorológico

Miguel Badany Cerne — DRE: 123370433

Cadastro de estações e leituras, médias móveis, detecção de variações e previsão por regressão linear.

## Compilar e executar

Requer GCC ou Clang e Make. Na pasta do projeto:

```sh
make
make run
```

`make clean` remove o executável e os objetos de `out/`.
Código em `src/`, cabeçalhos em `library/` e roteiros de entrada em `data/`.

## Menu

| Opção | Operação |
|---|---|
| 1 | Cadastrar estação |
| 2 | Adicionar leitura: estação, grandeza e valor |
| 3 | Selecionar grandeza e exibir médias móveis de janela 3 |
| 4 | Selecionar grandeza, ordenar estações por média e indicar variações |
| 5 | Prever a próxima leitura por estação e grandeza |
| 6 | Exibir relatório completo |
| 0 | Sair |

Nas listas de grandezas, `0` volta ao menu. Use nomes com a mesma grafia e ponto
para decimais. Os instantes são automáticos por estação e grandeza; os dados
ficam apenas na memória.

- **Opção 3:** exige três estações com sete leituras da grandeza cada.
- **Opção 4:** exige três leituras por estação para ordenar com Bubble Sort;
  quatro para calcular a variação, com média anterior diferente de zero.
  Variações acima de +15% ou abaixo de −15% são anormais.
- **Opção 5:** exige duas leituras; a previsão não é adicionada ao histórico.

## Testar e continuar usando o menu

```sh
(cat ./data/base-teste.txt; cat) | ./out/sistema_meteorologico
```

A base contém três estações e 43 leituras: sete temperaturas e sete umidades
por estação, mais uma pressão em EST-CENTRO. Executa as consultas e demonstra
os avisos de dados insuficientes para pressão nas opções 3, 4 e 5.
Nas listas, `1` é temperatura, `2` é umidade e `3` é pressão (`pressao`).

O arquivo não termina com `0`, permitindo continuar pelo teclado. Para sair,
digite **0 + Enter**, depois **Ctrl+D** na linha vazia para encerrar o `cat`.
Um Enter adicional também pode encerrar o `cat`; essa espera ocorre após o
programa já ter terminado.

Para executar o outro roteiro e encerrar automaticamente:

```sh
./out/sistema_meteorologico < ./data/exemplo-entrada.txt
```
