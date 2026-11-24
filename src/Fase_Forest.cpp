#include    "Fase_Forest.h"
#include    "Capanga_Cogumelo.h"
#include    "Planta_Acida.h"
#include    "Projetil_Acido.h"
#include    <iostream>
#include    "Lama.h"

Fase_Forest::Fase_Forest(Jogador* jogador)
    : Fase(1, jogador, 4, 6) {}

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

    // Lamas (1 a 3) e plataformas dividem o limite maxObstaculos:
    // quanto mais lamas, menos plataformas.
    int numLamas = sortear(1, 3);
    int numPlats = maxObstaculos - numLamas;          // 6 - (1..3) = 5..3

    vector<Plataforma*> plats = gerarPlataformasAleatorias(numPlats);
    numLamas = std::min(numLamas, static_cast<int>(plats.size()));

    // Embaralha para as lamas caírem em plataformas diferentes e aleatórias
    std::shuffle(plats.begin(), plats.end(), geradorAleatorio());

    // A planta 2 vai na última plataforma. Ela só divide espaço com uma lama
    // se houver uma lama em TODAS as plataformas (ex.: 3 lamas e 3 plataformas).
    const int total = static_cast<int>(plats.size());
    const bool plantaDivideComLama = (numLamas == total);

    for (int i = 0; i < numLamas; ++i) {
        sf::FloatRect b = plats[i]->getForma()->getGlobalBounds();
        const bool metade = (plantaDivideComLama && i == total - 1);

        // Na plataforma da planta a lama ocupa só a metade esquerda
        int xLama      = static_cast<int>(b.position.x) + (metade ? 5 : 10);
        int larguraLama = metade ? static_cast<int>(b.size.x / 2.f) - 5
                                 : static_cast<int>(b.size.x) - 20;

        criarPlataforma(xLama, static_cast<int>(b.position.y) - 10,
                        larguraLama, 10, new Lama());
    }

    // Capangas no chão
    criarCapanga(300.0f, 510.0f);
    criarCapanga(520.0f, 510.0f);

    // Planta 1 no chão
    Planta_Acida* planta1 = new Planta_Acida();
    planta1->setPosicao(680.0f, 510.0f);
    planta1->definirAlvo(pJogador);

    // Planta 2 sobre a última plataforma
    Planta_Acida* planta2 = new Planta_Acida();
    planta2->definirAlvo(pJogador);
    if (!plats.empty()) {
        sf::FloatRect b  = plats.back()->getForma()->getGlobalBounds();
        sf::Vector2f tam = planta2->getForma()->getSize();

        float xPlanta = plantaDivideComLama
            ? b.position.x + b.size.x - tam.x - 5.f          // canto direito
            : b.position.x + (b.size.x - tam.x) / 2.f;       // centralizada

        planta2->setPosicao(xPlanta, b.position.y - tam.y);
    }

    if (!registrarInimigo(planta1)) delete planta1;
    else pFisica->incluirProjetil(planta1->getProjetil());

    if (!registrarInimigo(planta2)) delete planta2;
    else pFisica->incluirProjetil(planta2->getProjetil());
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



void Fase_Forest::carregar() { std::cout << "[CARREGAR] Fase 1 carregada.\n"; }
