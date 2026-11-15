#include "Jogo.h"
#include "Projetil_Acido.h"

Jogo::Jogo()
    : chao(0, 560, 800, 40),
      teto(0, 0, 800, 20),
      paredeEsquerda(0, 0, 20, 600),
      paredeDireita(780, 0, 20, 600),
      plataforma1(150, 430, 200, 20),
      plataforma2(450, 330, 180, 20)
{

    Ente::setGG(&pGG);

    pGCL.getJogador(&pJog1);


    pGCL.incluirObstaculo(&chao);
    pGCL.incluirObstaculo(&teto);
    pGCL.incluirObstaculo(&paredeEsquerda);
    pGCL.incluirObstaculo(&paredeDireita);
    pGCL.incluirObstaculo(&plataforma1);
    pGCL.incluirObstaculo(&plataforma2);


    pPlanta.definirAlvo(&pJog1);
    pGCL.incluirInimigos(&pCog);
    pGCL.incluirInimigos(&pPlanta);


    pGCL.incluirProjetil(pPlanta.getProjetil());
    pBoitata.definirAlvo(&pJog1);

    pGCL.incluirInimigos(&pBoitata);

    pGCL.incluirProjetil(pBoitata.getProjetil());
}

Jogo::~Jogo()
{
}

void Jogo::executar()
{
    while (pGG.getJanela().isOpen())
    {
        while (const auto evento = pGG.getJanela().pollEvent())
        {
            if (evento->is<sf::Event::Closed>())
                pGG.getJanela().close();
        }

        pGG.getJanela().clear(sf::Color::Black);


        if (pJog1.estaVivo()){
            pJog1.executar();
            pJog1.desenhar();
        }
        if (pCog.estaVivo()){
            pCog.executar();
            pCog.desenhar();
        }
        if (pPlanta.estaVivo()){
            pPlanta.executar();
            pPlanta.desenhar();
        }

        if (pPlanta.getProjetil()->estaAtivo()){
            pPlanta.getProjetil()->desenhar();
        }
        if(pBoitata.estaVivo()){
            pBoitata.executar();
            pBoitata.desenhar();
        }

        if(pBoitata.getProjetil()->estaAtivo())
            pBoitata.getProjetil()->desenhar();

        pGCL.executar();

        chao.desenhar();
        teto.desenhar();
        paredeEsquerda.desenhar();
        paredeDireita.desenhar();
        plataforma1.desenhar();
        plataforma2.desenhar();

        pGG.getJanela().display();
    }
}
