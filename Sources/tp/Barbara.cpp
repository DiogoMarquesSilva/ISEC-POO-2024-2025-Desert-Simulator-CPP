

#include "Barbara.h"
#include "Global.h"
#include "Caravana.h"

// Construtor
Barbara::Barbara(const int maxInst, const std::string& nome, int linha, int coluna, int tripulantes)
    :maxInstantes(maxInst), Caravana(0, nome, linha, coluna, '!', 0, 100, 0, tripulantes) {
    this->setModoAutomatico(true);
}

// Movimento automático
void Barbara::moverAutomaticamente(const std::vector<Caravana*>& caravanasJogador) {
    int dx = rand() % 3 - 1; // -1, 0 ou 1
    int dy = rand() % 3 - 1; // -1, 0 ou 1
    linha += dx;
    coluna += dy;
    cout << "Caravana bárbara " << nome << " movida para (" << linha << ", " << coluna << ").\n";
}

// Combate com caravanas do jogador
void Barbara::combater(Caravana* caravanaJogador) {
    if (tripulantes > caravanaJogador->getTripulantes()) {
        caravanaJogador->setVida(false); // Caravana do jogador destruída
        roubarMercadorias(caravanaJogador);
        cout << "Caravana bárbara " << nome << " destruiu a caravana do jogador " << caravanaJogador->getNome() << " e roubou as suas mercadorias.\n";
    } else {
        aguaAtual = 0; // Caravana bárbara destruída
        cout << "Caravana do jogador " << caravanaJogador->getNome() << " destruiu a caravana bárbara " << nome << ".\n";
    }
}

// Resistência a tempestades de areia
void Barbara::lidarComTempestade() {
    cout << "Caravana bárbara " << nome << " está a enfrentar uma tempestade de areia.\n";

    // Perde 10% da tripulação
    int tripulantesPerdidos = tripulantes * 0.10;
    tripulantes -= tripulantesPerdidos;
    cout << "A Caravana bárbara " << nome << " perdeu " << tripulantesPerdidos << " tripulantes na tempestade.\n";
    if(tripulantes == 0){
        vida = false;
        std::cout << "A Caravana bárbara " << nome << " foi destruída na tempestade.\n";
    }
    // Chance de destruição
    if (rand() % 100 < 25) {
        vida = false;
        cout << "A Caravana bárbara " << nome << " foi destruída na tempestade.\n";
    }
}

// Roubo de mercadorias
void Barbara::roubarMercadorias(Caravana* caravanaJogador) {
    cargaAtual += caravanaJogador->getCargaAtual();
    caravanaJogador->setCargaAtual(0);
    cout << "A Caravana bárbara " << nome << " roubou " << caravanaJogador->getCargaAtual() << " toneladas de mercadorias da caravana do jogador " << caravanaJogador->getNome() << ".\n";
}

// Getter
int Barbara::getMaxInstantes() const {
    return maxInstantes;
}

// Destrutor
Barbara::~Barbara() {}