#include    "Jogo.h"

Jogo::Jogo(){
}

Jogo::~Jogo(){
}

void Jogo::executar(){

    while(pGG.getJanela().isOpen()){

        while(const auto evento =pGG.getJanela().pollEvent()){

            if (evento->is<sf::Event::Closed>())
            {
                    pGG.getJanela().close();
            }
        }
        pGG.getJanela().clear(sf::Color::Black);
        pGG.getJanela().display();

    }
}
