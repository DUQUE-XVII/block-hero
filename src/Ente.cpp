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

 bool Ente::carregarTextura(const std::string& caminho, const sf::IntRect& area)
{
    if (!textura.loadFromFile(caminho, false, area))
        return false;                       // arquivo não achado

    textura.setSmooth(true);
    retangulo->setTexture(&textura, true);  // true = ajusta ao tamanho da textura
    retangulo->setFillColor(sf::Color::White); // evita "tingir" a imagem
    return true;
}
