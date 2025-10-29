#include "Global.h"
#include "Simulador.h"
#include "Buffer.h"
#include "Parametros.h"

int main() {
    Simulador simulador;
    std::string comando;

    std::cout << "Bem-vindo ao simulador! Insira comandos para controlar a simulação." << std::endl;

    while (simulador.estaEmExecucao()) {
        std::cout << "> ";
        std::getline(std::cin, comando);

        try {
            simulador.processarComando(comando);
        } catch (const std::exception& e) {
            std::cerr << "Erro: " << e.what() << std::endl;
        }
    }

    std::cout << "Simulação encerrada. Obrigado por jogar!" << std::endl;
    return 0;
}