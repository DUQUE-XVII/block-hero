#pragma once

#include "CriaturaHostil.h"

class Projetil_Acido;

class Planta_Acida : public CriaturaHostil
{
private:
    int tempoRecarga;
    int contadorTempo;
    Projetil_Acido* pAcido;


public:
    Planta_Acida();
    virtual ~Planta_Acida();

    void executar() override;
    void mover() override; // A planta é fixa; não precisa se deslocar.
    void setEstado(int v, int cont);

    void salvar() override;
    void danificar(Jogador* pJogador) override;
    void restaurar(float px, float py, float vx, bool isAtivo);
    Projetil_Acido* getProjetil() const;
};
