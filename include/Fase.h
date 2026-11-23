#ifndef FASE_H
#define FASE_H

#include    "stdafx.h"
#include    "Ente.h"
#include    "Jogador.h"
#include    "CriaturaHostil.h"
#include    "Plataforma.h"
#include    "Gerenciador_CL.h"
#include    "ListaEntidade.h"
#include    "Capanga_Cogumelo.h"

class Fase : public Ente {
     protected:
        int numeroFase;
        bool concluida;

        int maxInimigos;
        int maxObstaculos;

        Jogador* pJogador;
        Gerenciador_CL* pFisica;

        ListaEntidades listaEntidades;
        std::vector<CriaturaHostil*> listaInimigos;
        std::vector<Obstaculo*> listaPlataformas;
        std::vector<Plataforma*> gerarPlataformasAleatorias(int quantidade);

        void criarLimitesArena();

        void criarCapanga(float x, float y);
        void criarPlataforma(float x, float y, int largura, int altura, Obstaculo* plataforma);

        static std::mt19937& geradorAleatorio();
        static int sortear(int minimo, int maximo);

    public:
        Fase(int num, Jogador* jogador,int limiteInimigos, int limiteObstaculos);
        virtual ~Fase();

        virtual void iniciarFase() = 0;
        virtual void executar() = 0;
        virtual void desenhar();

        virtual void salvar() = 0;
        virtual void carregar() = 0;

        Jogador* getJogador() const;
        int getNumeroFase() const;
        bool estaConcluida() const;
        bool registrarInimigo(CriaturaHostil* inimigo);
       vector<CriaturaHostil*> getInimigos() const;
};

#endif
