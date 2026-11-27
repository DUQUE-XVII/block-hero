#include "Fase_Forest.h"
#include "Capanga_Cogumelo.h"
#include "Planta_Acida.h"
#include "Projetil_Acido.h"
#include "Lama.h"
#include <iostream>

Fase_Forest::Fase_Forest(Jogador* jogador)
    : Fase(1, jogador, 5, 10) {} // 5 inimigos (3 cogumelos + 2 plantas), até 10 obstáculos

Fase_Forest::~Fase_Forest() {}

void Fase_Forest::iniciarFase() {
    std::cout << "[FASE 1] Iniciando a Floresta...\n";

    if (pJogador != nullptr) {
        pJogador->setX(100.0f);
        pJogador->setY(500.0f);
        pFisica->getJogador(pJogador);
        listaEntidades.incluir(pJogador);
    }

    criarLimitesArena();

    // Mínimo 3 plataformas e mínimo 3 / máximo 5 lamas
    int numPlats = sortear(3, 5);
    int numLamas = sortear(3, 5);

    list<Plataforma*> plats = gerarPlataformasAleatorias(numPlats);

    // Embaralha as plataformas para sortear onde caem as lamas
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
    int livreChaoX = 200; // evita o spawn do jogador no chão

    for (int i = 0; i < numLamas; ++i) {
        // Decide se a lama vai na plataforma (enquanto houver livre) ou no chão
        bool colocarNoChao = (itPlat == plats.end()) || (sortear(0, 1) == 1);

        if (!colocarNoChao) {
            Plataforma* platAtual = *itPlat++;
            fixas.push_back(platAtual);

            sf::FloatRect b = platAtual->getForma()->getGlobalBounds();
            int larguraLama = std::max(30, static_cast<int>(b.size.x) - 20);
            int xLama = static_cast<int>(b.position.x) + 10;

            criarPlataforma(static_cast<float>(xLama), b.position.y - 10.f,
                            larguraLama, 10, new Lama());
        } else {
            // Lama no chão (topo do chão = y 560)
            int larguraLama = sortear(60, 100);
            int xMax = std::max(livreChaoX, 740 - larguraLama);
            int xLama = sortear(livreChaoX, xMax);

            criarPlataforma(static_cast<float>(xLama), 550.f,
                            larguraLama, 10, new Lama());

            livreChaoX = std::min(680, xLama + larguraLama + 40);
        }
    }

    // 3 Cogumelos espalhados entre chão e plataformas
    espalharCapangas(3, plats);

    // 2 Plantas Ácidas (completando os 5 inimigos da Fase 1)
    Planta_Acida* planta1 = new Planta_Acida();
    planta1->setPosicao(680.0f, 510.0f);
    planta1->definirAlvo(pJogador);

    Planta_Acida* planta2 = new Planta_Acida();
    planta2->definirAlvo(pJogador);
    if (!plats.empty()) {
        Plataforma* ultima = plats.back();
        if (std::find(fixas.begin(), fixas.end(), ultima) == fixas.end())
            fixas.push_back(ultima);

        sf::FloatRect b  = ultima->getForma()->getGlobalBounds();
        sf::Vector2f tam = planta2->getForma()->getSize();

        // Se a plataforma já tiver lama, coloca a planta no canto direito; senão, centraliza
        float xPlanta = b.position.x + b.size.x - tam.x - 5.f;
        planta2->setPosicao(xPlanta, b.position.y - tam.y);
    }

    tornarPlataformasMoveis(plats, fixas);

    if (!registrarInimigo(planta1)) delete planta1;
    else pFisica->incluirProjetil(planta1->getProjetil());

    if (!registrarInimigo(planta2)) delete planta2;
    else pFisica->incluirProjetil(planta2->getProjetil());
}

void Fase_Forest::executar() {
    if (pJogador == nullptr || !pJogador->estaVivo()) return;

    listaEntidades.percorrer();
    pFisica->executar();
    desenhar();

    if (todosInimigosMortos())
        concluida = true;
}

void Fase_Forest::carregar() {
    numeroFase = 1;
    carregarArquivos("saves/");
}
