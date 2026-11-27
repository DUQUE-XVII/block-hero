#include    "Lama.h"
#include    "Gerenciador_CL.h"
Lama::Lama(){

     retangulo->setSize({30.f , 1.f});
     retangulo->setFillColor(sf::Color(139, 69, 19));
     reduzir =2.f;

}

Lama::~Lama(){

}

void Lama::obstaculizar(Jogador* pJogador){
    if(Lerdo)
        pJogador->reduzirVelocidade(reduzir /2);
    else
        pJogador->reduzirVelocidade(reduzir);
}

void Lama::executar(){
    Lerdo = rand() %100;
}

void Lama::salvar(){


    salvarDataBuffer();

    sf::Vector2f tamanho = retangulo->getSize();

    Salvamento << " "
               << tamanho.x << " "
               << tamanho.y;

}

bool Lama::reduzVelocidade(){
    return true;
}


