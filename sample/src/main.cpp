#include <iostream>
#include "Foo.h"
#include <functional>
int f(int x)
{
	return	x + 3;
}
int g(int x)
{
	return x * x;
}
int calc(int(*fx)(int),int(*gx)(int), int b)
{
	return fx(gx(b));
}
void function(int a)
{
	std::cout << " toto : " << a << std::endl;
}

void foo(void(*fn)(int), int b)
{
	fn(b);
}
int composestd(const std::function<int(int)>& fn, const std::function<int(int)>& gn, int x)
{
	return fn(gn(x));
}
std::function<int(int)> composestdfunction(const std::function<int(int)>& fn, const std::function<int(int)>& gn)
{
	return [&](int x)->int { return fn(gn(x)); };
}
int main()
{
	composestdfunction(f, g)(3);
	int toto = 2;
	std::cout << composestd(f, [&](int x)->int {return x * x + toto; }, 5);
	/*std::cout << calc(g,f, 3);*/
	foo(function, 3);
	//GameObjectFactory factory;
	//auto* entyty = factory.create("Player");
	//entyty->description();
	////Foo::display();
	//delete entyty;
	return 0;
}