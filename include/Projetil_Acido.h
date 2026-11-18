#pragma once

#include "Entidade.h"

// O projétil é uma Entidade para poder participar do sistema de colisões.
class Projetil_Acido : public Entidade
{
private:
    float velX;
    int dano;
    bool ativo;

public:
    Projetil_Acido();
    virtual ~Projetil_Acido();

    void executar() override;
    void salvar() override;

    void ativar(float xInicial, float yInicial, float direcaoX);
    void desativar();
    bool estaAtivo() const;
    int getDano() const;
};
