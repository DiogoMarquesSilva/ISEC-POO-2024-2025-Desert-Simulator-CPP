#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Global.h"
#include "Parametros.h"
#include "Buffer.h"
#include "Comercio.h"
#include "Militar.h"
#include "Utilizador.h"
#include "Cidade.h"
#include "Item.h"
#include "Barbara.h"
#include "Caravana.h"
#include "PaiNatal.h"

class Simulador {
private:
    Parametros parametros;           // Parâmetros do simulador
    Buffer buffer;                   // Buffer para gerenciar estados visuais
    bool emExecucao, configurado;                 // Indica se a simulação está em execução
    int moedas;                      // Moedas disponíveis

    Utilizador utilizador;           // Utilizador do simulador

    std::map<string, Buffer> copiasBuffer; // Mapa de cópias do buffer identificadas por nome
    std::vector<std::shared_ptr<Caravana>> caravanas; // Vetor de caravanas (Comercio, Militar, PaiNatal)
    std::vector<std::shared_ptr<Cidade>> cidades;
    std::vector<std::shared_ptr<Item>> itens;
    std::vector<std::shared_ptr<Barbara>> barbaros;
    static int idCaravana;                           // Identificador de caravana
    static int idBarbara;                            // Identificador de bárbara
    static int idCidade;                             // Identificador de cidade
    static int nTurnos;
    static int maxMovesComercio;
    static int maxMovesMilitar;
    static int CombatesVencidos;
    static int ComandoUtilizado;
    std::map<int, int> moveCounter; // Contador de movimentos para caravanas
    int idsDisponiveis[9][2]; // IDs disponíveis para caravanas

public:
    // Construtor
    Simulador();

    // Métodos principais
    void comandoConfig(const string& nomeFicheiro);
    void comandoSair();
    void comandoExec(const string& nomeFicheiro);
    void comandoMoedas(int n);
    void comandoTerminar();
    void comandoCompraC(const char cidade, char tipo);
    void comandoPrecos();
    void comandoCidade(const char nomeCidade);
    void comandoCaravana(int idCaravana);
    void comandoCompra(int idCaravana, int toneladas);
    void comandoVende(int idCaravana);
    void comandoMove(int idCaravana, const string& direcao);
    void Posicao(std::shared_ptr<Caravana> caravana, const string& direcao);
    void comandoAuto(int idCaravana);
    void comandoStop(int idCaravana);
    void comandoBarbaro(int linha, int coluna);
    void comandoAreia(int linha, int coluna, int raio);
    void comandoTripul(int idCaravana, int tripulantes);
    void comandoSaves(const string& nome);
    void comandoLoads(const string& nome);
    void comandoLists();
    void comandoDels(const string& nome);
    void processarComando(const string& comando);
    bool estaEmExecucao() const;
    void atualizarEstado();
    void inicializarObjetos(Parametros& parametros);
    void mostrarEstado() const;
    void executarTurno(int n = 1);
    void moverParaPosicaoAdjacenteAleatoria(int& x, int& y, const Buffer& buffer);
    void gerirCaravanasBarbaras(int nTurnos);
    void gerirItens(int nTurnos);
    void gerirCaravanas();
    void comportamentoCaravanaComercio(std::shared_ptr<Caravana> caravana);
    void comportamentoCaravanaMilitar(std::shared_ptr<Caravana> caravana);
    void comportamentoCaravanaPaiNatal(std::shared_ptr<Caravana> caravana);
    bool combate( std::shared_ptr<Barbara> barbaro );
    std::shared_ptr<Caravana> encontrarCaravanaPorSimbolo(char simbolo);
    void eliminarCaravana(std::shared_ptr<Caravana> caravana);
    void eliminarID(int id);
    void ocuparID(int id);
    int getPrimeiroID();
    int numCaravanas();
    void atualizarEntidades() ;

    ~Simulador();
};

#endif // SIMULADOR_H