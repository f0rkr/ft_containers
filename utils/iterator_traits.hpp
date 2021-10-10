/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:58:02 by                   #+#    #+#             */
/*   Updated: 2021/10/10 11:34:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

# include <cstddef>

namespace ft {
	/** @brief Iterator traits
	 * Traits class defining properties of iterators
	 *
	 * Standard algorithms determine certain properties of the iterators passed to them
	 * and the range they represent by using the members of the corresponding iterator_traits
	 * instantiation.
	 *
	 * Not: For output iterators that are not at least forward iterators, any of these member types
	 * (except for iterator_category) may be defined as void.
	 *
	 * The iterator_traits class template comes with a default definition that obtains these types from
	 * the iterator type itself. It is also specialized for pointers (T*) and pointers to const (const T*).
	 *
	 * Note that any custom class will have a valid instantiation of iterator_traits if it publicly inherits
	 * the base class std::iterator.
	 * @tparam Iterator
	 */
	template <class Iterator> class iterator_traits {
		public:

			/* ----------------- Member types ----------------- */



			/** @brief Difference type
			 * Type to express the result of subtracting one iterator
			 * from another
			 */
			typedef ptrdiff_t								difference_type;



			/** @brief Value type
			 * The type of the element the iterator
			 * can point to.
			 */
			typedef typename Iterator::value_type			value_type;


			/** @brief Pointer
			 * The type of a pointer to an element
			 * the iterator can point to.
			 */
			typedef typename Iterator::value_type			pointer;


			/** @brief Reference
			 * The type of a reference to an element
			 * the iterator can point to
			 */
			typedef typename Iterator::reference			reference;


			/** @brief Iterator category
			 * The iterator category. It can be one of these:
			 *
			 * @category input_iterator_tag
			 * @category output_iterator_tag
			 * @category forward_iterator_tag
			 * @category bidirectional_iterator_tag
			 * @category random_access_iterator_tag
			 */
			typedef typename Iterator::iterator_category	iterator_category;




			/* ----------------- Categories ----------------- */


			/** @brief Input iterator category
			 * Empty class to identify the category of an iterator as an input
			 * iterator:
			 *
			 * Input iterators are iterators that can be used in sequential input operations, where
			 * each value pointed by the iterator is read only once and then the iterator is incremented
			 *
			 * All forward, bidirectional and random-access iterators are also valid input iterators.
			 *
			 * There's not a single type of input iterator: Each container may define it's own specific iterator
			 * type able to iterate through it and access it's elements.
			 */
			struct input_iterator_tag {};


			/** @brief Output iterator category
			 * Empty class to identify the category of an iterator as an output
			 * iterator.
			 *
			 * Output iterators are iterators that can be used in sequential operations ,where each
			 * element pointed by the iterator is written a value only once and then the iterator is
			 * incremented.
			 *
			 * All forward, bidirectional and random-access iterators that are not constant iterators are also
			 * valid output iterators.
			 *
			 * There's not a single type of type iterator: Each container may define it's own specific iterator type
			 * able to iterate through it and access it's elements.
			 */
			struct output_iterator_tag {};


			/** @brief Forward iterator category
			 * Empty class to identify the category of an iterator as a forward iterator
			 *
			 * Forward iterators are iterators that can be used to access the sequence of elements
			 * in a range in the direction that goes from it's beginning towards it's end
			 *
			 * Performing operations on a forward iterator that is dereferenceable never makes it's iterator
			 * value non-dereferenceable. This enables algorithms that use this category of iterators to use
			 * multiple copies of an iterator to pass more than once by the same iterator values.
			 *
			 * All bidirectional and random-access iterators are also forward iterators.
			 *
			 * There's not a single type of forward iterator: Each container may define it's own iterator type
			 * able to iterate through it and access it's elements.
			 */
			struct forward_iterator_tag {};


			/** @brief Bidirectional iterator category
			 * Empty class to identify the category of an iterator as a bidirectional iterator
			 *
			 * Bidirectional iterators are iterators that can be used to access the sequence of elements in
			 * a range in both directions (Towards the end and towards the beginning).
			 *
			 * All random-access iterators are also valid bidirectional iterators.
			 *
			 * There's not a single type of bidirectional iterator: Each container may define it's own specific
			 * iterator type able to iterator though it and access it's element.
			 */
			struct bidirectional_iterator_tag {};


			/** @brief Random-access iterator category
			 * Empty class to identify the category of an iterator as a random-access iterator
			 *
			 * Random-access iterators are iterators that can be used to access elements at an arbitrary
			 * offset position relative to the element they point to, offering the same functionality
			 * as pointers.
			 *
			 * Random-access iterators are the most complete iterators in terms of functionality. All pointer types
			 * are also valid random-access iterators.
			 *
			 * There's not a single type of random-access iterator: Each container may define it's own specific
			 * iterator type able to iterate through it and access it's elements
			 */
			struct random_access_iterator_tag {};
	};
}
#endif
