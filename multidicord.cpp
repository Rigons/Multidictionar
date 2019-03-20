#include "multidicord.h"
#include "excepti.h"
#include "Listadublu.h"

int hashCode(const TCheie& c) {
	int s = 0;
	for (int i = 0; i < c.size(); i++) {
		s = s + c[i];
	}
	return s;
}
Nodmul::Nodmul(const TCheie& c, const  Ora& v, Nodmul* urm) {
	this->c = c;
	this->lis.add(v);
	this->urm = urm;
}

void Nodmul::add(const Ora& v) {
	this->lis.add(v);
}

int multidicord::d(const TCheie& c) const noexcept {
	return hashCode(c) % m;
}
bool multidicord::cauta(TCheie&c, const Ora& o)const {
	int i = d(c);
	auto p = l[i];
	while (p != NULL) {
		if (p->c == c)
		{
			for (auto q : p->lis) {
				if (o.getora() == q.getora() && q.getzi() == o.getzi()) {
					return 1;
				}
			}
		}
		p = p->urm;
	}
	return 0;
}
void multidicord::set(TCheie& c, Ora& o1, Ora&o2) {
	int i = d(c);
	auto p = l[i];
	while (p != NULL) {
		int j = 0;
		if (p->c == c)
		{
			for (auto q : p->lis) {
				if (o1.getora() == q.getora() && q.getzi() == o1.getzi()) {
					p->lis.set(j, o2);
					return;
				}
				j++;
			}
		}
		p = p->urm;
	}
	throw MylisttempException("Element inexistent");
}
void multidicord::adauga(const TCheie& c, const Ora& o) {
	int i = d(c);

	if (l[i] == NULL) {
		Nodmul* p = new Nodmul(c, o, NULL);
		l[i] = p;
	}
	else if (l[i]->getcheie() > c) {
		Nodmul* p = new Nodmul(c, o, NULL);
		p->urm = l[i];
		l[i] = p;

	}
	else {
		auto q = l[i];
		while (q->urm != NULL) {
			if (q->getcheie() == c) {
				q->lis.add(o);
				break;
			}
			if (q->urm->getcheie()>c) {
				Nodmul* p = new Nodmul(c, o, NULL);
				p->urm = q->urm;
				q->urm = p;
				break;
			}
			q = q->urm;
		}
		if (q->urm == NULL && q->getcheie() != c) {
			Nodmul* p = new Nodmul(c, o, NULL);
			q->urm = p;
		}
		else if (q->urm == NULL && q->getcheie() == c) {
			q->lis.add(o);
		}

	}
	dim++;
}
Mylisttemp<Ora>& multidicord::getorar(const TCheie& c) const {
	auto i = d(c);
	auto p = l[i];
	while (p != NULL) {
		if (p->c == c)
			return p->lis;
		p = p->urm;
	}
	throw MylisttempException("cheie inexistenta");
}
bool multidicord::vid()const {
	for (int i = 0; i < MAX; i++)
		if (l[i] != NULL)
			return 1;
	return 0;
}
std::vector<TCheie> multidicord::chei() const {
	int i = 0;
	vector<TCheie> perech;
	for (i = 0; i < MAX; i++) {
		auto p = l[i];
		while (p != NULL) {

			perech.push_back(p->c);

			p = p->urm;
		}
	}
	return perech;
}
std::vector<Pereche> multidicord::perechi()const {
	int i = 0;
	vector<Pereche> perech;
	for (i = 0; i < MAX; i++) {
		auto p = l[i];
		while (p != NULL) {
			int j = 0;
			for (auto q : p->lis) {
				Pereche per;
				per.c = p->c;
				per.o = q;
				perech.push_back(per);

			}
			p = p->urm;
		}
	}
	return perech;
}
std::vector<Ora> multidicord::valori()const {
	int i = 0;
	vector<Ora> perech;
	for (i = 0; i < MAX; i++) {
		auto p = l[i];
		while (p != NULL) {
			int j = 0;
			for (auto q : p->lis) {

				perech.push_back(q);

			}
			p = p->urm;
		}
	}
	return perech;
}

int multidicord::size()const {
	return dim;
}
void multidicord::stergere(const TCheie& c, const Ora& o) {
	int i = d(c);
	auto p = l[i];
	while (p != NULL) {
		int j = 0;
		if (p->c == c)
		{
			for (auto q : p->lis) {
				if (o.getora() == q.getora() && q.getzi() == o.getzi()) {
					p->lis.erase(j);
					if (p->lis.size() == 0) {
						delete p;

					}
					dim--;
					return;
				}
				j++;
			}
		}
		p = p->urm;
	}
	throw MylisttempException("Element inexistent");
}

Ora& multidicord::geto(TCheie& c, Ora& o) const {
	int i = d(c);
	auto p = l[i];
	while (p != NULL) {
		int j = 0;
		if (p->c == c)
		{
			for (auto q : p->lis) {
				if (o.getora() == q.getora() && q.getzi() == o.getzi()) {
					return p->lis.get(j);
					j++;
				}
			}
		}
		p = p->urm;
	}

	throw MylisttempException("Element inexistent");
}
Iteratormul multidicord::iterator() const {
	return Iteratormul(*this);
}
//Iteratormul multidicord::end()const noexcept { return Iteratormul::Iteratormul(*this, MAX + 1, 0, nullptr); }
//Iteratormul multidicord::begin()const noexcept { return Iteratormul::Iteratormul(*this); }

multidicord::multidicord()
{
	m = MAX;
	dim = 0;
	for (int i = 0; i < m; i++)
		l[i] = NULL;
}


multidicord::~multidicord()
{
	for (int i = 0; i < m; i++) {
		while (l[i] != NULL) {
			Nodmul* p = l[i];
			l[i] = l[i]->urm;
			delete p;
		}
	}
}

void Iteratormul::deplasare() {
	while (poz<dct.m && dct.l[poz] == NULL) poz++;
	if (poz < dct.m)
	{
		curent = dct.l[poz];
		pozlist = 0;
	}
}

Iteratormul::Iteratormul(const multidicord& d) : dct(d) { poz = 0; pozlist = 0; deplasare(); }

void Iteratormul::urmator() {
	pozlist++;
	if (pozlist == curent->lis.size())
	{
		curent = curent->urm;
		if (curent == NULL) {
			poz = poz + 1;
			deplasare();
		}
	}
}
bool Iteratormul::valid() const {
	return (poz < dct.m) && (curent != NULL) && curent->lis.size();
}
Ora& Iteratormul::element() const noexcept {
	return curent->lis.get(pozlist);
}
void Iteratormul::prim() {
	poz = 0;
	pozlist = 0;
	deplasare();
}
Ora& Iteratormul::operator*() noexcept {
	return element();
}
Iteratormul& Iteratormul::operator++()noexcept {
	urmator();
	return *this;
}
bool Iteratormul::operator==(const Iteratormul& ot)noexcept {
	return curent = ot.curent;
}
bool Iteratormul::operator!=(const Iteratormul& ot)noexcept {
	return !(*this == ot);
}
