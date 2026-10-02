# Sistema Meteorológico

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

Cada arquivo de `src/` é compilado em um objeto `.o` dentro de `out/`.
Esses objetos são ligados para gerar `out/sistema_meteorologico`. A pasta
`out/` é criada se necessário. Para executar diretamente:

```sh
./out/sistema_meteorologico
```

`make clean` remove os objetos `.o` e o executável de `out/`, preservando código
e dados.
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
    ├── main.o
    ├── Estacao.o
    ├── LeituraSensor.o
    ├── SistemaMeteorologico.o
    └── sistema_meteorologico
```

Os includes locais mantêm os nomes, como `#include "Estacao.hpp"`. A opção
`-Ilibrary` informa ao compilador onde encontrar os cabeçalhos. O arquivo
`compile_flags.txt` fornece as mesmas opções de compilação ao editor/clangd.
Alterar um `.cpp` recompila seu objeto e atualiza o executável. Alterações nos
cabeçalhos ou no Makefile recompilam os objetos. Sem alterações, `make` reutiliza
os arquivos existentes. Todos os arquivos gerados ficam em `out/`.

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
4. Escolher uma grandeza registrada em uma lista numerada e ordenar as estações
   pela última média (crescente), indicando variações superiores a 15% para mais
   ou para menos. Não exige executar a opção 3. Digite 0 para voltar ao menu.
5. Prever a próxima leitura da estação e grandeza informadas, mostrando os
   coeficientes a e b da regressão e a previsão para o próximo instante.
6. Exibir o relatório completo de todas as estações e leituras.
0. Sair.

Digite nomes sempre com a mesma grafia e use ponto para decimais. Uma entrada
não numérica em um campo numérico encerra o programa com mensagem.
Os dados ficam na memória durante a execução.

## Bibliotecas usadas e referências dos slides

- `<iostream>`: entrada e saída — 02-intro-c++.pdf.
- `<string>`: nomes — 06-referencias-sobrecargas-templates.pdf.
- `<vector>`: armazenamento — 08-intro-vector-array.pdf.
- `<iomanip>`: duas casas decimais — 06-referencias-sobrecargas-templates.pdf.

`push_back` aparece em 29-stl-1.pdf. Referências e composição aparecem nas
aulas 06 e 14. A ordenação é implementada com Bubble Sort, usando laços e trocas entre vizinhos.

## Regras dos cálculos

Todas as séries são filtradas por grandeza. A inserção mantém a ordem dos
instantes, começando em 1 e contando separadamente cada grandeza da estação.
Sete leituras geram cinco médias de janela 3. A ordenação usa Bubble Sort em ordem crescente, trocando médias e índices das
estações juntos. Médias iguais mantêm a ordem de cadastro.
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

Os arquivos `data/exemplo-entrada.txt` e `data/base-teste.txt` contêm respostas
ao menu, uma por linha, e podem ser redirecionados para a entrada do programa.

Para carregar a base de teste e continuar usando o menu, execute na pasta do
projeto:

```sh
make
(cat ./data/base-teste.txt; cat) | ./out/sistema_meteorologico
```

O primeiro `cat` envia as respostas do arquivo; o segundo lê o teclado e
encaminha suas respostas ao programa. Confirme cada resposta com Enter.

A base cadastra EST-CENTRO, EST-NORTE e EST-SUL e adiciona 43 leituras:
sete temperaturas e sete umidades por estação, além de uma leitura de
`pressao` em EST-CENTRO, com valor 1013.25 (em hPa). Depois, executa a evolução
das médias, a ordenação com detecção de variações e a previsão para ambas
as grandezas e exibe o relatório completo. O arquivo não inclui a opção 0,
para que você possa continuar usando o menu com os dados carregados.

Para demonstrar dados insuficientes no laboratório, a base também consulta
`pressao` nas opções 3, 4 e 5. Há apenas uma leitura dessa grandeza:

- Opção 3: informa que são necessárias três estações com sete leituras cada.
- Opção 4: informa que EST-CENTRO tem menos de três leituras e que nenhuma
  estação possui dados suficientes para a ordenação.
- Opção 5: informa que são necessárias pelo menos duas leituras para a previsão.

Na base, `pressao` aparece como a terceira grandeza nas opções 3 e 4.
Para repetir a demonstração manualmente, selecione 3 nessas listas; na opção 5,
informe a estação `EST-CENTRO` e a grandeza `pressao`.

Para sair:

1. No menu principal, digite `0` e pressione Enter.
2. Após a mensagem `Programa encerrado.`, pressione Ctrl+D, com a linha vazia,
   para encerrar também o segundo `cat` e retornar ao terminal.

O programa já terminou após o primeiro passo, mas o `cat` pode continuar
aguardando entrada. Um Enter adicional também pode fazê-lo encerrar ao tentar
enviar uma nova linha para o programa que já fechou; prefira Ctrl+D para
finalizar a leitura explicitamente. Essa espera vem do `cat`, não do menu.

Com redirecionamento direto (`./out/sistema_meteorologico < ./data/base-teste.txt`),
o programa encerra ao chegar ao fim do arquivo e não continua lendo o teclado.

A primeira ordenação ocorre antes da opção 3, pois independe dela.
Os instantes são atribuídos automaticamente ao adicionar as leituras.
O TXT deve conter apenas respostas ao menu, sem cabeçalhos ou comentários.

Nas opções 3 e 4, a lista reúne as grandezas das leituras de todas as estações, sem
repetições. Sem leituras, o programa informa que não há grandezas registradas.
Escolhas inválidas retornam ao menu, e 0 cancela a seleção.
Na opção 4, as estações precisam de três leituras da
grandeza escolhida para entrar na ordenação; com menos de quatro leituras ou
média anterior zero, a variação percentual fica indisponível. Estações sem a
grandeza selecionada são ignoradas.

No roteiro TXT, depois de escolher a opção 3 ou 4, informe o número da grandeza.
Nos dois roteiros, 1 corresponde a temperatura e 2 a umidade.

## Validação dos dados

Os setters de `Estacao` e `LeituraSensor` rejeitam nomes vazios ou compostos
apenas por espaços, tabulações e quebras de linha. `set_instante` exige um
inteiro positivo. Em caso de rejeição, retornam `false`, exibem uma mensagem
e preservam o atributo anterior. Os construtores chamam os setters; se os
argumentos forem inválidos, mantêm os nomes padrão “Estação sem nome” ou
“Grandeza sem nome” e o instante 1.

As operações de cadastro não inserem estações ou leituras com nomes inválidos.
A classe `SistemaMeteorologico` verifica duplicidade e existência da estação.
As condições para calcular as métricas continuam nas classes responsáveis.
Os getters consultam os dados sem modificá-los. `set_valor` aceita valores
negativos, pois podem representar temperaturas; não há limites físicos
específicos por grandeza.

A `main` verifica a leitura das opções e dos números. Nas listas de grandezas,
um laço verifica caracteres extras, rejeitando entradas como `1abc` e `1.5`.
