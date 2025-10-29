
#include "Global.h"
#include "Buffer.h"
#ifndef PARAMETROS_H
#define PARAMETROS_H



class Parametros {
private:
    int linhas;
    int colunas;
    int moedas;
    int instantesEntreNovosItens;
    int duracaoItem;
    int maxItens;
    int precoVendaMercadoria;
    int precoCompraMercadoria;
    int precoCaravana;
    int instantesEntreNovosBarbaros;
    int duracaoBarbaros;

public:
    // Construtor
    Parametros();

    // Métodos de acesso
    int getLinhas() const; // Retorna o número de linhas do mapa
    int getColunas() const; // Retorna o número de colunas do mapa
    int getMoedas() const; // Retorna o número de moedas
    int getInstantesEntreNovosItens() const; // Retorna os instantes entre novos itens
    int getDuracaoItem() const; // Retorna a duração do item
    int getMaxItens() const; // Retorna o número máximo de itens
    int getPrecoVenda() const; // Retorna o preço de venda da mercadoria
    int getPrecoCompra() const; // Retorna o preço de compra da mercadoria
    int getPrecoCaravana() const; // Retorna o preço da caravana
    int getInstantesEntreNovosBarbaros() const; // Retorna os instantes entre novos bárbaros
    int getDuracaoBarbaros() const; // Retorna a duração dos bárbaros

    // Método para carregar os parâmetros do ficheiro
    void carregarDeFicheiro(const std::string& nomeFicheiro, Buffer& buffer);
    void mostrarConteudo() const;

    ~Parametros() = default;
};


#endif //PARAMETROS_H
