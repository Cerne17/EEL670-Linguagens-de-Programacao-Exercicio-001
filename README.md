# Sistema Meteorológico — versão básica

Autor: Miguel Badany Cerne

DRE: 123370433

Implementação dos cinco itens do enunciado usando três classes, vector,
referências, condicionais e laços. Cada classe possui arquivos .hpp e .cpp.

## Compilação e execução

Requer GCC ou Clang e Make. Na pasta do projeto:

```sh
make
make run
```

O executável é gerado em `out/sistema_meteorologico`. A pasta `out/` é criada
se necessário. Para executar diretamente:

```sh
./out/sistema_meteorologico
```

`make clean` remove somente esse executável, preservando código e dados.
Para trocar de compilador, use `make clean` e depois `make CXX=clang++`.
O alvo `make sistema_meteorologico` também compila o programa.

## Estrutura dos arquivos

```text
sistema-meteorologico-completo/
├── Makefile
├── README.md
├── compile_flags.txt
├── .clang-format
├── src/
│   ├── main.cpp
│   ├── Estacao.cpp
│   ├── LeituraSensor.cpp
│   └── SistemaMeteorologico.cpp
├── library/
│   ├── Estacao.hpp
│   ├── LeituraSensor.hpp
│   └── SistemaMeteorologico.hpp
├── data/
│   ├── exemplo-entrada.txt
│   └── base-teste.txt
└── out/
    └── sistema_meteorologico
```

Os includes locais mantêm os nomes, como `#include "Estacao.hpp"`. A opção
`-Ilibrary` informa ao compilador onde encontrar os cabeçalhos. O arquivo
`compile_flags.txt` fornece as mesmas opções básicas ao editor/clangd.
Alterações nos fontes, cabeçalhos ou Makefile acionam a recompilação.

Para reformatar os arquivos com clang-format instalado:

```sh
clang-format -i src/*.cpp library/*.hpp
```

## Menu

1. Cadastrar estação pelo nome. Confirma e exibe todas as estações e leituras.
2. Inserir leitura: nome da estação, grandeza e valor. Atribui instante automático
   por estação e grandeza e exibe o relatório completo.
3. Exibir evolução da média móvel da grandeza informada, com janela de três
   leituras. Exige três estações com ao menos sete leituras dessa grandeza.
4. Ordenar estações pela última média (crescente), usando a grandeza escolhida
   na opção 3, e indicar variações superiores a 15% para mais ou para menos.
5. Prever a próxima leitura da estação e grandeza informadas, mostrando os
   coeficientes a e b da regressão e a previsão para o próximo instante.
6. Exibir o relatório completo de todas as estações e leituras.
0. Sair.

Digite nomes sempre com a mesma grafia e use ponto para decimais. Uma entrada
não numérica em um campo numérico encerra o programa com mensagem.
Os dados ficam somente na memória. Não há Observer, persistência, limpeza de
tela, seleção por listas ou relatórios adicionais.

## Bibliotecas usadas e referências dos slides

- `<iostream>`: entrada e saída — 02-intro-c++.pdf.
- `<string>`: nomes — 06-referencias-sobrecargas-templates.pdf.
- `<vector>`: armazenamento — 08-intro-vector-array.pdf.
- `<iomanip>`: duas casas decimais — 06-referencias-sobrecargas-templates.pdf.

`push_back` aparece em 29-stl-1.pdf. Referências e composição aparecem nas
aulas 06 e 14. O programa não usa map, algoritmos prontos de ordenação,
funções template próprias, herança ou bibliotecas externas.

## Regras dos cálculos

Todas as séries são filtradas por grandeza. A inserção mantém a ordem dos
instantes, começando em 1 e contando separadamente cada grandeza da estação.
Sete leituras geram cinco médias de janela 3. A ordenação usa laços e trocas.
A variação compara as duas últimas janelas, dividindo a diferença pelo módulo
da média anterior. Com base zero ou menos de quatro leituras, o percentual
fica indisponível. Exatamente +/-15% é normal.
A regressão usa todas as leituras da grandeza, com x = instante e y = valor,
e exige dois pontos. As previsões não são inseridas no histórico.

## Exemplo de execução

```sh
./out/sistema_meteorologico < data/exemplo-entrada.txt
```

O exemplo cadastra três estações, com sete temperaturas e sete umidades cada,
e executa os itens 3, 4 e 5. As médias de temperatura de EST-CENTRO são
20.33, 21.67, 23.00, 23.67 e 23.33. A previsão para o instante 8 é 24.14.

`data/exemplo-entrada.txt` contém respostas ao menu e pode ser redirecionado
para a entrada do programa. `data/base-teste.txt` é uma base salva pela versão
antiga com persistência; foi preservada, mas não é lida pela versão básica e
não deve ser usada como roteiro de entrada.
