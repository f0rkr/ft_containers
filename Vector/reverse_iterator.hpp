/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:39:17 by                   #+#    #+#             */
/*   Updated: 2021/10/16 16:45:09 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft {
	/** @brief Reverse iterator
	 * This class reverses the direction in which a bidirectional or random-access iterator through a range
	 *
	 * A copy of the original iterator (the base iterator) is kept internally and used to reflect the operations
	 * performed on the reverse_iterator: whenever the reverse_iterator is incremented, it's vase iterator is
	 * decreased, and vise versa. A copy of the base iterator with the current state can be obtained at any time
	 * by calling member base.
	 *
	 * Notice however that when an iterator is reversed, the reversed version does not point to the same element
	 * in the range, but to the one preceding it. This is so, in order to arrange for the past-the-end element of
	 * a range: An iterator pointing to a past-the-end element in a range, is pointing to the last element (not past it)
	 * of the range (this would be the first element of the reversed range). And if an iterator to the first element
	 * in a range is reversed, the reversed iterator points to the element before the first element (this would be
	 * the past-the-end element of the reversed range).
	 *
	 * @tparam Iterator A bidirectional iterator type.
	 * Or a random-access iterator, if an operator that requires such a category of iterators is used.
	 */
	template <class Iterator> class reverse_iterator{
		public:

			/* ------------------- Member types ------------------- */

			/** @brief Iterator's type
			 * @definition Iterator to iterator_type
			 */
			typedef Iterator													iterator_type;


			/** @brief Category Iterator
			 * Preserves Iterator's category
			 */
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;

			/** @brief value type
			 * Preserves Iterator's value type
			 */
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;

			/** @brief difference type
			 * Preservers Iterator's difference type
			 */
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;

			/** @brief pointer
			 * Preserves Iterator's pointer type
			 */
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			/** @brief reference
			 * Preserves Iterator's reference type
			 */
			typedef typename ft::iterator_traits<Iterator>::reference			reference;


			/* ------------------- Member functions ------------------- */


			/** @brief Default constructor
			 * Construct a reverse iterator that points to no object.
			 * The internal base iterator is value-initialized
			 *
			 * @param none
			 * @return none
			 */
			reverse_iterator() {
				_ptr = nullptr;
			}




			/** @brief Initialization constructor
			 * Constructs a reverse iterator from some original iterator it. The behavior of the
			 * constructed object replicates the original, except that it iterates through it's
			 * pointed elements in the reverse order.
			 *
			 * @param it An iterator, whose sense of iteration is inverted in the constructed object.
			 * @Member type iterator_type is the underlying bidirectional iterator type.
			 * @return none
			 */
			explicit	reverse_iterator (iterator_type it) {
				_ptr = static_cast<pointer>(it._ptr);
				return ;
			}



			/** @brief Copy / Type-cast constructor
			 * Constructs a reverse iterator from some other reverse iterator. The constructed object
			 * keeps the same sense of iteration as rev_it.
			 *
			 * @tparam Iter
			 * @param rev_it An iterator of a reverse_iterator type, whose sense of iteration is preserved.
			 * @return none
			 */
			template <class Iter>
					reverse_iterator (const reverse_iterator<Iter>& rev_it);



			/** @brief Return base iterator
			 * Returns a copy of the base iterator.
			 *
			 * The base iterator is an iterator of the same type as the one used to construct
			 * the reverse_iterator, but pointing to the element next to the one the reverse_iterator
			 * is currently pointing to (a reverse_iterator has always as offset of -1 with respect to it's
			 * base iterator).
			 *
			 * @param none
			 * @return A copy of the base iterator, which iterates in the opposite direction.
			 * Member type iterator_type is the underlying bidirectional iterator type (the class template
			 * parameter: Iterator).
			 */
			iterator_type	base() const;




			/** @brief Dereference iterator
			 * Returns a reference to the element pointed to by the iterator
			 *
			 * Internally, the function decreases a copy of it's base iterator and return the results
			 * of dereferencing it.
			 *
			 * The iterator shall point to some object in order to be dereferenceable.
			 *
			 * @param none
			 * @return A reference to the element pointed by the iterator
			 * Member type reference is an alias of the base iterator's own reference type
			 */
			reference	operator*() const {
				return (*_ptr);
			}




			/** @brief Addition operator
			 * Return a reverse iterator pointing to the element located n positions away from the element
			 * the iterator currently points to.
			 *
			 * Internally, the function applies the binary operator- on the base iterator and return a reverse
			 * iterator constructed with the resulting iterator value.
			 *
			 * @note That this function requires the base iterator to be a random-access iterator.
			 *
			 * This operator is also overloaded as a non-member function, with the left-hand and right-hand
			 * types inserted, but this the same behavior.
			 *
			 * @param n Number of elements to offset.
			 * Member type difference_type is an alias of the base iterator's own difference type.
			 *
			 * @return An iterator pointing to the element n positions away.
			 */
			reverse_iterator	operator+ (difference_type n) const;


			/** @brief Increment iterator position
			 * Advances the reverse_iterator by one position
			 *
			 * Internally, the pre-increment version decrements the base iterator kept by the object
			 * (as if applying operator-- to it)
			 *
			 * @param none, (the second version overloads the post-increment operator).
			 * @return The pre-increment return *this.
			 * the post-increment returns the value *this had before the call.
			 */
			reverse_iterator&	operator++() {
				--_ptr;
				return *this;
			}
			reverse_iterator	operator++(int) {
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
			}


			/** @brief Advance iterator
			 * Advances the reverse_iterator by n element positions
			 *
			 * Internally, the function decreases by n the base iterator kept by the object
			 * (as if applying operator-= to it)
			 *
			 * @note that this function requires the base iterator to be a random-access iterator
			 * @param n Number of elements to offset
			 * Member type difference_type is an alias of the base iterator's own difference type.
			 * @return The reverse iterator itself (*this).
			 */
			reverse_iterator&	operator+= (difference_type n) {
				*this = *this - n;
			}



			/** @brief Subtraction operation
			 * Returns a reverse iterator pointing to the element located n positions before the element
			 * the iterator currently points to.
			 *
			 * Internally, the function applies the binary operator+ on the base iterator and returns
			 * a reverse iterator constructed with the resulting value.
			 *
			 * @note that this function requires the base iterator to be a random-access iterator.
			 *
			 * This operator is also overloaded as a non-member function to return the difference
			 * of subtracting iterators
			 * @param n Number of element to offset
			 * difference_type is a member type defined as an alias of the base iterator's won difference
			 * type (generally, an integral type).
			 * @return An iterator pointing to the element n positions before the currently pointed one.
			 */
			reverse_iterator	operator- (difference_type n) const {
				return (_ptr + n)
			}



			/** Decrease iterator position
			 * Decrease the reverse_iterator by one position.
			 *
			 * Internally, the pre-decrement increments the base iterator kept by the object (as if
			 * applying operator++ to it).
			 *
			 * @param none
			 * @return The pre-decrement return *this
			 * The post-decrement returns the value *this had before the call.
			 */
			reverse_iterator&	operator--() {
				++_ptr;
				return *this;
			}
			reverse_iterator	operator--(int) {
				reverse_iterator tmp = *this;
				++(*this);
				return (tmp);
			}



			/** @brief Retrocede iterator
			 * Decreases the reverse_iterator by n element positions.
			 *
			 * Internally, the function increases by n the base iterator kept by the object (as if
			 * applying operator+= to it).
			 *
			 * @note that this function requires the base iterator to be a random-access iterator.
			 * @param n Number of elements to offset.
			 * Member type difference_type is an alias of the base iterator's own difference type.
			 * @return The reverse iterator itself (*this)
			 */
			reverse_iterator&	operator-= (difference_type n) {
				_ptr+=n;
				return (*this);
			}


			/** @brief Dereference iterator
			 * Returns a pointer to the element pointed by the iterator (in order to access one of it's
			 * members).
			 *
			 * Internally, the function calls operator* and return it's address
			 *
			 * @param none
			 * @return A pointer to the element pointed by the iterator
			 * Member type pointer is an alias of the base iterator's own pointer type.
			 */
			pointer				operator->() const {
				return &(operator*());
			}




			/** @brief Dereference iterator with offset
			 * Accesses the element located n positions away from the element currently pointed
			 * to by the iterator.
			 *
			 * if such an element does not exist, it causes undefined behavior.
			 *
			 * Internally, the function accesses the proper element of it's base iterator, returning the
			 * same as: base()[-n-1]
			 *
			 * @param n Number of elements to offset
			 * Member type difference_type is an alias of the base iterator's own difference type
			 *
			 * @return A reference to the element n positions away from the element currently pointed
			 * by the iterator.
			 * Member type reference is an alias of the base iterator's own reference type.
			 */
			reference			operator[] (difference_type n) const {return (_ptr[n]);}

			protected:
				pointer	_ptr;

	};

	/* ------------------- Non-member function overloads ------------------- */


	/** @brief Relational operators for reverse_iterator
	 * Performs the appropriate comparison operation between the reverse_iterator objects
	 * lhs and rhs
	 *
	 * Internally, the function compares directly the base iterators using the reflexively
	 * equivalent relational operators
	 *
	 * These operators are overloaded in header <iterator>
	 * @tparam Iterator
	 * @param lhs, rhs reverse_iterator objects (to the left- and right-hand size of the operator,
	 * respectively), having both the same template parameter (Iterator).
	 * @return true if the condition holds, and false otherwise
	 */
	template <class Iterator>
		bool operator== (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
		bool operator!= (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
		bool operator< (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
		bool operator<= (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
		bool operator> (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
		bool operator>= (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs);

	/** @brief Addition operator
	 * Returns a reverse iterator pointing to the element located n positions away from the element
	 * pointed to by rev_it.
	 *
	 * The function returns the same as: rev_it+n.
	 *
	 * This operator is also overloaded as a member function to return a reverse iterator offset by -n
	 * element positions.
	 *
	 * @tparam Iterator
	 * @param n Number of elements to offset.
	 * @param rev_it  Reverse iterator.
	 * @return An iterator pointing to the element n positions away from rev_it.
	 */
	template <class Iterator>
		reverse_iterator<Iterator> operator+ (
					typename	reverse_iterator<Iterator>::difference_type n,
					const		reverse_iterator<Iterator>& rev_it
				);

	/** @brief Subtraction operator
	 * Returns the distance between lhs and rhs.
	 *
	 * The function returns the same as subtracting lhs's base iterator from rhs's base iterator.
	 *
	 * @tparam Iterator
	 * @param lhs, rhs reverse_iterator objects (to the left- and right- hand side of the operator
	 * , respectively), having both the same template parameter (Iterator).
	 * @return The number of elements between lhs and rhs.
	 */
	template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type operator- (
				const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs);
}
#endif
