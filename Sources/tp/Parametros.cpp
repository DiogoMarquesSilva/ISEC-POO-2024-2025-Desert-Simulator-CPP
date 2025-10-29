

#include "Parametros.h"
#include "Global.h"
#include "Excecoes.h"
#include "Buffer.h"

// Construtor default
Parametros::Parametros() : linhas(0), colunas(0), moedas(0), instantesEntreNovosItens(0),
                           duracaoItem(0), maxItens(0), precoVendaMercadoria(0),
                           precoCompraMercadoria(0), precoCaravana(0),
                           instantesEntreNovosBarbaros(0), duracaoBarbaros(0) {}

// Métodos de acesso
int Parametros::getLinhas() const {
    return linhas;
}

int Parametros::getColunas() const {
    return colunas;
}

int Parametros::getMoedas() const {
    return moedas;
}

int Parametros::getPrecoVenda() const {
    return precoVendaMercadoria;
}

int Parametros::getPrecoCompra() const {
    return precoCompraMercadoria;
}
int Parametros::getInstantesEntreNovosItens() const {
    return instantesEntreNovosItens;
}

int Parametros::getDuracaoItem() const {
    return duracaoItem;
}

int Parametros::getMaxItens() const {
    return maxItens;
}

int Parametros::getPrecoCaravana() const {
    return precoCaravana;
}

int Parametros::getInstantesEntreNovosBarbaros() const {
    return instantesEntreNovosBarbaros;
}

int Parametros::getDuracaoBarbaros() const {
    return duracaoBarbaros;
}

// Método para carregar os parâmetros do ficheiro
void Parametros::carregarDeFicheiro(const std::string& nomeFicheiro, Buffer& buffer) {
    std::ifstream file(nomeFicheiro);
    if (!file) {
        throw std::runtime_error("Erro ao abrir o arquivo de configuração: " + nomeFicheiro);
    }

    std::string nome;
    int valor;
    std::string linha;

    // Ler dimensões do buffer (linhas e colunas)
    std::getline(file, linha);
    std::istringstream(linha) >> nome >> linhas;
    std::getline(file, linha);
    std::istringstream(linha) >> nome >> colunas;

    // Redimensionar o buffer com as dimensões especificadas
    buffer = Buffer(linhas, colunas);

    // Ler o mapa e armazenar no buffer
    for (int i = 0; i < linhas; ++i) {
        std::getline(file, linha);
        for (int j = 0; j < colunas; ++j) {
            buffer.setCaracter(i, j, linha[j]); // Colocar o caractere no buffer
        }
    }

    // Ler os valores configuráveis adicionais
    while (std::getline(file, linha)) {
        std::istringstream iss(linha);
        iss >> nome >> valor;

        if (nome == "moedas") {
            moedas = valor;
        } else if (nome == "instantes_entre_novos_itens") {
            instantesEntreNovosItens = valor;
        } else if (nome == "duração_item") {
            duracaoItem = valor;
        } else if (nome == "max_itens") {
            maxItens = valor;
        } else if (nome == "preço_venda_mercadoria") {
            precoVendaMercadoria = valor;
        } else if (nome == "preço_compra_mercadoria") {
            precoCompraMercadoria = valor;
        } else if (nome == "preço_caravana") {
            precoCaravana = valor;
        } else if (nome == "instantes_entre_novos_barbaros") {
            instantesEntreNovosBarbaros = valor;
        } else if (nome == "duração_bárbaros") {
            duracaoBarbaros = valor;
        } else {
            throw std::runtime_error("Parâmetro desconhecido no ficheiro: " + nome);
        }
    }

    buffer.imprimir();
    mostrarConteudo();
}


void Parametros::mostrarConteudo() const {
    cout << "Linhas: " << linhas << endl;
    cout << "Colunas: " << colunas << endl;
    cout << "Moedas: " << moedas << endl;
    cout << "Instantes Entre Novos Itens: " << instantesEntreNovosItens << endl;
    cout << "Duracao do Item: " << duracaoItem << endl;
    cout << "Max Itens: " << maxItens << endl;
    cout << "Preco Venda Mercadoria: " << precoVendaMercadoria << endl;
    cout << "Preco Compra Mercadoria: " << precoCompraMercadoria << endl;
    cout << "Preco Caravana: " << precoCaravana << endl;
    cout << "Instantes Entre Novos Barbaros: " << instantesEntreNovosBarbaros << endl;
    cout << "Duracao dos Barbaros: " << duracaoBarbaros << endl;
}