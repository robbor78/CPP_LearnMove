#include <iostream>
#include <memory>

using namespace std;


struct MyStruct {

  unique_ptr<int> original;
  string name;
  int x;
  int y;

  MyStruct(): name("default"), x(0), y(0) {}

  MyStruct(string name, int x, int y): name(name), x(x), y(y) {
    cout << "ctor ";
    print(cout);
    cout <<endl;
  }

  MyStruct(MyStruct const &a) : name(a.name), x(a.x), y(a.y) {
    cout << "copy ctor ";
    print(cout);
    cout << endl;
  }

  MyStruct(MyStruct &&a) : name(a.name), x(a.x), y(a.y) {
    cout << "move ctor ";
    print(cout);
    cout << endl;
  }

  // void doStuff(unique_ptr<int>&& parameter)
  //   {
  //     original = std::move(parameter);
  //   }

  MyStruct& operator=(MyStruct rhs) {
    cout << "assign op" <<endl;
    swap(*this, rhs);
    return *this;
  }

  friend void swap(MyStruct &a, MyStruct &b) {
    cout << "swap" << endl;
    using std::swap;

    swap(a.name, b.name);
    swap(a.x, b.x);
    swap(a.y, b.y);
  }

  MyStruct& operator+=(MyStruct const &a) {
    cout << "+= op" << endl;
    this->name = this->name + "+" + a.name;
    this->x += a.x;
    this->y += a.y;
    return *this;
  }

  ostream& print(ostream& out) const {
    out << "MyStruct " << name << ", x= "<<x<<", y= "<<y;
    return out;
  }

};

ostream& operator<<(ostream &lhs, MyStruct const &rhs) {
  return rhs.print(lhs);
}

inline MyStruct operator+(MyStruct lhs, MyStruct const &rhs) {
  cout << "+ op" << endl;
  lhs += rhs;
  return lhs;
}

MyStruct MakeStruct() {
  cout <<"Inside MakeStruct" << endl;
  MyStruct local("local",1,2);
  return local;
}

int main() {

  MyStruct a("a",5,7);
  MyStruct b("b",4,3);

  a=b;

  MyStruct c = a + b;

  MyStruct d(c);

  cout << a << endl;
  cout << b << endl;
  cout << c << endl;

  cout << "calling MakeStruct..." << endl;
  MyStruct e(MakeStruct());

  e.print(cout);

  return 0;
}
