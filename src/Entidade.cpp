#include "Entidade.h"

Entidade::Entidade()
    : x(0), y(0)
{
}

Entidade::~Entidade()
{
}

string Entidade::getDadosSalvos() const
{
    return Salvamento.str();
}

void Entidade::setPosicao(float novoX, float novoY)
{
    x = novoX;
    y = novoY;

    retangulo->setPosition({
        novoX,
        novoY
    });
}

void Entidade::salvarDataBuffer()
{
    Salvamento.str("");
    Salvamento.clear();

    Salvamento << x << " " << y;
}
