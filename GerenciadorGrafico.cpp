#include    "GerenciadorGrafico.h"
#include    "Ente.h"

#include "GerenciadorGrafico.h"
#include "Ente.h"

GerenciadorGrafico::GerenciadorGrafico()
    : obj(sf::VideoMode({800, 600}), "BLOCK HERO")
{

}

GerenciadorGrafico::~GerenciadorGrafico(){

}

void GerenciadorGrafico::desenharEnte(Ente* pE){

    if (pE != nullptr && pE->getForma() != nullptr)
        {
            obj.draw(*pE->getForma());
        }
}

sf::RenderWindow& GerenciadorGrafico::getJanela(){
    return obj;
}
