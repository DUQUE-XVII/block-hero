#pragma once

#include "CriaturaHostil.h"

class Projetil_Acido;

class Planta_Acida : public CriaturaHostil
{
private:
    int tempoRecarga;
    int contadorTempo;
    Projetil_Acido* pAcido;
    int pontosAoMorrer;

public:
    Planta_Acida();
    virtual ~Planta_Acida();

    void executar() override;
    void mover() override; // A planta é fixa; não precisa se deslocar.
    void salvar() override;
    void danificar(Jogador* pJogador) override;

    Projetil_Acido* getProjetil() const;
};
