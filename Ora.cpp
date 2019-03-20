#include "Ora.h"



Ora& Ora::operator=(const Ora& ot) {
	if (this == &ot) {
		return *this;
	}
	profesor = ot.profesor;
	clasa = ot.clasa;
	ora = ot.ora;
	zi = ot.zi;
	return *this;
}