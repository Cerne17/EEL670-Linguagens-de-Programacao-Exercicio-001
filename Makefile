# Autor: Miguel Badany Cerne
# DRE: 123370433
# Arquivo: Makefile
# Título: Compilação do programa
# Descrição: Compila src/, procura cabeçalhos em library/ e gera a saída em out/.

CXX = g++
CPPFLAGS = -Ilibrary
CXXFLAGS = -Wall -Wextra -pedantic

FONTES = src/main.cpp src/Estacao.cpp src/LeituraSensor.cpp src/SistemaMeteorologico.cpp
CABECALHOS = library/Estacao.hpp library/LeituraSensor.hpp library/SistemaMeteorologico.hpp
EXECUTAVEL = out/sistema_meteorologico

.PHONY: all run clean sistema_meteorologico

all: $(EXECUTAVEL)

sistema_meteorologico: $(EXECUTAVEL)

$(EXECUTAVEL): $(FONTES) $(CABECALHOS) Makefile | out
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(FONTES) -o $(EXECUTAVEL)

out:
	mkdir -p out

run: $(EXECUTAVEL)
	./$(EXECUTAVEL)

clean:
	rm -f $(EXECUTAVEL)
