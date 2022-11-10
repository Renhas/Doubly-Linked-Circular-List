#pragma once
#include <iostream>
using namespace std;

class CPoint {
private:
	int x, y;
public:
	CPoint(int = 0, int = 0);
	CPoint(const CPoint&);

	//virtual string getType() const;
	int X() const;
	int Y() const;
	void setX(int );
	void setY(int );
	bool operator==(const CPoint&);
	CPoint& operator=(const CPoint&);

	virtual ~CPoint();
};

ostream & operator<<(ostream&, const CPoint&);
istream& operator>>(istream&, CPoint&);