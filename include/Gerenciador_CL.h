#pragma once

#include "Jogador.h"
#include "GerenciadorGrafico.h"
#include "stdafx.h"
#include "Entidade.h"
#include "Obstaculo.h"
#include "CriaturaHostil.h"

class Projetil_Acido;

class Gerenciador_CL
{
private:
    Jogador* pJog1;
    list<Obstaculo*> LOs;
    list<CriaturaHostil*> LIs;
    list<Projetil_Acido*> LPs;

public:
    Gerenciador_CL();
    ~Gerenciador_CL();

    bool verificaColi(Entidade* pe1, Entidade* pe2) const;

    void colisaoObstaculo();
    void colisaoinimigo();
    void colisaoProjetil();
    void executar();
    void colisaoInimigoObstaculo();

    void salvarArquivos(const std::string& pasta = "saves/") const;
    void limparListas();

    void incluirObstaculo(Obstaculo* p);
    void getJogador(Jogador* jog);
    void incluirInimigos(CriaturaHostil* p);
    void incluirProjetil(Projetil_Acido* p);

    // Métodos auxiliares para a Fase sem precisar alterar ListaEntidades
    void desenharEntidades() const;
    bool todosInimigosMortos() const;
    int totalEntidades() const;
    void salvarEntidades(std::ostream& arquivo) const;
    void destruirEntidades();
    const list<Obstaculo*>& getObstaculos() const;
};
