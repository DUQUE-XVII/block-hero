#pragma once

template <class TL>
class Lista
{
private:

    template <class TE>
    class Elemento
    {
    private:
        TE pInfo{};
        Elemento<TE>* pProx;

    public:
        Elemento() : pProx(nullptr) {}
        ~Elemento() = default;

        void incluir(const TE& p) { pInfo = p; }
        void setProx(Elemento<TE>* p) { pProx = p; }
        Elemento<TE>* getProx() const { return pProx; }
        TE getInfo() const { return pInfo; }
    };

    Elemento<TL>* pPrimeiro;
    Elemento<TL>* pUltimo;
    int quantidade;

    // Impede cópia superficial da lista.
    Lista(const Lista&) = delete;
    Lista& operator=(const Lista&) = delete;

public:

    Lista() : pPrimeiro(nullptr), pUltimo(nullptr), quantidade(0) {}

    ~Lista()
    {
        limpar();
    }

    void incluir(const TL& p)
    {
        Elemento<TL>* novo = new Elemento<TL>();
        novo->incluir(p);

        if(pPrimeiro == nullptr)
        {
            pPrimeiro = novo;
            pUltimo = novo;
        }
        else
        {
            pUltimo->setProx(novo);
            pUltimo = novo;
        }
        ++quantidade;
    }

    void limpar()
    {
        Elemento<TL>* atual = pPrimeiro;

        while(atual != nullptr)
        {
            Elemento<TL>* proximo = atual->getProx();
            delete atual;
            atual = proximo;
        }

        pPrimeiro = nullptr;
        pUltimo = nullptr;
        quantidade = 0;
    }

    int tamanho() const { return quantidade; }

    template <class Funcao>
    void percorrer(Funcao acao) const
    {
        Elemento<TL>* atual = pPrimeiro;

        while(atual != nullptr)
        {
            acao(atual->getInfo());
            atual = atual->getProx();
        }
    }

    bool vazia() const
    {
        return pPrimeiro == nullptr;
    }
};
