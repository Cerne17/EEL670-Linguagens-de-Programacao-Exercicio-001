/*
 * Autor: Miguel Badany Cerne
 * DRE: 123370433
 * Arquivo: LeituraSensor.cpp
 * Título: Implementação da classe LeituraSensor
 * Descrição: Inicializa e permite consultar grandeza, valor e instante.
 */

#include "LeituraSensor.hpp"
#include <iostream>

bool LeituraSensor::set_nome(const std::string& nome)
{
  bool tem_texto = false;
  for (std::size_t i = 0; i < nome.size(); i++) {
    if (nome[i] != ' ' && nome[i] != '\t' && nome[i] != '\r' &&
        nome[i] != '\n') {
      tem_texto = true;
    }
  }
  if (!tem_texto) {
    std::cout << "O nome da grandeza não pode ficar vazio.\n";
    return false;
  }
  m_nome = nome;
  return true;
}

LeituraSensor::LeituraSensor(const std::string& nome,
                             double valor,
                             int instante)
{
  m_nome = "Grandeza sem nome";
  m_instante = 1;
  set_nome(nome);
  set_valor(valor);
  set_instante(instante);
}

void LeituraSensor::set_valor(double valor)
{
  m_valor = valor;
}

bool LeituraSensor::set_instante(int instante)
{
  if (instante < 1) {
    std::cout << "O instante deve ser maior que zero.\n";
    return false;
  }
  m_instante = instante;
  return true;
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
