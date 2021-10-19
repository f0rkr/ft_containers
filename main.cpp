/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 08:17:35 by                   #+#    #+#             */
/*   Updated: 2021/10/19 10:11:47 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Vector/Vector.hpp"
# include <iostream>
# include <vector>

int 	main() {
	std::vector<int> a(10, 10);

	ft::Vector<int> vec(a.begin(), a.end());

	std::cout << vec[1] << " : " << vec.size() << std::endl;
	vec.resize(5);
	std::cout << vec[9] << " : " << vec.size() << std::endl;
	vec.push_back(200);
	std::cout << vec[6] << " : " << vec.size() << std::endl;
}