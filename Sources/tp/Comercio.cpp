
#include "Comercio.h"
#include "Global.h"

// Construtor
Comercio::Comercio(int id, const string& nome, int linha, int coluna, char simbolo,
                   int capacidadeCarga, int capacidadeAgua, int consumoAguaPorInstante, int tripulantes)
    :Caravana(id, nome, linha, coluna, simbolo, capacidadeCarga, capacidadeAgua, consumoAguaPorInstante, tripulantes), instantesSemTripulantes(0) {}

// Move a caravana de comércio no mapa
void Comercio::mover(int dx, int dy) {
    linha += dx;
    coluna += dy;
    cout << "Caravana de comércio " << nome << " movida para (" << linha << ", " << coluna << ").\n";
}

// Atualiza o estado
void Comercio::atualizarEstado() {}

// Lida com eventos de tempestade
void Comercio::lidarComTempestade() {
    cout << "A Caravana de comércio " << nome << " está a enfrentar uma tempestade de areia.\n";

    // Chance de destruição
    int chanceDestruicao = (cargaAtual > capacidadeCarga * 0.5) ? 50 : 25;//50% de chance de destruição se a carga atual for maior que 50% da capacidade, 25% caso contrário
    if (rand() % 100 < chanceDestruicao) {
        vida = false;
        cout << "A Caravana de comércio " << nome << " foi destruída na tempestade.\n";
    }

    // Perde 25% da carga total
    int cargaPerdida = cargaAtual * 0.25;
    cargaAtual -= cargaPerdida;
    cout << "A Caravana de comércio " << nome << " perdeu " << cargaPerdida << " toneladas de carga na tempestade.\n";


}

// Vende mercadorias
void Comercio::venderMercadorias() {
    cout << "A Caravana de comércio " << nome << " vendeu " << cargaAtual << " toneladas de mercadorias.\n";
    cargaAtual = 0;
}

// Consome recursos a cada atualização
void Comercio::consumirRecursos() {
    // Gasta 2 litros de água por instante, ou 1 se tiver menos de metade dos seus tripulantes, 0
    //se não tiver nenhum tripulante
    int consumo = consumoAguaPorInstante;
    if (tripulantes < 0.5 * tripulantes) {
        consumo = consumo / 2;
    }
    if (tripulantes == 0) {
        modoAutomatico=true;
        consumo = 0;
    }
    aguaAtual -= consumo;
    cout << "A Caravana de comércio " << nome << " consumiu " << consumo << " litros de água.\n";
    // Verifica se a caravana ficou sem água
    if (aguaAtual <= 0) {
        tripulantes--;
        if (tripulantes == 0) {
            instantesSemTripulantes++;
            modoAutomatico = true;
            if (instantesSemTripulantes >=5) {
                vida = false;
                cout << "A Caravana de comércio " << nome << " está para ser destruída.\n";
            }
        }
    }
}

// Obtém o ID da caravana
int Comercio::getId() const {
    return id;
}

// Define o ID da caravana
int Comercio::setId(int id) {
    this->id = id;
    return id;
}

// Imprimir informações da caravana
void Comercio::imprimirStatus() const {
    cout << "Caravana de comércio " << nome << " (ID: " << id << ")\n";
    cout << "Localização: (" << linha << ", " << coluna << ")\n";
    cout << "Carga atual: " << cargaAtual << " / " << capacidadeCarga << " toneladas\n";
    cout << "Água atual: " << aguaAtual << " / " << capacidadeAgua << " litros\n";
    cout << "Tripulantes: " << tripulantes << "\n";
    cout << "Consumo de água por instante: " << consumoAguaPorInstante << " litros\n";
    cout << "Modo: " << (modoAutomatico ? "Automático" : "Manual") << "\n";
    cout << "================================\n";
}
