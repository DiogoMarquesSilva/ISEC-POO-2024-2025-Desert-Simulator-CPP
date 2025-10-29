
#include "Global.h"
#include "Caravana.h"

class Utilizador {
private:
    int moedas;                     // Total de moedas do utilizador
    int turnos;                     // Número de turnos jogados
    vector<Caravana*> caravanas;    // Caravanas controladas pelo utilizador
    int combatesVencidos;           // Total de combates vencidos

public:
    // Construtor
    Utilizador(int moedas);

    // Métodos de acesso
    int getMoedas() const;
    int getTurnos() const;
    int getCombatesVencidos() const;
    vector<Caravana*> getCaravanas() const;

    // Métodos de manipulação
    void adicionarMoedas(int quantidade);
    void removerMoedas(int quantidade);
    void adicionarCaravana(Caravana* novaCaravana);
    void removerCaravana(int idCaravana);
    void incrementarTurno();
    void registrarCombateVencido();

    //Setter
    void setMoedas(int moedas);

    // Relatório final
    void exibirResumoSimulacao() const;

    // Destrutor
     ~Utilizador();

};
