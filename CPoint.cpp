#include "CPoint.h"

CPoint::CPoint(int x_, int y_) : x(x_), y(y_)
{
}

CPoint::CPoint(const CPoint& p) : x(p.x), y(p.y)
{
}

//string CPoint::getType() const
//{
//    return "Point";
//}

int CPoint::X() const
{
    return x;
}

int CPoint::Y() const
{
    return y;
}

void CPoint::setX(int n)
{
    x = n;
}

void CPoint::setY(int n)
{
    y = n;
}

bool CPoint::operator==(const CPoint& p)
{
    return (x == p.x && y == p.y);
}

CPoint& CPoint::operator=(const CPoint& p)
{
    x = p.x;
    y = p.y;
    return *this;
}

CPoint::~CPoint()
{
}

ostream & operator<<(ostream& out, const CPoint& p)
{
    out << "(" << p.X() << ", " << p.Y() << ")";
    return out;
}

istream& operator>>(istream& in, CPoint& p)
{
    int x, y; 
    //string buf;
    bool correct = false;
    do {
        correct = true;
        cin >> x;
        if (cin.fail()) {
            cin.clear();
            correct = false;
            cout << "Некорректный ввод" << endl;
            cin.ignore(32000, '\n');
            continue;
        }
        cin >> y; 
        if (cin.fail()) {
            cin.clear();
            correct = false;
            cout << "Некорректный ввод" << endl;
            cin.ignore(32000, '\n');
        }
    } while (!correct);
    p.setX(x);
    p.setY(y);
    return in;
}
