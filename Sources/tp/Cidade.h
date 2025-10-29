#ifndef CIDADE_H
#define CIDADE_H
#include "Global.h"
#include "Caravana.h"

class Utilizador;

class Cidade : public Entidade {
private:
    char letra; // Letra única que representa a cidade no mapa
    std::vector<std::shared_ptr<Caravana>> caravanasDisponiveis; // Caravanas disponíveis para venda
    std::vector<std::shared_ptr<Caravana>> caravanasNaCidade; // Caravanas que estão na cidade
    int preço_venda_mercadoria;// Preço de venda da mercadoria
    int preço_compra_mercadoria;// Preço de compra da mercadoria
    int preço_caravana; // Preço padrão da caravana

public:
    // Construtor
    Cidade(std::string nome, char letra, int preço_venda_mercadoria, int preço_compra_mercadoria, int preço_caravana, int linha, int coluna);

    // Métodos principais
    void entrarCaravana(std::shared_ptr<Caravana> caravana);// Entrada de caravana na cidade
    void saidaCaravana(std::shared_ptr<Caravana> caravana); // Saída de caravana da cidade
    bool existeCaravana(std::shared_ptr<Caravana> caravana); // Verifica se a caravana está na cidade
    void inspecionar(); // Inspecionar o conteúdo da cidade
    void comprarMercadoria(Caravana* caravana, Utilizador* user, int quantidade);  // Comprar mercadoria para a caravana
    void venderMercadoria(Caravana* caravana, Utilizador* user); // Vender mercadoria da caravana
    void contratarTripulantes(Caravana* caravana, Utilizador* user, int quantidade); // Contratar tripulantes para a caravana
    bool comprarCaravana(Utilizador* user, char tipoCaravana); // Comprar uma nova caravana
    void atualizarEstado() override;
    void imprimirStatus() const override;

    void mostrarCaravanasDisponiveis() const;

    // Getters
    char getLetra() const;
    int getPrecoVendaMercadoria() const;
    int getPrecoCompraMercadoria() const;
    int getPrecoCaravana() const;
    const std::vector<std::shared_ptr<Caravana>>& getCaravanasDisponiveis() const;

    // Destrutor
    ~Cidade() = default;
};

#endif // CIDADE_H