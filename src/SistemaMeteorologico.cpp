/*
 * Autor: Miguel Badany Cerne
 * DRE: 123370433
 * Arquivo: SistemaMeteorologico.cpp
 * Título: SistemaMeteorologico
 * Descrição: Implementação das operações da classe.
 */

#include "SistemaMeteorologico.hpp"
#include <iostream>

int SistemaMeteorologico::buscar_estacao(const std::string& nome) const
{
  for (std::size_t i = 0; i < m_estacoes.size(); i++) {
    if (m_estacoes[i].get_nome() == nome) {
      return static_cast<int>(i);
    }
  }
  return -1;
}

bool SistemaMeteorologico::inserir_estacao(const std::string& nome)
{
  Estacao estacao("Estação sem nome");
  if (!estacao.set_nome(nome)) {
    return false;
  }
  if (buscar_estacao(nome) != -1) {
    std::cout << "Já existe uma estação com esse nome.\n";
    return false;
  }
  m_estacoes.push_back(estacao);
  return true;
}

bool SistemaMeteorologico::inserir_leitura(const std::string& nome,
                                           const std::string& grandeza,
                                           double valor)
{
  int indice = buscar_estacao(nome);
  if (indice == -1) {
    std::cout << "Estação não encontrada.\n";
    return false;
  }
  return m_estacoes[indice].inserir_leitura(grandeza, valor);
}

void SistemaMeteorologico::exibir_relatorio() const
{
  std::cout << "\n=== Relatório das estações ===\n";
  if (m_estacoes.size() == 0) {
    std::cout << "Nenhuma estação cadastrada.\n";
  }
  for (std::size_t i = 0; i < m_estacoes.size(); i++) {
    std::cout << "\nEstação: " << m_estacoes[i].get_nome() << '\n';
    const std::vector<LeituraSensor>& leituras = m_estacoes[i].get_leituras();
    if (leituras.size() == 0) {
      std::cout << "  Nenhuma leitura cadastrada.\n";
    }
    for (std::size_t j = 0; j < leituras.size(); j++) {
      std::cout << "  Grandeza: " << leituras[j].get_nome()
                << " | Valor: " << leituras[j].get_valor()
                << " | Instante: " << leituras[j].get_instante() << '\n';
    }
  }
}

bool SistemaMeteorologico::exibir_evolucao_medias(
  const std::string& grandeza) const
{
  int aptas = 0;
  for (std::size_t i = 0; i < m_estacoes.size(); i++) {
    if (m_estacoes[i].filtrar_leituras(grandeza).size() >= 7) {
      aptas++;
    }
  }
  if (aptas < 3) {
    std::cout << "Cadastre pelo menos 3 estações com 7 leituras de " << grandeza
              << ".\n";
    return false;
  }
  std::cout << "\nEvolução das médias de " << grandeza << " (janela 3):\n";
  for (std::size_t i = 0; i < m_estacoes.size(); i++) {
    std::vector<LeituraSensor> serie = m_estacoes[i].filtrar_leituras(grandeza);
    if (serie.size() < 7) {
      if (serie.size() > 0) {
        std::cout << m_estacoes[i].get_nome()
                  << ": menos de 7 leituras; desconsiderada.\n";
      }
      continue;
    }
    std::vector<double> medias = m_estacoes[i].calcular_medias_moveis(grandeza);
    std::cout << m_estacoes[i].get_nome() << ": ";
    for (std::size_t j = 0; j < medias.size(); j++) {
      std::cout << "[instante " << serie[j + 2].get_instante() << ": "
                << medias[j] << "] ";
    }
    std::cout << '\n';
  }
  return true;
}

std::vector<std::string> SistemaMeteorologico::listar_grandezas() const
{
  std::vector<std::string> grandezas;

  for (std::size_t i = 0; i < m_estacoes.size(); i++) {
    const std::vector<LeituraSensor>& leituras = m_estacoes[i].get_leituras();

    for (std::size_t j = 0; j < leituras.size(); j++) {
      const std::string& nome = leituras[j].get_nome();
      bool encontrada = false;

      for (std::size_t k = 0; k < grandezas.size(); k++) {
        if (grandezas[k] == nome) {
          encontrada = true;
          break;
        }
      }

      if (!encontrada) {
        grandezas.push_back(nome);
      }
    }
  }

  return grandezas;
}

void SistemaMeteorologico::ordenar_estacoes_e_indicar_variacoes(
  const std::string& grandeza) const
{
  // Dois vectors correspondentes: posição da estação e sua última média.
  std::vector<int> indices;
  std::vector<double> medias;
  for (std::size_t i = 0; i < m_estacoes.size(); i++) {
    if (!m_estacoes[i].possui_grandeza(grandeza)) {
      continue;
    }
    std::vector<double> historico =
      m_estacoes[i].calcular_medias_moveis(grandeza);
    if (historico.size() == 0) {
      std::cout << m_estacoes[i].get_nome()
                << ": menos de 3 leituras; sem média.\n";
      continue;
    }
    indices.push_back(static_cast<int>(i));
    medias.push_back(historico[historico.size() - 1]);
  }
  // Bubble Sort: troca vizinhos e leva a maior média ao fim de cada passagem.
  for (std::size_t limite = medias.size(); limite > 1; limite--) {
    for (std::size_t j = 0; j + 1 < limite; j++) {
      if (medias[j] > medias[j + 1]) {
        double media_aux = medias[j];
        medias[j] = medias[j + 1];
        medias[j + 1] = media_aux;

        // A estação acompanha sua média em cada troca.
        int indice_aux = indices[j];
        indices[j] = indices[j + 1];
        indices[j + 1] = indice_aux;
      }
    }
  }

  std::cout << "\nEstações por média crescente de " << grandeza << ":\n";
  if (indices.size() == 0) {
    std::cout << "Nenhuma estação com dados suficientes.\n";
  }
  for (std::size_t i = 0; i < indices.size(); i++) {
    const Estacao& estacao = m_estacoes[indices[i]];
    std::cout << estacao.get_nome() << " | Média: " << medias[i];
    double variacao;
    if (estacao.calcular_variacao_percentual(grandeza, variacao)) {
      std::cout << " | Variação: " << variacao << "%";
      if (estacao.detectar_variacao_anormal(variacao)) {
        std::cout << " | ANORMAL";
      } else {
        std::cout << " | Normal";
      }
    } else {
      std::cout << " | Variação indisponível: menos de 4 leituras ou média "
                   "anterior zero";
    }
    std::cout << '\n';
  }
}

void SistemaMeteorologico::exibir_previsao(const std::string& nome,
                                           const std::string& grandeza) const
{
  int indice = buscar_estacao(nome);
  if (indice == -1) {
    std::cout << "Estação não encontrada.\n";
    return;
  }
  double a, b, previsao;
  const Estacao& estacao = m_estacoes[indice];
  if (!estacao.calcular_regressao(grandeza, a, b) ||
      !estacao.prever_proxima_leitura(grandeza, previsao)) {
    std::cout << "São necessárias pelo menos 2 leituras da grandeza para a "
                 "regressão.\n";
    return;
  }
  std::vector<LeituraSensor> serie = estacao.filtrar_leituras(grandeza);
  std::cout << "\nEstação: " << nome << " | Grandeza: " << grandeza
            << "\n_coeficiente angular (a): " << a
            << "\n_coeficiente linear (b): " << b << "\nPróximo instante: "
            << serie[serie.size() - 1].get_instante() + 1
            << "\nPrevisão: " << previsao << '\n';
}
