#include "Fase_Boss.h"
#include "Boitata.h"
#include "Projetil_Acido.h"


Fase_Boss::Fase_Boss(Jogador* jogador)
    : Fase(2, jogador, 3, 4) {}

Fase_Boss::~Fase_Boss() {}

void Fase_Boss::iniciarFase() {
    std::cout << "[FASE 2] Iniciando a Caverna do Boitata...\n";

    if (pJogador != nullptr) {
        pJogador->setX(100.0f);
        pJogador->setY(500.0f);
        pFisica->getJogador(pJogador);
        listaEntidades.incluir(pJogador);
    }

    criarLimitesArena();
    gerarPlataformasAleatorias(3);   // plataformas aleatórias para desviar do fogo

    // Capangas patrulhando o chão
    criarCapanga(250.0f, 510.0f);
    criarCapanga(550.0f, 510.0f);

    // Chefão
    Boitata* boss = new Boitata();
    boss->setPosicao(600.0f, 200.0f);
    boss->definirAlvo(pJogador);

    if (!registrarInimigo(boss)) {
        delete boss;
        return;
    }
    pFisica->incluirProjetil(boss->getProjetil());
}

void Fase_Boss::executar() {
    if (pJogador == nullptr || !pJogador->estaVivo()) return;

    pJogador->executar();

    bool bossDerrotado = true;
    for (CriaturaHostil* inimigo : listaInimigos) {
        if (inimigo != nullptr && inimigo->estaVivo()) {
            inimigo->executar();
            bossDerrotado = false;
        }
    }

    pFisica->executar();

    desenhar();
    for (CriaturaHostil* inimigo : listaInimigos) {
        Boitata* boss = dynamic_cast<Boitata*>(inimigo);
        if (boss != nullptr && boss->getProjetil()->estaAtivo()) {
            boss->getProjetil()->desenhar();
        }
    }

    if (bossDerrotado) {
        concluida = true;
    }
}

void Fase_Boss::salvar() { std::cout << "[SALVAR] Fase 2 salva.\n"; }
void Fase_Boss::carregar() { std::cout << "[CARREGAR] Fase 2 carregada.\n"; }
