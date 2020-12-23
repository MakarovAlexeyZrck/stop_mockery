#pragma once

#include <iostream>
#include <string>


class trumpet
{

private:
	int id;

public:
	static int MaxID;
	double length;
	double diameter;
	bool is_broken = 0;

	int from, to;

	int Weight;
	int Throughput;

	trumpet();

	friend std::ostream& operator << (std::ostream& out, const trumpet& s);
	friend std::istream& operator >> (std::istream& in, trumpet& s);
	friend std::ofstream& operator << (std::ofstream& fout, const trumpet& p);
	friend std::ifstream& operator >> (std::ifstream& fin, trumpet& p);

	void trumpet_mode();
	int GetId() const;
	int GetThroughput() const;
	int GetWeight() const;
};

