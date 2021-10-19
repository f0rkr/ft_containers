//
// Created by Mohamed Ashad on 10/19/21.
//

#ifndef SET_HPP
#define SET_HPP

namespace ft {
	/** @brief Set
	 * Sets are containers that store unique elements following a specific order.
	 *
	 * In a set, the value of an element also identifies it (the value is itself the key, of type T), and each value must be unique.
	 * The value of the elements in a set cannot be modified once in the container (the elements are always const),
	 * but they can be inserted or removed from the container.
	 *
	 * Internally, the elements in a set are always sorted following a specific strict weak ordering criterion indicated
	 * by its internal comparison object (of type Compare).
	 *
	 * set containers are generally slower than unordered_set containers to access individual elements by
	 * their key, but they allow the direct iteration on subsets based on their order.
	 *
	 * Sets are typically implemented as binary search trees.
	 * @tparam T
	 * @tparam Compare
	 * @tparam Alloc
	 */
	template < class T,                        // set::key_type/value_type
			class Compare = less<T>,        // set::key_compare/value_compare
			class Alloc = allocator<T>      // set::allocator_type
	> class set {

	};
}
#endif
