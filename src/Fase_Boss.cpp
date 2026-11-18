#include "Fase_Boss.h"
#include "Boitata.h"
#include "Projetil_Acido.h"


Fase_Boss::Fase_Boss(Jogador* jogador)
    : Fase(2, jogador), maxChefes(1), maxObstaculos(3) {}

Fase_Boss::~Fase_Boss() {}

void Fase_Boss::iniciarFase() {
    std::cout << "[FASE 2] Iniciando a Caverna do Boitata...\n";

    // 1. Reposiciona o Jogador mantendo a vida atual
    if (pJogador != nullptr) {
        pJogador->setX(100.0f);
        pJogador->setY(500.0f);
        pFisica->getJogador(pJogador);
        listaEntidades.incluir(pJogador);
    }

    // 2. Cria arena e plataforma elevada para desviar do fogo
    criarLimitesArena();

    Plataforma* platCentral = new Plataforma(280, 420, 240, 20);
    listaPlataformas.push_back(platCentral);
    pFisica->incluirObstaculo(platCentral);
    listaEntidades.incluir(platCentral);

    // 3. Instancia o Chefão
    Boitata* boss = new Boitata();
    boss->setPosicao(600.0f, 200.0f);
    boss->definirAlvo(pJogador);

    listaInimigos.push_back(boss);
    pFisica->incluirInimigos(boss);
    pFisica->incluirProjetil(boss->getProjetil());
    listaEntidades.incluir(boss);
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
