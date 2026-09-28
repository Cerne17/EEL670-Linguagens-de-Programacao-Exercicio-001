/*
 * Autor: Miguel Badany Cerne
 * DRE: 123370433
 * Arquivo: LeituraSensor.hpp
 * Título: Declaração da classe LeituraSensor
 * Descrição: Define os dados e os métodos de consulta de uma leitura.
 */

#pragma once

#include <string>

class LeituraSensor
{
private:
  std::string m_nome;
  double m_valor;
  int m_instante;

public:
  const std::string& get_nome() const;
  double get_valor() const;
  int get_instante() const;
  LeituraSensor(const std::string& nome, double valor, int instante);
};
