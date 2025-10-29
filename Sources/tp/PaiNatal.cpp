
#include "PaiNatal.h"
#include "Global.h"
#include "Caravana.h"

int PaiNatal::numPresentes = 0;

// Construtor
PaiNatal::PaiNatal(int id, const string& nome, int linha, int coluna, char simbolo, int capacidadeCarga, int capacidadeAgua, int consumoAguaPorInstante, int tripulantes, int intervaloDrop)
        : Caravana(id, nome, linha, coluna, simbolo, capacidadeCarga, capacidadeAgua, consumoAguaPorInstante, tripulantes),
          turnosRestantes(15), turnosDesdeUltimoDrop(0), intervaloDrop(intervaloDrop) {
    modoAutomatico=true;
    setCargaAtual(capacidadeCarga);
}

// Verifica se o Pai Natal está ativo
bool PaiNatal::estaAtivo() const {
    if(turnosRestantes==0 || cargaAtual==0){
        return false;
    }
    return true;
}

void PaiNatal::atualizarEstado() {

}

void PaiNatal::consumirRecursos() {
}

void PaiNatal::imprimirStatus() const {
    cout << "Pai Natal " << id << " - " << nome << endl;
    cout << "Posição: " << linha << ", " << coluna << endl;
    cout << "Carga atual: " << cargaAtual << " / " << capacidadeCarga << endl;
    cout << "Turnos restantes: " << turnosRestantes << endl;
    cout << "Turnos desde o último drop: " << turnosDesdeUltimoDrop << endl;
    cout << "Intervalo de drop: " << intervaloDrop << endl;
    cout << "Número de presentes espalhados: " << numPresentes << endl;
    cout << "================================\n";
}

// Getters e Setters

void PaiNatal::setTurnosRestantes(int turnosRestantes) {
    PaiNatal::turnosRestantes = turnosRestantes;
}

void PaiNatal::setTurnosDesdeUltimoDrop(int turnosDesdeUltimoDrop) {
    PaiNatal::turnosDesdeUltimoDrop = turnosDesdeUltimoDrop;
}

void PaiNatal::setIntervaloDrop(int intervaloDrop) {
    PaiNatal::intervaloDrop = intervaloDrop;
}

int PaiNatal::getTurnosRestantes() const {
    return turnosRestantes;
}

int PaiNatal::getTurnosDesdeUltimoDrop() const {
    return turnosDesdeUltimoDrop;
}

int PaiNatal::getIntervaloDrop() const {
    return intervaloDrop;
}

void PaiNatal::espalharPresentes() {
    numPresentes++;
}