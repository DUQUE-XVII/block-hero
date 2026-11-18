#include "Fase_Boss.h"
#include "Boitata.h"
#include <iostream>

Fase_Boss::Fase_Boss() : Fase(2), maxChefes(1), maxObstaculos(3) {}

Fase_Boss::~Fase_Boss() {}

void Fase_Boss::iniciarFase() {
    cout << "[FASE 2] Iniciando a Caverna do Boitata...\n";

    // 1. Cria o Herói (mantém a vida da fase anterior, em teoria)
    pJogador = new Jogador();
    pJogador->setPosicao(100.0f, 500.0f);

    // 2. Instancia o Chefão
    Boitata* boss = new Boitata();
    boss-> // Voa mais alto
    boss->definirAlvo(pJogador); // Passa o alvo para o Boitatá perseguir

    listaInimigos.push_back(boss);
}

void Fase_Boss::executar() {
    if (pJogador->getVida() <= 0) return;

    pJogador->atualizar();

    for (CriaturaHostil* inimigo : listaInimigos) {
        inimigo->executar();
    }

    pFisica->verificarDano(pJogador, listaInimigos);
}

void Fase_Boss::salvar() { std::cout << "[SALVAR] Fase 2 salva.\n"; }
void Fase_Boss::carregar() { std::cout << "[CARREGAR] Fase 2 carregada.\n"; }
