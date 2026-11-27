#include "Fase_Boss.h"
#include "Boitata.h"
#include "Projetil_Acido.h"
#include <iostream>

Fase_Boss::Fase_Boss(Jogador* jogador)
    : Fase(2, jogador, 5, 10) {} // 5 inimigos (4 cogumelos + 1 Boitatá), até 10 obstáculos

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

    // Mínimo 3 plataformas e mínimo 3 / máximo 5 lavas
    int numPlats = sortear(3, 5);
    int numLavas = sortear(3, 5);

    list<Plataforma*> plats = gerarPlataformasAleatorias(numPlats);

    // Embaralha plataformas para sortear onde colocar lavas aéreas
    list<Plataforma*> embaralhadas;
    while (!plats.empty()) {
        int idx = sortear(0, static_cast<int>(plats.size()) - 1);
        auto it = std::next(plats.begin(), idx);
        embaralhadas.push_back(*it);
        plats.erase(it);
    }
    plats = embaralhadas;

    list<Plataforma*> fixas;
    auto itPlat = plats.begin();
    int livreChaoX = 200; // longe do spawn do jogador (x 100..160)

    for (int i = 0; i < numLavas; ++i) {
        // Decide se a lava vai em uma plataforma ou no chão
        bool naPlataforma = (itPlat != plats.end()) && (sortear(0, 1) == 1);

        if (naPlataforma) {
            Plataforma* platAtual = *itPlat++;
            fixas.push_back(platAtual); // plataforma com lava fica parada

            sf::FloatRect b = platAtual->getForma()->getGlobalBounds();
            int larguraLava = std::min(80, static_cast<int>(b.size.x) - 20);
            int xLava = static_cast<int>(b.position.x + (b.size.x - larguraLava) / 2.f);

            criarPlataforma(static_cast<float>(xLava), b.position.y - 12.f,
                            larguraLava, 12, new Lava());
        } else {
            int larguraLava = sortear(55, 85);
            int xMax = std::max(livreChaoX, 740 - larguraLava);
            int xLava = sortear(livreChaoX, xMax);

            criarPlataforma(static_cast<float>(xLava), 548.f,
                            larguraLava, 12, new Lava());

            livreChaoX = std::min(680, xLava + larguraLava + 45);
        }
    }

    // Plataformas sem lava podem se mover
    tornarPlataformasMoveis(plats, fixas);

    // 4 Cogumelos espalhados entre chão e plataformas
    espalharCapangas(4, plats);

    // Chefão Boitatá
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

    listaEntidades.percorrer();
    pFisica->executar();
    desenhar();

    if (todosInimigosMortos())
        concluida = true;
}

void Fase_Boss::carregar() {
    numeroFase = 2;
    carregarArquivos("saves/");
}
