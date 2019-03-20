#pragma once
#include "excepti.h"
template <typename ElemT>
class Iterator;

template <typename ElemT>
class Nod;

template <typename ElemT>
class Mylisttemp;

template <typename ElemT>
class Nod {
public:

	friend class Mylisttemp<ElemT>;
	Nod(ElemT el, Nod* urm) {
		this->e = el;
		this->urm = urm;
	}
	ElemT& element()noexcept {
		return e;
	}
	Nod* urmator() noexcept {
		return urm;
	}
	/*~Nod() {
	delete el;
	urm = nullptr;
	}*/
	//void setNod(ElemT e);
private:
	ElemT e;
	Nod* urm;
};

template <typename ElemT>
class Mylisttemp
{
private:
	Nod<ElemT> * prim;
	Nod<ElemT> *ult;
	int lg;
public:
	friend class Iterator<ElemT>;
	Mylisttemp() noexcept {
		prim = nullptr;
		lg = 0;
		ult = nullptr;
	}
	//void addinceput(const ElemT& elem);

	void add(const ElemT& elem);


	//void addmijloc(const ElemT elem);

	void sterge(Nod<ElemT>* n);

	Nod<ElemT>* copiaza(Nod<ElemT>* n);

	Mylisttemp(const Mylisttemp<ElemT>& ot) {
		auto i = ot.prim;
		lg = ot.lg;
		prim = nullptr;
		ult = nullptr;
		while (i != nullptr) {
			Nod<ElemT> *n = new Nod<ElemT>(i->e, nullptr);
			if (prim == nullptr) {
				prim = ult = n;
			}
			ult->urm = n;
			ult = n;
			i = i->urm;
		}
	}

	void erase(const int & index);

	Mylisttemp& operator=(const Mylisttemp& ot);

	void set(int poz, const ElemT& elem);

	ElemT& get(int poz) const noexcept;

	int size()const noexcept;

	~Mylisttemp();

	Iterator<ElemT> iterator() const;
	Iterator<ElemT> end() const noexcept { return Iterator<ElemT>::Iterator(*this, nullptr); }
	Iterator <ElemT> begin() const noexcept { return Iterator<ElemT>::Iterator(*this); }
};
template <typename ElemT>
void Mylisttemp<ElemT>::erase(const int & index) {
	int n = index;
	if (n < 0 || n>lg-1) {
		throw MylisttempException("Index prea mare");
	}
	if (n == 0 && lg == 1) {
		Nod<ElemT>*p = prim;
		ult = prim = nullptr;
		delete p;
		lg = 0;
		return;
	}
	if (n == 0) {
		Nod<ElemT>*p = prim;
		prim = prim->urm;
		delete p;
		lg--;
		return;
	}
	Nod<ElemT>*nod = prim;
	for (int i = 0; i < n-1; nod = nod->urm, i++);

	Nod<ElemT>*nodurm = nod->urm;

	nod->urm = nod->urm->urm;
	if (nod->urm == nullptr)
		ult = nod;
	delete nodurm;
	lg--;
}

template <typename ElemT>
class Iterator {
private:

	Iterator(const Mylisttemp<ElemT>& list) noexcept;
	Iterator(const Mylisttemp<ElemT>& list, Nod<ElemT>* n)noexcept;
	const Mylisttemp<ElemT>& lista;
	Nod<ElemT>* curent;
public:

	friend class Mylisttemp<ElemT>;

	void prim();

	void urmator()noexcept;

	bool valid()const;

	ElemT& element() const noexcept;

	ElemT& operator*() noexcept;

	Iterator& operator++() noexcept;

	bool operator==(const Iterator& ot)noexcept;

	bool operator!=(const Iterator& ot)noexcept;

};
template <typename ElemT>
Mylisttemp<ElemT>& Mylisttemp<ElemT>::operator=(const Mylisttemp<ElemT>& ot) {
	if (this == &ot) {
		return *this;
	}
	sterge(prim);
	auto i = ot.prim;
	lg = ot.lg;
	prim = nullptr;
	ult = nullptr;
	while (i != nullptr) {
		Nod<ElemT> *n = new Nod<ElemT>(i->e, nullptr);
		if (prim == nullptr) {
			prim = ult = n;
		}
		ult->urm = n;
		ult = n;
		i = i->urm;
	}
	return *this;
}


template <typename ElemT>
void Mylisttemp<ElemT>::add(const ElemT& elem) {
	Nod<ElemT>* n = new Nod<ElemT>(elem, nullptr);
	lg++;
	if (prim == nullptr) {
		prim = ult = n;
		return;
	}
	ult->urm = n;
	ult = n;
}

template <typename ElemT>
Mylisttemp<ElemT>::~Mylisttemp()
{
	ult = nullptr;
	while (prim != nullptr) {
		auto n = prim;
		prim = prim->urm;
		delete n;
	}
	lg = 0;
}

template <typename ElemT>
void Mylisttemp<ElemT>::sterge(Nod<ElemT>* n) {
	if (n == nullptr) {
		return;
	}
	sterge(n->urm);
	delete n;
}

template <typename ElemT>
int Mylisttemp<ElemT>::size() const noexcept {
	return lg;
}

template <typename ElemT>
void Mylisttemp<ElemT>::set(int poz, const ElemT& elem) {
	int i = 1;
	auto curent = prim;
	while (i < poz) {
		curent = curent->urm;
	}
	curent->e = elem;
}


template <typename ElemT>
Nod<ElemT>* Mylisttemp<ElemT>::copiaza(Nod<ElemT>* n) {
	if (n == nullptr)
		return nullptr;
	Nod<ElemT>* p = new Nod<ElemT>(n->e, copiaza(n->urm));
	return p;
	//!!!!!
}
template <typename ElemT>
Iterator<ElemT> Mylisttemp<ElemT>::iterator()const {
	return Iterator<ElemT>::Iterator(*this);
}

template <typename ElemT>
Iterator<ElemT>::Iterator(const Mylisttemp<ElemT>& list, Nod<ElemT>* n)noexcept : lista(list) { curent = n; }

template <typename ElemT>
Iterator<ElemT>::Iterator(const Mylisttemp<ElemT>& list) noexcept :
	lista(list) {
	curent = list.prim;
}

template <typename ElemT>
void Iterator<ElemT>::prim() {
	curent = lista.prim;
}

template <typename ElemT>
void Iterator<ElemT>::urmator()noexcept {
	curent = curent->urmator();
}

template<typename ElemT>
bool Iterator<ElemT>::valid() const {
	return curent != nullptr;
}

template<typename ElemT>
ElemT& Iterator<ElemT>::element() const noexcept {
	return curent->element();
}

template<typename ElemT>
ElemT& Iterator<ElemT>::operator*() noexcept {
	return element();
}

template <typename ElemT>
Iterator<ElemT>& Iterator<ElemT>::operator++() noexcept {
	urmator();
	return *this;
}


template <typename ElemT>
bool Iterator<ElemT>::operator==(const Iterator<ElemT>& ot)noexcept {
	return curent == ot.curent;
}
template<typename ElemT>
bool Iterator<ElemT>::operator!=(const Iterator<ElemT>& ot) noexcept {
	return !(*this == ot);
}


template <typename ElemT>
ElemT& Mylisttemp<ElemT>::get(int poz) const noexcept {
	int i = 0;
	auto curent = prim;
	while (i < poz&& curent->urm != nullptr) {
		curent = curent->urm;
		i++;
	}
	return curent->e;
}