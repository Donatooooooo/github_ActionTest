#include <iostream>
#include "Linked_list.h"
using namespace std;

class eo_strings {
public:
	void add(string s);
	void del(string s);
	void del(char c, Linked_list<string> s);
	void show(Linked_list<string> s);
	Linked_list<string> getEvenList();
	Linked_list<string> getOddList();

private:
	Linked_list<string> even;
	Linked_list<string> odd;

	bool isEven(string s);
	Linked_list<string>::posizione posizione(Linked_list<string>& lista, string s);
};

bool eo_strings::isEven(string s) {
	if(s.length()% 2 == 0)	{
		return true;
	}
	return false;
}

Linked_list<string>::posizione eo_strings::posizione(Linked_list<string>& lista, string s){
	Linked_list<string>::posizione pos;
	pos = lista.primoLista();
		while(!lista.fineLista(pos))
		{
			if(lista.leggiLista(pos) == s)
			{
				break;
			}
			pos = lista.succLista(pos);
		}
	return pos;
}

void eo_strings::add(string s) {
	if(isEven(s)) {
		even.inserisciCoda(s);
	} else {
		odd.inserisciCoda(s);
	}
}

void eo_strings::del(string s) {
	Linked_list<string>::posizione pos;
	if(isEven(s)) {
		pos = posizione(even, s);
		even.cancLista(pos);
	} else {
		pos = posizione(odd, s);
		odd.cancLista(pos);
	}
}

void eo_strings::del(char c, Linked_list<string> s) {
	Linked_list<string>::posizione pos;
	pos = s.primoLista();
	while(!s.fineLista(pos)) {
		const char * str = s.leggiLista(pos).c_str();
		if(str[0] == c) {
			s.cancLista(pos);
			pos = even.primoLista();
		} else {
			pos = even.succLista(pos);
		}
	}
}

Linked_list<string> eo_strings::getEvenList(){
	return even;
}

Linked_list<string> eo_strings::getOddList(){
	return odd;
}

void eo_strings::show(Linked_list<string> s) {
	cout << s << endl;
}

int main() {
	eo_strings categorizer;

	categorizer.add("apple");
	categorizer.add("banana");
	categorizer.add("pear");
	categorizer.add("orange");
	categorizer.add("kiwi");
	categorizer.add("strawberry");

	cout << "Lista delle stringhe pari: ";
	categorizer.show(categorizer.getEvenList());

	cout << "Lista delle stringhe dispari: ";
	categorizer.show(categorizer.getOddList());

	 categorizer.del("banana");
	 categorizer.del("kiwi");

	cout << "Lista pari modificata: ";
	categorizer.show(categorizer.getEvenList());

	categorizer.del('s', categorizer.getEvenList());

	cout << "Lista pari senza strawberry: ";
	categorizer.show(categorizer.getEvenList());
	
	system("pause");
	return 0;
}
