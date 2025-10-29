

#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <map>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cstring>
#include <memory>
#include <charconv>
#include <set>
using namespace std;

// Representação visual do mapa
const char DESERTO = '.';                   // Espaço vazio no mapa
const char MONTANHA = '+';                  // Montanha
const char BARBARO = '!';                   // Caravana bárbara
// Nota: As cidades são identificadas por letras minúsculas no mapa ('a', 'b', etc.).

// Configuração de combates (valores fixos no enunciado)
const double PERDA_TRIPULANTES_VENCEDOR = 0.2;  // Percentagem de tripulantes perdidos pelo vencedor
const double MULTIPLICADOR_PERDA_VENCIDO = 2.0; // Multiplicador para a perda do perdedor

// Configuração de tempestades de areia (valores fixos no enunciado)
const int PERDA_TRIPULANTES_TEMPESTADE = 10;    // Percentagem de tripulantes perdidos em tempestades
const int PROB_DESTRUICAO_COMERCIO = 50;        // Probabilidade de destruição de caravanas de comércio
const int PROB_DESTRUICAO_MILITAR = 33;         // Probabilidade de destruição de caravanas militares
const int PROB_DESTRUICAO_BARBAROS = 25;        // Probabilidade de destruição de caravanas bárbaras

// Configuração de itens (fixos no enunciado)
const double CAIXA_PANDORA_MORTALIDADE = 0.2;  // Percentagem de tripulantes mortos pela Caixa de Pandora
const double ARCA_TESOURO_BONUS = 0.1;         // Percentagem de moedas adicionadas pelo Tesouro

#endif

