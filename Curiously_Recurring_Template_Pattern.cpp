/*
// The Curiously Recurring Template Pattern (CRTP) General Form
template<class T>
class Base
{
    // methods within Base can use template to access members of Derived
};
class Derived : public Base<Derived>
{
    // ...
};
*/
#include <iostream>

template<typename Derived>
struct Base {
	void eval() {
		static_cast<Derived&>(*this).eval();
	}
};

struct Child : Base<Child> {
	void eval() {
		std::cout << "eval in Child;" << std::endl;
	}
};

template<typename T>
void test(Base<T>& t) {
	t.eval();
}
int main() {
	Child c;
	test(c);
	system("pause");
}