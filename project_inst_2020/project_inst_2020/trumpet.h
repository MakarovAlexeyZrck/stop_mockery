#pragma once

#include <iostream>
#include <string>


class trumpet
{


public:
	int id;
	static int MaxID;
	double length;
	double diameter;
	bool is_broken = 0;

	int from, to;

	trumpet();
	~trumpet();

	friend std::ostream& operator << (std::ostream& out, const trumpet& s);
	friend std::istream& operator >> (std::istream& in, trumpet& s);

	void trumpet_mode();
	int get_weight();
};

