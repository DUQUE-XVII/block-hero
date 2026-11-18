#include    "Obstaculo.h"

Obstaculo::Obstaculo()
{
    dano = false;
}

Obstaculo::~Obstaculo()
{
}

void Obstaculo::salvarDataBuffer()
{
    Entidade::salvarDataBuffer();

    Salvamento << " " << dano;
}
