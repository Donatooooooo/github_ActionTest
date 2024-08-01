#include "Linear_list.h"
#include <stdexcept>
#ifndef REALIZZAZIONI_LINKED_LIST_H
#define REALIZZAZIONI_LINKED_LIST_H

template <class T>
class Linked_list;

template <class T>
class Nodo_lista
{
    friend class Linked_list<T>;
public:
    typedef T tipoelem;
private:
    tipoelem valore;
    Nodo_lista<tipoelem> *precedente;
    Nodo_lista<tipoelem> *successivo;
};

template <class T>
class Linked_list : public Linear_List<T, Nodo_lista<T> *>
{
public:
    typedef typename Linear_List<T, Nodo_lista<T> *>::tipoelem tipoelem;
    typedef typename Linear_List<T, Nodo_lista<T> *>::posizione posizione;

    Linked_list();
    Linked_list(const Linked_list<T> &);
    ~Linked_list();

    void creaLista();    
    bool listaVuota() const;
    tipoelem leggiLista(posizione) const;
    void scriviLista(const tipoelem&, posizione);
    posizione primoLista() const;
    bool fineLista(posizione) const;
    posizione succLista(posizione) const;
    posizione precLista(posizione) const;
    void insLista(const tipoelem&, posizione&);
    void cancLista(posizione&);

    Linked_list<T>& operator= (const Linked_list<T>&);
    bool operator == (const Linked_list<T>&);

    void inserisciTesta(const tipoelem&);
    void inserisciCoda(const tipoelem&);
    void rimuoviTesta();
    void rimuoviCoda();
    posizione ultimoLista() const;
    int lunghezza() const;
    void scambiaElementi(posizione, posizione);

private:
    Nodo_lista<T> * testa;
    int lunghezzaLista;
};

/*
 * Costruttore della lista
 * POST CONDIZIONE: Lista vuota
 */
template <class T>
void Linked_list<T>::creaLista() {
    testa = new Nodo_lista<T>;
    testa->successivo=testa;
    testa->precedente=testa;
    lunghezzaLista = 0;

}

/*
 * Costruttore della lista
 * POST CONDIZIONE: Lista vuota
 */
template <class T>
Linked_list<T>::Linked_list()
{
  creaLista();
}

/*
 * costruttore di copia della lista
 */
template <class T>
Linked_list<T>::Linked_list(const Linked_list<T> &L)
{
    testa = new Nodo_lista<T>;
    testa->successivo = testa;
    testa->precedente = testa;
    posizione p=L.primoLista();
    posizione p1=this->primoLista();
    while (!L.fineLista(p))
    {
        this->insLista(L.leggiLista(p),p1);
        p1=this->succLista(p1);
        p=L.succLista(p);
    }

}

/*
 * distruttore
 */
template <class T>
Linked_list<T>::~Linked_list()
{
    posizione tmp,p=ultimoLista();
    while (!fineLista(p)) {
        tmp = p;
        p = p->precedente;
        tmp = nullptr;
        delete tmp;
    }
    testa=nullptr;
    delete testa;
}

/*
 * Verifica se una lista è vuota
 * POST CONDIZIONE: Return TRUE se lista vuota, FALSE altrimenti
 */
template <class T>
bool Linked_list<T>::listaVuota() const {
    return (testa == testa->successivo);
}

/*
 * Restituisce la posizione del primo elemento della lista
 * POST CONDIZIONE: Return della posizione del primo elemento della lista
 */
template <class T>
typename Linked_list<T>::posizione
Linked_list<T>::primoLista() const {
    return(testa->successivo);
}

/*
 * Restituisce l'ultimo elemento della lista
 */
template <class T>
typename Linked_list<T>::posizione
Linked_list<T>::ultimoLista() const {
    return (testa->precedente);
}

/*
 * Restituisce la posizione successiva a p nella lista
 * PRE CONDIZIONE: p=pos(i), 1<=i<=n , n numero di elementi della lista
 * POST CONDIZIONE: return di pos(i+1)
 */
template <class T>
typename Linked_list<T>::posizione
Linked_list<T>::succLista(Linked_list::posizione p) const {
        return p->successivo;
}

/*
 * Restituisce la posizione precedente a p nella lista
 * PRE CONDIZIONE: p=pos(i), 2<=i<=n , n numero di elementi della lista
 * POST CONDIZIONE: return di pos(i-1)
 */
template <class T>
typename Linked_list<T>::posizione Linked_list<T>::precLista(Linked_list::posizione p) const {
    if (p != testa->successivo)
        return (p->precedente);
    else throw std::out_of_range("POSIZIONE NON VALIDA");
}
/*
 * Verifica se la lista è terminata
  * PRE CONDIZIONE: p=pos(i), 1<=i<=n+1 , n numero di elementi della lista
 * POST CONDIZIONE: return true se p=pos(n+1), false altrimenti
 */
template <class T>
bool Linked_list<T>::fineLista(Linked_list<T>::posizione p) const {
    return (p==testa); //se p equivale alla sentinella allora siamo arrivati alla fine della lista
}

/*
 * Legge l'elemento in posizione p della lista
 * PRE CONDIZIONE: p=pos(i), 1<=i<=n , n numero di elementi della lista
 * POST CONDIZIONE: return a=a(i)
 */
template <class T>
typename Linked_list<T>::tipoelem
Linked_list<T>::leggiLista(Linked_list::posizione p) const {
    if (!fineLista(p))
        return (p->valore);
    else throw out_of_range("POSIZIONE NON VALIDA");
}

/*
 * Scrive l'elemento in posizione p della lista
 * PRE CONDIZIONE: p=pos(i), 1<=i<=n , n numero di elementi della lista
 * POST CONDIZIONE: l=<a1,...,a(i-1),a,(ai+1),...,an>
 */
template <class T>
void Linked_list<T>::scriviLista(const Linked_list::tipoelem &e, Linked_list::posizione p) {
    if (!fineLista(p))
        p->valore = e;
   else throw out_of_range("POSIZIONE NON VALIDA");
}

/*
 * Inserire l'elemento in posizione p della lista
 * PRE CONDIZIONE: p=pos(i), 1<=i<=n+1 , n numero di elementi della lista
 * POST CONDIZIONE: l=<a1,...,a(i-1),a,a(i),(ai+1),...,an> se 1<=i<=n, l=<a1,...,an,a> altrimenti
 */
template <class T>
void Linked_list<T>::insLista(const Linked_list::tipoelem &e, Linked_list::posizione& p) {
    posizione t = new Nodo_lista<T>;
    t->valore = e;
    t->precedente = p->precedente;
    t->successivo = p;
    p->precedente->successivo = t;
    p->precedente = t;
    lunghezzaLista++;
    p=p->precedente;

}


/*
 * Cancella l'elemento in posizione p della lista
 * PRE CONDIZIONE: p=pos(i), 1<=i<=n , n numero di elementi della lista
 * POST CONDIZIONE: l=<a1,...,a(i-1),(ai+1),...,an>
 */
template <class T>
void Linked_list<T>::cancLista(Linked_list<T>::posizione& p) {
    if (!listaVuota() && !fineLista(p))
    {
        posizione tmp=p->successivo;
        p->precedente->successivo = p->successivo;
        p->successivo->precedente = p->precedente;
        delete p;
        p= tmp;
        lunghezzaLista--;
    }
    else throw std::out_of_range("POSIZIONE NON VALIDA");
}

/*
 * Sovrascrive l'assegnazione per copiare una lista in un'altra
 */
template <class T>
Linked_list<T> &Linked_list<T>::operator=(const Linked_list<T> &L)
{
    if (this != &L)
    {
        this->~Linked_list();
        testa = new Nodo_lista<T>;
        testa->successivo = testa;
        testa->precedente = testa;
        posizione pl=L.primoLista();
        posizione p1=this->primoLista();
        while (!L.fineLista(pl))
        {
            this->insLista(L.leggiLista(pl),p1);
            p1=this->succLista(p1);
            pl=L.succLista(pl);
        }
    }
    return *this;
}

/*
 * Sovrascrive l'operatore == e confronta, elemento per elemento se due liste sono uguali
 */
template <class T>
bool Linked_list<T>::operator==(const Linked_list<T> &L)
{
    if (L.lunghezzaLista != this->lunghezzaLista)
        return false;
    posizione p, pL;
    p = primoLista();
    pL = L.primoLista();
    while (!fineLista(p))
    {
        if (p->valore != pL->valore)
            return false;
        p = p->successivo;
        pL = pL->successivo;
    }
    return true;
}

/*
 * Inserisce in prima posizione
 */
template <class T>
void Linked_list<T>::inserisciTesta(const tipoelem& e)
{
    Nodo_lista<T>* p=new Nodo_lista<T>;
    p->valore=e;
        testa->successivo->precedente=p;
        p->successivo=testa->successivo;
        p->precedente=testa;
        testa->successivo=p;
    lunghezzaLista++;
}

/*
 * Inserisce in ultima posizione (la prima libera)
 */
template<class T>
void Linked_list<T>::inserisciCoda(const tipoelem& e) {
        posizione p = new Nodo_lista<T>;
        p->valore = e;
        posizione pu=ultimoLista();
        p->precedente=pu;
        p->successivo=testa;
        pu->successivo=p;
        testa->precedente=p;
        lunghezzaLista++;
    }


/*
 * rimuove dalla prima posizione
 */
template <class T>
void Linked_list<T>::rimuoviTesta() {
    posizione p=new Nodo_lista<T>;
    p=testa->successivo;
    testa->successivo=testa->successivo->successivo;
    p= nullptr;
    delete p;
    lunghezzaLista--;
}

/*
 * Rimuove l'ultimo elemento
 */
template <class T>
void Linked_list<T>::rimuoviCoda()
{
    posizione p=new Nodo_lista<T>;
    p=ultimoLista();
    p->precedente->successivo=testa;
    p=nullptr;
    delete p;
    lunghezzaLista--;
}

/*
 * Ritorna il numero di elementi nella lista
 */
template<class T>
int Linked_list<T>::lunghezza() const {
    return lunghezzaLista;
};

/*
 * Scambia gli elementi nelle posizioni specificate all'interno della lista.
 */
template <class T>
void Linked_list<T>::scambiaElementi(Linked_list::posizione p1, Linked_list::posizione p2) {

        if( p1 != p2 && (p1 != nullptr && p2 != nullptr))
        {
            tipoelem temp=leggiLista(p1);
            scriviLista(leggiLista(p2),p1);
            scriviLista(temp, p2);
        }
}

#endif //REALIZZAZIONI_LINKED_LIST_H
