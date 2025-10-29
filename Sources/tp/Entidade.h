

#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "Global.h"

class Entidade {
protected:
    string nome;        // Nome ou identificação da entidade
    int linha, coluna;  // Posição no mapa
    char simbolo;       // Representação visual no mapa

public:
    Entidade(const string& nome, int linha, int coluna, char simbolo);// Construtor

    //Getters
    string getNome() const { return nome; }
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }
    char getSimbolo() const { return simbolo; }

    void setPosicao(int novaLinha, int novaColuna);

    virtual void atualizarEstado()=0; // Atualiza o estado (se aplicável)
    virtual void imprimirStatus() const = 0; // Imprime os detalhes da entidade

    virtual ~Entidade() {}
};

#endif // ENTIDADE_H

