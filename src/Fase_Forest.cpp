#include "Fase_Forest.h"
#include "Capanga_Cogumelo.h"
#include "Planta_Acida.h"
#include "Projetil_Acido.h"
#include <iostream>

Fase_Forest::Fase_Forest(Jogador* jogador)
    : Fase(1, jogador), maxInimigos(4), maxObstaculos(6) {}

Fase_Forest::~Fase_Forest() {}

void Fase_Forest::iniciarFase() {
    std::cout << "[FASE 1] Iniciando a Floresta...\n";

    // 1. Configura o Jogador
    if (pJogador != nullptr) {
        pJogador->setX(100.0f);
        pJogador->setY(500.0f);
        pFisica->getJogador(pJogador);
        listaEntidades.incluir(pJogador);
    }

    // 2. Cria bordas e plataformas da fase
    criarLimitesArena();

    Plataforma* plat1 = new Plataforma(150, 430, 200, 20);
    Plataforma* plat2 = new Plataforma(450, 330, 180, 20);
    listaPlataformas.push_back(plat1);
    listaPlataformas.push_back(plat2);
    pFisica->incluirObstaculo(plat1);
    pFisica->incluirObstaculo(plat2);
    listaEntidades.incluir(plat1);
    listaEntidades.incluir(plat2);

    // 3. Cria os 4 Inimigos
    Capanga_Cogumelo* cogumelo1 = new Capanga_Cogumelo();
    cogumelo1->setPosicao(300.0f, 510.0f);

    Capanga_Cogumelo* cogumelo2 = new Capanga_Cogumelo();
    cogumelo2->setPosicao(520.0f, 510.0f);

    Planta_Acida* planta1 = new Planta_Acida();
    planta1->setPosicao(680.0f, 510.0f);
    planta1->definirAlvo(pJogador);

    // Segunda planta posicionada sobre a plataforma 2 (y = 330 - 50 = 280)
    Planta_Acida* planta2 = new Planta_Acida();
    planta2->setPosicao(510.0f, 280.0f);
    planta2->definirAlvo(pJogador);

    // Registra inimigos nas listas e na física
    listaInimigos.push_back(cogumelo1);
    listaInimigos.push_back(cogumelo2);
    listaInimigos.push_back(planta1);
    listaInimigos.push_back(planta2);

    for (CriaturaHostil* inimigo : listaInimigos) {
        pFisica->incluirInimigos(inimigo);
        listaEntidades.incluir(inimigo);
    }

    // Registra os projéteis das duas plantas ácidas
    pFisica->incluirProjetil(planta1->getProjetil());
    pFisica->incluirProjetil(planta2->getProjetil());
}

void Fase_Forest::executar() {
    if (pJogador == nullptr || !pJogador->estaVivo()) return;

    pJogador->executar();

    bool todosMortos = true;
    for (CriaturaHostil* inimigo : listaInimigos) {
        if (inimigo != nullptr && inimigo->estaVivo()) {
            inimigo->executar();
            todosMortos = false;
        }
    }

    pFisica->executar();

    desenhar();
    for (CriaturaHostil* inimigo : listaInimigos) {
        Planta_Acida* planta = dynamic_cast<Planta_Acida*>(inimigo);
        if (planta != nullptr && planta->getProjetil()->estaAtivo()) {
            planta->getProjetil()->desenhar();
        }
    }

    if (todosMortos) {
        concluida = true;
    }
}

void Fase_Forest::salvar() { std::cout << "[SALVAR] Fase 1 salva.\n"; }
void Fase_Forest::carregar() { std::cout << "[CARREGAR] Fase 1 carregada.\n"; }
