
#include "Utilizador.h"
#include "Global.h"

// Construtor
Utilizador::Utilizador(int moedasIniciais) : moedas(moedasIniciais), turnos(0), combatesVencidos(0) {}

// Getteres
int Utilizador::getMoedas() const {
    return moedas;
}

int Utilizador::getTurnos() const {
    return turnos;
}

int Utilizador::getCombatesVencidos() const {
    return combatesVencidos;
}

vector<Caravana*> Utilizador::getCaravanas() const {
    return caravanas;
}

// Métodos de manipulação
void Utilizador::adicionarMoedas(int quantidade) {
    moedas += quantidade;
}

void Utilizador::removerMoedas(int quantidade) {
    if (moedas >= quantidade) {
        moedas -= quantidade;
    } else {
        cerr << "Erro: Moedas insuficientes.\n";
    }
}

void Utilizador::adicionarCaravana(Caravana* novaCaravana) {
    caravanas.push_back(novaCaravana);
}

void Utilizador::removerCaravana(int idCaravana) {
    if (idCaravana >= 0 && idCaravana < caravanas.size()) {
        caravanas.erase(caravanas.begin() + idCaravana);
    } else {
        cerr << "Erro: ID de caravana inválido.\n";
    }
}

void Utilizador::incrementarTurno() {
    ++turnos;
}

void Utilizador::registrarCombateVencido() {
    ++combatesVencidos;
}

void Utilizador::setMoedas(int moedas) {
    this->moedas = moedas;
}

void Utilizador::exibirResumoSimulacao() const {
    std::cout << "Resumo da Simulação:\n";
    std::cout << "Moedas restantes: " << moedas << "\n";
    std::cout << "Turnos jogados: " << turnos << "\n";
    std::cout << "Combates vencidos: " << combatesVencidos << "\n";
    std::cout << "Número de caravanas: " << caravanas.size() << "\n";
}

// Destrutor
Utilizador::~Utilizador() {
    for (Caravana* caravana : caravanas) {
        delete caravana;
    }
}
