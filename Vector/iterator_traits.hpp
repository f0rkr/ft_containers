/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:58:02 by                   #+#    #+#             */
/*   Updated: 2021/10/16 10:25:42 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

# include <cstddef>
# include <iostream>

namespace ft {
	/** @brief Iterator base class
	 * This is a base class template that can be used to derive iterator classes from it. It is not an iterator class
	 * and does not provide any of the functionality an iterator an iterator is expected to have.
	 *
	 * The base class only provides some member types, which in fact are not required to be present in any iterator type
	 * (Iterator types have no specific member requirements), but they might be useful, since they define the members
	 * needed for the default iterator_traits class template to generate the appropriate instantiation automatically (
	 * and such instantiation is required to be valid for all iterator types).
	 * @tparam Category Category to which the iterator belongs to.
	 * @tparam T Type of elements pointed by the iterator.
	 * @tparam Distance Type to present the difference between two iterators.
	 * @tparam Pointer Type to represent a pointer to an element pointed by the iterator.
	 * @tparam Reference Type to represent a reference to an element pointed by the iterator.
	 */
	template <class Category,              // iterator::iterator_category
			class T,                     // iterator::value_type
			class Distance = ptrdiff_t,  // iterator::difference_type
			class Pointer = T*,          // iterator::pointer
			class Reference = T&         // iterator::reference
	> class iterator {
		public:
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;
	};
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
	template <class Iterator> class iterator_traits{
		public:

			/* ----------------- Member types ----------------- */



			/** @brief Difference type
			 * Type to express the result of subtracting one iterator
			 * from another
			 */
			typedef ptrdiff_t									difference_type;



			/** @brief Value type
			 * The type of the element the iterator
			 * can point to.
			 */
			typedef typename Iterator::value_type				value_type;


			/** @brief Pointer
			 * The type of a pointer to an element
			 * the iterator can point to.
			 */
			typedef typename Iterator::pointer					pointer;


			/** @brief Reference
			 * The type of a reference to an element
			 * the iterator can point to
			 */
			typedef typename Iterator::reference				reference;


			/** @brief Iterator category
			 * The iterator category. It can be one of these:
			 *
			 * @category input_iterator_tag
			 * @category output_iterator_tag
			 * @category forward_iterator_tag
			 * @category bidirectional_iterator_tag
			 * @category random_access_iterator_tag
			 */
			typedef typename Iterator::iterator_category		iterator_category;
	};


	template <class T> class iterator_traits<T*> {
	public:

		/* ----------------- Member types ----------------- */



		/** @brief Difference type
		 * Type to express the result of subtracting one iterator
		 * from another
		 */
		typedef ptrdiff_t				difference_type;



		/** @brief Value type
		 * The type of the element the iterator
		 * can point to.
		 */
		typedef  T				value_type;


		/** @brief Pointer
		 * The type of a pointer to an element
		 * the iterator can point to.
		 */
		typedef  T*				pointer;


		/** @brief Reference
		 * The type of a reference to an element
		 * the iterator can point to
		 */
		typedef  T&				reference;


		/** @brief Iterator category
		 * The iterator category. It can be one of these:
		 *
		 * @category input_iterator_tag
		 * @category output_iterator_tag
		 * @category forward_iterator_tag
		 * @category bidirectional_iterator_tag
		 * @category random_access_iterator_tag
		 */
		typedef std::random_access_iterator_tag	iterator_category;
	};
}
#endif
