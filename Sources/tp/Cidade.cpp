#include "Global.h"
#include "Cidade.h"
#include "Caravana.h"
#include "Utilizador.h"
#include "Comercio.h"
#include "Militar.h"
#include "PaiNatal.h"

// Construtor
Cidade::Cidade(std::string nome, char letra, int preço_venda_mercadoria, int preço_compra_mercadoria, int preço_caravana, int linha, int coluna)
    : Entidade(nome, linha, coluna, letra), letra(letra), preço_venda_mercadoria(preço_venda_mercadoria), preço_compra_mercadoria(preço_compra_mercadoria), preço_caravana(preço_caravana) {
    // Adicionar caravanas disponíveis para venda
    caravanasDisponiveis.push_back(std::make_shared<Comercio>(0,"Comercio", linha, coluna, 'C', 40, 200, 2, 20));
    caravanasDisponiveis.push_back(std::make_shared<Militar>(0,"Militar", linha, coluna, 'M', 400, 3, 40));
    caravanasDisponiveis.push_back(std::make_shared<PaiNatal>(0,"PaiNatal", linha, coluna, 'P', 40, 200, 2, 20,3));
}

// Entrada de caravana na cidade
void Cidade::entrarCaravana(std::shared_ptr<Caravana> caravana) {
    caravanasNaCidade.push_back(caravana);
    cout << "Caravana " << caravana->getNome() << " entrou na cidade " << nome << ".\n";
}

// Saída de caravana da cidade
void Cidade::saidaCaravana(std::shared_ptr<Caravana> caravana) {
    for (auto it = caravanasNaCidade.begin(); it != caravanasNaCidade.end(); ++it) {
        if (*it == caravana) {
            caravanasNaCidade.erase(it);
            std::cout << "Caravana " << caravana->getNome() << " saiu da cidade " << nome << ".\n";
            return;
        }
    }
    cerr << "Erro: Caravana não encontrada na cidade.\n";
}

// Verifica se a caravana está na cidade
bool Cidade::existeCaravana(std::shared_ptr<Caravana> caravana) {
    for (const auto& c : caravanasNaCidade) {
        if (c == caravana) {
            return true;
        }
    }
    return false;
}

// Inspecionar o conteúdo da cidade
void Cidade::inspecionar() {
    cout << "Inspecionando a cidade " << nome << ":\n";
    for (const auto& caravana : caravanasNaCidade) {
        cout << "Caravana " << caravana->getNome() << " está presente na cidade.\n";
    }
}
// Comprar mercadoria para a caravana
void Cidade::comprarMercadoria(Caravana* caravana, Utilizador* user, int quantidade) {
    int custo = quantidade * preço_compra_mercadoria;
    int cargaDisponivel = caravana->getCapacidadeCarga() - caravana->getCargaAtual();
    int quantidadeFinal = std::min(quantidade, cargaDisponivel);
    int custoFinal = quantidadeFinal * preço_compra_mercadoria;

    if (user->getMoedas() >= custoFinal) {
        user->removerMoedas(custoFinal);
        caravana->setCargaAtual(caravana->getCargaAtual() + quantidadeFinal);
        cout << "Caravana " << caravana->getNome() << " comprou " << quantidadeFinal << " toneladas de mercadoria.\n";
    } else {
        cerr << "Erro: Moedas insuficientes para comprar mercadoria.\n";
    }
}

// Vender mercadoria da caravana
void Cidade::venderMercadoria(Caravana* caravana, Utilizador* user) {
    int quantidade = caravana->getCargaAtual();
    int ganho = quantidade * preço_venda_mercadoria;
    user->adicionarMoedas(ganho);
    caravana->setCargaAtual(0);
    cout << "Caravana " << caravana->getNome() << " vendeu " << quantidade << " toneladas de mercadoria.\n";
}

// Contratar tripulantes para a caravana
void Cidade::contratarTripulantes(Caravana* caravana, Utilizador* user, int quantidade) {
    int custo = quantidade;
    if (user->getMoedas() >= custo) {
        user->removerMoedas(custo);
        caravana->ajustarTripulacao(quantidade);
        cout << "Caravana " << caravana->getNome() << " contratou " << quantidade << " tripulantes.\n";
    } else {
        cerr << "Erro: Moedas insuficientes para contratar tripulantes.\n";
    }
}

// Comprar uma nova caravana
bool Cidade::comprarCaravana(Utilizador* user, char tipoCaravana) {
    int custoCaravana = preço_caravana;
    string tipoNome;

    switch (tipoCaravana) {
        case 'C':
            tipoNome = "Comercio";
        break;
        case 'M':
            tipoNome = "Militar";
        break;
        case 'S':
            tipoNome = "PaiNatal";
        break;
        default:
            cerr << "Erro: Tipo de caravana inválido.\n";
        return false;
    }

    // Procurar e remover a caravana correspondente pelo nome
    for (auto it = caravanasDisponiveis.begin(); it != caravanasDisponiveis.end(); ++it) {
        if ((*it)->getNome() == tipoNome) {
            if (user->getMoedas() >= custoCaravana) {
                user->removerMoedas(custoCaravana);
                caravanasDisponiveis.erase(it); // Remover caravana
                cout << "Caravana " << tipoNome << " foi comprada e está agora na cidade " << nome << ".\n";
                mostrarCaravanasDisponiveis(); // Mostrar restantes
                return true;
            } else {
                cerr << "Erro: Moedas insuficientes para comprar a caravana " << tipoNome << ".\n";
                return false;
            }
        }
    }

    cerr << "Erro: Tipo de caravana não disponível para compra.\n";
    mostrarCaravanasDisponiveis();
    return false;
}

// Mostrar caravanas disponíveis
void Cidade::mostrarCaravanasDisponiveis() const {
    cout << "Caravanas disponíveis para venda na cidade " << nome << ":\n";
    if (caravanasDisponiveis.empty()) {
        std::cout << "Nenhuma caravana disponível.\n";
        return;
    }

    for (const auto& caravana : caravanasDisponiveis) {
        cout << "  - " << caravana->getNome() << "\n";
    }
}

// Getters
char Cidade::getLetra() const {
    return letra;
}

int Cidade::getPrecoVendaMercadoria() const {
    return preço_venda_mercadoria;
}

int Cidade::getPrecoCompraMercadoria() const {
    return preço_compra_mercadoria;
}

int Cidade::getPrecoCaravana() const {
    return preço_caravana;
}

const std::vector<std::shared_ptr<Caravana>>& Cidade::getCaravanasDisponiveis() const {
    return caravanasDisponiveis;
}

void Cidade::atualizarEstado() {
}

void Cidade::imprimirStatus() const {
    cout << "\nCidade " << nome << ":\n";
    cout << "Preço de venda da mercadoria: " << preço_venda_mercadoria << "\n";
    cout << "Preço de compra da mercadoria: " << preço_compra_mercadoria << "\n";
    cout << "Preço da caravana: " << preço_caravana << "\n";
    cout << "Caravanas disponíveis para venda:\n";
    for (const auto& caravana : caravanasDisponiveis) {
        cout << " - " << caravana->getNome() << " (Preço: " <<getPrecoCaravana() << ")\n";
    }
}
