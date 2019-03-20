#pragma once
#include <string>
#include <iostream>
using namespace std;
class Ora
{
public:
	Ora() = default;
	Ora(const std::string profesor, std::string clasa, int zi, int ora) :profesor{ profesor }, clasa{ clasa }, zi{ zi }, ora{ ora } {}
	string getprofesor()const noexcept {
		return profesor;
	}
	string getclasa() const noexcept {
		return clasa;
	}
	int getora() const noexcept {
		return ora;
	}
	int  getzi() const noexcept {
		return zi;
	}
	bool operator<(Ora &ot) {
		if (ot.getzi() == zi) {
			if (ot.getora() > ora) {
				return 1;
			}
			else return 0;
		}
		else if (ot.getzi() > zi) {
			return 1;
		}
		else return 0;
	}
	Ora& operator=(const Ora& ot);
private:
	std::string profesor;
	std::string clasa;
	int  zi;
	int ora;
};

