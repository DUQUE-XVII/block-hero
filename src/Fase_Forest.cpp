#include "Fase_Forest.h"
#include "Planta_Acida.h"
#include "Projetil_Acido.h"
#include "Lama.h"
#include <iostream>

Fase_Forest::Fase_Forest(Jogador* jogador)
    : Fase(1, jogador, 10, 15), // comporta 4 bordas + até 5 plataformas + até 5 lamas
      maxCogumelos(5),
      maxPlantas(4)
{
}

Fase_Forest::~Fase_Forest() {}

void Fase_Forest::iniciarFase()
{
    std::cout << "[FASE 1] Iniciando a Floresta...\n";

    if (pJogador != nullptr)
    {
        pJogador->setX(100.0f);
        pJogador->setY(500.0f);
        pFisica->getJogador(pJogador);
        listaEntidades.incluir(pJogador);
    }

    criarLimitesArena();

    int numPlats = sortear(3, 5);
    int numLamas = sortear(3, 5);

    list<Plataforma*> plats = gerarPlataformasAleatorias(numPlats);

    // Embaralha as plataformas para distribuir lamas e plantas de forma variada
    list<Plataforma*> embaralhadas;
    while (!plats.empty())
    {
        int idx = sortear(0, static_cast<int>(plats.size()) - 1);
        auto it = std::next(plats.begin(), idx);
        embaralhadas.push_back(*it);
        plats.erase(it);
    }
    plats = embaralhadas;

    list<Plataforma*> fixas;
    auto itPlat = plats.begin();
    int livreChaoX = 180;

    // 1. Cria de 3 a 5 Lamas (nas plataformas ou espaçadas no chão)
    for (int i = 0; i < numLamas; ++i)
    {
        bool cabeNoChao = (livreChaoX <= 650);
        bool temPlatLivre = (itPlat != plats.end());
        bool naPlataforma = temPlatLivre && (!cabeNoChao || sortear(0, 1) == 1);

        if (naPlataforma)
        {
            Plataforma* platAtual = *itPlat++;
            fixas.push_back(platAtual);

            sf::FloatRect b = platAtual->getForma()->getGlobalBounds();
            int larguraLama = std::min(80, static_cast<int>(b.size.x) - 20);
            int xLama = static_cast<int>(b.position.x + (b.size.x - larguraLama) / 2.f);

            criarPlataforma(static_cast<float>(xLama), b.position.y - 10.f,
                            larguraLama, 10, new Lama());
        }
        else
        {
            int larguraLama = sortear(55, 80);
            int xMax = std::max(livreChaoX, 730 - larguraLama);
            int xLama = sortear(livreChaoX, xMax);

            criarPlataforma(static_cast<float>(xLama), 550.f,
                            larguraLama, 10, new Lama());

            livreChaoX = xLama + larguraLama + 35;
        }
    }

    // 2. Cria de 3 a 4 Plantas Ácidas (nas plataformas livres restantes ou no chão)
    int qtdPlantas = sortear(3, maxPlantas);
    int livrePlantaChaoX = 240;

    for (int i = 0; i < qtdPlantas; ++i)
    {
        Planta_Acida* planta = new Planta_Acida();
        float altPlanta = planta->getForma()->getGlobalBounds().size.y;
        float largPlanta = planta->getForma()->getGlobalBounds().size.x;

        if (itPlat != plats.end())
        {
            Plataforma* platAtual = *itPlat++;
            fixas.push_back(platAtual);

            sf::FloatRect b = platAtual->getForma()->getGlobalBounds();
            float px = b.position.x + (b.size.x - largPlanta) / 2.f;
            float py = b.position.y - altPlanta;
            planta->setPosicao(px, py);
        }
        else
        {
            int xMax = std::max(livrePlantaChaoX, 720 - static_cast<int>(largPlanta));
            float px = static_cast<float>(sortear(livrePlantaChaoX, xMax));
            float py = 560.f - altPlanta;
            planta->setPosicao(px, py);

            livrePlantaChaoX = std::min(680, static_cast<int>(px + largPlanta + 60.f));
        }

        planta->definirAlvo(pJogador);
        if (registrarInimigo(planta))
            pFisica->incluirProjetil(planta->getProjetil());
        else
            delete planta;
    }

    // 3. Torna móveis apenas as plataformas que ficaram livres
    tornarPlataformasMoveis(plats, fixas);

    // 4. Cria de 3 a 5 Capangas Cogumelo
    int qtdCogumelos = sortear(3, maxCogumelos);
    espalharCapangas(qtdCogumelos, plats);
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
