#ifndef BARBARA_H
#define BARBARA_H

#include "Caravana.h"
#include "Global.h"


class Barbara : public Caravana {
private:
    int maxInstantes;
public:
    // Construtor
    Barbara(const int maxInst, const std::string& nome, int linha, int coluna, int tripulantes);

    // Métodos principais
    void moverAutomaticamente(const std::vector<Caravana*>& caravanasJogador); // Movimento automático
    void combater(Caravana* caravanaJogador); // Combater
    void lidarComTempestade() override; // Resistência a tempestades de areia
    void roubarMercadorias(Caravana* caravanaJogador); // Roubo de mercadorias
    int getMaxInstantes() const; // Getter

    // Destrutor
    ~Barbara() override;
};


#endif //BARBARA_H
