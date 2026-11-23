#include    "GerenciadorGrafico.h"
#include    "Ente.h"

GerenciadorGrafico::GerenciadorGrafico()
    : obj(sf::VideoMode({800, 600}), "BLOCK HERO"),
      fonteCarregada(false)
{
    obj.setFramerateLimit(60);

    const char* caminhos[] = {"assets/Fonte/Fonte.TTF"};

    for (const char* caminho : caminhos) {
        if (fonte.openFromFile(caminho)) {
            fonteCarregada = true;
            break;
        }
    }

    if (!fonteCarregada)
        std::cout << "[GG] Nenhuma fonte encontrada. Coloque um .ttf em assets/Fonte/fonte.ttf\n";
}


GerenciadorGrafico::~GerenciadorGrafico(){

}
void GerenciadorGrafico::desenharTexto(const std::string& conteudo,
float x, float y, unsigned int tamanho)
{
    if (!fonteCarregada)
        return;

    sf::Text texto(fonte, conteudo, tamanho);
    texto.setFillColor(sf::Color::White);
    texto.setOutlineColor(sf::Color::Black);
    texto.setOutlineThickness(2.f);
    texto.setPosition({x, y});

    obj.draw(texto);
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
