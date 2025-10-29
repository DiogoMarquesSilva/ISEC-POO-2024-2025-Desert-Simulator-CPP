
#ifndef MILITAR_H
#define MILITAR_H
#include "Caravana.h"
#include "Global.h"


class Militar : public Caravana {
    int instantesSemTripulantes;
    int ultimodx, ultimody;
    bool andarNaMesmaDirecao;
public:
    // Construtor
    Militar(int id, const string& nome, int linha, int coluna, char simbolo,
            int capacidadeAgua, int consumoAguaPorInstante, int tripulantes);

    // Métodos principais
    void mover(int dx, int dy) override; // Move a caravana militar no mapa
    void atualizarEstado() override;     // Atualiza o estado (ex.: modo automático)
    void lidarComTempestade();  // Lida com eventos de tempestade
    void combater();            // Lida com eventos de combate
    int getId() const { return id; } // Retorna o id da caravana
    void imprimirStatus() const override; // Imprime o status da caravana
    void consumirRecursos() override; // Consome recursos em cada atualização
    void setUltimoMovimento(int dx, int dy) { ultimodx = dx; ultimody = dy; } // Define o último movimento
    int getUltimoMovimentoX() { return ultimodx; } // Retorna o último movimento
    int getUltimoMovimentoY() { return ultimody; } // Retorna o último movimento
    bool getAndarNaMesmaDirecao(); // Retorna se a caravana militar deve andar na mesma direção


    // Destrutor virtual
    virtual ~Militar() {}
};

#endif // MILITAR_H
