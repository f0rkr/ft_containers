/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:02:36 by mashad            #+#    #+#             */
/*   Updated: 2021/10/23 11:04:18 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Vector/Vector.hpp"
# include <iostream>
# include <vector>

int 	main() {

	{
		ft::Vector<int> b(5, 10);
		ft::Vector<int> c(10, 0);
		std::cout << "capacity : " << b.capacity() << " size: " << b.size() << std::endl;

		b.insert(b.begin() + 1, 12, 0);
		ft::Vector<int>::iterator it = b.begin();
		while (it != b.end())
			std::cout << *it++ << " ";
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "me capacity : " << b.capacity() << " size: " << b.size() << std::endl;
	}

	std::cout << "**********************" << std::endl;

	{
		std::vector<int>d(5, 10);

		std::cout << "capacity : " << d.capacity() << " size: " << d.size() << std::endl;

		d.insert(d.begin() + 1, 12, 0);
		std::vector<int>::iterator at = d.begin();
		while (at != d.end())
			std::cout << *at++ << " ";
		std::cout << std::endl;
		std::cout << "capacity : " << d.capacity() << " size: " << d.size() << std::endl;
	}
//	{
//		ft::Vector<int> b(5, 1);
//		ft::Vector<int> a(1e10, 0);
//
//		a.push_back(100);
//		ft::Vector<int>::iterator it = a.begin();
//		ft::Vector<int>::iterator at = a.end();
//		for (; it != at; ++it) {
//			std::cout << *it << " ";
//		}
//		std::cout << std::endl;
//	}
//
//	std::vector<int> b(5, 1);
//	std::vector<int> a(1e10, 0);
//
//	a.push_back(100);
//	std::vector<int>::iterator it = a.begin();
//	std::vector<int>::iterator at = a.end();
//	for (; it != at ; ++it) {
//		std::cout << *it << " ";
//	}
//	std::cout << std::endl;



	 // ft::Vector<int>::iterator t = a.begin();
	// ft::Vector<int>::iterator att = a.end();
	// for (; t != att ; ++t) {
	// 	std::cout << *t << " ";
	// }
	// std::cout << std::endl;
	// vec.push_back(200);
	// std::cout << "VEC SIZE: " << a.capacity() << " " << "A size: "<< vec.capacity() << std::endl;
	// ft::Vector<int>::iterator it = vec.begin();
	// ft::Vector<int>::iterator at = vec.end();
	// for (; it != at ; ++it) {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;
	// vec.assign(a.end() - 2, a.begin());
	// it = vec.begin();
	// at = vec.end();
	// for (; it != at ; ++it) {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;
	// ft::Vector<int>::iterator d = vec.erase(vec.end() - 5, vec.end());
	// *d = 100;
	// it = vec.begin();
	// at = vec.end();
	// for (; it != at ; ++it) {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;
}