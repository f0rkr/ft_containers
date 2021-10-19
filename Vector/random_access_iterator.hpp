/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:31:38 by                   #+#    #+#             */
/*   Updated: 2021/10/16 10:35:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
#define FT_CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft {
	/** @brief Random Access iterator
	 * Random-access iterators are iterators that can be used to access elements at an arbitrary offset
	 * position relative to the element at an arbitrary offset position relative to the element they point
	 * to, offering the same functionality as pointers.
	 *
	 * Random-access iterators are the most complete iterators in terms of functionality. All pointer types
	 * are also valid random-access iterators.
	 *
	 * There is not a single type of random-access iterator: Each container may define it's own specific iterator
	 * type able to iterate through it and access it's elements.
	 * @tparam T
	 */
	template <class T, typename iterator = ft::iterator<std::random_access_iterator_tag, T> > class random_access_iterator {
		public:
			typedef typename iterator::pointer			pointer;
			typedef typename iterator::value_type		value_type;
			typedef typename iterator::difference_type	difference_type;
			typedef typename iterator::reference 		reference;
			typedef typename iterator::iterator_category iterator_category;
		protected:
			pointer	_ptr;
		public:
};

}
#endif //FT_CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
