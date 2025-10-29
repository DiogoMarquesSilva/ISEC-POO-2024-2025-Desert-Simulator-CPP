
#ifndef COMERCIO_H
#define COMERCIO_H
#include "Caravana.h"
#include "Global.h"


class Comercio : public Caravana {
    int instantesSemTripulantes;
public:
    // Construtor
    Comercio(int id, const string& nome, int linha, int coluna, char simbolo,
             int capacidadeCarga, int capacidadeAgua, int consumoAguaPorInstante, int tripulantes);

    // Métodos principais
    void mover(int dx, int dy) override; // Move a caravana de comércio no mapa
    void atualizarEstado() override;     // Atualiza o estado (ex.: modo automático)
    void lidarComTempestade() override;  // Lida com eventos de tempestade
    void venderMercadorias();            // Vende mercadorias
    int getId() const;            // Obtém o ID da caravana
    int setId(int id);               // Define o ID da caravana
    void imprimirStatus() const override;
    void consumirRecursos() override;

    // Destrutor virtual
    virtual ~Comercio() {}
};

#endif //COMERCIO_H
