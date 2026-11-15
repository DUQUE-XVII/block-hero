
#include "CriaturaHostil.h"

CriaturaHostil::CriaturaHostil() : id(0), vidas(10), posX(0), posY(0), danoContato(1), alvo(nullptr)
{

}
CriaturaHostil::~CriaturaHostil() {}


void CriaturaHostil::definirAlvo(Jogador* pJogador) {
    alvo = pJogador;
}
int CriaturaHostil::getVida() const{return vidas;}
bool CriaturaHostil::estaVivo() const { return vidas > 0; }
void CriaturaHostil::receberDano(int dano) { vidas -= dano; }
float CriaturaHostil::getX() const { return posX; }
float CriaturaHostil::getY() const { return posY; }
