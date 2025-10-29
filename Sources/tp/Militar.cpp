
#include "Militar.h"
#include "Caravana.h"
#include "Global.h"

// Construtor
Militar::Militar(int id, const string& nome, int linha, int coluna, char simbolo,
                 int capacidadeAgua, int consumoAguaPorInstante, int tripulantes)
    : Caravana(id, nome, linha, coluna, simbolo, 5, capacidadeAgua, consumoAguaPorInstante, tripulantes),
    instantesSemTripulantes(0), ultimodx(0), ultimody(0), andarNaMesmaDirecao(false){}

// Move a caravana militar no mapa
void Militar::mover(int dx, int dy) {
    for (int i = 0; i < 3; ++i) { // Pode mover-se até 3 vezes por turno
        linha += dx;
        coluna += dy;
    }
    cout << "Caravana militar " << nome << " movida para (" << linha << ", " << coluna << ").\n";
}

// Atualiza o estado
void Militar::atualizarEstado() {
    if (modoAutomatico) {
        cout << "Caravana militar " << nome << " está no modo automático.\n";
        //A Lógica para perseguição de caravanas bárbaras vai ser implementada aqui
    }
    consumirRecursos(); // Consome recursos em cada atualização
}

// Lida com eventos de tempestade
// Perde 10% dos tripulantes e 33% de chance de ser destruída
void Militar::lidarComTempestade() {
    cout << "A Caravana Militar " << nome << " está a enfrentar uma tempestade de areia.\n";
    tripulantes -= tripulantes * 0.1; // Perde 10% dos tripulantes
    if (rand() % 3 == 0) { // 33% de chance de ser destruída
        vida = false;
        cout << "A Caravana Militar " << nome << " foi destruída na tempestade.\n";
    }
}

// Combate
void Militar::combater() {
    cout << "Caravana militar " << nome << " está em combate.\n";
}

// Consome recursos em cada atualização
void Militar::consumirRecursos() {
    //Gasta 3 litros de água por instante, 1 litro apenas se tiver menos que metade
    //dos tripulantes (inclusive se não tiver tripulante nenhum)
    int consumo = consumoAguaPorInstante;
    if (tripulantes < 0.5 * tripulantes) {
        consumo = consumo / 3;
    }
    aguaAtual -= consumo;
    if (aguaAtual < 0) {
        //Quando uma caravana fica sem água, perde um tripulante a cada turno
        tripulantes--;
        if(tripulantes == 0){
            instantesSemTripulantes++;
            andarNaMesmaDirecao = true;
            if (instantesSemTripulantes>=7) {
                vida = false;
            cout << "Caravana militar " << nome << " está para ser destruída.\n";
            }
        }
    }
}

// Imprimir status da caravana militar
void Militar::imprimirStatus() const {
    cout << "Caravana Militar " << nome << " (ID: " << id << ")\n";
    cout << "Posição: (" << linha << ", " << coluna << ")\n";
    cout << "Carga: " << cargaAtual << "/" << capacidadeCarga << "\n";
    cout << "Tripulantes: " << tripulantes << "\n";
    cout << "Água: " << aguaAtual << "/" << capacidadeAgua << "\n";
    cout << "Vida: " << vida << "\n";
    cout << "Modo: " << (modoAutomatico ? "Automático" : "Manual") << "\n";
    cout << "--------------------------------\n";
}

// Retorna se a caravana militar deve andar na mesma direção
bool Militar::getAndarNaMesmaDirecao() {
    return andarNaMesmaDirecao;
}
