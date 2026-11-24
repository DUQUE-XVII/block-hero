#include "Projetil_Acido.h"

Projetil_Acido::Projetil_Acido()
    : velX(0.f), dano(1), ativo(false)
{
    retangulo->setSize({14.f, 8.f});
    retangulo->setFillColor(sf::Color(80, 220, 40));
    retangulo->setPosition({-100.f, -100.f});
}

Projetil_Acido::~Projetil_Acido()
{
}

void Projetil_Acido::ativar(float xInicial, float yInicial, float direcaoX)
{
    x = xInicial;
    y = yInicial;
    velX = direcaoX * 5.f;
    ativo = true;
    retangulo->setPosition({x, y});
}

void Projetil_Acido::executar()
{
    if (!ativo)
        return;

    x += velX;
    retangulo->setPosition({x, y});

    // Desativa o projétil quando ele sai da área de jogo.
    if (x + retangulo->getSize().x < 0.f || x > 800.f)
        desativar();
}

void Projetil_Acido::desativar()
{
    ativo = false;
    retangulo->setPosition({-100.f, -100.f});
}

bool Projetil_Acido::estaAtivo() const
{
    return ativo;
}

int Projetil_Acido::getDano() const
{
    return dano;
}

void Projetil_Acido::salvar()
{
    salvarDataBuffer();

    Salvamento << " " << velX
               << " " << dano
               << " " << ativo;
}
