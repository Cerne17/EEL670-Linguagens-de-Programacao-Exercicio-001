/*
 * Autor: Miguel Badany Cerne
 * DRE: 123370433
 * Arquivo: Estacao.hpp
 * Título: Estacao
 * Descrição: Declaração da classe.
 */

#pragma once
#include "LeituraSensor.hpp"
#include <string>
#include <vector>

class Estacao
{
private:
  std::string m_nome;
  std::vector<LeituraSensor> m_leituras;

public:
  const std::string& get_nome() const;
  const std::vector<LeituraSensor>& get_leituras() const;
  void inserir_leitura(const std::string& grandeza, double valor);
  std::vector<LeituraSensor> filtrar_leituras(
    const std::string& grandeza) const;
  bool possui_grandeza(const std::string& grandeza) const;
  std::vector<double> calcular_medias_moveis(const std::string& grandeza) const;
  bool calcular_variacao_percentual(const std::string& grandeza,
                                    double& variacao) const;
  bool detectar_variacao_anormal(double variacao) const;
  bool calcular_regressao(const std::string& grandeza,
                          double& a,
                          double& b) const;
  bool prever_proxima_leitura(const std::string& grandeza,
                              double& previsao) const;
  Estacao(const std::string& nome);
};
