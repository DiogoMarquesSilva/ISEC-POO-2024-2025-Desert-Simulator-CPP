#ifndef ITEM_H
#define ITEM_H

#include "Global.h"
#include "Entidade.h"
#include "Caravana.h"
/*#include "Utilizador.h"*///Evitar dependência circular

class Utilizador;

class Item : public Entidade {
protected:
    std::string tipo;
    int tempoExistencia; // Tempo de existência no mapa

public:
    Item(std::string tipo, const std::string &nome, int linha, int coluna, char simbolo, int tempoExistencia);//Construtor
    virtual ~Item();//Destrutor
    virtual void aplicarEfeito(Caravana* caravana, Utilizador* utilizador)=0;
    void reduzirTempoExistencia();//Reduz o tempo de existência do item
    bool estaAtivo() const;//Verifica se o item ainda está ativo

    //Getters e Setters
    string getTipo() const;
    int getTempoExistencia() const;

    void setTipo(std::string tipo);
    void setTempoExistencia(int tempo);
    void setLinha(int linha);
    void setColuna(int coluna);
    void imprimirStatus() const override;
    void atualizarEstado() override;


};

// Itens específicos

// Caixa de Pandora
class CaixaDePandora : public Item {
public:
    CaixaDePandora(const std::string &nome, int linha, int coluna, char simbolo, int tempoExistencia)
        : Item("CAIXA_DE_PANDORA", nome, linha, coluna, simbolo, tempoExistencia) {}

    void aplicarEfeito(Caravana* caravana, Utilizador* utilizador) override;

    void imprimirStatus() const override;
};

// Arca do Tesouro
class ArcaDoTesouro : public Item {
public:
    ArcaDoTesouro(const std::string &nome, int linha, int coluna, char simbolo, int tempoExistencia)
        : Item("ARCA_DO_TESOURO", nome, linha, coluna, simbolo, tempoExistencia) {}

    void aplicarEfeito(Caravana* caravana, Utilizador* utilizador) override;

    void imprimirStatus() const override;
};

// Jaula
class Jaula : public Item {
public:
    Jaula(const std::string &nome, int linha, int coluna, char simbolo, int tempoExistencia)
        : Item("JAULA", nome, linha, coluna, simbolo, tempoExistencia) {}

    void aplicarEfeito(Caravana* caravana, Utilizador* utilizador) override;

    void imprimirStatus() const override;
};

// Mina
class Mina : public Item {
public:
    Mina(const std::string &nome, int linha, int coluna, char simbolo, int tempoExistencia)
        : Item("MINA", nome, linha, coluna, simbolo, tempoExistencia) {}

    void aplicarEfeito(Caravana* caravana, Utilizador* utilizador) override;

    void imprimirStatus() const override;
};

// Surpresa
class Surpresa : public Item {
public:
    Surpresa(const std::string &nome, int linha, int coluna, char simbolo, int tempoExistencia)
        : Item("SURPRESA", nome, linha, coluna, simbolo, tempoExistencia) {}

    void aplicarEfeito(Caravana* caravana, Utilizador* utilizador) override;

    void imprimirStatus() const override;
};

#endif // ITEM_H
