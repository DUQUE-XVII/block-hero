#ifndef FASE_H
#define FASE_H

#include "stdafx.h"
#include "Ente.h"
#include "Jogador.h"
#include "CriaturaHostil.h"
#include "Plataforma.h"
#include "Gerenciador_CL.h"
#include "ListaEntidade.h"

class Fase : public Ente {
protected:
    int numeroFase;
    bool concluida;
    Jogador* pJogador;
    Gerenciador_CL* pFisica;

    ListaEntidades listaEntidades;
    std::vector<CriaturaHostil*> listaInimigos;
    std::vector<Plataforma*> listaPlataformas;

    void criarLimitesArena();

public:
    Fase(int num, Jogador* jogador = nullptr);
    virtual ~Fase();

    virtual void iniciarFase() = 0;
    virtual void executar() = 0;
    virtual void desenhar();

    virtual void salvar() = 0;
    virtual void carregar() = 0;

    Jogador* getJogador() const;
    int getNumeroFase() const;
    bool estaConcluida() const;
    std::vector<CriaturaHostil*> getInimigos() const;
};

#endif
