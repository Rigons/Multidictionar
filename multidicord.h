#pragma once
#include <string>
#include <vector>
#include "Ora.h"
#include "Listadublu.h"
#define MAX 10

typedef std::string TCheie;
/*typedef struct TElem{
TCheie c;
Mylisttemp<Ora> lis;
}TElem;*/
typedef struct Pereche {
	TCheie c;
	Ora o;
};

int hashCode(const TCheie& c);

class Iteratormul;

class Nodmul;

class Nodmul {
private:
	TCheie c;
	Mylisttemp<Ora> lis;
	Nodmul* urm;
public:
	friend class multidicord;
	friend class Iteratormul;
	Nodmul(const TCheie& c, const Ora& v, Nodmul* urm);
	void add(const Ora& v);
	TCheie& getcheie() {
		return c;
	}
};
class multidicord
{
private:
	int m;
	Nodmul* l[MAX];
	int dim;
	int d(const TCheie& c)const noexcept;
public:
	friend class Iteratormul;
	multidicord();
	void adauga(const TCheie& c, const Ora& v);
	Mylisttemp<Ora>& getorar(const TCheie& c) const;
	void stergere(const TCheie& c, const Ora& o);
	int size()const;
	bool vid()const;
	std::vector<TCheie> chei()const;
	std::vector<Ora> valori()const;
	bool cauta(TCheie&c, const Ora& o)const;
	void set(TCheie& c, Ora& o1, Ora&o2);
	Ora& geto(TCheie& c, Ora& o) const;
	std::vector<Pereche> perechi()const;
	Iteratormul iterator() const;
	//Iteratormul end()const noexcept;
	//Iteratormul begin()const noexcept;
	~multidicord();
};
class Iteratormul {
private:
	Iteratormul(const multidicord& d);
	Iteratormul(const multidicord& d, int poz, int pozlist, Nodmul*curent) :dct{ d }, poz{ poz }, pozlist{ pozlist }, curent{ curent } {}
	void deplasare();
	const multidicord& dct;
	int poz;
	int pozlist;
	Nodmul* curent;
public:
	friend class multidicord;
	void prim();
	void urmator();
	bool valid() const;
	Ora& operator*() noexcept;
	Iteratormul& operator++()noexcept;
	bool operator==(const Iteratormul& ot)noexcept;
	bool operator!=(const Iteratormul& ot)noexcept;
	Ora& element() const noexcept;
};
