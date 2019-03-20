#include "Tester.h"
#include <string>
#include <assert.h>
#include "multidicord.h"
void test_hashcode() {
	std::string q = "abc";
	assert(97 * 3 + 3 == hashCode(q));
	multidicord dict;
	assert(dict.vid() == 0);
	std::string  c = "Ana Maria";
	Ora o("Ana Maria", "12B", 0, 10);
	dict.adauga(c, o);
	Ora o2("Ana Maria", "12B", 0, 10);
	dict.adauga(c, o2);
	c = "Ana Mar";
	Ora o1("Ana Mar", "10B", 0, 10);
	dict.adauga(c, o1);
	c = "Ana Maric";
	Ora o3("Ana Maric", "10B", 3, 12);
	dict.adauga(c, o3);
	c = "Ana Maric";
	Ora o4("Ana Maric", "10B", 3, 12);
	dict.adauga(c, o4);
	c = "Ana Marib";
	Ora o5("Ana Marib", "10B", 3, 12);
	dict.adauga(c, o5);
	c = "Ana Marib";
	Ora o6("Ana Marib", "10B", 3, 12);
	dict.adauga(c, o6);
	dict.stergere(c, o6);
	Ora o7("Ana Marib", "9B", 3, 12);
	dict.set(c, o6, o7);
	assert(6 == dict.size());
	assert(dict.vid() == 1);
	Mylisttemp<Ora> ls = dict.getorar(o.getprofesor());
}
void test_all() {
	test_hashcode();
}