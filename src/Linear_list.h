#include <ostream>
#include <iostream>
using namespace std;
#ifndef REALIZZAZIONI_LINEAR_LIST_H
#define REALIZZAZIONI_LINEAR_LIST_H

/*
 * Dato astratto che rappresenta una lista
 */
template <class T, class P>
class Linear_List {
public:
    typedef T tipoelem;
    typedef P posizione;

    virtual void creaLista() =0;
    virtual bool listaVuota() const=0;
    virtual tipoelem leggiLista(posizione) const=0;
    virtual void scriviLista(const tipoelem&, posizione) =0;
    virtual posizione primoLista() const =0;
    virtual bool fineLista(posizione)  const=0;
    virtual posizione succLista(posizione) const=0;
    virtual posizione precLista(posizione) const=0;
    virtual void insLista(const tipoelem&, posizione&) =0;
    virtual void cancLista(posizione&)=0;

    template <class T1, class P1>
            friend ostream& operator<<(ostream& , const Linear_List<T1,P1>&);

    virtual void inserisciTesta(const tipoelem&)=0;
    virtual void inserisciCoda(const tipoelem&)=0;
    virtual void rimuoviTesta()=0;
    virtual void rimuoviCoda()=0;
    virtual posizione ultimoLista() const=0;
    virtual int lunghezza() const=0;
    virtual void scambiaElementi(posizione, posizione)=0;
    bool ricercaElemento(T&)const;
    void inverti();
    bool palindroma();
};



/*
 * Overload dell'operatore di output per stampare una lista in un flusso di output.
 */
template< class T, class P >
ostream& operator<<(ostream& os, const Linear_List<T,P> &l){
    typename Linear_List<T,P>::posizione p;
    p = l.primoLista();
    os << "[";
    while (!l.fineLista(p)){
        if (p != l.primoLista())
            os << ", " <<l.leggiLista(p);
        else
            os << l.leggiLista(p);
        p = l.succLista(p);
    }
    os << "]" << endl;
    return os;
}

/*
 * Inverte l'ordine degli elementi nella lista.
 */
template <class T, class P>
void Linear_List<T, P>::inverti() {
    posizione prima=primoLista();
    posizione ultimo=ultimoLista();
    tipoelem e1,e2;
    for (int i=0;i<(lunghezza()/2);i++)
    {
        e1= leggiLista(prima);
        e2= leggiLista(ultimo);
        scriviLista(e2,prima);
        scriviLista(e1,ultimo);
        prima=succLista(prima);
        ultimo= precLista(ultimo);

    }
}

/*
 * Verifica se la lista è palindroma.
 */
template <class T,class P>
bool Linear_List<T, P>::palindroma() {
    posizione prima=primoLista();
    posizione ultimo=ultimoLista();
    for (int i=0;i<(lunghezza()/2);i++)
    {
        if (leggiLista(prima)!= leggiLista(ultimo))
        {
            return false;
        }
        prima=succLista(prima);
        ultimo= precLista(ultimo);
    }
    return true;
}

/*
 * Verifica se l'elemento in input è presente nella lista
*/
template <class T,class P>
bool Linear_List<T,P>::ricercaElemento(T& e) const {
    posizione p=this->primoLista();
    while (!fineLista(p))
    {
        if (e==leggiLista(p))
            return true;
        else
            p= succLista(p);
    }
    return false;
}
#endif //REALIZZAZIONI_LINEAR_LIST_H
