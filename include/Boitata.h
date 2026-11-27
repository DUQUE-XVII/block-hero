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


public:
    Boitata();
    virtual ~Boitata();

    void executar() override;
    void mover() override;

    void salvar() override;
    void danificar(Jogador* pJogador) override;
    void setEstado(int v, int cont);

    Projetil_Acido* getProjetil() const;
};

#endif
