/*
 * Autor: Miguel Badany Cerne
 * DRE: 123370433
 * Arquivo: SistemaMeteorologico.hpp
 * Título: SistemaMeteorologico
 * Descrição: Declaração da classe.
 */

#pragma once
#include "Estacao.hpp"
#include <string>
#include <vector>

class SistemaMeteorologico
{
private:
  std::vector<Estacao> m_estacoes;

public:
  bool inserir_estacao(const std::string& nome);
  int buscar_estacao(const std::string& nome) const;
  bool inserir_leitura(const std::string& estacao,
                       const std::string& grandeza,
                       double valor);

  void exibir_relatorio() const;

  bool exibir_evolucao_medias(const std::string& grandeza) const;

  std::vector<std::string> listar_grandezas() const;

  void ordenar_estacoes_e_indicar_variacoes(const std::string& grandeza) const;

  void exibir_previsao(const std::string& estacao,
                       const std::string& grandeza) const;
};
