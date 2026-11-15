#ifndef CAPANGA_COGUMELO_H
#define CAPANGA_COGUMELO_H

#include    "CriaturaHostil.h"
#include    "stdafx.h"
#include    "Jogador.h"

class Capanga_Cogumelo : public CriaturaHostil {
private:
    int direcao; // 1 = Direita, -1 = Esquerda
    float velocidadeAndar;

public:
    Capanga_Cogumelo();
    ~Capanga_Cogumelo();


    void mover() override;
    void salvar() override;

    void executar(); // Apenas anda na direção atual
    void danificar(Jogador* pJogador);

    // O Gerenciador de Física vai chamar esse método quando o cogumelo bater na parede
    void inverterDirecao();
    bool estaVivo();


};

#endif
