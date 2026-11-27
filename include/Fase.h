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

    int numInimigos;
    int numObstaculos;

    Jogador* pJogador;
    Gerenciador_CL* pFisica;

    ListaEntidades listaEntidades;

    list<Plataforma*> gerarPlataformasAleatorias(int quantidade);
    bool todosInimigosMortos() const;
    void criarLimitesArena();

    void criarCapanga(float x, float y, float limEsq = 25.f, float limDir = 775.f);
    void espalharCapangas(int quantidade, const list<Plataforma*>& plats);

    void criarPlataforma(float x, float y, int largura, int altura, Obstaculo* plataforma);

    static std::mt19937& geradorAleatorio();
    static int sortear(int minimo, int maximo);

    void tornarPlataformasMoveis(const list<Plataforma*>& plats,const list<Plataforma*>& fixas = {});
    bool carregarArquivos(const std::string& pasta = "saves/");

public:
    Fase(int num, Jogador* jogador, int limiteInimigos, int limiteObstaculos);
    virtual ~Fase();

    virtual void iniciarFase() = 0;
    virtual void executar() = 0;
    virtual void desenhar();

    virtual void salvar(const std::string& pasta = "saves/");
    virtual void carregar() =0;

    Jogador* getJogador() const;
    int getNumeroFase() const;
    bool estaConcluida() const;
    bool registrarInimigo(CriaturaHostil* inimigo);
};

#endif
