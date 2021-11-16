/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:37:15 by mashad            #+#    #+#             */
/*   Updated: 2021/11/15 12:19:27 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <type_traits>

namespace ft {
	/** @brief Enable type if condition is met
	 * The type T is enabled as member type enable_if::type if Cond is true.
	 *
	 * Otherwise, enable_if::type is not defined.
	 *
	 * This is useful to hide signatures on compile time when a particular condition is not met, since in this
	 * case, the member enable_if::type will not be defined and attempting to compile using it should fail.
	 *
	 *
	 * @tparam Cond A compile-time constant of type bool
	 * @tparam T A type
	 */
	template <bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> {
		typedef T type;
	};


	template<class lhit, class rhit>
	bool equal(lhit first1, lhit last1, rhit first2)
	{
		while (first1 != last1) {
		  if (!(*first1 == *first2))
		    return false;
		  ++first1; ++first2;
		}
		return true;
	}
	template <class lhit, class rhit, class BinaryPredicate>
	bool equal ( lhit first1, lhit last1, rhit first2, BinaryPredicate pred)
	{
		while (first1!=last1) {
		  if (!pred(*first1,*first2))
		    return false;
		  ++first1; ++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2){
		while (first1!=last1)
		{
		  if (first2==last2 || *first2<*first1)
			  return false;
		  else if (*first1<*first2)
			  return true;
		  ++first1; ++first2;
		}
		return (first2!=last2);
	}
	template <class InputIterator1, class InputIterator2, class Compare>
		  bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
										InputIterator2 first2, InputIterator2 last2,
										Compare comp){
				for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
					if (comp(*first1, *first2)) return true;
					if (comp(*first2, *first1)) return false;
				}
				return (first1 == last1) && (first2 != last2);
			}
	/** @brief Is integral
	 * Traits class that identifies whether T is an integral type.
	 *
	 * It inherits from integral_constant as being either true_type or false_type, depending on whether T is an
	 * integral type.
	 *
	 * All fundamental integral types, along with all their aliases (like those in cstdint), are considered integral
	 * types by this class, including their const and volatile qualified variants.
	 *
	 * Enums are not considered integral types in C++
	 *
	 * @tparam T A type
	 */
	template <typename T> struct is_integral {static const bool value = false;};
	template <> struct is_integral<bool> {static const bool value = true;};
	template <> struct is_integral<char> {static const bool value = true;};
	template <> struct is_integral<char16_t> {static const bool value = true;};
	template <> struct is_integral<char32_t> {static const bool value = true;};
	template <> struct is_integral<wchar_t> {static const bool value = true;};
	template <> struct is_integral<signed char> {static const bool value = true;};
	template <> struct is_integral<short int> {static const bool value = true;};
	template <> struct is_integral<int> {static const bool value = true;};
	template <> struct is_integral<long int> {static const bool value = true;};
	template <> struct is_integral<long long int> {static const bool value = true;};
	template <> struct is_integral<unsigned char> {static const bool value = true;};
	template <> struct is_integral<unsigned short int> {static const bool value = true;};
	template <> struct is_integral<unsigned int> {static const bool value = true;};
	template <> struct is_integral<unsigned long int> {static const bool value = true;};
	template <> struct is_integral<unsigned long long int> {static const bool value = true;};

	/** @brief Binary function object base class
	 * This is a base class for standard binary function objects.
	 *
	 * Generically, function objects are instances of a class with member function operator() defined. This member
	 * function allows the object to be used with the same syntax as a regular function call, and therefore it's type
	 * can be used as template parameter when a generic function type is expected.
	 *
	 * In the case of binary function object, this operator() member function takes two parameters.
	 *
	 * binary_function is just a base class, from which specific binary function object are derived. It has no operator()
	 * member defined (which derived classes are expected to define) - it simply has three public data members that are
	 * typedefs of the template parameters.
	 *
	 * @tparam Arg1 Type of the first argument in member operator()
	 * @tparam Arg2  Type of second argument in member operator()
	 * @tparam Result  Type returned by member operator()
	 */
	template <class Arg1, class Arg2, class Result>
		struct binary_function {
			typedef Arg1	first_argument_type;
			typedef Arg2	second_argument_type;
			typedef Result	result_type;
		};

	/** @brief Function object class for less-than inequality comparison
	 * Binary function object class whose call returns whether it's first argument compares less than the second ( as
	 * returned by operator < ).
	 *
	 * Generically, function objects are instances of a class with member function operator() defined. This member function
	 * allows the object to be used with the same syntax as a function call.
	 *
	 * @tparam T Type of the arguments to compare by the functional call
	 */
	template <class T> struct less : binary_function <T,T,bool> {
		bool operator() (const T& x, const T& y) const {return x<y;}
	};

}