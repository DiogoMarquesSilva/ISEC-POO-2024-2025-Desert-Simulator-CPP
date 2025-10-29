

#ifndef PAINATAL_H
#define PAINATAL_H
#include "Global.h"
#include "Caravana.h"

class PaiNatal : public Caravana {
public:
    // Construtor
    PaiNatal(int id, const string& nome, int linha, int coluna, char simbolo, int capacidadeCarga, int capacidadeAgua, int consumoAguaPorInstante, int tripulantes, int intervaloDrop);

    bool estaAtivo() const;// Verifica se o Pai Natal está ativo

    void atualizarEstado() override;
    void imprimirStatus() const override;
    void consumirRecursos() override;

    // Getters e Setters
    void setTurnosRestantes(int turnosRestantes);
    void setTurnosDesdeUltimoDrop(int turnosDesdeUltimoDrop);
    void setIntervaloDrop(int intervaloDrop);

    int getTurnosRestantes() const;
    int getTurnosDesdeUltimoDrop() const;
    int getIntervaloDrop() const;

    //Espalha presentes
    void espalharPresentes();

    //Destrutor
    ~PaiNatal() override = default;
private:
    int turnosRestantes;// Turnos restantes para o Pai Natal morrer
    int turnosDesdeUltimoDrop;
    int intervaloDrop; // Quantos turnos até o próximo drop
    static int numPresentes; // Número de presentes
};


#endif // PAINATAL_H
