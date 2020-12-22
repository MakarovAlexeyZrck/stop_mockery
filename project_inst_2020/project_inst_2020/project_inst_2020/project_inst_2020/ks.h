#pragma once

#include <iostream>
#include <string>
#include <fstream>

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
	int GetId() const;

	friend std::istream& operator >> (std::istream& in, ks& cs);
	friend std::ostream& operator << (std::ostream& out, const ks& cs);
	friend std::ofstream& operator << (std::ofstream& fout, const ks& k);
	friend std::ifstream& operator >> (std::ifstream& fin, ks& k);

	void edit_ks();

};

