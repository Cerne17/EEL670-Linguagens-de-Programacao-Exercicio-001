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
#include <vector>

int main()
{
  SistemaMeteorologico sistema;

  std::cout << std::fixed << std::setprecision(2);

  // As seguintes variaveis devem ser atualizadas a cada iteração do loop, por
  // isso são definidas aqui
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
    // Caso omitido, "\n" continua no buffer de leitura e seria lido pelo
    // proximo getline, sendo assim, a proxima variável começaria com \n
    std::cin.ignore(10000, '\n');

    // poderia ser um switch case, mas optei por if's para ser mais simples de
    // ler
    if (opcao == 0) { // Sair
      break;

    } else if (opcao == 1) { // Cadastrar Estação
      std::cout << "Nome da estação: ";
      if (!std::getline(std::cin, nome)) {
        break; // Erro na leitura
      }
      if (sistema.inserir_estacao(nome)) {
        std::cout << "Estação cadastrada com sucesso.\n";
        sistema.exibir_relatorio();
      }

    } else if (opcao == 2) { // Adicionar Leitura
      std::cout << "Nome da estação: ";
      if (!std::getline(std::cin, nome)) {
        break; // Erro na leitura
      }
      std::cout << "Grandeza: ";
      if (!std::getline(std::cin, grandeza)) {
        break;
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
      }

    } else if (opcao == 3 || opcao == 4) { // Seleção da grandeza
      std::vector<std::string> grandezas = sistema.listar_grandezas();
      if (grandezas.size() == 0) {
        std::cout
          << "Nenhuma grandeza registrada. Adicione uma leitura primeiro.\n";
        continue;
      }

      std::cout << "Grandezas registradas:\n";
      for (std::size_t i = 0; i < grandezas.size(); i++) {
        std::cout << i + 1 << " - " << grandezas[i] << '\n';
      }
      std::cout << "0 - Voltar ao menu\nEscolha a grandeza: ";

      int escolha;
      if (!(std::cin >> escolha)) {
        if (std::cin.eof()) {
          break;
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Escolha inválida. Digite um número da lista.\n";
        continue;
      }

      std::string restante;
      std::getline(std::cin, restante);
      bool tem_caractere_extra = false;
      for (std::size_t i = 0; i < restante.size(); i++) {
        if (restante[i] != ' ' && restante[i] != '\t' && restante[i] != '\r') {
          tem_caractere_extra = true;
        }
      }
      if (tem_caractere_extra || escolha < 0 ||
          escolha > static_cast<int>(grandezas.size())) {
        std::cout << "Escolha inválida. Digite um número da lista.\n";
        continue;
      }
      if (escolha == 0) {
        continue;
      }

      if (opcao == 3) {
        sistema.exibir_evolucao_medias(grandezas[escolha - 1]);
      } else {
        sistema.ordenar_estacoes_e_indicar_variacoes(grandezas[escolha - 1]);
      }

    } else if (opcao == 5) { // Previsão da próxima leitura
      std::cout << "Nome da estação: ";
      if (!std::getline(std::cin, nome)) {
        break;
      }
      std::cout << "Grandeza: ";
      if (!std::getline(std::cin, grandeza)) {
        break;
      }
      sistema.exibir_previsao(nome, grandeza);

    } else if (opcao == 6) { // Exibir relatório completo
      sistema.exibir_relatorio();
    } else { // Qualquer outro input que não 1..6 ou 0
      std::cout << "Opção inválida.\n";
    }
  }
  std::cout << "Programa encerrado.\n";
  return 0;
}
