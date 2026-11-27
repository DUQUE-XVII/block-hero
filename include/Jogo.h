#pragma once

#include "stdafx.h"
#include "GerenciadorGrafico.h"
#include "Jogador.h"
#include "Ente.h"
#include "Menu.h"
#include "Ranking.h"
#include "Fase.h"
#include "Fase_Forest.h"
#include "Fase_Boss.h"

class Jogo {
private:
    enum class Estado {
        MENU,
        JOGANDO,
        PAUSADO,
        RANKING
    };

    Jogador pJog1;
    GerenciadorGrafico pGG;
    Menu menu;
    Menu menuPausa;
    Ranking ranking;
    Fase* faseAtual;
    Estado estadoAtual;

    bool teclaSalvarAnterior;
    bool teclaEscAnterior;
    std::string mensagemPausa;

    void iniciarFaseEscolhida(int opcao);
    void carregarJogoSalvo();

public:
    Jogo();
    ~Jogo();
    void executar();
};
