#include "Simulador.h"
#include "Global.h"

int Simulador::idCaravana = 1; // Inicializar idCaravana
int Simulador::idBarbara = 1;  // Inicializar idBarbara
int Simulador::idCidade = 1;   // Inicializar idCidade
int Simulador::nTurnos = 0;    // Inicializar nTurnos
int Simulador::maxMovesComercio = 2; // Inicializar maxMovesComercio
int Simulador::maxMovesMilitar = 3; // Inicializar maxMovesMilitar
int Simulador::CombatesVencidos = 0; // Inicializar CombatesVencidos
int Simulador::ComandoUtilizado = 0; // Inicializar ComandoUtilizado

// Construtor
Simulador::Simulador() : emExecucao(true), moedas(0), configurado(false), utilizador(100), buffer(0,0) {
    for (int i = 0; i < 9; ++i) {
        idsDisponiveis[i][0] = i + 1; // ID de 1 a 9
        idsDisponiveis[i][1] = 0;     // 0 significa disponível
    }
}


// Métodos principais


// Método para processar o comando de configuração
// Recebe o nome do ficheiro de configuração
// Carrega os parâmetros do ficheiro e inicializa os objetos
void Simulador::comandoConfig(const string& nomeFicheiro) {
    try {
        parametros.carregarDeFicheiro(nomeFicheiro, buffer);
        inicializarObjetos(parametros);
        configurado = true;
        cout << "Configuração carregada com sucesso." << endl;
        mostrarEstado();
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
    }
}

// Método para processar o comando de saída
// Altera o estado do simulador para terminar a execução
void Simulador::comandoSair() {
    emExecucao = false;
    configurado=false;
}

// Método para processar o comando de execução de comandos a partir de um ficheiro
// Recebe o nome do ficheiro com os comandos
// Abre o ficheiro e executa os comandos um a um
void Simulador::comandoExec(const string& nomeFicheiro) {
    std::ifstream file(nomeFicheiro);
    if (!file.is_open()) {
        cerr << "Erro: Não foi possível abrir o arquivo " << nomeFicheiro << endl;
        return;
    }

    string linha;
    while (std::getline(file, linha)) {
        if (!linha.empty()) {
            try {
                processarComando(linha);
            } catch (const std::exception& e) {
                cerr << "Erro ao processar comando: " << e.what() << endl;
            }
        }
    }

    file.close();
    cout << "Execução de comandos do arquivo " << nomeFicheiro << " concluída." << endl;
}

// Método para processar o comando de ajuste de moedas
// Recebe o número de moedas a adicionar
// Adiciona o número de moedas ao utilizador
void Simulador::comandoMoedas(int n) {
    utilizador.adicionarMoedas(n);
    cout << "Moedas ajustadas para: " << utilizador.getMoedas() << endl;
}

// Método para processar o comando de término da simulação
// Imprime a pontuação final e reinicia as variáveis e estados
void Simulador::comandoTerminar() {
    cout << "Simulação terminada. Pontuação final: " << utilizador.getMoedas() << endl;
    cout << "Combates vencidos: " << CombatesVencidos << endl;

    // Redefinir variáveis e estados
    idCaravana = 1;
    idBarbara = 1;
    idCidade = 1;
    nTurnos = 0;
    maxMovesComercio = 2;
    maxMovesMilitar = 3;
    CombatesVencidos = 0;
    emExecucao = true;
    configurado=false;
    moedas = 0;
    utilizador = Utilizador(100);
    buffer = Buffer(0, 0);
    caravanas.clear();
    barbaros.clear();
    cidades.clear();
    itens.clear();
    moveCounter.clear();
    copiasBuffer.clear();
    for (int i = 0; i < 9; ++i) {
        idsDisponiveis[i][0] = i + 1;
        idsDisponiveis[i][1] = 0;
    }
    ComandoUtilizado=0;
    cout << "Simulação reiniciada." << endl;
}

// Método para processar o comando de compra de caravanas
// Recebe a cidade e o tipo de caravana
// Verifica se a cidade existe e se o tipo de caravana é válido
// Compra a caravana e a adiciona à cidade
void Simulador::comandoCompraC(const char cidade, char tipo) {
    // Verifica se a cidade existe
    std::shared_ptr<Cidade> cidadePtr = nullptr;
    for (auto& c : cidades) {
        if (c->getSimbolo() == cidade) {
            cidadePtr = c;
            break;
        }
    }
    //Verifica se a cidade foi encontrada
    if (!cidadePtr) {
        cerr << "Cidade " << cidade << " não encontrada." << endl;
        return;
    }
    // Verifica se o tipo de caravana é válido
    if (tipo != 'C' && tipo != 'M' && tipo != 'S') {
        cerr << "Tipo de caravana inválido." << endl;
        return;
    }
    //Compra a caravana
    if(numCaravanas()>= 9){
        cerr << "Número máximo de caravanas atingido." << endl;
        return;
    }
    if(cidadePtr->comprarCaravana(&utilizador, tipo)) {
        char c;
        c = '0' + getPrimeiroID();
        //Cria a caravana
        std::shared_ptr<Caravana> caravana = nullptr;
        if (tipo == 'C') {

            caravana = std::make_shared<Comercio>(
                getPrimeiroID(),
                "CaravanaC " + std::to_string(getPrimeiroID()),
                cidadePtr->getLinha(),
                cidadePtr->getColuna(),
                c, // Interpretar o número como capacidade ou identificação
                40,
                200,
                maxMovesComercio,
                20
            );
            ocuparID(getPrimeiroID());
        } else if (tipo == 'M') {
            caravana = std::make_shared<Militar>(
                getPrimeiroID(),
                "CaravanaM " + std::to_string(getPrimeiroID()),
                cidadePtr->getLinha(),
                cidadePtr->getColuna(),
                c,
                400,
                3,
                40
            );
            ocuparID(getPrimeiroID());
        } else if (tipo == 'S') {
            caravana = std::make_shared<PaiNatal>(
                getPrimeiroID(),
                "Pai Natal " + std::to_string(getPrimeiroID()),
                cidadePtr->getLinha(),
                cidadePtr->getColuna(),
                c,
                50,
                0,
                0,
                20,
                3
            );
            ocuparID(getPrimeiroID());
        }else {
            // Caso o tipo de caravana seja inválido
            cerr << "Tipo de caravana inválido." << endl;
        }
        // Adiciona a caravana ao vetor unificado
        caravanas.push_back(caravana);
        // Adiciona a caravana à cidade
        cidadePtr->entrarCaravana(caravana);
    }
}

// Método para processar o comando de listagem de preços
// Imprime os preços de compra, venda e caravana
void Simulador::comandoPrecos() {
    //Usa os parametros para obter os preços
    cout << "Preço de compra: " << parametros.getPrecoCompra() <<" * número de toneladas"<< endl;
    cout << "Preço de venda: " << parametros.getPrecoVenda() <<" * número de toneladas"<< endl;
    cout << "Preço de caravana: " << parametros.getPrecoCaravana() << endl;
    cout << "----------------------------\n";
}

// Método para processar o comando de listagem de informações de uma cidade
// Recebe a letra da cidade
// Itera pelas cidades e imprime as informações da cidade correspondente
void Simulador::comandoCidade(const char nomeCidade) {
    //Iterar pelas cidades
    for (auto& cidade : cidades) {
        if (cidade->getLetra() == nomeCidade) {
            cidade->imprimirStatus();
            return;
        }
    }

}

// Método para processar o comando de listagem de informações de uma caravana
// Recebe o ID da caravana
// Itera pelas caravanas e imprime as informações da caravana correspondente
void Simulador::comandoCaravana(int idCaravana) {
    //Iterar pelas caravanas
    for (auto& caravana : caravanas) {
        if (caravana->getId() == idCaravana) {
            caravana->imprimirStatus();
            return;
        }

        cerr<<"Caravana com ID "<<idCaravana<<" não encontrada."<<endl;
    }
}

// Método para processar o comando de compra de mercadorias
// Recebe o ID da caravana e o número de toneladas
// Verifica se a caravana existe e está numa cidade
// Compra as mercadorias na cidade
void Simulador::comandoCompra(int idCaravana, int toneladas) {
    // Verifica se a caravana existe
    std::shared_ptr<Caravana> caravana = nullptr;
    for (auto& c : caravanas) {
        if (c->getId() == idCaravana) {
            caravana = c;
            break;
        }
    }

    if (!caravana) {
        cerr << "Caravana com ID " << idCaravana << " não encontrada." << endl;
        return;
    }

    // Verifica se a caravana está nalguma cidade
    for (auto& cidade : cidades) {
        if (cidade->existeCaravana(caravana)) {
            // Utiliza os métodos da cidade para comprar mercadorias
            cidade->comprarMercadoria(caravana.get(), &utilizador, toneladas);
            return;
        }
    }

    cerr << "Caravana não está em nenhuma cidade." << endl;
}

// Método para processar o comando de venda de mercadorias
// Recebe o ID da caravana
// Verifica se a caravana existe e está numa cidade
// Vende as mercadorias na cidade
void Simulador::comandoVende(int idCaravana){
    // Verifica se a caravana existe
    std::shared_ptr<Caravana> caravana = nullptr;
    for (auto& c : caravanas) {
        if (c->getId() == idCaravana) {
            caravana = c;
            break;
        }
    }
    if (!caravana) {
        cerr << "Caravana com ID " << idCaravana << " não encontrada." << endl;
        return;
    }

    // Verifica se a caravana está nalguma cidade
    for (auto& cidade : cidades) {
        if (cidade->existeCaravana(caravana)) {
            // Utiliza os métodos da cidade para vender mercadorias
            cidade->venderMercadoria(caravana.get(), &utilizador);
            return;
        }
    }

    cerr << "Caravana não está em nenhuma cidade." << endl;

}

// Método para processar o comando de movimento de caravanas
// Recebe o ID da caravana e a direção
// Verifica se a direção é válida
// Move a caravana para a nova posição
void Simulador::comandoMove(int idCaravana, const string& direcao) {
    // Verifica se a direção é válida
    if (direcao != "D" && direcao != "E" && direcao != "C" && direcao != "B" &&
        direcao != "CE" && direcao != "CD" && direcao != "BE" && direcao != "BD") {
        cerr << "Direção inválida." << endl;
        return;
        }

    // Busca a caravana pelo ID no vetor unificado
    std::shared_ptr<Caravana> caravana = nullptr;
    for (const auto& c : caravanas) {
        if (c->getId() == idCaravana) {
            caravana = c;
            break;
        }
    }

    // Verifica se a caravana foi encontrada
    if (!caravana) {
        cerr << "Caravana com ID " << idCaravana << " não encontrada." << endl;
        return;
    }

    // Verifica o tipo de caravana e o número de movimentos permitidos
    int maxMoves = 0;
    if (dynamic_cast<Comercio*>(caravana.get())) {
        maxMoves = maxMovesComercio;
    } else if (dynamic_cast<Militar*>(caravana.get())) {
        maxMoves = maxMovesMilitar;
    }else if (dynamic_cast<PaiNatal*>(caravana.get())) {
        maxMoves = 1;
    }

    // Verifica se a caravana já atingiu o limite de movimentos
    if (moveCounter[idCaravana] >= maxMoves) {
        cerr << "Caravana com ID " << idCaravana << " atingiu o limite de movimentos." << endl;
        return;
    }

    // Verifica se a caravana está numa cidade e fá-la sair se houver movimentos restantes
    for (const auto& cidade : cidades) {
        if (cidade->existeCaravana(caravana)) {
            cidade->saidaCaravana(caravana);
            break;
        }
    }

    // Move a caravana para a nova posição
    Posicao(caravana, direcao);

    // Incrementa o contador de movimentos
    moveCounter[idCaravana]++;
}

// Método auxiliar para mover a caravana para a nova posição
//Recebe uma caravana e a direção para onde se quer mover
//Verifica se a nova posição é válida e move a caravana
//Atualiza o buffer e a posição da caravana
//Interage com os itens e verifica se a caravana morreu
void Simulador::Posicao(std::shared_ptr<Caravana> caravana, const string& direcao) {
    int dx = 0, dy = 0;

    // Define o deslocamento com base na direção
    if (direcao == "D") {
        dx = 1; dy = 0; // Direita
    } else if (direcao == "E") {
        dx = -1; dy = 0; // Esquerda
    } else if (direcao == "C") {
        dx = 0; dy = -1; // Cima
    } else if (direcao == "B") {
        dx = 0; dy = 1; // Baixo
    } else if (direcao == "CE") {
        dx = -1; dy = -1; // Cima-Esquerda
    } else if (direcao == "CD") {
        dx = 1; dy = -1; // Cima-Direita
    } else if (direcao == "BE") {
        dx = -1; dy = 1; // Baixo-Esquerda
    } else if (direcao == "BD") {
        dx = 1; dy = 1; // Baixo-Direita
    } else {
        cerr << "Direção inválida." << endl;
        return;
    }

    // Calcula a nova posição com movimento toroidal
    int linhas = buffer.getLinhas();
    int colunas = buffer.getColunas();
    int novaLinha = (caravana->getLinha() + dy + linhas) % linhas;
    int novaColuna = (caravana->getColuna() + dx + colunas) % colunas;

    char novoCaracter = buffer.getCaracter(novaLinha, novaColuna);

    // Verifica se a nova posição é válida
    if (novoCaracter == '.') {
        // Atualiza o buffer e a posição da caravana
        if (!std::islower(buffer.getCaracter(caravana->getLinha(), caravana->getColuna()))) {
            buffer.setCaracter(caravana->getLinha(), caravana->getColuna(), '.');
        }
        caravana->setPosicao(novaLinha, novaColuna);
        buffer.setCaracter(novaLinha, novaColuna, caravana->getSimbolo());
        cout << "Caravana movida para (" << novaLinha << ", " << novaColuna << ")." << endl;
    } else if (novoCaracter == 'I') {
        // Interage com o item
        for (auto it = itens.begin(); it != itens.end(); ++it) {
            if ((*it)->getLinha() == novaLinha && (*it)->getColuna() == novaColuna) {
                (*it)->aplicarEfeito(caravana.get(), &utilizador);
                buffer.setCaracter(caravana->getLinha(), caravana->getColuna(), '.');
                caravana->setPosicao(novaLinha, novaColuna);
                buffer.setCaracter(novaLinha, novaColuna, caravana->getSimbolo());
                itens.erase(it);
                cout << "Caravana movida para (" << novaLinha << ", " << novaColuna << ") e interagiu com um item." << endl;

                // Verifica se a caravana morreu
                if (!caravana->getVida()) {
                    eliminarCaravana(caravana);
                    cout << "A caravana foi destruída pela mina." << endl;
                }
                break;
            }
        }
    } else if (std::islower(novoCaracter)) {
        // Adiciona a caravana à cidade
        for (auto& cidade : cidades) {
            if (cidade->getLinha() == novaLinha && cidade->getColuna() == novaColuna) {
                cidade->entrarCaravana(caravana);
                buffer.setCaracter(caravana->getLinha(), caravana->getColuna(), '.');
                caravana->setPosicao(novaLinha, novaColuna);
                cout << "Caravana movida para a cidade " << cidade->getNome() << "." << endl;
                return;
            }
        }
    } else {
        cerr << "Posição inválida para mover a caravana." << endl;
    }

    // Consome recursos após mover a caravana
    caravana->consumirRecursos();
    // Verifica se a caravana morreu
    if (!caravana->getVida()) {
        eliminarCaravana(caravana);
        cout << "A caravana foi destruída por falta de recursos." << endl;
    }
}

// Método para processar o comando de ativação do modo automático
// Recebe o ID da caravana
// Ativa o modo automático da caravana correspondente
void Simulador::comandoAuto(int idCaravana) {
    // Iterar pelas caravanas no vetor geral
    for (auto& caravana : caravanas) {
        if (caravana->getId() == idCaravana) {
            caravana->setModoAutomatico(true);
            cout << "Caravana " << idCaravana << " está agora em modo automático." << endl;
            return;
        }
    }

    // Caso o ID não corresponda a nenhuma caravana
    cerr << "Caravana com ID " << idCaravana << " não encontrada." << endl;
}

// Método para processar o comando de desativação do modo automático
// Recebe o ID da caravana
// Desativa o modo automático da caravana correspondente
void Simulador::comandoStop(int idCaravana) {
    // Iterar pelas caravanas no vetor geral
    for (auto& caravana : caravanas) {
        if (caravana->getId() == idCaravana) {
            caravana->setModoAutomatico(false);
            cout << "Caravana " << idCaravana << " está agora em modo manual." << endl;
            return;
        }
    }

    // Caso o ID não corresponda a nenhuma caravana
    cerr << "Caravana com ID " << idCaravana << " não encontrada." << endl;
}

// Método para processar o comando de criação de bárbaros
// Recebe a linha e a coluna onde criar o bárbaro
// Verifica se a posição é válida e cria o bárbaro
// Atualiza o buffer e imprime uma mensagem de sucesso
void Simulador::comandoBarbaro(int linha, int coluna) {
    //Verifica se no buffer a posição é válida (deserto)
    if (buffer.getCaracter(linha, coluna) != '.') {
        cerr << "Posição inválida para criar um bárbaro." << endl;
        return;
    }
    //Cria um bárbaro
    auto barbaro = std::make_shared<Barbara>(
        parametros.getDuracaoBarbaros(),
        "Barbara" + std::to_string(idBarbara),
        linha,
        coluna,
        40
    );
    //Atualiza o buffer
    buffer.setCaracter(linha, coluna, '!');
    cout << "Bárbaro criado com sucesso." << endl;
}

// Método para processar o comando de aplicação de tempestade de areia
// Recebe a linha, a coluna e o raio da tempestade
// Aplica o efeito da tempestade nas caravanas e bárbaros
// Atualiza o buffer e imprime uma mensagem de sucesso
void Simulador::comandoAreia(int linha, int coluna, int raio) {
    // Calcula as extremidades do quadrado considerando o "mapa redondo"
    int linhaMin = (linha - raio + parametros.getLinhas()) % parametros.getLinhas();
    int linhaMax = (linha + raio) % parametros.getLinhas();
    int colunaMin = (coluna - raio + parametros.getColunas()) % parametros.getColunas();
    int colunaMax = (coluna + raio) % parametros.getColunas();

    // Função para verificar se uma posição está dentro do quadrado afetado
    auto estaDentroDoRaio = [&](int x, int y) {
        return (linhaMin <= linhaMax
                    ? (x >= linhaMin && x <= linhaMax)
                    : (x >= linhaMin || x <= linhaMax)) &&
               (colunaMin <= colunaMax
                    ? (y >= colunaMin && y <= colunaMax)
                    : (y >= colunaMin || y <= colunaMax));
    };

    // Aplica o efeito da tempestade nas caravanas
    for (auto it = caravanas.begin(); it != caravanas.end();) {
        auto& caravana = *it;
        if (estaDentroDoRaio(caravana->getLinha(), caravana->getColuna())) {
            caravana->lidarComTempestade();
            if (!caravana->getVida()) {
                buffer.setCaracter(caravana->getLinha(), caravana->getColuna(), '.');
                cout << "Caravana " << caravana->getId() << " foi destruída pela tempestade." << endl;
                eliminarCaravana(*it); // Remove a caravana
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }

    // Aplica o efeito da tempestade nas caravanas bárbaras
    for (auto it = barbaros.begin(); it != barbaros.end();) {
        auto& barbaro = *it;
        if (estaDentroDoRaio(barbaro->getLinha(), barbaro->getColuna())) {
            barbaro->lidarComTempestade();
            if (!barbaro->getVida()) {
                buffer.setCaracter(barbaro->getLinha(), barbaro->getColuna(), '.');
                cout << "Caravana bárbara " << barbaro->getNome() << " foi destruída pela tempestade." << endl;
                it = barbaros.erase(it); // Remove o bárbaro
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }

    cout << "Tempestade de areia aplicada na área centrada em (" << linha
              << ", " << coluna << ") com raio " << raio << "." << endl;
}

// Método para processar o comando para contratar tripulantes
// Recebe o ID da caravana e o numero de tripulantes a contratar
// Verifica se a caravana existe e está numa cidade
// Contrata tripulantes para a caravana
void Simulador::comandoTripul(int idCaravana, int tripulantes) {
    // Verifica se a caravana existe
    std::shared_ptr<Caravana> caravana = nullptr;
    for (auto& c : caravanas) {
        if (c->getId() == idCaravana) {
            caravana = c;
            break;
        }
    }
    //Verifica se a caravana foi encontrada
    if (!caravana) {
        cerr << "Caravana com ID " << idCaravana << " não encontrada." << endl;
        return;
    }
    // Verifica se a caravana está em alguma cidade
    for (auto& cidade : cidades) {
        if (cidade->existeCaravana(caravana)) {
            // Utiliza os métodos da cidade para contratar tripulantes
            cidade->contratarTripulantes(caravana.get(), &utilizador, tripulantes);
            return;
        }else{
            cerr << "Caravana não está em nenhuma cidade." << endl;
        }
    }
}

// Método para processar o comando para guardar o buffer atual
// Recebe o nome da cópia a ser salva
// Guarda o buffer atual com o nome fornecido
void Simulador::comandoSaves(const string& nome) {
    if (copiasBuffer.find(nome) != copiasBuffer.end()) {
        cerr << "Já existe uma cópia salva com o nome: " << nome << endl;
        return;
    }
    copiasBuffer[nome] = buffer; // Guarda o buffer atual com o nome fornecido
    cout << "Estado salvo como: " << nome << endl;
}

// Método para processar o comando para carregar uma cópia guardada
// Recebe o nome da cópia a ser carregada
// Carrega o buffer com a cópia correspondente
// Atualiza as entidades com base no novo buffer
void Simulador::comandoLoads(const string& nome) {
    auto it = copiasBuffer.find(nome); // Procura a cópia no mapa
    if (it == copiasBuffer.end()) {
        cerr << "Cópia com o nome " << nome << " não encontrada." << endl;
        return;
    }
    buffer = it->second; // Atualiza o buffer principal com a cópia encontrada
    atualizarEntidades(); // Atualiza as entidades com base no novo buffer
    cout << "Estado carregado: " << nome << endl;
}

// Método para processar o comando de listagem de cópias guardadas
// Imprime os nomes das cópias guardadas
void Simulador::comandoLists() {
    if (copiasBuffer.empty()) {
        cout << "Nenhuma cópia salva." << endl;
        return;
    }
    cout << "Cópias salvas:" << endl;
    for (const auto& [nome, _] : copiasBuffer) {
        cout << " - " << nome << endl;
    }
}

// Método para processar o comando de eliminação de cópias guardadas
// Recebe o nome da cópia a ser eliminada
// Elimina a cópia correspondente
void Simulador::comandoDels(const string& nome) {
    if (copiasBuffer.erase(nome) > 0) { // Tenta apagar a entrada do mapa
        cout << "Cópia " << nome << " excluída." << endl;
    } else {
        cerr << "Cópia com o nome " << nome << " não encontrada." << endl;
    }
}

// Método para processar destribuir os comandos
void Simulador::processarComando(const string& comando) {
    istringstream iss(comando);
    string operacao;
    iss >> operacao;
    //Se não estiver configurado, não permite a execução de comandos sem ser o config ou o sair
    if (!configurado && operacao != "config" && operacao != "sair") {
        cerr << "O simulador não está configurado." << endl;
        cout << "> ";
        return;
    }

    if (operacao == "config") {
        string ficheiro;
        iss >> ficheiro;
        comandoConfig(ficheiro);
    } else if (operacao == "sair") {
        comandoSair();
    } else if (operacao == "exec") {
        string ficheiro;
        iss >> ficheiro;
        comandoExec(ficheiro);
    } else if (operacao == "prox") {
        int n;
        if (iss >> n) {
            executarTurno(n);
        } else {
            executarTurno();
        }
    } else if (operacao == "moedas") {
        int n;
        if (iss >> n) {
            comandoMoedas(n);
        } else {
            cerr << "Comando moedas inválido." << endl;
        }
    } else if (operacao == "terminar") {
        comandoTerminar();
    } else if (operacao == "comprac") {
        char cidade;
        char tipo;
        iss >> cidade >> tipo;
        comandoCompraC(cidade, tipo);
    } else if (operacao == "precos") {
        comandoPrecos();
    } else if (operacao == "cidade") {
        char nomeCidade;
        iss >> nomeCidade;
        comandoCidade(nomeCidade);
    } else if (operacao == "caravana") {
        int idCaravana;
        iss >> idCaravana;
        comandoCaravana(idCaravana);
    } else if (operacao == "compra") {
        int idCaravana;
        int toneladas;
        iss >> idCaravana >> toneladas;
        comandoCompra(idCaravana, toneladas);
    } else if (operacao == "vende") {
        int idCaravana;
        iss >> idCaravana;
        comandoVende(idCaravana);
    } else if (operacao == "move") {
        int idCaravana;
        string direcao;
        iss >> idCaravana >> direcao;
        comandoMove(idCaravana, direcao);
    } else if (operacao == "auto") {
        int idCaravana;
        iss >> idCaravana;
        comandoAuto(idCaravana);
    } else if (operacao == "stop") {
        int idCaravana;
        iss >> idCaravana;
        comandoStop(idCaravana);
    } else if (operacao == "barbaro") {
        int linha, coluna;
        iss >> linha >> coluna;
        comandoBarbaro(linha, coluna);
    } else if (operacao == "areia") {
        int linha, coluna, raio;
        iss >> linha >> coluna >> raio;
        comandoAreia(linha, coluna, raio);
    } else if (operacao == "tripul") {
        int idCaravana;
        int tripulantes;
        iss >> idCaravana >> tripulantes;
        comandoTripul(idCaravana, tripulantes);
    } else if (operacao == "saves") {
        string nome;
        iss >> nome;
        comandoSaves(nome);
    } else if (operacao == "loads") {
        string nome;
        iss >> nome;
        comandoLoads(nome);
    } else if (operacao == "lists") {
        comandoLists();
    } else if (operacao == "dels") {
        string nome;
        iss >> nome;
        comandoDels(nome);
    }else if(operacao == "info") {
        mostrarEstado();
    }else {
        cerr << "Comando desconhecido: " << operacao << endl;
        cout << "> ";
    }
    buffer.imprimir();
}

bool Simulador::estaEmExecucao() const {
    return emExecucao;
}

void Simulador::atualizarEstado() {
    cout << "Estado atualizado para o próximo turno." << endl;
}

// Método para inicializar o simulador com os parâmetros do ficheiro de configuração
// Recebe os parametros do ficheiro de configuração
// Inicializa o buffer e as entidades com base nos parametros
void Simulador::inicializarObjetos(Parametros& parametros) {
    // Inicializar o utilizador com o número de moedas
    utilizador = Utilizador(parametros.getMoedas());

    for (int i = 0; i < parametros.getLinhas(); ++i) {
        for (int j = 0; j < parametros.getColunas(); ++j) {
            char c = buffer.getCaracter(i, j);

            if (c == '.') {
                // Posição vazia, nada a fazer
                continue;
            } else if (c == '+') {
                // Montanha, nada a fazer
                continue;
            } else if (std::islower(c)) {
                // Letra minúscula, criar cidade
                auto cidade = std::make_shared<Cidade>(
                    "Cidade " + std::to_string(idCidade),
                    c,
                    parametros.getPrecoVenda(),
                    parametros.getPrecoCompra(),
                    parametros.getPrecoCaravana(),
                    i,
                    j
                );
                cidades.push_back(cidade);
                idCidade++;
            } else if (std::isdigit(c)) {
                // Número, criar caravana de comércio
                auto caravana = std::make_shared<Comercio>(
                    getPrimeiroID(),
                    "CaravanaC " + std::to_string(getPrimeiroID()),
                    i,
                    j,
                    c, // Interpretar o número como capacidade ou identificação
                    40,
                    200,
                    maxMovesComercio,
                    20
                );
                caravanas.push_back(caravana); // Adiciona ao vetor unificado
                ocuparID(getPrimeiroID());
            } else if (c == '!') {
                // Símbolo de bárbaros, criar caravana bárbara
                auto barbaro = std::make_shared<Barbara>(
                    parametros.getDuracaoBarbaros(),
                    "Barbara " + std::to_string(idBarbara),
                    i,
                    j,
                    40
                );
                barbaros.push_back(barbaro); // Adiciona ao vetor unificado
                idBarbara++;
            } else if (c == 'I') {
                // Símbolo de item encontrado no buffer
                int tipoAleatorio = rand() % 5; // 5 tipos diferentes de itens
                std::shared_ptr<Item> novoItem;
                string nomeItem = "Item " + std::to_string(itens.size() + 1);

                // Criar item aleatório
                switch (tipoAleatorio) {
                    case 0:
                        novoItem = std::make_shared<CaixaDePandora>(nomeItem + "CaixaDePandora", i, j, 'I', parametros.getDuracaoItem());
                        break;
                    case 1:
                        novoItem = std::make_shared<ArcaDoTesouro>(nomeItem + " ArcaDoTesouro", i, j, 'I', parametros.getDuracaoItem());
                        break;
                    case 2:
                        novoItem = std::make_shared<Jaula>(nomeItem + " Jaula", i, j, 'I', parametros.getDuracaoItem());
                        break;
                    case 3:
                        novoItem = std::make_shared<Mina>(nomeItem + " Mina", i, j, 'I', parametros.getDuracaoItem());
                        break;
                    case 4:
                        novoItem = std::make_shared<Surpresa>(nomeItem + " Surpresa", i, j, 'I', parametros.getDuracaoItem());
                        break;
                }

                // Adiciona o item ao vetor de itens
                itens.push_back(novoItem);
            }
        }
    }
}

// Método para mostrar o estado do simulador
void Simulador::mostrarEstado() const {
    cout << "===== Estado do Simulador =====" << endl;

    // Mostrar moedas do utilizador
    cout << "Moedas do Utilizador: " << utilizador.getMoedas() << endl;

    // Mostrar conteúdo do buffer
    cout << "\nBuffer:\n";
    buffer.imprimir();

    // Mostrar cidades
    cout << "\nCidades:\n";
    if (cidades.empty()) {
        cout << "Nenhuma cidade encontrada." << endl;
    } else {
        for (const auto& cidade : cidades) {
            cidade->imprimirStatus();
        }
    }

    // Mostrar caravanas (unificadas)
    cout << "\nCaravanas:\n";
    if (caravanas.empty()) {
        cout << "Nenhuma caravana encontrada." << endl;
    } else {
        for (const auto& caravana : caravanas) {
            caravana->imprimirStatus();
        }
    }

    // Mostrar itens
    cout << "\nItens:\n";
    if (itens.empty()) {
        cout << "Nenhum item encontrado." << endl;
    } else {
        for (const auto& item : itens) {
            item->imprimirStatus();
        }
    }

    // Mostrar bárbaros
    cout << "\nBárbaros:\n";
    if (barbaros.empty()) {
        cout << "Nenhum bárbaro encontrado." << endl;
    } else {
        for (const auto& barbaro : barbaros) {
            barbaro->imprimirStatus();
        }
    }

    cout << "================================" << endl;
}

// Executar um turno
// Recebe o número de turnos a executar
// Atualiza o número de turnos
// Gerir caravanas bárbaras
// Gerir itens
// Gerir caravanas
// Reinicia o contador de movimentos
void Simulador::executarTurno(int n) {
    while(n>0){
        nTurnos++;
        cout << "Turno " << nTurnos << endl;
        //Gerir Caravanas Bárbaras
        gerirCaravanasBarbaras(nTurnos);
        gerirItens(nTurnos);
        gerirCaravanas();

        n--;
        moveCounter.clear();
    }

    cout << "Turno executado com sucesso." << endl;
}

// Metodo para mover as caravanas para uma posição adjacente aleatória
// Recebe as coordenadas da caravana e o buffer
// Define os deslocamentos para as 8 direções (cima, baixo, esquerda, direita, diagonais)
// Calcula as novas coordenadas baseadas no deslocamento
// Movimento toroidal: ajustar coordenadas que ultrapassam os limites
// Verifica se a posição é um '.'
// Move para a nova posição
// Se não for um '.' mas for cima, baixo, esquerda ou direita e esse caraceter for um 'I'
// Interage com o item
void Simulador::moverParaPosicaoAdjacenteAleatoria(int& x, int& y, const Buffer& buffer) {
    // Define os deslocamentos para as 8 direções (cima, baixo, esquerda, direita, diagonais)
    const int deslocamentos[8][2] = {
        {-1, 0},  // Cima
        {1, 0},   // Baixo
        {0, -1},  // Esquerda
        {0, 1},   // Direita
        {-1, -1}, // Diagonal superior esquerda
        {-1, 1},  // Diagonal superior direita
        {1, -1},  // Diagonal inferior esquerda
        {1, 1}    // Diagonal inferior direita
    };

    // Dimensões do mapa
    int maxLinhas = buffer.getLinhas();
    int maxColunas = buffer.getColunas();

    // Loop para tentar encontrar uma posição válida
    while (true) {
        // Sorteia uma direção (índice de 0 a 7)
        int direcao = rand() % 8;

        // Calcula as novas coordenadas baseadas no deslocamento
        int novoX = x + deslocamentos[direcao][0];
        int novoY = y + deslocamentos[direcao][1];

        // Movimento toroidal: ajustar coordenadas que ultrapassam os limites
        if (novoY < 0) novoY = maxColunas - 1; // Saiu pela esquerda, volta pela direita
        if (novoY >= maxColunas) novoY = 0;   // Saiu pela direita, volta pela esquerda
        if (novoX < 0) novoX = maxLinhas - 1; // Saiu por cima, volta por baixo
        if (novoX >= maxLinhas) novoX = 0;    // Saiu por baixo, volta por cima

        // Verifica se a posição é um '.'
        if (buffer.getCaracter(novoX, novoY) == '.') {
            // Move para a nova posição
            x = novoX;
            y = novoY;
            break; // Sai do loop

        }
        //Se não for um '.' mas for cima, baixo, esquerda ou direita e esse caraceter for um 'I'
        //Interage com o item
        else if (buffer.getCaracter(novoX, novoY) == 'I' && (direcao == 0 || direcao == 1 || direcao == 2 || direcao == 3)) {
            x = novoX;
            y = novoY;
            break; // Sai do loop
        }

    }
}

// Método para gerir as caravanas barbáras
// Recebe o número de turnos
// Verifica se se pode eliminar bárbaros aborrecidos
// Adiciona novo bárbaro em intervalos
// Movimentar os bárbaros
// Verifica se o bárbaro encontrou uma ao lado e combate
// Verifica posições na mesma linha (horizontal)
// Verifica posições na mesma coluna (vertical)
// Verifica se a posição é um 'I' e aplica o efeito do item
// Atualiza o buffer e a posição da caravana
// Remove o bárbaro se não tiver vida
void Simulador::gerirCaravanasBarbaras(int nTurnos) {
    // Verificar se se pode eliminar bárbaros aborrecidos
    for (auto it = barbaros.begin(); it != barbaros.end();) {
        auto& barbaro = *it;
        if ((nTurnos % barbaro->getMaxInstantes()) ==0) {
            buffer.setCaracter(barbaro->getLinha(), barbaro->getColuna(), '.');
            it = barbaros.erase(it); // Remove o bárbaro e atualiza o iterador
        } else {
            ++it;
        }
    }

    // Adicionar novo bárbaro em intervalos
    if ((nTurnos % parametros.getInstantesEntreNovosBarbaros()) == 0) {
        auto barbaro = std::make_shared<Barbara>(
            parametros.getDuracaoBarbaros(),
            "Barbara" + std::to_string(idBarbara),
            0,
            0,
            40
        );
        barbaros.push_back(barbaro);
        idBarbara++;

        int linha = rand() % parametros.getLinhas();
        int coluna = rand() % parametros.getColunas();
        while (buffer.getCaracter(linha, coluna) != '.') {
            linha = rand() % parametros.getLinhas();
            coluna = rand() % parametros.getColunas();
        }
        barbaro->setPosicao(linha, coluna);
        buffer.setCaracter(linha, coluna, '!');
    }

    // Movimentar os bárbaros
    auto it = barbaros.begin();
    while (it != barbaros.end()) {
        auto& barbaro = *it;
        bool combateRealizado = combate(barbaro);
        if (combateRealizado) {
            if(it == barbaros.end()) {
                break;
            }
            ++it;
            continue;
        }

        bool encontrouCaravana = false;
        int alvoX = -1, alvoY = -1;

        int barbaroX = barbaro->getLinha();
        int barbaroY = barbaro->getColuna();

        int maxLinhas = buffer.getLinhas();
        int maxColunas = buffer.getColunas();

        // Verificar posições na mesma linha (horizontal)
        for (int offset = -8; offset <= 8; ++offset) {
            if (offset == 0) continue;
            int colunaVerificada = (barbaroY + offset + maxColunas) % maxColunas;
            char caractere = buffer.getCaracter(barbaroX, colunaVerificada);
            if (caractere >= '1' && caractere <= '9') {
                encontrouCaravana = true;
                alvoX = barbaroX;
                alvoY = colunaVerificada;
                break;
            }
        }

        // Verificar posições na mesma coluna (vertical)
        if (!encontrouCaravana) {
            for (int offset = -8; offset <= 8; ++offset) {
                if (offset == 0) continue;
                int linhaVerificada = (barbaroX + offset + maxLinhas) % maxLinhas;
                char caractere = buffer.getCaracter(linhaVerificada, barbaroY);
                if (caractere >= '1' && caractere <= '9') {
                    encontrouCaravana = true;
                    alvoX = linhaVerificada;
                    alvoY = barbaroY;
                    break;
                }
            }
        }

        buffer.setCaracter(barbaroX, barbaroY, '.');
        if (encontrouCaravana) {
            if (barbaroY < alvoY) barbaroY = (barbaroY + 1) % maxColunas;
            else if (barbaroY > alvoY) barbaroY = (barbaroY - 1 + maxColunas) % maxColunas;

            if (barbaroX < alvoX) barbaroX = (barbaroX + 1) % maxLinhas;
            else if (barbaroX > alvoX) barbaroX = (barbaroX - 1 + maxLinhas) % maxLinhas;
        } else {
            moverParaPosicaoAdjacenteAleatoria(barbaroX, barbaroY, buffer);
            if (buffer.getCaracter(barbaroX, barbaroY) == 'I') {
                for (auto itItem = itens.begin(); itItem != itens.end(); ++itItem) {
                    if ((*itItem)->getLinha() == barbaroX && (*itItem)->getColuna() == barbaroY) {
                        (*itItem)->aplicarEfeito(barbaro.get(), &utilizador);
                        itens.erase(itItem);
                        break;
                    }
                }
            }
        }

        barbaro->setPosicao(barbaroX, barbaroY);
        if (!barbaro->getVida()) {
            buffer.setCaracter(barbaroX, barbaroY, '.');
            it = barbaros.erase(it); // Remove o bárbaro e atualiza o iterador
        } else {
            buffer.setCaracter(barbaroX, barbaroY, '!');
            ++it;
        }
    }
}

// Método para gerir os itens
// Recebe o número de turnos
// Verifica se é possível criar novos itens
// Sorteia o tipo de item
// Escolhe uma posição vazia
// Cria o item correspondente ao tipo sorteado
// Adiciona o item ao vetor e atualiza o buffer
void Simulador::gerirItens(int nTurnos) {

    if (nTurnos % parametros.getInstantesEntreNovosItens() == 0 && itens.size() < parametros.getMaxItens()) {
        // Sorteio do tipo de item
        int tipoAleatorio = rand() % 5; // 5 tipos diferentes
        string nomeItem = "Item" + std::to_string(itens.size() + 1);

        // Escolher uma posição vazia
        int linha, coluna;
        do {
            linha = rand() % parametros.getLinhas();
            coluna = rand() % parametros.getColunas();
        } while (buffer.getCaracter(linha, coluna) != '.');

        // Criar o item correspondente ao tipo sorteado
        std::shared_ptr<Item> novoItem;
        switch (tipoAleatorio) {
            case 0:
                novoItem = std::make_shared<CaixaDePandora>(nomeItem + " CaixaDePandora", linha, coluna, 'I', parametros.getDuracaoItem());
            break;
            case 1:
                novoItem = std::make_shared<ArcaDoTesouro>(nomeItem + " ArcaDoTesouro", linha, coluna, 'I', parametros.getDuracaoItem());
            break;
            case 2:
                novoItem = std::make_shared<Jaula>(nomeItem + " Jaula", linha, coluna, 'I', parametros.getDuracaoItem());
            break;
            case 3:
                novoItem = std::make_shared<Mina>(nomeItem + " Mina", linha, coluna, 'I', parametros.getDuracaoItem());
            break;
            case 4:
                novoItem = std::make_shared<Surpresa>(nomeItem + " Surpresa", linha, coluna, 'I', parametros.getDuracaoItem());
            break;
        }

        // Adicionar o item ao vetor e atualizar o buffer
        itens.push_back(novoItem);
        buffer.setCaracter(linha, coluna, 'I');
        cout << "Item " << nomeItem << " criado com sucesso." << endl;
    }

    // Atualizar o tempo de existência dos itens
    for (auto it = itens.begin(); it != itens.end();) {
        auto& item = *it;
        item->reduzirTempoExistencia();

        // Remover itens que expiraram
        if (!item->estaAtivo()) {
            buffer.setCaracter(item->getLinha(), item->getColuna(), '.');
            it = itens.erase(it);
        } else {
            ++it;
        }
    }
}

// Método para combater
// Recebe o bárbaro
// Verifica posições adjacentes para encontrar caravanas
// Determina as forças de combate usando a função num_combate
// Verifica o vencedor
// Calcula as perdas de tripulantes
// Atualiza o número de tripulantes
// Atualiza o buffer
// Elimina a caravana se o número de tripulantes for 0
// Elimina o bárbaro se o número de tripulantes for 0
// Retorna verdadeiro se o bárbaro foi destruído ou se o combate foi realizado
// Retorna falso se nenhum combate foi realizado
bool Simulador::combate(std::shared_ptr<Barbara> barbaro) {
    int barbaroX = barbaro->getLinha();
    int barbaroY = barbaro->getColuna();

    // Verificar posições adjacentes para encontrar caravanas
    const int deslocamentos[4][2] = {
        {0, 1},  // Direita
        {0, -1}, // Esquerda
        {1, 0},  // Abaixo
        {-1, 0}  // Acima
    };

    for (const auto& deslocamento : deslocamentos) {
        int alvoX = (barbaroX + deslocamento[0] + buffer.getLinhas()) % buffer.getLinhas();
        int alvoY = (barbaroY + deslocamento[1] + buffer.getColunas()) % buffer.getColunas();

        char caractere = buffer.getCaracter(alvoX, alvoY);
        if (caractere >= '1' && caractere <= '9') {
            // Encontrar a caravana alvo
            auto caravana = encontrarCaravanaPorSimbolo(caractere);
            if (!caravana) continue;

            // Determinar as forças de combate usando sua função
            int barbarosForca = barbaro->num_combate();
            int caravanaForca = caravana->num_combate();

            cout << "Combate: " << barbaro->getNome() << " (Força: " << barbarosForca << ") VS "
                      << caravana->getNome() << " (Força: " << caravanaForca << ")" << endl;

            // Verificar o vencedor
            if (barbarosForca > caravanaForca) {
                int perdasBarbara = barbaro->getTripulantes() * 0.2; // 20% dos tripulantes do bárbaro
                int perdasCaravana = perdasBarbara * 2; //O dobro disso para a caravana

                caravana->alteraTripulantes(-perdasCaravana);
                barbaro->alteraTripulantes(-perdasBarbara);

                if (caravana->getTripulantes()==0) {
                    buffer.setCaracter(alvoX, alvoY, '.');
                    eliminarID(caravana->getId());
                    cout << caravana->getNome() << " foi destruída." << endl;
                    caravanas.erase(std::remove(caravanas.begin(), caravanas.end(), caravana), caravanas.end());
                }

            } else if (caravanaForca > barbarosForca) {
                // Caravana vence
                CombatesVencidos++;
                int perdasCaravana = caravana->getTripulantes() * 0.2; // 20% dos tripulantes da caravana
                int perdasBarbara = perdasCaravana * 2; //O dobro disso para o bárbaro

                barbaro->alteraTripulantes(-perdasBarbara);
                caravana->alteraTripulantes(-perdasCaravana);

                if (barbaro->getTripulantes()==0) {
                    buffer.setCaracter(barbaroX, barbaroY, '.');
                    cout << barbaro->getNome() << " foi destruído." << endl;
                    barbaros.erase(std::remove(barbaros.begin(), barbaros.end(), barbaro), barbaros.end());
                    return true; // Bárbaro destruído, combate encerrado
                }

            } else {
                // Empate, combate continua no próximo turno
                cout << "Combate empatado entre " << barbaro->getNome() << " e " << caravana->getNome()
                          << ". Continuará no próximo turno." << endl;
            }

            // Combate foi realizado
            return true;
        }
    }

    return false; // Nenhum combate foi realizado
}

// Método para encontrar uma caravana por símbolo
// Recebe o símbolo da caravana
// Itera sobre as caravanas e retorna a caravana correspondente
std::shared_ptr<Caravana> Simulador::encontrarCaravanaPorSimbolo(char simbolo) {
    for (const auto& caravana : caravanas) {
        if (caravana->getSimbolo() == simbolo) {
            return caravana;
        }
    }
    return nullptr; // Não encontrada
}

// Método para gerir as caravanas
// Itera sobre as caravanas
// Ignora caravanas que não estão em modo automático
// Verifica o tipo da caravana e invoca a função correspondente
void Simulador::gerirCaravanas() {
    for (auto& caravana : caravanas) {
        if (!caravana->getModoAutomatico()) {
            continue; // Ignorar caravanas que não estão em modo automático
        }

        // Verificar o tipo da caravana e invocar a função correspondente
        if (dynamic_cast<Comercio*>(caravana.get())) {
            comportamentoCaravanaComercio(caravana);
        } else if (dynamic_cast<Militar*>(caravana.get())) {
            comportamentoCaravanaMilitar(caravana);
        } else if (dynamic_cast<PaiNatal*>(caravana.get())) {
            comportamentoCaravanaPaiNatal(caravana);
        } else {
            cerr << "Caravana desconhecida: ID " << caravana->getId() << endl;
        }
    }
}

// Método para fazer o comportamento da caravana de comércio
// Recebe a caravana
// Verifica itens a uma distância de 2 linhas e/ou colunas
// Encontra um item, aplica o efeito e move-se para a posição
// Atualiza a posição da caravana no buffer
// Se não encontrou itens adjacentes, tenta manter-se ao lado de outra caravana do utilizador
// Se não encontrou itens ou outra caravana, move-se aleatoriamente 1 ou 2 posições
void Simulador::comportamentoCaravanaComercio(std::shared_ptr<Caravana> caravana) {
    // Cast para garantir que é uma caravana de comércio
    auto comercio = std::dynamic_pointer_cast<Comercio>(caravana);
    if (!comercio) {
        cerr << "Erro: Caravana não é do tipo Comércio." << endl;
        return;
    }

    int linha = comercio->getLinha();
    int coluna = comercio->getColuna();

    // Verificar itens a uma distância de 2 linhas e/ou colunas
    const int deslocamentos[8][2] = {
        {0, 1}, {0, 2}, {0, -1}, {0, -2}, // Horizontal
        {1, 0}, {2, 0}, {-1, 0}, {-2, 0}  // Vertical
    };

    for (const auto& deslocamento : deslocamentos) {
        int novaLinha = (linha + deslocamento[0] + buffer.getLinhas()) % buffer.getLinhas();
        int novaColuna = (coluna + deslocamento[1] + buffer.getColunas()) % buffer.getColunas();

        char caractere = buffer.getCaracter(novaLinha, novaColuna);
        if (caractere == 'I') {
            // Encontrou item, aplica o efeito e move-se para a posição
            for (auto it = itens.begin(); it != itens.end(); ++it) {
                if ((*it)->getLinha() == novaLinha && (*it)->getColuna() == novaColuna) {
                    (*it)->aplicarEfeito(comercio.get(), &utilizador);
                    if (!comercio->getVida()) {
                        eliminarCaravana(comercio);
                        cout << "A caravana foi destruída por um item mina." << endl;
                        itens.erase(it);
                        if(!std::islower(buffer.getCaracter(caravana->getLinha(), caravana->getColuna())))
                            buffer.setCaracter(linha, coluna, '.');
                        buffer.setCaracter(novaLinha, novaColuna, '.');
                        return;
                    }
                    itens.erase(it);
                    break;
                }
            }

            // Atualizar a posição da caravana no buffer
            if(!std::islower(buffer.getCaracter(caravana->getLinha(), caravana->getColuna())))
                buffer.setCaracter(linha, coluna, '.');
            buffer.setCaracter(novaLinha, novaColuna, comercio->getSimbolo());
            comercio->setPosicao(novaLinha, novaColuna);

            cout << "Caravana de comércio " << comercio->getNome() << " apanhou um item na posição ("
                      << novaLinha << ", " << novaColuna << ").\n";
            comercio->consumirRecursos();
            if (!comercio->getVida()) {
                eliminarCaravana(comercio);
                cout << "A caravana foi destruída por falta de recursos." << endl;
            }
            return; // Já se moveu neste turno
        }
    }

    // Se não encontrou itens adjacentes, tenta manter-se ao lado de outra caravana do utilizador
    for (const auto& outraCaravana : caravanas) {
        if (outraCaravana != caravana) {
            int outraLinha = outraCaravana->getLinha();
            int outraColuna = outraCaravana->getColuna();

            if (std::abs(linha - outraLinha) <= 2 && std::abs(coluna - outraColuna) <= 2) {
                // Move para uma posição adjacente à outra caravana
                int dx = (outraLinha > linha) ? 1 : (outraLinha < linha) ? -1 : 0;
                int dy = (outraColuna > coluna) ? 1 : (outraColuna < coluna) ? -1 : 0;

                int novaLinha = (linha + dx + buffer.getLinhas()) % buffer.getLinhas();
                int novaColuna = (coluna + dy + buffer.getColunas()) % buffer.getColunas();

                if (buffer.getCaracter(novaLinha, novaColuna) == '.') {
                    if(!std::islower(buffer.getCaracter(caravana->getLinha(), caravana->getColuna())))
                        buffer.setCaracter(linha, coluna, '.');
                    buffer.setCaracter(novaLinha, novaColuna, comercio->getSimbolo());
                    comercio->setPosicao(novaLinha, novaColuna);

                    cout << "Caravana de comércio " << comercio->getNome() << " moveu-se para posição ("
                              << novaLinha << ", " << novaColuna << ") para ficar próxima de outra caravana.\n";
                    comercio->consumirRecursos();
                    if (!comercio->getVida()) {
                        eliminarCaravana(comercio);
                        cout << "A caravana foi destruída por falta de recursos." << endl;
                    }
                    return; // Já se moveu neste turno
                }
            }
        }
    }

    // Se não encontrou itens ou outra caravana, move-se aleatoriamente 1 ou 2 posições
    int passos = rand() % 2 + 1; // 1 ou 2 passos
    for (int i = 0; i < passos; ++i) {
        int novoX = linha, novoY = coluna;
        moverParaPosicaoAdjacenteAleatoria(novoX, novoY, buffer);

        // Atualizar a posição da caravana no buffer
        if(!std::islower(buffer.getCaracter(caravana->getLinha(), caravana->getColuna())))
            buffer.setCaracter(linha, coluna, '.');
        buffer.setCaracter(novoX, novoY, comercio->getSimbolo());
        comercio->setPosicao(novoX, novoY);

        linha = novoX;
        coluna = novoY;
    }

    cout << "Caravana de comércio " << comercio->getNome() << " moveu-se para posição ("
              << linha << ", " << coluna << ").\n";
    comercio->consumirRecursos();
    if (!comercio->getVida()) {
        eliminarCaravana(comercio);
        cout << "A caravana foi destruída por falta de recursos." << endl;
    }
}


// Método para fazer o comportamento da caravana militar
// Recebe a caravana
// Verifica se a caravana deve andar na mesma direção
// Se sim, move-se na mesma direção até 3 posições
// Se encontrar um item mina, aplica o efeito e remove o item
// Se a caravana ficar sem recursos, remove a caravana
// Se não, verifica se há caravanas bárbaras a 6 posições de distância
// Se sim, move-se em direção ao bárbaro
void Simulador::comportamentoCaravanaMilitar(std::shared_ptr<Caravana> caravana) {
    auto militar = std::dynamic_pointer_cast<Militar>(caravana);
    if (!militar) {
        cerr << "Erro: Caravana não é do tipo Militar." << endl;
        return;
    }

    int linha = militar->getLinha();
    int coluna = militar->getColuna();

    // Verificar se a caravana deve andar na mesma direção
    if (militar->getAndarNaMesmaDirecao()) {
        int dx = militar->getUltimoMovimentoX();
        int dy = militar->getUltimoMovimentoY();
        if(!std::islower(buffer.getCaracter(caravana->getLinha(), caravana->getColuna())))
            buffer.setCaracter(linha, coluna, '.');
        for (int i = 0; i < 3; ++i) {
            int novaLinha = (linha + dx + buffer.getLinhas()) % buffer.getLinhas();
            int novaColuna = (coluna + dy + buffer.getColunas()) % buffer.getColunas();
            char novoCaracter = buffer.getCaracter(novaLinha, novaColuna);
            if (novoCaracter == '.' || novoCaracter == 'I') {

                if (novoCaracter == 'I') {
                    for (auto it = itens.begin(); it != itens.end(); ++it) {
                        if ((*it)->getLinha() == novaLinha && (*it)->getColuna() == novaColuna) {
                            (*it)->aplicarEfeito(militar.get(), &utilizador);
                            if (!militar->getVida()) {
                                eliminarCaravana(militar);
                                cout << "A caravana foi destruída por um item mina." << endl;
                                itens.erase(it);
                                if(!std::islower(buffer.getCaracter(caravana->getLinha(), caravana->getColuna())))
                                    buffer.setCaracter(linha, coluna, '.');
                                buffer.setCaracter(novaLinha, novaColuna, '.');
                                return;
                            }
                            itens.erase(it);
                            break;
                        }
                    }
                }
                linha = novaLinha;
                coluna = novaColuna;
            } else {
                break;
            }
        }
        militar->setPosicao(linha, coluna);
        buffer.setCaracter(linha, coluna, militar->getSimbolo());
        militar->consumirRecursos();
        if (!militar->getVida()) {
            if(!std::islower(buffer.getCaracter(caravana->getLinha(), caravana->getColuna())))
                buffer.setCaracter(linha, coluna, '.');
            eliminarCaravana(militar);
            cout << "A caravana foi destruída por falta de recursos." << endl;
        }
        return;
    }

    // Verificar se há caravanas bárbaras a 6 posições de distância
    bool encontrouBarbaro = false;
    int alvoX = -1, alvoY = -1;
    for (const auto& barbaro : barbaros) {
        int barbaroX = barbaro->getLinha();
        int barbaroY = barbaro->getColuna();
        if (std::abs(linha - barbaroX) <= 6 && std::abs(coluna - barbaroY) <= 6) {
            encontrouBarbaro = true;
            alvoX = barbaroX;
            alvoY = barbaroY;
            break;
        }
    }

    if (encontrouBarbaro) {
        int dx = (alvoX > linha) ? 1 : (alvoX < linha) ? -1 : 0;
        int dy = (alvoY > coluna) ? 1 : (alvoY < coluna) ? -1 : 0;
        for (int i = 0; i < 3; ++i) {
            int novaLinha = (linha + dx + buffer.getLinhas()) % buffer.getLinhas();
            int novaColuna = (coluna + dy + buffer.getColunas()) % buffer.getColunas();
            char novoCaracter = buffer.getCaracter(novaLinha, novaColuna);
            if (novoCaracter == '.' || novoCaracter == 'I') {
                if (novoCaracter == 'I') {
                    for (auto it = itens.begin(); it != itens.end(); ++it) {
                        if ((*it)->getLinha() == novaLinha && (*it)->getColuna() == novaColuna) {
                            (*it)->aplicarEfeito(militar.get(), &utilizador);
                            if (!militar->getVida()) {
                                eliminarCaravana(militar);
                                cout << "A caravana foi destruída por um item mina." << endl;
                                itens.erase(it);
                                if(!std::islower(buffer.getCaracter(caravana->getLinha(), caravana->getColuna())))
                                    buffer.setCaracter(linha, coluna, '.');
                                buffer.setCaracter(novaLinha, novaColuna, '.');
                                return;
                            }
                            itens.erase(it);
                            break;
                        }
                    }
                }
                linha = novaLinha;
                coluna = novaColuna;
            } else {
                break;
            }
        }
        militar->setUltimoMovimento(dx, dy);
    }

    // Atualizar a posição da caravana no buffer
    if (!std::islower(buffer.getCaracter(caravana->getLinha(), caravana->getColuna()))){
        buffer.setCaracter(militar->getLinha(), militar->getColuna(), '.');
        buffer.setCaracter(linha, coluna, militar->getSimbolo());
    }
    militar->setPosicao(linha, coluna);

    // Consumir recursos e verificar a vida da caravana
    militar->consumirRecursos();
    if (!militar->getVida()) {
        eliminarCaravana(militar);
        cout << "A caravana foi destruída por falta de recursos." << endl;
    }
}

// Método para fazer o comportamento da caravana do Pai Natal
// Recebe a caravana
// Reduz turnos restantes
// Verifica se o Pai Natal está sem turnos ou sem carga
// Atualiza o contador de turnos desde o último drop
// Drop de presente se o intervalo foi atingido
// Movimento aleatório
void Simulador::comportamentoCaravanaPaiNatal(std::shared_ptr<Caravana> caravana) {
    auto paiNatal = std::dynamic_pointer_cast<PaiNatal>(caravana);
    if (!paiNatal) {
        cerr << "Erro: Caravana não é do tipo Pai Natal." << endl;
        return;
    }

    // Reduz turnos restantes
    paiNatal->setTurnosRestantes(paiNatal->getTurnosRestantes() - 1);

    // Verifica se o Pai Natal está sem turnos ou sem carga
    if (!paiNatal->estaAtivo() || paiNatal->getCargaAtual() < 10) {
        cout << "Pai Natal " << paiNatal->getNome() << " terminou sua missão.\n";
        eliminarCaravana(paiNatal);
        return;
    }

    // Atualiza o contador de turnos desde o último drop
    int turnosDesdeUltimoDrop = paiNatal->getTurnosDesdeUltimoDrop() + 1;
    paiNatal->setTurnosDesdeUltimoDrop(turnosDesdeUltimoDrop);
    cout << "Turnos desde o último drop: " << turnosDesdeUltimoDrop
              << " / Intervalo de drop: " << paiNatal->getIntervaloDrop() << endl;

    int criado = 0;

    // Drop de presente se o intervalo foi atingido
    if (turnosDesdeUltimoDrop >= paiNatal->getIntervaloDrop()) {
        int tipoAleatorio = rand() % 5; // 5 tipos diferentes
        std::shared_ptr<Item> novoItem;
        string nomeItem = "Presente " + std::to_string(itens.size() + 1);

        // Criar presente baseado no tipo aleatório
        switch (tipoAleatorio) {
            case 0:
                novoItem = std::make_shared<CaixaDePandora>(nomeItem + " CaixaDePandora", paiNatal->getLinha(), paiNatal->getColuna(), 'I', parametros.getDuracaoItem());
                break;
            case 1:
                novoItem = std::make_shared<ArcaDoTesouro>(nomeItem + " ArcaDoTesouro", paiNatal->getLinha(), paiNatal->getColuna(), 'I', parametros.getDuracaoItem());
                break;
            case 2:
                novoItem = std::make_shared<Jaula>(nomeItem + " Jaula", paiNatal->getLinha(), paiNatal->getColuna(), 'I', parametros.getDuracaoItem());
                break;
            case 3:
                novoItem = std::make_shared<Mina>(nomeItem + " Mina", paiNatal->getLinha(), paiNatal->getColuna(), 'I', parametros.getDuracaoItem());
                break;
            case 4:
                novoItem = std::make_shared<Surpresa>(nomeItem + " Surpresa", paiNatal->getLinha(), paiNatal->getColuna(), 'I', parametros.getDuracaoItem());
                break;
        }

        // Consome capacidade de carga e registra o presente
        paiNatal->setCargaAtual(paiNatal->getCargaAtual() - 10); // Cada presente custa 10 unidades de carga
        itens.push_back(novoItem);
        buffer.setCaracter(paiNatal->getLinha(), paiNatal->getColuna(), 'I'); // Representa o presente no mapa
        paiNatal->espalharPresentes(); // Atualiza o contador de presentes
        criado = 1;
        cout << "Pai Natal " << paiNatal->getNome() << " deixou um presente (" << nomeItem << ") em (" << paiNatal->getLinha() << ", " << paiNatal->getColuna() << ").\n";

        // Reinicia o contador de turnos desde o último drop
        paiNatal->setTurnosDesdeUltimoDrop(0);
    }

    // Movimento aleatório
    int linha = paiNatal->getLinha();
    int coluna = paiNatal->getColuna();
    moverParaPosicaoAdjacenteAleatoria(linha, coluna, buffer);

    // Atualiza a posição
    if (!std::islower(buffer.getCaracter(caravana->getLinha(), caravana->getColuna())) && criado == 0) {
        buffer.setCaracter(caravana->getLinha(), caravana->getColuna(), '.');
    }
    paiNatal->setPosicao(linha, coluna);
    buffer.setCaracter(linha, coluna, paiNatal->getSimbolo()); // Atualiza a nova posição
}


// Método para eliminar uma caravana
// Recebe a caravana
// Marca o ID como disponível
// Remove a caravana do vetor de caravanas
// Atualiza o buffer
void Simulador::eliminarCaravana(std::shared_ptr<Caravana> caravana) {
    if (!caravana) {
        cerr << "Erro: Tentativa de eliminar uma caravana nula." << endl;
        return;
    }

    int id = caravana->getId();
    for (int i = 0; i < 9; ++i) {
        if (idsDisponiveis[i][0] == id) {
            idsDisponiveis[i][1] = 0; // Marca o ID como disponível
            break;
        }
    }
    string nome = caravana->getNome();

    // Remove a caravana do vetor de caravanas
    auto it = std::find_if(caravanas.begin(), caravanas.end(),
                           [id](const std::shared_ptr<Caravana>& c) { return c->getId() == id; });
    if (it != caravanas.end()) {
        caravanas.erase(it);
    }

    // Atualiza o buffer
    if (caravana->getLinha() >= 0 && caravana->getColuna() >= 0 && !std::islower(buffer.getCaracter(caravana->getLinha(), caravana->getColuna()))) {
        buffer.setCaracter(caravana->getLinha(), caravana->getColuna(), '.');
    }

    cout << "Caravana " << nome << " eliminada com sucesso." << endl;
}

// Método para tornar um ID disponível
void Simulador::eliminarID(int id) {
    for (int i = 0; i < 9; ++i) {
        if (idsDisponiveis[i][0] == id) {
            idsDisponiveis[i][1] = 0; // Marca o ID como disponível
            break;
        }
    }
}

// Método para tornar um ID ocupado
void Simulador::ocuparID(int id) {
    for (int i = 0; i < 9; ++i) {
        if (idsDisponiveis[i][0] == id) {
            idsDisponiveis[i][1] = 1; // Marca o ID como disponível
            break;
        }
    }
}

// Método para obter o primeiro ID disponível
int Simulador::getPrimeiroID() {
    // Encontra o primeiro ID disponível
    for (int i = 0; i < 9; ++i) {
        if (idsDisponiveis[i][1] == 0) {
            return idsDisponiveis[i][0];
        }
    }
    return -1; // Nenhum ID disponível
}

// Método para obter o número de caravanas
// Retorna o número de IDs ocupados
int Simulador::numCaravanas() {
    // Retorna o número de ids ocupados
    int num = 0;
    for (int i = 0; i < 9; ++i) {
        if (idsDisponiveis[i][1] == 1) {
            num++;
        }
    }
    return num;
}

// Método para atualizar o simulador caso outro buffer seja implementado
// Atualiza as caravanas, bárbaros e itens
// Remove caravanas que já não estão no buffer
// Adiciona novas caravanas
// Adiciona bárbaros
// Adiciona itens
void Simulador::atualizarEntidades() {
    // Atualizar caravanas
    set<int> idsEncontrados; // IDs das caravanas encontradas no buffer

    for (int i = 0; i < buffer.getLinhas(); ++i) {
        for (int j = 0; j < buffer.getColunas(); ++j) {
            char c = buffer.getCaracter(i, j);
            if (std::isdigit(c)) { // Representa uma caravana
                int idCaravana = c - '0';
                idsEncontrados.insert(idCaravana);

                auto it = std::find_if(caravanas.begin(), caravanas.end(),
                                       [idCaravana](const std::shared_ptr<Caravana>& caravana) {
                                           return caravana->getId() == idCaravana;
                                       });

                if (it != caravanas.end()) {
                    // Atualiza a posição da caravana existente
                    (*it)->setPosicao(i, j);
                } else {
                    // Nova caravana no buffer (não estava no vetor)
                    auto novaCaravana = std::make_shared<Comercio>(
                        idCaravana, "CaravanaC " + std::to_string(idCaravana), i, j, c, 40, 200, maxMovesComercio, 20);
                    caravanas.push_back(novaCaravana);
                    cout << "Nova caravana adicionada: " << novaCaravana->getNome() << " em (" << i << ", " << j << ").\n";
                }
            }
        }
    }

    // Remover caravanas que não estão mais no buffer
    for (auto it = caravanas.begin(); it != caravanas.end();) {
        if (idsEncontrados.find((*it)->getId()) == idsEncontrados.end()) {
            cout << "Caravana removida: " << (*it)->getNome() << " (ID: " << (*it)->getId() << ").\n";
            eliminarID((*it)->getId());
            it = caravanas.erase(it); // Remove a caravana
        } else {
            ++it;
        }
    }

    // Atualizar bárbaros
    barbaros.clear();
    for (int i = 0; i < buffer.getLinhas(); ++i) {
        for (int j = 0; j < buffer.getColunas(); ++j) {
            if (buffer.getCaracter(i, j) == '!') { // Representa um bárbaro
                auto barbaro = std::make_shared<Barbara>(
                    parametros.getDuracaoBarbaros(),
                    "Barbara" + std::to_string(idBarbara),
                    0,
                    0,
                    40
                );
                barbaros.push_back(barbaro);
                cout << "Bárbaro adicionado: " << barbaro->getNome() << " em (" << i << ", " << j << ").\n";
            }
        }
    }

    // Atualizar itens
    itens.clear();
    for (int i = 0; i < buffer.getLinhas(); ++i) {
        for (int j = 0; j < buffer.getColunas(); ++j) {
            if (buffer.getCaracter(i, j) == 'I') { // Representa um item
                int tipoAleatorio = rand() % 5; // 5 tipos diferentes
                std::shared_ptr<Item> novoItem;
                string nomeItem = "Item " + std::to_string(itens.size() + 1);

                // Criar item baseado no tipo aleatório
                switch (tipoAleatorio) {
                    case 0:
                        novoItem = std::make_shared<CaixaDePandora>(nomeItem + " CaixaDePandora", i, j, 'I', parametros.getDuracaoItem());
                    break;
                    case 1:
                        novoItem = std::make_shared<ArcaDoTesouro>(nomeItem + " ArcaDoTesouro", i, j, 'I', parametros.getDuracaoItem());
                    break;
                    case 2:
                        novoItem = std::make_shared<Jaula>(nomeItem + " Jaula", i, j, 'I', parametros.getDuracaoItem());
                    break;
                    case 3:
                        novoItem = std::make_shared<Mina>(nomeItem + " Mina", i, j, 'I', parametros.getDuracaoItem());
                    break;
                    case 4:
                        novoItem = std::make_shared<Surpresa>(nomeItem + " Surpresa", i, j, 'I', parametros.getDuracaoItem());
                    break;
                }
                itens.push_back(novoItem);
                cout << "Item adicionado: " << novoItem->getNome() << " em (" << i << ", " << j << ").\n";
            }
        }
    }

    cout << "Entidades sincronizadas com o buffer carregado.\n";
}

//Destrutor
Simulador::~Simulador() {
    caravanas.clear();
    barbaros.clear();
    cidades.clear();
    itens.clear();
}