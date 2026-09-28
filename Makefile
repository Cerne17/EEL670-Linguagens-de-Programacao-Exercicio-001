# Autor: Miguel Badany Cerne
# DRE: 123370433
# Arquivo: Makefile
# Título: Compilação do programa
# Descrição: Compila src/, procura cabeçalhos em library/ e gera a saída em out/.

CXX = g++
CPPFLAGS = -Ilibrary
CXXFLAGS = -Wall -Wextra -pedantic

OBJETOS = out/main.o out/Estacao.o out/LeituraSensor.o out/SistemaMeteorologico.o
CABECALHOS = library/Estacao.hpp library/LeituraSensor.hpp library/SistemaMeteorologico.hpp
EXECUTAVEL = out/sistema_meteorologico

.PHONY: all run clean sistema_meteorologico

all: $(EXECUTAVEL)

sistema_meteorologico: $(EXECUTAVEL)

$(EXECUTAVEL): $(OBJETOS)
	$(CXX) $(CXXFLAGS) $(OBJETOS) -o $(EXECUTAVEL)

out/%.o: src/%.cpp $(CABECALHOS) Makefile | out
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

out:
	mkdir -p out

run: $(EXECUTAVEL)
	./$(EXECUTAVEL)

clean:
	rm -f $(OBJETOS) $(EXECUTAVEL)
