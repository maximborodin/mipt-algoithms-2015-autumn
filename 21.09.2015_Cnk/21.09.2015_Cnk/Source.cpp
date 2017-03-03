#include <iostream>
#include <cstdio>

template <int n, int k>
class C
{
public:
	static const int result = C<n - 1, k - 1>::result + C<n - 1, k>::result;
};

template <int n>
class C <n, 0>
{
public:
	static const int result = 1;
};

template <int k>
class C <0, k>
{
public:
	static const int result = 0;
};
template<>
class C <0, 0>
{
public:
	static const int result = 1;
};

int main()
{
	std::cout << C<5, 2>::result << std::endl;
	for (;;);
	return 0;
}
