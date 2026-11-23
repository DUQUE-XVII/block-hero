#include "Fase_Boss.h"
#include "Boitata.h"
#include "Projetil_Acido.h"


Fase_Boss::Fase_Boss(Jogador* jogador)
    : Fase(2, jogador, 3, 5) {}

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

    // Poças de lava (1 a 2) e plataformas dividem o limite maxObstaculos
    int numLavas = sortear(1, 2);
    gerarPlataformasAleatorias(maxObstaculos - numLavas);   // 4..3 plataformas

    // Poças no chão (topo do chão = y 560), longe do spawn do herói (x 100..140)
    int livreA_partirDe = 200;
    for (int i = 0; i < numLavas; ++i) {
        int largura = sortear(60, 100);
        int restantes = numLavas - i - 1;
        // reserva espaço para as poças que ainda faltam
        int xMaximo = 760 - largura - restantes * 160;
        int x = sortear(livreA_partirDe, xMaximo);

        criarPlataforma(x, 548, largura, 12, new Lava());
        livreA_partirDe = x + largura + 60;   // 60 px de vão até a próxima
    }

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
