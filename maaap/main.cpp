# include "Map.hpp"
# include "red_black_tree.hpp"
int	main() {


	ft::Node<ft::pair<const int, int>, std::allocator<ft::pair<const int, int> > > b(ft::make_pair(0, 10));
	ft::Node<ft::pair<const int, int>, std::allocator<ft::pair<const int, int> > > c(ft::make_pair(0, 10));
	ft::Map<int, int> a;
	ft::Map<int, int>::iterator it(&b, nullptr);
	ft::Map<int, int>::iterator ita(&c, nullptr);
	std::cout << b.data->first << " " << b.data->second << std::endl;

	a.insert(ft::make_pair(1, 20));

	it = a.begin();

	std::cout << it->first << " " << it->second<< std::endl;


	it++;
//	if (it)
//		std::cout <<  << std::endl;
//		std::cout << it->first << " " << it->second << std::endl;
//	std::cout << d << std::endl;
}
