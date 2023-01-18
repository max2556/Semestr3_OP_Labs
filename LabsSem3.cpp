///
/// Объединить два упорядоченных списка L1 и L2 в один упорядоченный список L1, 
/// меняя соответствующим образом ссылки в L1 и L2.
/// 

#include <iostream>
#include "List.hpp"

int main()
{
	std::cout << "Lab14. Makarov\n";

	List<int> L1({ 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 });
	List<int> L2({ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 20, 20 });

	L1.merge(&L2); //теперь L1 = L2 = L1+L2

	std::cout << "L1 = [ ";
	while(L1.getHead())
	{ 
		std::cout << L1.pop_front() << ", ";
	}
	std::cout << "\b\b";
	std::cout << " ];\n";
}

