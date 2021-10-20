/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:02:36 by mashad            #+#    #+#             */
/*   Updated: 2021/10/20 16:29:40 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Vector/Vector.hpp"
# include <iostream>
# include <vector>

int 	main() {
	ft::Vector<int> a(11, 10);

	ft::Vector<int> vec(15, 10);

	a = vec;

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