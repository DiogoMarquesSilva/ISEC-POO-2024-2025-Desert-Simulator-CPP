
#include "Global.h"
#ifndef EXCECOES_H
#define EXCECOES_H


// Classe Base
class SimuladorExcecao : public std::runtime_error {
public:
    explicit SimuladorExcecao(const std::string& mensagem)
        : std::runtime_error(mensagem) {}
};

// Exceção para configuração
class ConfiguracaoExcecao : public SimuladorExcecao {
public:
    explicit ConfiguracaoExcecao(const std::string& mensagem)
        : SimuladorExcecao("Erro de Configuração: " + mensagem) {}
};

// Exceção para simulação
class SimulacaoExcecao : public SimuladorExcecao {
public:
    explicit SimulacaoExcecao(const std::string& mensagem)
        : SimuladorExcecao("Erro de Simulação: " + mensagem) {}
};



#endif //EXCECOES_H
