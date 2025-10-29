
#ifndef BUFFER_H
#define BUFFER_H

#include "Global.h"


class Buffer {
private:
    char* matriz;        // Armazena os caracteres do buffer
    int linhas, colunas; // Dimensões do buffer
    int cursorLinha, cursorColuna; // Posição atual do cursor

public:
    // Construtor e Destrutor
    Buffer() : linhas(0), colunas(0) {}
    Buffer(int linhas, int colunas);
    Buffer(const Buffer& other);
    ~Buffer();

    // Métodos principais
    void limpar(); // Limpa o buffer (preenche com espaços)
    void moverCursor(int linha, int coluna); // Move o cursor virtual
    void escrever(char c); // Escreve um caractere no buffer
    void escrever(const string& str); // Escreve uma string no buffer
    void escrever(int valor); // Escreve um inteiro no buffer
    void imprimir() const; // Imprime o conteúdo do buffer na consola
    char getCaracter(int linha, int coluna) const; // Obtém um caractere do buffer
    char setCaracter(int linha, int coluna, char c); // Define um caractere no buffer
    int getLinhas() const; // Obtém o número de linhas do buffer
    int getColunas() const; // Obtém o número de colunas do buffer

    // Operadores
    Buffer& operator<<(const char c);
    Buffer& operator<<(const string& str);
    Buffer& operator<<(int valor);
    //Operador de atribuição
    Buffer& operator=(const Buffer& other);


};

#endif //BUFFER_H
