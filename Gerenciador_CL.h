#pragma once

#include    "Jogador.h"
#include    "GerenciadorGrafico.h"
#include    "stdafx.h"
#include    "Entidade.h"
#include    "Obstaculo.h"
#include    "CriaturaHostil.h"

class Projetil_Acido;

class Gerenciador_CL
{
private:
    Jogador* pJog1;
    list<Obstaculo*> LOs;
    vector<CriaturaHostil*> LIs;
    vector<Projetil_Acido*> LPs;

public:
    Gerenciador_CL();
    ~Gerenciador_CL();

    bool verificaColi(Entidade* pe1, Entidade* pe2) const;

    void colisaoObstaculo();
    void colisaoinimigo();
    void colisaoProjetil();
    void executar();

    void incluirObstaculo(Obstaculo* p);
    void getJogador(Jogador* jog);
    void incluirInimigos(CriaturaHostil* p);
    void incluirProjetil(Projetil_Acido* p);
};
