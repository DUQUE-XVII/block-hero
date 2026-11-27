#pragma once

#include "stdafx.h"
#include "GerenciadorGrafico.h"

class Ranking
{
private:
    struct Registro {
        std::string nome;
        int pontos;
    };

    std::vector<Registro> registros;
    std::string caminhoArquivo;

    void carregarArquivo();
    void salvarArquivo() const;

public:
    Ranking(const std::string& arquivo = "saves/ranking.txt");
    ~Ranking() = default;

    void adicionarPontuacao(const std::string& nome, int pontos);
    void desenhar(GerenciadorGrafico& pGG) const;
};
