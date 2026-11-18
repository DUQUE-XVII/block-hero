#include "Fase_Forest.h"
#include "Capanga_Cogumelo.h"
#include "Planta_Acida.h"
#include <iostream>

Fase_Forest::Fase_Forest() : Fase(1), maxInimigos(3), maxObstaculos(5) {}

Fase_Forest::~Fase_Forest() {}

void Fase_Forest::iniciarFase() {
    std::cout << "[FASE 1] Iniciando a Floresta Roxa...\n";

    // 1. Cria o Herói
    pJogador = new Jogador();
    pJogador->setPosicao(100.0f, 500.0f); // Começa na esquerda

    // 2. Cria os Inimigos (Respeitando o maxInimigos)
    Capanga_Cogumelo* cogumelo1 = new Capanga_Cogumelo();
    cogumelo1->setPosicao(300.0f, 500.0f);

    Planta_Acida* planta1 = new Planta_Acida();
    planta1->setPosicao(500.0f, 400.0f);
    planta1->definirAlvo(pJogador); // Passa o alvo para a planta atirar

    // Adiciona na lista de inimigos da fase
    listaInimigos.push_back(cogumelo1);
    listaInimigos.push_back(planta1);
}

void Fase_Forest::executar() {
    if (pJogador->getVida() <= 0) return; // Se morreu, para a fase (em teoria)

    // 1. O Herói age (no futuro, lê o teclado)
    pJogador->atualizar();

    // 2. Os inimigos agem
    for (CriaturaHostil* inimigo : listaInimigos) {
        inimigo->executar();
    }

    // 3. A física resolve as tretas (colisões)
    pFisica->verificarDano(pJogador, listaInimigos);
}

void Fase_Forest::salvar() { std::cout << "[SALVAR] Fase 1 salva.\n"; }
void Fase_Forest::carregar() { std::cout << "[CARREGAR] Fase 1 carregada.\n"; }
