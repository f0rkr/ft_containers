# include "Map.hpp"
# include "red_black_tree.hpp"
int	main() {
	ft::Map<int, int> a;
	// ft::Map<int, int>::iterator it(&b, nullptr);
	// ft::Map<int, int>::iterator ita(&c, nullptr);
	// std::cout << b.data->first << " " << b.data->second << std::endl;

	a.insert(ft::make_pair(1, 20));
	a.insert(ft::make_pair(2, 20));
	a.insert(ft::make_pair(3, 20));
	a.insert(ft::make_pair(4, 20));

	a.print();

	a.erase(3);

	a.print();


	// it++;
//	if (it)
//		std::cout <<  << std::endl;
//		std::cout << it->first << " " << it->second << std::endl;
//	std::cout << d << std::endl;
}