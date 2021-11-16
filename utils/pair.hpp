/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 08:17:55 by                   #+#    #+#             */
/*   Updated: 2021/10/10 10:24:03 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PAIR_HPP
#define PAIR_HPP


/** @brief Implementation for std::pair and std::make_pair template objects
 *
 * @copyright mashad
 */

namespace ft {
	/** Pair of values
	 * This class couples together a pair of values, which my be of different types
	 * (T1, and T2). The individual values can be accessed through it's public
	 * members first and second.
	 *
	 * Pairs are a particular case of tuple.
	 *
	 * @tparam T1 The first template parameter (T1)
	 * @tparam T2 The second template parameter (T2)
	 */
	template <class T1, class T2> struct pair {
		public:

			/* ------------- Member types ------------- */

			typedef T1	first_type;
			typedef T2	second_type;


			/* ------------- Member variables ------------- */

			first_type	first;
			second_type second;

			/** @brief Default constructor
			 * Constructs a pair object with it's elements value-initialized
			 *
			 * @param none
			 * @return none
			 * @complixity none
			 */
			pair() { return ; }


			/** @brief Copy / Move constructor (and implicit conversion)
			 * The object is initialized with the contents of the ppr pair object.
			 * The corresponding member of pr is passing to the constructor of each
			 * of it's members.
			 * @tparam U
			 * @tparam V
			 * @param pr Another pair object.
			 * This may be an object of the same type as the object being constructed
			 *  or of a pair type whose elements' types are implicitly convertible to those
			 *  in the pair being constructed.
			 */
			template< class U, class V>pair (const pair<U, V>& pr) {
				*this = pr;
				return ;
			}


			/** @brief Initialization constructor
			 * Constructs members first and second in place, passing the elements of first_args
			 * as arguments to the constructor of first, and the elements of second_args to
			 * the constructor of second.
			 *
			 * Most forms have two signatures: one taking const lvalue references, which copies
			 * the value into the pair, and one taking lvalue references, which moves them instead
			 * if their types support move semantics (for such types, the contents are transferred
			 * to the pair object and lost by their previous referrers, which are left in an unspecified
			 * but valid state).
			 *
			 * @param a An object of the type of first, or some other type implicitly convertible to it
			 * @param b An object of the type of second, or some other type implicitly convertible to it
			 */
			pair (const first_type& a, const second_type& b): first(a), second(b) {
				return ;
			}


			/**@brief Assign contents
			 * Assigns pr as the new content for the pair object.
			 *
			 * Member first is assigned pr.first, and member is assigned pr.second.
			 *
			 * The copying perform copy assignments, with the elements of it's argument preserving
			 * their values after the call.
			 * @param pr Another pair object.
			 * This may be an object of the same type or of a pair type whose elements' types are
			 * implicitly convertible.
			 * @return *this
			 */
			pair&	operator= (const pair& pr) {
                if (this == &other)
                    return (*this);
				// TO-DO: Assigns pr as the new content for this.
				this->first = pr.first;
				this->second = pr.second;
				return (*this);
			}
	};

	/**@brief Construct pair object
	 * Constructs a pair object with it's first element set to x and it's second element set to y.
	 *
	 * The template types can be implicitly deduced from the arguments passed to make_pair
	 *
	 * Pair objects can be constructed from other pair objects containing types, if the respective
	 * types are implicitly convertible.
	 *
	 *
	 * @tparam T1
	 * @tparam T2
	 * @param x, y Values for the members first and second, respectively, of the pair object being
	 * constructed.
	 * @return A pair object whose elements first and second are set to x and y respectively.
	 * The template parameters can be implicitly deduced.
	 */
	 template <class T1, class T2>
	 pair<T1, T2>	make_pair (T1 x, T2 y) {
		 return ( pair<T1,T2>(x,y) );
	 }
    template<typename T1, typename T2>
    bool	operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (lhs.first == rhs.first && lhs.second == rhs.second); }
    template<typename T1, typename T2>
    bool	operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return !(lhs == rhs); }
    template<typename T1, typename T2>
    bool	operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (lhs.first < rhs.first || lhs.second < rhs.second); }
    template<typename T1, typename T2>
    bool	operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return rhs < lhs; }
    template<typename T1, typename T2>
    bool	operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (lhs == rhs || lhs < rhs); }
    template<typename T1, typename T2>
    bool	operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (lhs == rhs || rhs < lhs); }
}

#endif