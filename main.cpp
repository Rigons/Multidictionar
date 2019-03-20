#include "UI.h"
#include "multidicord.h"
int main()
{
	multidicord dct;
	validator val;
	UI cons(dct, val);
	cons.start();
	return 0;
}
