/*
 * Autor: Miguel Badany Cerne
 * DRE: 123370433
 * Arquivo: main.cpp
 * Título: Menu do Sistema Meteorológico
 * Descrição: Recebe os dados do usuário e chama as operações do sistema.
 */

#include "SistemaMeteorologico.hpp"
#include <iomanip>
#include <iostream>
#include <string>

int main()
{
  SistemaMeteorologico sistema;
  std::cout << std::fixed << std::setprecision(2);
  std::string grandeza_selecionada;
  int opcao;
  std::string nome, grandeza;
  double valor;

  while (true) {
    std::cout << "\n=== Sistema Meteorológico ===\n"
              << "1 - Cadastrar estação\n"
              << "2 - Adicionar leitura\n"
              << "3 - Evolução da média móvel\n"
              << "4 - Ordenação e variações\n"
              << "5 - Previsão da próxima leitura\n"
              << "6 - Exibir relatório completo\n"
              << "0 - Sair\n"
              << "Opção: ";
    // A leitura resulta em falso quando falha; ! inverte esse resultado.
    if (!(std::cin >> opcao)) {
      std::cout << "Entrada encerrada ou opção não numérica.\n";
      break;
    }
    // Descarta o restante da linha antes de usar getline.
    std::cin.ignore(10000, '\n');

    if (opcao == 0) {
      break;
    } else if (opcao == 1) {
      std::cout << "Nome da estação: ";
      if (!std::getline(std::cin, nome)) {
        break;
      }
      if (nome == "") {
        std::cout << "O nome não pode ficar vazio.\n";
        continue;
      }
      if (sistema.inserir_estacao(nome)) {
        std::cout << "Estação cadastrada com sucesso.\n";
        sistema.exibir_relatorio();
      } else {
        std::cout << "Já existe uma estação com esse nome.\n";
      }
    } else if (opcao == 2) {
      std::cout << "Nome da estação: ";
      if (!std::getline(std::cin, nome)) {
        break;
      }
      std::cout << "Grandeza: ";
      if (!std::getline(std::cin, grandeza)) {
        break;
      }
      if (nome == "" || grandeza == "") {
        std::cout << "Nome e grandeza não podem ficar vazios.\n";
        continue;
      }
      std::cout << "Valor coletado: ";
      if (!(std::cin >> valor)) {
        std::cout << "Entrada encerrada ou valor não numérico.\n";
        break;
      }
      std::cin.ignore(10000, '\n');
      if (sistema.inserir_leitura(nome, grandeza, valor)) {
        std::cout << "Leitura adicionada com sucesso.\n";
        sistema.exibir_relatorio();
      } else {
        std::cout << "Estação não encontrada.\n";
      }
    } else if (opcao == 3) {
      std::cout << "Grandeza: ";
      if (!std::getline(std::cin, grandeza)) {
        break;
      }
      // Guarda a grandeza apenas se a análise tiver dados suficientes.
      if (sistema.exibir_evolucao_medias(grandeza)) {
        grandeza_selecionada = grandeza;
      }
    } else if (opcao == 4) {
      if (grandeza_selecionada == "") {
        std::cout << "Execute primeiro a opção 3 com dados suficientes.\n";
      } else {
        sistema.ordenar_estacoes_e_indicar_variacoes(grandeza_selecionada);
      }
    } else if (opcao == 5) {
      std::cout << "Nome da estação: ";
      if (!std::getline(std::cin, nome)) {
        break;
      }
      std::cout << "Grandeza: ";
      if (!std::getline(std::cin, grandeza)) {
        break;
      }
      sistema.exibir_previsao(nome, grandeza);
    } else if (opcao == 6) {
      sistema.exibir_relatorio();
    } else {
      std::cout << "Opção inválida.\n";
    }
  }
  std::cout << "Programa encerrado.\n";
  return 0;
}
