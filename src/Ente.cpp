#include    "Ente.h"

GerenciadorGrafico* Ente::pGG = nullptr;
Ente::Ente()
{
    retangulo = new sf::RectangleShape();
}

Ente::~Ente()
{
    delete retangulo;
    retangulo = nullptr;
}

void Ente::executar(){
}

void Ente::desenhar(){
    if (pGG != nullptr) {
        pGG->desenharEnte(this);
    }

}

void Ente::setGG(GerenciadorGrafico* GG){
    pGG = GG;

}

sf::RectangleShape* Ente::getForma(){
    return retangulo;

 }
