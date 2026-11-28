#include "Fase_Boss.h"
#include "Projetil_Acido.h"
#include "Lava.h" // <-- Adicione esta linha
#include <iostream>

Fase_Boss::Fase_Boss(Jogador* jogador)
    : Fase(2, jogador, 10, 15),
      maxChefoes(4),
      maxCogumelos(5),
      chefoesRestantes(0),
      chefaoAtual(nullptr)
{
}

Fase_Boss::~Fase_Boss() {}

void Fase_Boss::invocarProximoChefao()
{
    Boitata* boss = new Boitata();
    boss->setPosicao(600.0f, 200.0f);
    boss->definirAlvo(pJogador);

    if (!registrarInimigo(boss))
    {
        delete boss;
        chefaoAtual = nullptr;
        return;
    }

    pFisica->incluirProjetil(boss->getProjetil());
    chefaoAtual = boss;
    chefoesRestantes--;

    std::cout << "[FASE 2] Um Boitata apareceu! Restantes na fila: "
              << chefoesRestantes << "\n";
}

void Fase_Boss::iniciarFase()
{
    std::cout << "[FASE 2] Iniciando a Caverna do Boitata...\n";

    if (pJogador != nullptr)
    {
        pJogador->setX(100.0f);
        pJogador->setY(500.0f);
        pFisica->getJogador(pJogador);
        listaEntidades.incluir(pJogador);
    }

    criarLimitesArena();

    int numPlats = sortear(3, 5);
    int numLavas = sortear(3, 5);

    list<Plataforma*> plats = gerarPlataformasAleatorias(numPlats);

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
    int livreChaoX = 200;

    for (int i = 0; i < numLavas; ++i)
    {
       list<Plataforma*> fixas;
    auto itPlat = plats.begin();
    int livreChaoX = 180; // começa logo após o spawn do jogador (x = 100..140)

    for (int i = 0; i < numLavas; ++i)
    {
        bool cabeNoChao = (livreChaoX <= 660);
        bool temPlatLivre = (itPlat != plats.end());

        // Vai para plataforma se não couber mais no chão ou por sorteio (50%)
        bool naPlataforma = temPlatLivre && (!cabeNoChao || sortear(0, 1) == 1);

        if (naPlataforma)
        {
            Plataforma* platAtual = *itPlat++;
            fixas.push_back(platAtual);

            sf::FloatRect b = platAtual->getForma()->getGlobalBounds();
            int larguraLava = std::min(75, static_cast<int>(b.size.x) - 20);
            int xLava = static_cast<int>(b.position.x + (b.size.x - larguraLava) / 2.f);

            criarPlataforma(static_cast<float>(xLava), b.position.y - 12.f,
                            larguraLava, 12, new Lava());
        }
        else
        {
            int larguraLava = sortear(50, 70);
            int xMax = std::max(livreChaoX, 730 - larguraLava);
            int xLava = sortear(livreChaoX, xMax);

            criarPlataforma(static_cast<float>(xLava), 548.f,
                            larguraLava, 12, new Lava());

            livreChaoX = xLava + larguraLava + 35;
        }
    }
    }

    tornarPlataformasMoveis(plats, fixas);

    // Mínimo 3 cogumelos (aleatório até maxCogumelos)
    int qtdCogumelos = sortear(3, maxCogumelos);
    espalharCapangas(qtdCogumelos, plats);

    // Mínimo 3 chefões (aleatório até maxChefoes), nascendo 1 por vez
    chefoesRestantes = sortear(3, maxChefoes);
    chefaoAtual = nullptr;
    invocarProximoChefao();
}

void Fase_Boss::executar()
{
    if (pJogador == nullptr || !pJogador->estaVivo())
        return;

    listaEntidades.percorrer();
    pFisica->executar();
    desenhar();

    // Quando o chefão atual morre, invoca o próximo da fila
    if (chefoesRestantes > 0)
    {
        if ((chefaoAtual != nullptr && !chefaoAtual->estaVivo()) ||
            (chefaoAtual == nullptr && todosInimigosMortos()))
        {
            invocarProximoChefao();
        }
    }

    if (chefoesRestantes == 0 && todosInimigosMortos())
        concluida = true;
}

void Fase_Boss::salvar(const std::string& pasta)
{
    Fase::salvar(pasta);

    // Grava também quantos chefões ainda faltam nascer em fase.txt
    std::ofstream arqFase(pasta + "fase.txt");
    if (arqFase.is_open())
        arqFase << numeroFase << " " << concluida << " " << chefoesRestantes << "\n";
}

void Fase_Boss::carregar()
{
    numeroFase = 2;
    chefaoAtual = nullptr;
    chefoesRestantes = 0;

    std::ifstream arqFase("saves/fase.txt");
    int num = 2;
    bool conc = false;
    if (arqFase.is_open())
        arqFase >> num >> conc >> chefoesRestantes;

    carregarArquivos("saves/");
}
