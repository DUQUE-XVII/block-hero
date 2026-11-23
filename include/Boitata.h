#ifndef BOITATA_H
#define BOITATA_H

#include "CriaturaHostil.h"

class Projetil_Acido;

class Boitata : public CriaturaHostil
{
private:
    float velocidadePerseguicao;
    int tempoRecargaFogo;
    int contadorTempoFogo;
    Projetil_Acido* pFogo;
    int pontosAoMorrer;

public:
    Boitata();
    virtual ~Boitata();

    void executar() override;
    void mover() override;
    void salvar() override;
    void danificar(Jogador* pJogador) override;

    Projetil_Acido* getProjetil() const;
};

#endif
