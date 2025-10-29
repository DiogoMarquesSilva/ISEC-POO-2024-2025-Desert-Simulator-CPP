
#ifndef CARAVANA_H
#define CARAVANA_H
#include "Global.h"
#include "Entidade.h"

class Caravana : public Entidade {
protected:
    int id;                      // Identificador da caravana
    int capacidadeCarga;         // Capacidade máxima de carga (toneladas)
    int cargaAtual;              // Carga atualmente transportada
    int tripulantes;             // Número atual de tripulantes
    int capacidadeAgua;          // Capacidade máxima de água (litros)
    int aguaAtual;               // Quantidade atual de água disponível
    int consumoAguaPorInstante;  // Consumo de água por instante
    bool modoAutomatico;         // Indica se a caravana está em modo automático
    bool vida;                   // Indica se a caravana está operacional

public:
    // Construtor
    Caravana(int id, const string& nome, int linha, int coluna, char simbolo,
             int capacidadeCarga, int capacidadeAgua, int consumoAguaPorInstante,
             int tripulantes);

    // Métodos principais
    virtual void mover(int dx, int dy); // Move a caravana no mapa
    virtual void consumirRecursos();    // Consome água e verifica estado da tripulação
    void carregar(int toneladas);       // Adiciona carga à caravana
    void descarregar();                 // Remove toda a carga
    void atualizarEstado() override;    // Atualiza o estado (ex.: modo automático)

    // Métodos auxiliares
    void reabastecerAgua();               // Reabastece a água ao máximo
    void ajustarTripulacao(int qtd);      // Ajusta o número de tripulantes
    bool estaOperacional() const;         // Verifica se a caravana está operacional
    void imprimirStatus() const override; // Exibe informações da caravana
    virtual void lidarComTempestade();    // Lida com eventos de tempestade
    int num_combate() const;              // Retorna a probabilidade para ganhar o combate
    void alteraTripulantes(int num);      // Altera o número de tripulantes

    // Getters
    int getCapacidadeCarga() const;
    int getCargaAtual() const;
    int getTripulantes() const;
    int getCapacidadeAgua() const;
    int getAguaAtual() const;
    int getConsumoAguaPorInstante() const;
    bool getModoAutomatico() const;
    int getMaxTripulantes() const;
    bool getVida() const;
    int getId() const;

    // Setters
    void setCapacidadeCarga(int capacidade);
    void setCargaAtual(int carga);
    void setTripulantes(int tripulantes);
    void setCapacidadeAgua(int capacidade);
    void setAguaAtual(int agua);
    void setConsumoAguaPorInstante(int consumo);
    void setModoAutomatico(bool modo);
    void setVida(bool vida);
    void setId(int id);

    // Destrutor virtual
    virtual ~Caravana() {}
};

#endif // CARAVANA_H

