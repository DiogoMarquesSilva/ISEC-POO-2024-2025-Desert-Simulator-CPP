
#include "Global.h"
#include "Entidade.h"

// Construtor
Entidade::Entidade(const string& nome, int linha, int coluna, char simbolo)
    : nome(nome), linha(linha), coluna(coluna), simbolo(simbolo) {}

// Define a nova posição da entidade
void Entidade::setPosicao(int novaLinha, int novaColuna) {
    linha = novaLinha;
    coluna = novaColuna;
}