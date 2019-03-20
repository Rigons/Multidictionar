#pragma once
#include "multidicord.h"
#include "validator.h"

class UI
{
private:
	multidicord dct;

	validator val;

	string v[7] = { "Luni","Marti","Miercuri","Joi","Vineri","Sambata","Duminica" };

	void addUI();

	void modUI();

	void remUI();

	void detclas();

	void sali();

	void orarprofesor();
	void init();


public:
	UI(multidicord& dct, validator val)noexcept : dct{ dct }, val{ val } {}
	UI(const UI& ot) = delete;
	void start();
};

