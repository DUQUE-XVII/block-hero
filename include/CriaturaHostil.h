#ifndef CRIATURA_HOSTIL_H
#define CRIATURA_HOSTIL_H

#include    "Jogador.h"
#include    "stdafx.h"
#include    "Personagem.h"
class CriaturaHostil: public Personagem{
protected:
    int id;
    int vidas;
    float posX, posY;
    int danoContato;

    Jogador* alvo; // O Enemy(Easy) vai ignorar isso, mas os outros usam.

public:
    CriaturaHostil();
    virtual ~CriaturaHostil();

    // Métodos puros
    virtual void executar() = 0;
    virtual void danificar(Jogador* pJogador) = 0;
    virtual void atualizar(){executar();} // Chamado pelo GerenciadorFisico para atualizar a lógica do inimigo

    void definirAlvo(Jogador* pJogador);
    bool estaVivo() const;
    void receberDano(int dano);

    void setPosicao(float novoX, float novoY);
    float getX() const;
    float getY() const;
    int getVida() const;
};

#endif
