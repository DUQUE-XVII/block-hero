#include "Gerenciador_CL.h"
#include "Projetil_Acido.h"

Gerenciador_CL::Gerenciador_CL()
    : pJog1(nullptr)
{
}

Gerenciador_CL::~Gerenciador_CL()
{

}

bool Gerenciador_CL::verificaColi(Entidade* pe1, Entidade* pe2) const
{
    if (pe1 == nullptr || pe2 == nullptr ||
        pe1->getForma() == nullptr || pe2->getForma() == nullptr)
        return false;

    return pe1->getForma()->getGlobalBounds()
        .findIntersection(pe2->getForma()->getGlobalBounds()).has_value();
}

void Gerenciador_CL::colisaoObstaculo()
{
    if (pJog1 == nullptr)
        return;

    for (Obstaculo* pObstaculo : LOs)
    {
        if (pObstaculo == nullptr || !verificaColi(pJog1, pObstaculo))
            continue;
        if(pObstaculo->reduzVelocidade())
            pJog1->reduzirVelocidade();
        else
            pJog1->restaurarVelocidade();
        pObstaculo->obstaculizar(pJog1);

    }
}

void Gerenciador_CL::getJogador(Jogador* jog)
{
    pJog1 = jog;
}

void Gerenciador_CL::incluirObstaculo(Obstaculo* p)
{
    if (p != nullptr)
        LOs.push_back(p);
}

void Gerenciador_CL::incluirInimigos(CriaturaHostil* p)
{
    if (p != nullptr)
        LIs.push_back(p);
}

void Gerenciador_CL::incluirProjetil(Projetil_Acido* p)
{
    if (p != nullptr)
        LPs.push_back(p);
}

void Gerenciador_CL::colisaoinimigo()
{
    if (pJog1 == nullptr)
        return;

    for (CriaturaHostil* pInimigo : LIs)
    {
        if (pInimigo == nullptr || !pInimigo->estaVivo())
            continue;

        if (!verificaColi(pJog1, pInimigo))
            continue;

        sf::FloatRect jogador = pJog1->getForma()->getGlobalBounds();
        sf::FloatRect inimigo = pInimigo->getForma()->getGlobalBounds();

        const bool sobrepoeX =
            jogador.position.x + jogador.size.x > inimigo.position.x &&
            jogador.position.x < inimigo.position.x + inimigo.size.x;

        const bool caiuSobre =
            pJog1->getVelocidadeY() > 0.f &&
            pJog1->getYAnterior() + jogador.size.y <= inimigo.position.y &&
            jogador.position.y + jogador.size.y >= inimigo.position.y &&
            sobrepoeX;

        if (caiuSobre)
        {
            pJog1->setY(inimigo.position.y - jogador.size.y);
            pInimigo->receberDano(2);
            pJog1->quicar();
        }
        else
        {
            pInimigo->danificar(pJog1);
        }
    }
}

void Gerenciador_CL::colisaoProjetil()
{
    if (pJog1 == nullptr || !pJog1->estaVivo())
        return;

    for (Projetil_Acido* pProjetil : LPs)
    {
        if (pProjetil == nullptr || !pProjetil->estaAtivo())
            continue;

        if (verificaColi(pJog1, pProjetil))
        {
            pJog1->receberDano(pProjetil->getDano());
            pProjetil->desativar();
        }
    }
}

void Gerenciador_CL::executar()
{
    colisaoObstaculo();
    colisaoinimigo();
    colisaoProjetil();
}
