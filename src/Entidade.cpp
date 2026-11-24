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

void Entidade::salvarDataBuffer()
{
    Salvamento.str("");
    Salvamento.clear();

    Salvamento << x << " " << y;
}
