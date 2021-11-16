/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 08:16:34 by                   #+#    #+#             */
/*   Updated: 2021/11/15 10:28:47 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "Vector.hpp"

namespace ft {
	/** Stack template
	 ** Stack are a type of container adaptor, specifically designed to operate in a LIFO
	 ** context (last-in first-out), where elements are inserted and extracted only from
	 ** one end of the container.
	 **
	 ** @tparam T Type of the elements. Aliased as member type stack::value_type.
	 ** @tparam Alloc Type of the internal underlying container object where the
	 ** elements are stored. It's value_type shall be T.
	 ** Aliased as member type stack::container_type.
	*/
	template <class T, class Container = ft::Vector<T, class   = allocator<T> >>>
			class Stack {
				private:
					Container	*_cntr;
				public:
					/** Value type
					 * The first template parameter T
					 * Types of the elements
					 */
					typedef	T		value_type;



					/** Container type
					 * The second template parameter (Container)
					 * Type of the underlying container
					 */
					 typedef Container		container_type;



					 /** Size type
					  * An unsigned integral type
					  * usually the same sa size_t
					  */
					 typedef size_t			size_type;


					 /** Construct stack
					  * Constructs a stack container adaptor object
					  *
					  * A container adaptor keeps internally a container object as data. This
					  * container object is a copy of the ctnr argument passed to the
					  * constructor, if any, otherwise it is an empty container.
					  *
					  * @param ctnr Container object.
					  * container_type is the type of the underlying container type (defined
					  * as an alias of the second class template parameter, Container)
					  * @return none
					  */
					 explicit	Stack (const container_type& ctnr = container_type());


					 /* -------------------- Member functions -------------------- */



					 /** Test whether container is empty
					  * Returns whether the stack is empty: i.e. whether it's size is zero.
					  *
					  * This member function effectively calls member empty of the underlying
					  * container object
					  * @param none
					  * @return true if the underlying container's size is 0, false otherwise
					  */
					 bool 		empty() const {return ((this->_cntr->size() == 0 ? true : false))}



					 /** Return size
					  * Returns the number of elements in the stack
					  *
					  * This member function effectively calls member size
					  * of the underlying container object
					  * @param none
					  * @return The number of elements in the underlying container.
					  * Member type size_type is an unsigned integral type.
					  */
					 size_type	size() const {return (this->_cntr->size())}



					 /** Access next element
					  * Returns a reference to the top element in the stack
					  *
					  * Since stacks are last-in first-out containers, the top element is the last
					  * element inserted into the stack.
					  *
					  * This member function effectively calls member back of the underlying container
					  * object
					  * @param none
					  * @return A reference to the top element in the stack
					  * Member type value_type is the type of the elements in the container (defined as an alias of the
					  * class template parameter, T)
					  */
					 value_type&		top() {return (this->_cntr->back())};
					 const value_type&	top() const {return (this->_cntr->back())};




					 /** Insert element
					  * Inserts a new element at the top of the stack, above it's current top element. The content
					  * of this new element is initialized to a copy of val.
					  *
					  * This member function effectively calls the member function push_back of the underlying
					  * container object.
					  *
					  * @param val Value to which the inserted element is initialized
					  * Member type value_type is the type of the elements in the container (defined as an alias of the
					  * first class template parameter, T)
					  * @return none
					  */
					 void 				push (const value_type& val) {this->_cntr->push_back(val)};




					 /** Remove top element
					  * Removes the element on to of the stack, effectively reducing it's size by one.
					  *
					  * The element removed is the latest element inserted into the stack, whose value can
					  * be retrieved by calling member stack::top
					  *
					  * This calls the removed element's destructor
					  *
					  * This member function effectively calls the member function pop_back of the underlying
					  * container object
					  * @param none
					  * @return none
					  */
					 void 				pop(this->_cntr->pop_back());
			};

			/* -------------------- Non-member function overload -------------------- */


			/** Relation operators for stack
			 * Performs the appropriate comparison operation between lhs and rhs
			 * Each of these operator overloads calls the same operator on the
			 * underlying container objects
			 *
			 * @tparam T
			 * @tparam Container
			 * @param lhs, rhs Stack objects (to the left- and right-hand size of the operator, respectively).
			 * @return true if the condition holds, and false otherwise
			 */
			template <class T, class Container>>
					bool 	operator==	(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
			template <class T, class Container>>
					bool	operator!=	(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
			template <class T, class Container>>
					bool	operator<	(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
			template <class T, class Container>>
					bool	operator<=	(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
			template <class T, class Container>>
					bool 	operator>	(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
			template <class T, class Container>>
					bool 	operator>=	(const stack<T,Container>& lhs, const stack<T,Container>& rhs);


}

#endif