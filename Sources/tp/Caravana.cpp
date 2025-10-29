
#include "Global.h"
#include "Caravana.h"

// Construtor
Caravana::Caravana(int id, const string& nome, int linha, int coluna, char simbolo,
                   int capacidadeCarga, int capacidadeAgua, int consumoAguaPorInstante,
                   int tripulantes)
    : Entidade(nome, linha, coluna, simbolo),
      capacidadeCarga(capacidadeCarga), cargaAtual(0),
      capacidadeAgua(capacidadeAgua), aguaAtual(capacidadeAgua),
      consumoAguaPorInstante(consumoAguaPorInstante),
      tripulantes(tripulantes), modoAutomatico(false), vida(true), id(id) {}


// Move a caravana no mapa
void Caravana::mover(int dx, int dy) {
    linha += dx;
    coluna += dy;
    cout << "Caravana " << nome << " movida para (" << linha << ", " << coluna << ").\n";
}

// Consome recursos por instante
void Caravana::consumirRecursos() {
    if (aguaAtual > 0) {
        aguaAtual -= consumoAguaPorInstante;
        if (aguaAtual < 0) aguaAtual = 0;
    } else if (tripulantes > 0) {
        tripulantes -= 1; // Perde tripulantes quando água acaba
        cout << "Caravana " << nome << " perdeu um tripulante por falta de água.\n";
    }
}

// Carrega mercadorias
void Caravana::carregar(int toneladas) {
    if (cargaAtual + toneladas <= capacidadeCarga) {
        cargaAtual += toneladas;
        cout << "Caravana " << nome << " carregou " << toneladas << " toneladas.\n";
    } else {
        cout << "Carga excede a capacidade máxima!\n";
    }
}

// Descarrega a carga
void Caravana::descarregar() {
    cout << "Caravana " << nome << " descarregou " << cargaAtual << " toneladas.\n";
    cargaAtual = 0;
}

// Atualiza o estado (modo automático ou manual)
void Caravana::atualizarEstado() {
    if (modoAutomatico) {
        cout << "Caravana " << nome << " está no modo automático.\n";
    }
    consumirRecursos();
}

// Reabastece a água ao máximo
void Caravana::reabastecerAgua() {
    aguaAtual = capacidadeAgua;
    cout << "Caravana " << nome << " reabasteceu a água ao máximo.\n";
}

// Ajusta o número de tripulantes
void Caravana::ajustarTripulacao(int qtd) {
    tripulantes += qtd;
    if (tripulantes < 0) tripulantes = 0;
    cout << "Tripulação da caravana " << nome << " ajustada para " << tripulantes << ".\n";
}

// Verifica se a caravana está operacional
bool Caravana::estaOperacional() const {
    return (tripulantes > 0 && aguaAtual > 0);
}

// Imprime informações da caravana
void Caravana::imprimirStatus() const {
    cout << "Caravana: " << nome << "\n"
         << "Posicao: (" << linha << ", " << coluna << ")\n"
         << "Tripulantes: " << tripulantes << "\n"
         << "Carga Atual: " << cargaAtual << " / " << capacidadeCarga << " toneladas\n"
         << "Agua Atual: " << aguaAtual << " / " << capacidadeAgua << " litros\n"
         << "Estado: " << (estaOperacional() ? "Operacional" : "Inativa") << "\n"
         << "----------------------------\n";
}

void Caravana::lidarComTempestade() {
}

int Caravana::num_combate() const {
    //numero ramdom entra 0 e o numero de tripulantes
    int num = rand() % tripulantes;
    return num;
}

void Caravana::alteraTripulantes(int num) {
    tripulantes += num;
    if (tripulantes < 0){
        tripulantes = 0;
        vida=false;
    }
    cout << "Tripulação da caravana " << nome << " ajustada para " << tripulantes << ".\n";
}

// Getters
int Caravana::getCapacidadeCarga() const {
    return capacidadeCarga;
}

int Caravana::getCargaAtual() const {
    return cargaAtual;
}

int Caravana::getTripulantes() const {
    return tripulantes;
}

int Caravana::getCapacidadeAgua() const {
    return capacidadeAgua;
}

int Caravana::getAguaAtual() const {
    return aguaAtual;
}

int Caravana::getConsumoAguaPorInstante() const {
    return consumoAguaPorInstante;
}

bool Caravana::getModoAutomatico() const {
    return modoAutomatico;
}

int Caravana::getId() const {
    return id;
}
int Caravana::getMaxTripulantes() const {
    return 10;
}

bool Caravana::getVida() const {
    return vida;
}

// Setters
void Caravana::setCapacidadeCarga(int capacidade) {
    capacidadeCarga = capacidade;
}

void Caravana::setCargaAtual(int carga) {
    cargaAtual = carga;
}

void Caravana::setTripulantes(int tripulantes) {
    this->tripulantes = tripulantes;
}

void Caravana::setCapacidadeAgua(int capacidade) {
    capacidadeAgua = capacidade;
}

void Caravana::setAguaAtual(int agua) {
    aguaAtual = agua;
}

void Caravana::setConsumoAguaPorInstante(int consumo) {
    consumoAguaPorInstante = consumo;
}

void Caravana::setModoAutomatico(bool modo) {
    modoAutomatico = modo;
}

void Caravana::setVida(bool vida) {
    this->vida = vida;
}

void Caravana::setId(int id) {
    this->id = id;
}
