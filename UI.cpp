#include "UI.h"
#include "Ora.h"
#include "excepti.h"
#include "Listadublu.h"
#include <iostream>
#include <string>

using namespace std;

template<typename T>
T myread(const char* msg) {
	T cmd{};
	while (true) {
		std::cout << std::endl << msg;
		std::cin >> cmd;
		const bool fail = std::cin.fail();
		std::cin.clear();//resetez failbit
		const auto& aux = std::cin.ignore(1000, '\n');
		if (!fail && aux.gcount() <= 1) {
			break; //am reusit sa citesc numar
		}
	}
	return cmd;
}
void UI::addUI() {
	string profesor, clasa;
	int ora, zi;
	profesor = myread<string>("Numele profesorului: ");
	clasa = myread<string>("Numele clasei: ");
	ora = myread<int>("Ora: ");
	zi = myread<int>("Ziua: ");
	Ora o(profesor, clasa, zi,ora);
	val.validateOra(o);
	dct.adauga(profesor, o);
}
void UI::remUI() {
	string profesor;
	int ora, zi;
	profesor = myread<string>("Numele profesorului: ");
	ora = myread<int>("Ora: ");
	zi = myread<int>("Ziua: ");
	Ora o(profesor, "i", ora, zi);
	val.validateOra(o);
	dct.stergere(profesor, o);
}
void UI::modUI() {
	string profesor, clasa, nclasa;
	int ora, zi, nora, nzi;
	profesor = myread<string>("Numele profesorului: ");
	ora = myread<int>("Ora: ");
	zi = myread<int>("Ziua: ");
	nclasa = myread<string>("Numele clasei: ");
	nora = myread<int>("Ora: ");
	nzi = myread<int>("Ziua: ");
	Ora o(profesor, "e", zi, ora);
	Ora no(profesor, nclasa, nzi, nora);
	val.validateOra(o);
	dct.set(profesor, o, no);
}
void UI::orarprofesor() {
	string profesor;
	profesor = myread<string>("Numele profesorului: ");
	Mylisttemp<Ora> lst = dct.getorar(profesor);
	while (lst.size()>0) {
		Ora min = lst.get(0);
		int ind = 0;
		for (int j = 1; j < lst.size(); j++) {
			if (lst.get(j) < min) {
				min = lst.get(j);
				ind = j;
			}
		}
		cout << "Zi: " << v[min.getzi()] << " Ora: " << min.getora() << " Clasa: " << min.getclasa() << "\n";
		lst.erase(ind);

	}

}
void UI::init() {
	dct.adauga("Manolecu",Ora("Manolecu", "C300", 0, 10));
	dct.adauga("Manolecu",Ora("Manolecu", "C320", 0, 11));
	dct.adauga("Manolecu",Ora("Manolecu", "C320", 2, 9));
	dct.adauga("Nicoara",Ora("Nicoara", "B20", 4, 18));
	dct.adauga("Nicoara",Ora("Nicoara", "B20", 4, 12));
}
void UI::detclas() {
	string profesor, clasa;
	int ora, zi;
	profesor = myread<string>("Numele profesorului: ");
	ora = myread<int>("Ora: ");
	zi = myread<int>("Ziua: ");
	Ora ol(profesor, "i", zi,ora);
	validator(o);
	auto no=dct.geto(profesor, ol);
	cout << "Profesorul are ora in sala: " << no.getclasa()<<"\n";
}

void UI::sali() {
	string profesor;
	profesor = myread<string>("Numele profesorului: ");
	Mylisttemp<Ora> lst = dct.getorar(profesor);
	string t = "";
	for (auto o : lst) {
		t = t + " " + o.getclasa();
	}
	cout << "Clasele in care " << profesor << " are ore sunt: " << t<<" \n";
}

void UI::start() {
	init();
	while (true) {
		cout << "Meniu:\n";
		cout << "1.Adauga\n2.Sterge\n3.Modifica\n4.Afisare orar profesor\n5.Cauta Clasa\n6.Salile in care ora un profesor\n";
		cout << "0.Iesire\n";
		int cmd;
		cmd = myread<int>("Dati comanda:");
		try {
			switch (cmd)
			{
			case 1:
				addUI();
				break;
			case 2:
				remUI();
				break;
			case 3:
				modUI();
				break;
			case 4:
				orarprofesor();
				break;
			case 5:
				detclas();
				break;
			case 6:
				sali();
				break;
			case 0:
				return;
			default:
				cout << "Comanda invalida";
			}
		}
		catch (ValidException& ex) {
			cout << "\n" << ex.getMessage() << "\n";
		}
		catch (MylisttempException& ex) {
			cout << "\n" << ex.getMessage() << "\n";
		}

	}
}
