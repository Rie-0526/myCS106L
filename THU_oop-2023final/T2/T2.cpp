#include <iostream>

using namespace std;


//declare class and function
template <typename T>
class Point;
template <typename T>
class Line;

template <typename T>
bool operator<(const Line<T>& l1, const Line<T>& l2);


//define class
template <typename T>
class Line{
    private:
        T k; T b;
    public:
        Line(T k) : k(k){};
        Line(T k, T b) : k(k), b(b){};
        bool intersect(const Line&);
        void show();
        friend bool operator< <T>(const Line& l1, const Line& l2);     //what the operator< <T> fuck
        // Function declare from other class 
        friend bool Point<T>::check(Line const& l);
};



template <typename T>
class Point{
    private:
        T x; T y;
    public:
        Point(T x, T y);
        void move(T dx, T dy);
        void show();
        bool check(Line<T> const& l);
};


//define class LINE functions

template <typename T>
bool operator<(const Line<T>& l1, const Line<T>& l2){
    return l1.k < l2.k;
}

template <typename T>
bool Line<T> :: intersect(const Line<T>& l2){
    if ((k == l2.k) && (b != l2.b))   // L1 paraollel to L2
        return false;
    else    
        return true; 
}

template <typename T>
void Line<T> :: show(){
    cout << k << ',' << b << endl;
}




//define class POINT functions

template <typename B>
Point<B>::Point(B x, B y):x(x),y(y){;}

template <typename T>
void Point<T>::move(T dx, T dy){
    x += dx;
    y += dy;
}

template <typename T>
void Point<T>::show(){
    cout << '(' << x << ',' << y << ')' << endl;
}

template <typename T>
bool Point<T>::check(Line<T> const& l){
    return y == (l.k * x + l.b);
}









int main() {
    Point<int> p1(2,4);
    p1.move(3,2);
    p1.show();
    // 此处应该输出(5,6)

    Line<int> line1(2);
    Line<int> line2(2, 4);
    cout << line1.intersect(line2) << endl;
    // 此处应输出 0

    Line<int> line3(3);
    Line<int> line4(2, 6);
    if (line3 < line4) line3.show();
    else line4.show();
    // 此处应输出 2,6

    Point<int> p2(4,12);
    cout << p2.check(line2) << endl;
    //此处应该输出1
    return 0;
}