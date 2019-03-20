#include "validator.h"



void validator::validateOra(const Ora& o)const {
	vector<string> v;
	if (o.getprofesor().size() == 0)
		v.push_back("Campul profesorului este invalid");
	if (o.getclasa().size() == 0)
		v.push_back("Campul clasa este invalid");
	if (o.getzi()>6 && o.getzi()<0)
		v.push_back("Campul zi este invalid");
	if (o.getora() < 1 || o.getora()>24)
		v.push_back("Campul profesorului este invalid");
}
