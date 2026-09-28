/*
 * Autor: Miguel Badany Cerne
 * DRE: 123370433
 * Arquivo: Estacao.cpp
 * Título: Estacao
 * Descrição: Implementação das operações da classe.
 */

#include "Estacao.hpp"

Estacao::Estacao(const std::string& nome)
  : m_nome(nome)
{
}

const std::string& Estacao::get_nome() const
{
  return m_nome;
}

const std::vector<LeituraSensor>& Estacao::get_leituras() const
{
  return m_leituras;
}

void Estacao::inserir_leitura(const std::string& grandeza, double valor)
{
  int instante = 1;
  // Sem remoção de m_leituras, contar as anteriores fornece o próximo instante.
  for (std::size_t i = 0; i < m_leituras.size(); i++) {
    if (m_leituras[i].get_nome() == grandeza) {
      instante++;
    }
  }
  m_leituras.push_back(LeituraSensor(grandeza, valor, instante));
}

std::vector<LeituraSensor> Estacao::filtrar_leituras(
  const std::string& grandeza) const
{
  std::vector<LeituraSensor> resultado;
  for (std::size_t i = 0; i < m_leituras.size(); i++) {
    if (m_leituras[i].get_nome() == grandeza) {
      resultado.push_back(m_leituras[i]);
    }
  }
  // A inserção já mantém os instantes de cada grandeza em ordem crescente.
  return resultado;
}

bool Estacao::possui_grandeza(const std::string& grandeza) const
{
  for (std::size_t i = 0; i < m_leituras.size(); i++) {
    if (m_leituras[i].get_nome() == grandeza) {
      return true;
    }
  }
  return false;
}

std::vector<double> Estacao::calcular_medias_moveis(
  const std::string& grandeza) const
{
  std::vector<LeituraSensor> serie = filtrar_leituras(grandeza);
  std::vector<double> medias;
  for (std::size_t i = 2; i < serie.size(); i++) {
    double soma = serie[i - 2].get_valor() + serie[i - 1].get_valor() +
                  serie[i].get_valor();
    medias.push_back(soma / 3.0);
  }
  return medias;
}

bool Estacao::calcular_variacao_percentual(const std::string& grandeza,
                                           double& variacao) const
{
  variacao = 0;
  std::vector<double> medias = calcular_medias_moveis(grandeza);
  if (medias.size() < 2) {
    return false;
  }
  double anterior = medias[medias.size() - 2];
  double atual = medias[medias.size() - 1];
  if (anterior == 0) {
    return false; // Percentual indefinido: evita divisão por zero.
  }
  double base = anterior;
  if (base < 0) {
    base = -base;
  }
  variacao = (atual - anterior) / base * 100.0;
  return true;
}

bool Estacao::detectar_variacao_anormal(double variacao) const
{
  return variacao > 15.0 || variacao < -15.0;
}

bool Estacao::calcular_regressao(const std::string& grandeza,
                                 double& a,
                                 double& b) const
{
  a = 0;
  b = 0;
  std::vector<LeituraSensor> serie = filtrar_leituras(grandeza);
  if (serie.size() < 2) {
    return false;
  }
  double n = serie.size();
  double soma_x = 0, soma_y = 0, soma_xy = 0, soma_xx = 0;
  for (std::size_t i = 0; i < serie.size(); i++) {
    double x = serie[i].get_instante();
    double y = serie[i].get_valor();
    soma_x += x;
    soma_y += y;
    soma_xy += x * y;
    soma_xx += x * x;
  }
  double denominador = n * soma_xx - soma_x * soma_x;
  if (denominador == 0) {
    return false;
  }
  // Mínimos quadrados para y = a*x + b, com x = instante e y = valor.
  a = (n * soma_xy - soma_x * soma_y) / denominador;
  b = (soma_y - a * soma_x) / n;
  return true;
}

bool Estacao::prever_proxima_leitura(const std::string& grandeza,
                                     double& previsao) const
{
  previsao = 0;
  double a, b;
  if (!calcular_regressao(grandeza, a, b)) {
    return false;
  }
  std::vector<LeituraSensor> serie = filtrar_leituras(grandeza);
  int proximo_instante = serie[serie.size() - 1].get_instante() + 1;
  previsao = a * proximo_instante + b;
  return true;
}
