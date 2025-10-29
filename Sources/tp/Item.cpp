
#include "Global.h"
#include "Item.h"
#include "Caravana.h"
#include "Entidade.h"
#include "Utilizador.h"

// Construtor
Item::Item(string tipo, const std::string &nome, int linha, int coluna, char simbolo, int tempoExistencia)
    : Entidade(nome, linha, coluna, simbolo), tipo(tipo), tempoExistencia(tempoExistencia) {}

// Destrutor
Item::~Item() {}

// Reduz o tempo de existência do item
void Item::reduzirTempoExistencia() {
    if (tempoExistencia > 0) {
        --tempoExistencia;
    }
}

// Verifica se o item ainda está ativo
bool Item::estaAtivo() const {
    return tempoExistencia > 0;
}

// Getters
string Item::getTipo() const {
    return tipo;
}

int Item::getTempoExistencia() const {
    return tempoExistencia;
}

// Setters
void Item::setTipo(string tipo) {
    this->tipo = tipo;
}

void Item::setTempoExistencia(int tempo) {
    this->tempoExistencia = tempo;
}

void Item::setLinha(int linha) {
    this->linha = linha;
}

void Item::setColuna(int coluna) {
    this->coluna = coluna;
}

// Imprime o status do item
void Item::imprimirStatus() const {
    std::cout << "Item " << nome << " (" << tipo << ") na posição (" << linha << ", " << coluna << ") com tempo de existência " << tempoExistencia << ".\n";
}

// Atualiza o estado do item
void Item::atualizarEstado() {
}

// Aplica o efeito do item na caravana e no utilizador

// Caixa de Pandora
// Reduz 20% da tripulação
void CaixaDePandora::aplicarEfeito(Caravana* caravana, Utilizador* utilizador) {
    cout << "Caravana " << caravana->getNome() << " encontrou uma Caixa de Pandora!\n";
    caravana->setTripulantes(caravana->getTripulantes() * 0.80); // Reduz 20% da tripulação
}

// Arca do Tesouro
// Aumenta 10% das moedas
void ArcaDoTesouro::aplicarEfeito(Caravana* caravana, Utilizador* utilizador) {
    cout << "Caravana " << caravana->getNome() << " encontrou uma Arca do Tesouro!\n";
    utilizador->setMoedas(utilizador->getMoedas() * 1.10); // Aumenta 10% das moedas
}

// Jaula
// Adiciona 10 prisioneiros à tripulação
void Jaula::aplicarEfeito(Caravana* caravana, Utilizador* utilizador) {
    cout << "Caravana " << caravana->getNome() << " encontrou uma Jaula!\n";
    caravana->setTripulantes(min(caravana->getTripulantes() + 10, caravana->getMaxTripulantes())); // Adiciona prisioneiros à tripulação sem exceder o máximo
}

// Mina
// Destrói a caravana
void Mina::aplicarEfeito(Caravana* caravana, Utilizador* utilizador) {
    std::cout << "Caravana " << caravana->getNome() << " encontrou uma Mina!\n";
    caravana->setVida(false); // Destrói a caravana
}

// Surpresa (Lagoa Dourada)
// Aumenta a quantidade de moedas do utilizador na mesma quantidade de agua que a caravana recebe.
// Restabelece a agua da caravana
// Existe 40 % de change de encontrar uma pedra preciosa que aumenta a quantidade de moedas do utilizador para o dobro
void Surpresa::aplicarEfeito(Caravana* caravana, Utilizador* utilizador) {
    cout << "Caravana " << caravana->getNome() << " encontrou uma Surpresa!\n";

    int aguaMax = caravana->getCapacidadeAgua();
    int agua = caravana->getAguaAtual();
    int aguaRestante = aguaMax - agua;
    int moedas = utilizador->getMoedas();
    utilizador->setMoedas(moedas + aguaRestante);
    caravana->setAguaAtual(aguaMax);
    int chance = rand() % 100;
    if (chance < 40) {
        moedas = utilizador->getMoedas();
        utilizador->setMoedas(moedas * 2);
    }
}

// Imprime o status do item

void CaixaDePandora::imprimirStatus() const {
    cout << "Caixa de Pandora " << nome << " na posição (" << linha << ", " << coluna << ") com tempo de existência " << tempoExistencia << ".\n";
}

void ArcaDoTesouro::imprimirStatus() const {
    cout << "Arca do Tesouro " << nome << " na posição (" << linha << ", " << coluna << ") com tempo de existência " << tempoExistencia << ".\n";
}

void Jaula::imprimirStatus() const {
    cout << "Jaula " << nome << " na posição (" << linha << ", " << coluna << ") com tempo de existência " << tempoExistencia << ".\n";
}

void Mina::imprimirStatus() const {
    cout << "Mina " << nome << " na posição (" << linha << ", " << coluna << ") com tempo de existência " << tempoExistencia << ".\n";
}

void Surpresa::imprimirStatus() const {
    cout << "Surpresa " << nome << " na posição (" << linha << ", " << coluna << ") com tempo de existência " << tempoExistencia << ".\n";
}