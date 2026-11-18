#pragma once

#include    "stdafx.h"
#include    "GerenciadorGrafico.h"
#include    "Jogador.h"
#include    "Ente.h"
#include    "Fase.h"
#include    "Fase_Forest.h"
#include    "Fase_Boss.h"

class Jogo {
private:
    Jogador pJog1;
    GerenciadorGrafico pGG;
    Fase* faseAtual;

public:
    Jogo();
    ~Jogo();
    void executar();
};
