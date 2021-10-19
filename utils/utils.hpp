/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 08:40:40 by                   #+#    #+#             */
/*   Updated: 2021/10/19 09:08:29 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
}