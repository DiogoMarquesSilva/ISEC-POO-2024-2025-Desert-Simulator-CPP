
#include "Global.h"
#include "Buffer.h"


// Construtor
Buffer::Buffer(int linhas, int colunas)
    : linhas(linhas), colunas(colunas), cursorLinha(0), cursorColuna(0) {
    matriz = new char[linhas * colunas]; // Aloca espaço para o buffer
    limpar(); // Inicializa com espaços
}

// Construtor por cópia
Buffer::Buffer(const Buffer& other)
    : linhas(other.linhas), colunas(other.colunas), cursorLinha(other.cursorLinha), cursorColuna(other.cursorColuna) {
    matriz = new char[linhas * colunas];
    copy(other.matriz, other.matriz + (linhas * colunas), matriz);
}

// Destrutor
Buffer::~Buffer() {
    delete[] matriz;
}

// Limpa o buffer
void Buffer::limpar() {
    for (int i = 0; i < linhas * colunas; ++i) {
        matriz[i] = ' ';
    }
    cursorLinha = 0;
    cursorColuna = 0;
}

// Move o cursor virtual
void Buffer::moverCursor(int linha, int coluna) {
    if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) {
        cursorLinha = linha;
        cursorColuna = coluna;
    }
}

// Escreve um caractere no buffer
void Buffer::escrever(char c) {
    if (cursorLinha >= 0 && cursorLinha < linhas &&
        cursorColuna >= 0 && cursorColuna < colunas) {
        matriz[cursorLinha * colunas + cursorColuna] = c;
        ++cursorColuna; // Avança o cursor
        if (cursorColuna >= colunas) { // Move para a próxima linha, se necessário
            cursorColuna = 0;
            ++cursorLinha;
        }
        }
}

// Escreve uma string no buffer
void Buffer::escrever(const string& str) {
    for (char c : str) {
        escrever(c);
    }
}

// Escreve um inteiro no buffer
void Buffer::escrever(int valor) {
    escrever(to_string(valor));
}

// Imprime o conteúdo do buffer na consola
void Buffer::imprimir() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            std::cout << matriz[i * colunas + j];
        }
        std::cout << std::endl; // Quebra de linha
    }
}

// Obtém um caractere do buffer
char Buffer::getCaracter(int linha, int coluna) const {
    if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) {
        return matriz[linha * colunas + coluna];
    }
    return ' '; // Retorna espaço se a posição for inválida
}

// Define um caractere no buffer
char Buffer::setCaracter(int linha, int coluna, char c) {
    if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) {
        matriz[linha * colunas + coluna] = c;
    }
    return c;
}


// Sobrecarga do operador de inserção
Buffer& Buffer::operator<<(const char c) {
    escrever(c);
    return *this;
}

Buffer& Buffer::operator<<(const string& str) {
    escrever(str);
    return *this;
}

Buffer& Buffer::operator<<(int valor) {
    escrever(valor);
    return *this;
}

Buffer& Buffer::operator=(const Buffer& other) {
    if (this == &other) {
        return *this; // Auto-atribuição
    }

    delete[] matriz; // Libera a memória existente

    linhas = other.linhas;
    colunas = other.colunas;
    cursorLinha = other.cursorLinha;
    cursorColuna = other.cursorColuna;

    matriz = new char[linhas * colunas];
    copy(other.matriz, other.matriz + (linhas * colunas), matriz);

    return *this;
}

int Buffer::getLinhas() const {
    return linhas;
}

int Buffer::getColunas() const {
    return colunas;
}