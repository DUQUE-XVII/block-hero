#pragma once

#include    "stdafx.h"
#include    "GerenciadorGrafico.h"
#include    "Jogador.h"
#include    "Ente.h"
#include    "Plataforma.h"
#include    "Gerenciador_CL.h"
#include    "Capanga_Cogumelo.h"
#include    "Planta_Acida.h"
#include    "Boitata.h"

class Jogo{

    private:

        Jogador pJog1;
        GerenciadorGrafico pGG;
        Gerenciador_CL pGCL;

        Plataforma chao;
        Plataforma teto;
        Plataforma paredeEsquerda;
        Plataforma paredeDireita;

        Plataforma plataforma1;
        Plataforma plataforma2;

        Capanga_Cogumelo pCog;
        Planta_Acida pPlanta;
        Boitata pBoitata;


    public:

        Jogo();
        ~Jogo();
        void executar();

};


