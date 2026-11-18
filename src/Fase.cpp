#include "Fase.h"

Fase::Fase(int num, Jogador* jogador)
    : numeroFase(num), concluida(false), pJogador(jogador) {
    pFisica = new Gerenciador_CL();
}

Fase::~Fase() {
    delete pFisica;
    pFisica = nullptr;

    for (CriaturaHostil* inimigo : listaInimigos) {
        delete inimigo;
    }
    listaInimigos.clear();

    for (Plataforma* plat : listaPlataformas) {
        delete plat;
    }
    listaPlataformas.clear();
}

void Fase::criarLimitesArena() {
    // Mesmas bordas usadas originalmente em Jogo.cpp (janela 800x600)
    Plataforma* chao = new Plataforma(0, 560, 800, 40);
    Plataforma* teto = new Plataforma(0, 0, 800, 20);
    Plataforma* paredeEsquerda = new Plataforma(0, 0, 20, 600);
    Plataforma* paredeDireita = new Plataforma(780, 0, 20, 600);

    listaPlataformas.push_back(chao);
    listaPlataformas.push_back(teto);
    listaPlataformas.push_back(paredeEsquerda);
    listaPlataformas.push_back(paredeDireita);

    for (Plataforma* p : listaPlataformas) {
        pFisica->incluirObstaculo(p);
        listaEntidades.incluir(p);
    }
}

void Fase::desenhar() {
    if (pJogador != nullptr && pJogador->estaVivo()) {
        pJogador->desenhar();
    }

    for (CriaturaHostil* inimigo : listaInimigos) {
        if (inimigo != nullptr && inimigo->estaVivo()) {
            inimigo->desenhar();
        }
    }

    for (Plataforma* plat : listaPlataformas) {
        if (plat != nullptr) {
            plat->desenhar();
        }
    }
}

Jogador* Fase::getJogador() const { return pJogador; }
int Fase::getNumeroFase() const { return numeroFase; }
bool Fase::estaConcluida() const { return concluida; }
std::vector<CriaturaHostil*> Fase::getInimigos() const { return listaInimigos; }
