#ifndef CAPANGA_COGUMELO_H
#define CAPANGA_COGUMELO_H

#include "CriaturaHostil.h"
#include "stdafx.h"
#include "Jogador.h"

class Capanga_Cogumelo : public CriaturaHostil {
private:
    int direcao; // 1 = Direita, -1 = Esquerda
    float velocidadeAndar;
    float limiteEsquerdo;
    float limiteDireito;

public:
    Capanga_Cogumelo();
    ~Capanga_Cogumelo();

    void mover() override;
    void salvar() override;

    void executar();
    void danificar(Jogador* pJogador);

    void inverterDirecao();
    bool estaVivo();
    void definirLimitesPatrulha(float esq, float dir);
    void setEstado(int v, int dir);
};

#endif
