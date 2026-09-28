/*
 * Autor: Miguel Badany Cerne
 * DRE: 123370433
 * Arquivo: LeituraSensor.cpp
 * Título: Implementação da classe LeituraSensor
 * Descrição: Inicializa e permite consultar grandeza, valor e instante.
 */

#include "LeituraSensor.hpp"

LeituraSensor::LeituraSensor(const std::string& nome,
                             double valor,
                             int instante)
  : m_nome(nome)
  , m_valor(valor)
  , m_instante(instante)
{
}

const std::string& LeituraSensor::get_nome() const
{
  return m_nome;
}

double LeituraSensor::get_valor() const
{
  return m_valor;
}

int LeituraSensor::get_instante() const
{
  return m_instante;
}
