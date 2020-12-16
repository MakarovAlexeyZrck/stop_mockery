#pragma once

#include <iostream>
#include <string>

class ks
{

private:
	int id;

public:
	static int MaxID;
	std::string ks_name;
	int count_workshops;
	int active_workshops;
	double efficiency;

	ks();

	friend std::istream& operator >> (std::istream& in, ks& cs);
	friend std::ostream& operator << (std::ostream& out, const ks& cs);

};

