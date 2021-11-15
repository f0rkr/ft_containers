/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 19:00:53 by mashad            #+#    #+#             */
/*   Updated: 2021/11/14 15:25:43 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MAP_HPP
# define MAP_HPP

# include "../utils/pair.hpp"
# include "../utils/utils.hpp"
# include "RBTree.hpp"
# include <iostream>

namespace ft {
	/** Map template
	 * Maps are associative containers that store elements formed by a combination of a key
	 * value and a mapped value, following a specific order.
	 *
	 * In a map, the key values are generally used to sort and uniquely identify the elements, while
	 * the mapped values sort the content associated to this Key. The types and mapped value may differ,
	 * and are grouped together in member type value_type, which is a pair type combining both
	 *
	 * Internally, the elements in a map are always sorted by it's key following a specific strict weak
	 * ordering criterion indicated by it's internal comparison object (of type Compare).
	 *
	 * map containers are generally slower than unordered_map containers to access individual elements by their
	 * key, but they allow the direct iteration on subsets based on their order.
	 *
	 * The mapped values in a map can be accessed directly by their corresponding key using the bracket operator ([])
	 * Maps are typically implemented as binary search trees.
	 *
	 * @tparam Key Type of the keys. Each element in a map is uniquely identified by it's key value.
	 * aliased as member type map::key_type.
	 * @tparam T Type of the mapped value. Each element in a map stores some data as it's mapped value.
	 * Aliased as member type map::mapped_type.
	 * @tparam Compare A binary predicate that takes two element keys as arguments and returns a bool. The expression
	 * comp(a, b), where comp is an object of this type and a and b are key values, shall return true if a is considered
	 * to go before b in the strict weak ordering the function defines.
	 * The map object uses this expression to determine both the order the elements follow in the container and whether
	 * two element keys are equivalent (by comparing them reflexively: they are equivalent if !comp(a,b) && !comp(b,a).
	 * No two elements in a map container can have equivalent keys.
	 * This can be a function pointer or a function object. This defaults to less<T>, which returns the same as applying
	 * the less-than operator (a<b).
	 * Aliased as member type map::key_compare.
	 * @tparam Alloc Type of the allocator object used to define the storage allocation model. By default, the allocator class
	 * template is used, which defines the simplest memory allocation model and is value-independent.
	 * Aliased as member type map::allocator_type.
	 */
	template <	class Key, class T, class Compare = ft::less<Key>, class Alloc = std::alllocator<ft::pair<const Key, T>> >
			class map {
				public:

					/* --------------------------- Member types --------------------------- */


					/**
					 * key_type
					 * The first template parameter (Key)
					 */
					typedef Key																key_type;

					/**
					 * mapped_type
					 * The second template parameter (T)
					 */
					typedef T																mapped_type;


					typedef ft::pair<const key_type, mapped_type>							value_type;

					/**
					 * key_compare
					 * The third template parameter (Compare)
					 * @defaults to: less<key_type>
					 */
					typedef less<key_type>													key_compare;

					/**
					 * value_compare
					 * Nested function class to compare elements
					 */
					typedef  name;


					/**
					 * allocator_type
					 * The forth template parameter (Alloc)
					 * @defaults to : allocator<value_type>
					 */
					typedef Alloc															allocator_type;


					/**
					 * reference
					 * allocator_type::reference
					 * @defaults: allocator value_type&
					 */
					typedef allocator_type::reference										reference;





					/**
					  * const_reference
					  * allocator_type::const_reference
					  * @defaults: allocator const value_type&
					  */
					typedef allocator_type::const_reference								const_reference;





					/**
					  * pointer
					  * allocator_type::pointer
					  * @defaults: allocator value_type*
					  */
					typedef allocator_type::pointer										pointer;





					/**
					   * const_pointer
					   * allocator_type::const_pointer
					   * @defaults: allocator const value_type*
					   */
					typedef allocator_type::cont_pointer								const_pointer;





					/**
					 * iterator
					 * a bidirectional iterator to value_type
					 * @convertible to const_iterator
					 */
					typedef typename ft::randome_access_iterator::iterator				iterator;


					/**
					 * const_iterator
					 * A bidirectional iterator to const value_type
					 */
					typedef typename ft::randome_access_iterator::const_iterator		const_iterator;



					/**
					 * reverse_iterator
					 * reverse_iterator<iterator>
					 */
					typedef typename ft::reverse_iterator::iterator						reverse_iterator;



					/**
					 * const_reverse_iterator
					 * reverse_iterator<const_iterator>
					 */
					typedef typename ft::reverse_iterator::const_iterator				const_reverse_iterator;


					/**
					 * difference_type
					 * A signed integral type, identical to:
					 * iterator_traits<iterator>::difference_type
					 */
					typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;




					/**
					 * size_type
					 * An unsigned integral type that can represent any non-negative value of
					 * difference_type
					 */
					typedef size_t														size_type;

					typedef ft::RBTree<value_type, value_compare, allocator_type>						tree_type;
					class value_compare {
						public:
							typedef key_compare		comp;
							bool	operator()(const value_type& x, const value_type& y) const {
								return comp()(x.first, y.first);
							}
					}
				private:
					tree_type		*_rbtree;
					key_compare		_compare;
					value_compare	_value_compare;
					allocator_type	_alloc;
				public:
					/* --------------------------- Member functions --------------------------- */

					/** @Default constructor
				     * Construct a map container object, initializing it's contents depending
				     * on the constructor version used.
				     *
					 * Empty container constructor (default constructor)
					 * Constructs an empty container, with no elements.
					 * @param comp Binary predicate that, taking two element keys as argument, returns true if
					 * the first argument goes before the second argument in the strict weak ordering it defines
					 * and false otherwise.
					 * This shall be a function pointer or a function object.
					 * Member type type_compare is the internal comparison object type sed by the container,
					 * defined in map as an alias of it's third template parameter (Compare).
					 * if key_compare uses the default less (which has no state), this parameter is not relevant.
					 * @param alloc Allocator object.
					 * The container keeps and uses an internal copy of this allocator.
					 * Member type allocator_type tis the internal allocator type used by the container, defined in
					 * map as an alias of it's fourth template parameter (Alloc).
					 * If allocator_type is an instantiation of the default allocator (which has no state), this
					 * parameter is not relevant.
					 */
					explicit Map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _rbtree(nullptr), _alloc(alloc), _compare(comp), _value_compare(value_compare());







					/** @Range constructor
					 * Construct a map container object, initializing it's contents depending
					 * on the constructor version used.
					 *
					 * Constructs a container with as many elements as the range [first, last], with each
					 * element constructed from it's corresponding element in that range.
					 *
					 * The container keeps an internal copy of alloc and comp, which are used to allocate
					 * storage and to sort the elements throughout it's lifetime.
					 * @tparam InputIterator
					 * @param first
					 * @param last
					 * @param comp Binary predicate that, taking two element keys as argument, returns true if
					 * the first argument goes before the second argument in the strict weak ordering it defines
					 * and false otherwise.
					 * This shall be a function pointer or a function object.
					 * Member type type_compare is the internal comparison object type sed by the container,
					 * defined in map as an alias of it's third template parameter (Compare).
					 * if key_compare uses the default less (which has no state), this parameter is not relevant.
					 * @param alloc Allocator object.
					 * The container keeps and uses an internal copy of this allocator.
					 * Member type allocator_type tis the internal allocator type used by the container, defined in
					 * map as an alias of it's fourth template parameter (Alloc).
					 * If allocator_type is an instantiation of the default allocator (which has no state), this
					 * parameter is not relevant.
					 * @return none
					 */
					template <class InputIterator>
									  Map (InputIterator first, InputIterator last,
										   const key_compare& comp = key_compare(),
										   const allocator_type& alloc = allocator_type()) {
									  	_compare = comp;
									  	_alloc = alloc;
									  	_value_compare = value_compare();
									  	for (InputIterator it = first, it != last ; it++) {
									  		_rbtree.insert(*tmp);
									  	}
									  }



					/** @Copy constructor
					 * Constructs a container with a copy of each of the elements in x
					 *
					 * The container keeps an internal copy of alloc and comp, which are used to allocate
					 * storage and to sort elements throughout it's lifetime.
					 * The copy constructor creates a container that keeps and uses copies of x's allocator and
					 * comparison object.
					 * The storage for the elements is allocated using this internal allocator.
					 *
					 * @param x Another map object of the same type (with the same class template arguments Key, T
					 * , Compare and Alloc), whose contents are either copied of acquired.
					 * @return none
					 */
					Map (const Map& x) {*this = x;}





					/** Map @Destructor
					 * Destroys the container object.
					 * This destroys all container elements, and deallocates all the storage capacity allocated
					 * by the map container using it's allocator.
					 *
					 * @complixity Linear
					 * @return none
					 */
					~Map();


					/** @Copy container content
					 * Assigns new contents to the container, replacing it's current content.
					 *
					 * Copies all the elements from x into the container, changing it's size accordingly
					 * The container preserves it's current allocator, which is used to allocate additional
					 * storage if needed.
					 *
					 * The elements stored in the container before the call are either assigned to or destoryed
					 *
					 * @param x A map object of the same type(i.e., with the same template parameters, Key, T
					 * Compare and Alloc).
					 * @return  *this
					 * @complixity Linear in sizes (destruction, copies).
					 */
					Map&			operator= (const Map& x) {
						if (*this == other)
							return (*this);
						_rbtree = other._rbtree;
						_alloc = x._alloc;
						_compare = x._compare;
						_value_compare = x._value_compare;
						return (*this);
					}


					/* --------------------------- Iterators --------------------------- */



					/** Return iterator to beginning
					 * Returns an iterator referring to the first element in the map container
					 *
					 * Because map containers keep their elements ordered at all times, begin points to the
					 * element that goes first following the container's sorting criterion.
					 *
					 * If the container is empty, the returned iterator value shall not be dereferenced.
					 * @param none
					 * @return An iterator to the first element in the container.
					 * If the map object is const-qualified, the function returns a const_iterator.Otherwise,
					 * it returns an iterator.
					 * Member types iterator and const_iterator are bidirectional iterator types pointing to
					 * elements (of type value_type).
					 * Notice that value_type in map containers is an alias of pair<const key_type, mapped_type>
					 * @complixity constant.
					 */
					iterator			begin() {return _rbtree->begin();}
					const_iterator 	begin() const {return _rbtree.begin();}




					/** Returns iterator to end
					 * Return an iterator referring to the past-the end element in the map container.
					 *
					 * The past-the-end element is theoretical element that would follow the last element in
					 * the map container. It does not point to any element, and thus shall not be dereferenced
					 *
					 * Because the ranges used by functions of the standard library do not include the element
					 * pointed by their closing iterator, this function is often used in combination with
					 * map::begin to specify a range including all the elements in the container.
					 *
					 * If the container is empty, this function returns the same as map::begin
					 *
					 * @param none
					 * @return An iterator past-the-end element in the container.
					 * If the map object is const-qualified, the function returns a const_iterator. Otherwise,
					 * it returns an iterator. Member types iterator and const_iterator are bidirectional iterator
					 * types pointing to elements.
					 * @complixity constant
					 */
					iterator 			end() {return _rbtree.end();}
					const_iterator 	end() const {return _rbtree.end();}




					/** Return reverse iterator to reverse beginning
					 * Returns a reverse iterator pointing to the last element in the container (i.e, it's
					 * reverse beginning).
					 *
					 * Reverse iterators iterate backwards: increasing them moves them towards the beginning
					 * of the container.
					 *
					 * rbegin points to the element preceding the one that would be pointed to by member end.
					 *
					 * @param none
					 * @return A reverse iterator to the reverse beginning of the sequence container.
					 * If the map object is const-qualified, the function returns a const_reverse_iterator.
					 * Otherwise, it returns a reverse_iterator.
					 *
					 * Member types reverse_iterator and const_reverse_iterator and reverse bidirectional
					 * iterator types pointing to elements.
					 * @complixity Constant
					 */
					reverse_iterator			rbegin() {return _rbtree.rbegin();}
					const_reverse_iterator	rbegin() const {return _rbtree.end();}








					/** Return reverse iterator to reverse end
					 * Returns a reverse iterator pointing to the theoretical element right before the first
					 * element in the map container (which is considered it's reversed end).
					 *
					 * The range between map::rbegin and map::rend contains all the elements of the container
					 * (in reverse order).
					 *
					 * @param none
					 * @return A reverse iterator to the reverse end of the sequence container.
					 * If the map object is const-qualified, the function returns a const_reverse_iterator.
					 * Otherwise, it returns a reverse_iterator.
					 *
					 * Member types reverse_iterator and const_reverse_iterator are reverse bidirectional
					 * iterator types pointing to elements.
					 * @complixity Constant
					 */
					reverse_iterator				rend() {return (_rbtree.rend());}
					const_reverse_iterator		rend() const {return (_rbtree.rend());}




					/* --------------------------- Capacity --------------------------- */





					/** Test whether container is empty
					 * Returns whether the map container is empty (i.e. whether it's size is 0)
					 *
					 * This function does not modify the container in any way. To clear the content of a map
					 * container.
					 *
					 * @param none
					 * @return true if the container size is 0, false otherwise
					 * @complixity constant
					 */
					bool				empty() const {
						return (_rbtree.getSize() == 0);
					}




					/** Return container size
					 * Return the number of elements in the map container.
					 *
					 * @param none
					 * @return The number of elements in the container
					 * Member type size_type is an unsigned integral type
					 * @complixity constant
					 */
					size_type			size() const {return (_rbtree.getSize())}




					/** Return maximum size
					 * Returns the maximum number of elements that the map container can hold.
					 *
					 * This is the maximum potential size the container can reach due to known system or
					 * library implementation limitations, but the container is by no means guaranteed to be
					 * able to reach that size:: it can still fail to allocate storage at any point before
					 * that size is reached
					 *
					 * @param none
					 * @return The maximum number of elements a map container can hold as content.
					 * Member type size_type is an unsigned integral type
					 * @complexity Constant
					 */
					size_type			max_size() const {
						return (_rbtree.max_size());
					}



					/* --------------------------- Element access --------------------------- */


					/** Access element
					 * If k matches the key of an element in the container, the function returns a reference
					 * to it's mapped value.
					 *
					 * If k does not match the key of any element in the container, the function inserts a new
					 * element with that key and returns a reference to it's mapped value. Notice that this
					 * always increase the container size by one, even if no mapped value is assigned to the
					 * element (the element is constructed using it's default constructor).
					 *
					 * A similar member function, map::at has the same behavior when an element with the key
					 * exist, but throws an exception when it does not.
					 *
					 * @param k Key value of the element whose mapped value is accessed.
					 * Member type key_type is the type of the keys for the elements stored in the container,
					 * defined in map as an alias of it's first template parameter (Key).
					 * If an rvalue (second version), the key is moved instead of copied when a new element
					 * is inserted.
					 * @return A reference to that mapped value of the element with a key equivalent to k.
					 * Member type mapped_type is the type of the mapped values in the container, define in map
					 * as an alias of it's second template parameter (T).
					 * @complixity Logarithmic in size
					 */
					mapped_type&	operator[] (const key_type& k) {
						iterator 
					}


					/** Insert elements
					 * Extends the container by inserting new elements, effectively increasing the container size by
					 * the number of elements inserted.
					 *
					 * Because element keys in a map are unique, the insertion operation checks whether each inserted
					 * element has a key equivalent to the one of an element already in the container, and if so, the
					 * element is not inserted, returning an iterator to this existing element (if the function returns
					 * a value).
					 *
					 * An alternative way to insert elements in a map is by using member function map::operator[]
					 *
					 * Internally, ma containers keep all their elements sorted by their key following the criterion
					 * specified by it's comparison object. The elements are always inserted in it's respective position
					 * following this ordering.
					 *
					 * The parameters determine how many elements are inserted and to which values they are initialized:
					 *
					 *
					 * @param val value to copied to (or move as) inserted element.
					 * member type value_type is the type of the elements in the container, defined in map as pair<const
					 * key_type, mapped_type>
					 * The template parameter P shall be a type convertible to value_type
					 * If P is instantiated as a reference type, the argument is copied.
					 * @param position Hint for the position where the element can be inserted.
					 * The function optimizes it's insertion time if position points to the element that will precede the
					 * inserted element.
					 * Notice that this is just a hint that does not force the new element to be inserted at that position
					 * within the map container (the elements in a map always follow a specific order depending on their
					 * key).
					 * Member types iterator and const_iterator are defined in map as bidirectional iterator types that point
					 * to elements
					 * @param first, last Iterators specifying a range of [first, last] are inserted in the container.
					 * Notice that the range includes all the elements between first and last, including the element
					 * pointed by first but not the one pointed by last.
					 * The function template argument InputIterator shall be an input iterator type that points to elements
					 * of a type from which value_type objects can be constructed.
					 * @return The single element return a pair, with it's member pair::first set to an iterator pointing
					 * to either the newly inserted element or to the element with an equivalent key in the map. The
					 * pair::second element in the pair is set to true if a new element was inserted or false if an equivalent
					 * key already existed.
					 *
					 * The version with a hint (2) return an iterator pointing to either the newly inserted element or
					 * the element that already had an equivalent key in the map.
					 *
					 * Member type iterator is a bidirectional iterator type that points to elements.
					 * @complixity if a single element is inserted, logarithmic in size in general, but amortized constant
					 * if a hint is given and the position given is the optimal. If N elements inserted, Nlog(size+N)
					 * in general, but linear in size+N if the elements are already sorted according to the same ordering
					 * criterion used by the container.
					 */
					pair<iterator, bool>	insert (const value_type& val) {
						return _rbtree.insert(val);
					}
					iterator				insert (iterator position, const value_type& val) {
						return _rbtree.insert(val).first;
					}
					template <class InputIterator>
							void 			insert (InputIterator first, InputIterator last) {
								for (InputIterator it = first; it != last; it++) {
									_rbtree.insert(*it);
								}
							}






					/** Erase elements
					 * Remove from the map container either a single element or a range of elements ([first, last]).
					 *
					 * This effectively reduces the container size by the number of elements removed, which are destroyed.
					 *
					 * @param position	Iterator pointing to a single element to be removed from the map.
					 * This shall point to a valid and dereferenceable element.
					 * Member types iterator and const_iterator are bidirectional iterator types that point to elements.
					 * @param k Key of the element to be remove from the map.
					 * Member type key_type is the type of the elements in the container, defined in map as an alias of it's
					 * first template parameter <key>.
					 * @param first, last Iterators specifying a range within the map container to be removed: [first, last].i.e,
					 * the range includes all the elements between first and last, including the element pointed by first
					 * but not the one pointed by last.
					 * Member types iterator and const_iterator are bidirectional iterator types that point to elements.
					 * @return For the key-based version (2), the function the number of element erased.
					 * Member type size_type is an unsigned integral type.
					 */
					void 					erase (iterator position) {
						_rbtree.remove(*position);
					}
					size_type				erase (const key_type& k) {
						iterator it = find(k);

						if (k != end()) {
							_rbtree.remove(*found);
							return (1);
						}
						return (0);
					}
					void 					erase (iterator first, iterator last) {
						for (iterator it = first; it != last ; it++) {
							_rbtree.remove(*it);
						}
					}




					/** Swap content
					 * Exchanges the content of the container by the content of x, which is anotherr map of the same type
					 * Sizes may differ.
					 *
					 * After the call to this member function, the elements in this container are those which were in x
					 * before the call, and the elements of x are those which were in this. All iterators, references
					 * and pointers remain valid for the swapped objects.
					 *
					 * Notice that a non-member function exists with the same name, swap overloading that algorithm with an
					 * optimization that behaves like this member function
					 *
					 * Whether the internal container allocators and comparison objects are swapped is undefined.
					 *
					 * @param x Another map container of the same type as this (i.e., with the same template
					 * parameters, key, T, Compare and Alloc) whose content is swapped with that of this container.
					 * @return none
					 * @complixity Constant
					 */
					void 					swap (Map& x) {
						ft::swap(_alloc, x._alloc);
						ft::swap(_compare, x._compare);
						ft::swap(_value_compare, x._value_compare);
						_rbtree.swap(x._rbtree);
					}



					/** Clear content
					 * Remove all elements from the map container (which are destroyed), leaving the container with a
					 * size of 0.
					 *
					 * @param none
					 * @return none
					 * @complixity Linear in size (destructions).
					 */
					void 					clear() {_rbtree.clear();}





					/* --------------------------- Observers --------------------------- */



					/** Return key comparison object
					 * Returns a copy of the comparison object used by the container to compare keys.
					 *
					 * The comparison object of a map object is set on construction. It's type (member key_compare) is
					 * the third template parameter of the map template. By default, this is a less object, which returns
					 * the same as operator<.
					 *
					 * This object determines the order of the elements in the container: it's a function pointer or a
					 * function object that takes two arguments of the same types as the element keys, and returns true
					 * if the first argument is considered to go before the second in the strict weak ordering it defines,
					 * and false otherwise.
					 *
					 * Two keys are considered equivalent if key_comp returns false reflexively (i.e., no matter the order
					 * in which they keys are passed as arguments).
					 *
					 * @param none
					 * @return The comparison object.
					 * Member type key_compare is the tye of the comparison object associated to the container, defined
					 * in map as an alias of it's third template parameter (Compare).
					 * @complixity none
					 */
					key_compare 	key_comp() const {return (_compare);}





					/** Return value comparison object
					 * Returns a comparison object that can be used to compare two elements to get whether the key of the first
					 * one goes before the second.
					 *
					 * The arguments taken by this function object are of member type value_type (defined in map as an alias
					 * oof pari<const key_type, mapped_type>), but the mapped_type part of the value is not taken into
					 * consideration in this comparison.
					 *
					 * The comparison object returned is an object of the member type map::value_compare, which is a nested
					 * class that uses the internal comparison object ot generate the appropriate comparison functional
					 * class
					 *
					 * The public member of this comparison class returns true if the key of the first argument is considered
					 * to go before that of the second (according to the strict weak ordering specified by the container's comparison
					 * object, key_comp), and false otherwise.
					 *
					 * Notice that value_compare has no public constructor, therefore no objects can directly created from this
					 * nested class outside map members
					 *
					 * @param none
					 * @return The comparison object for element values.
					 * Member type value_compare is a nested class type.
					 * @complixity constant
					 */
					value_compare	value_comp() const {return _value_compare;}




					/* --------------------------- Operations --------------------------- */




					/** Get iterator to element
					 * Searches the container for an element with a key equivalent to k and returns an iterator to it
					 * if found, otherwise it returns an iterator to map::end;
					 *
					 * Two keys are considered equivalent if the container's comparison object returns false reflexively
					 * (i.e., no matter the order in which the elements are passed as arguments).
					 *
					 * Another member function, map:count, can be used to just check whether a particular key exist.
					 *
					 * @param k Key to be searched for.
					 * Member type key_type is the type of the keys for the elements in the container, defined in map as
					 * an alias of it's first template parameter (Key).
					 *
					 * @return An iterator to the element, if an element with specified key is found, or map::end otherwise.
					 * If the map object is const-qualified, the function returns a const_iterator. Otherwise, it returns
					 * as iterator.
					 *
					 * Member types iterator and const_iterator are bidirectional iterator types pointing to elements (of
					 * type value_type).
					 *
					 * Notice that value_type in map container is an alias of pair<const key_type, mapped_type>.
					 * @complixity Logarithmic in size
					 */
					iterator 		find (const key_type& k);
					const_iterator 	find (const key_type& k) const;







					/** Count elements with a specific key
					 * Search the container for elements with a key equivalent to k and returns the number of matches
					 *  Because all elements in a map container are unique, the function can only return 1 (if the element
					 *  is found) or zero otherwise.
					 *
					 *  Two keys are considered equivalent fi the container's comparison object return false reflexively
					 *  (i.e., no matter the order in which the keys are passed as arguments).
					 *
					 * @param k Key to search for.
					 * Member type key_type is the type of the element keys in the container, defined in map as an alias
					 * of it's first template parameter (Key).
					 * @return 1 if the container contains as element whose key is equivalent to k, or zero otherwise.
					 * Member type size_type is an unsigned integral type.
					 * @complixity Logarithmic in size
					 */
					size_type		count (const key_type& k) const;




					/** Return iterator to lower bound
					 * Returns an iterator pointing to the first element in the container whose key is not considered
					 * to go before k (i.e., either it is equivalent or goes after).
					 *
					 * The function uses it's integral comparison object (key_comp) to determine this, return an iterator
					 * to the first element which key_comp(element_key, k) would return false.
					 *
					 * If the map class is instantiated with the default comparison type (less), the function returns an iterator
					 * to the first element whose key is not less than k.
					 *
					 * A similar member function, upper_bound ,has the same behavior as lower_bound, except in the case that
					 * the map contains an element with a key equivalent to k: In this case, lower_bound returns an iterator
					 * pointing to that element, whereas upper_bound return an iterator pointing to the next element.
					 *
					 * @param k Key to search for.
					 * Member type key_type is the type of the elements in the container, defined in map as an alias of it's
					 * first template parameter (Key).
					 * @return An iterator to the first element in the container whose key is not considered to go before k,
					 * or map::end if all keys are considered to go before k.
					 *
					 * If the map object is const-qualified, the function return a const_iterator. otherwise, it returns an
					 * iterator.
					 *
					 * Member types iterator and const_iterator are bidirectional iterator types pointing to element (of type
					 * value_type).
					 * Notice that value_type in map containers is itself also a pair type: pair<const key_type, mapped_type>.
					 * @complixity Logarithmic in size
					 */
					iterator 		lower_bound (const key_type& k);
					const_iterator	lower_bound (const key_type& k) const;






					/** Return iterator to upper bound
					 * Return an iterator pointing to the first element in the container whose key is considered to go
					 * after k.
					 *
					 * The function uses it's internal comparison object (key_comp) to determine this, return an iterator
					 * to the first element whose key is greater than k.
					 *
					 * A similar member function, lower_bound, has the same behavior as upper_bound, except in the case that
					 * the map container an element with a key equivalent to k: In this case lower_bound returns an iterator
					 * pointing to that element, whereas upper_bound returns an iterator pointing to the next element.
					 *
					 * @param k Key to search for.
					 * Member type key_type is the type of the elements in the container, defined in map as an alias of it's
					 * first template parameter (Key).
					 * @return An iterator to the first element in the container whose key is considered to go after k,
					 * or map::end if no keys are considered to go after k.
					 * If the map object const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator
					 *
					 * Member types iterator and const_iterator are bidirectional iterator types pointing to elements.
					 * @complixity Logarithmic in size
					 */
					iterator		upper_bound (const key_type& k);
					const_iterator 	upper_bound (const key_type& k) const;





					/** Get range of equal elements
					 * Returns the bound of a range that includes all the elements in the container which have a key
					 * equivalent to k.
					 *
					 * Because the elements in a map container have unique keys, the range returned will contain a single
					 * element at most.
					 *
					 * If no matches are found, the range returned has a length of zero, with both iterators pointing to the
					 * first element that has a key considered to go after k according to the container's internal
					 * comparison object (key_comp).
					 *
					 * Two keys are considered equivalent if the container's comparison object returns false reflexively
					 * (i.e., no matter the order in which the keys are passed as arguments).
					 *
					 * @param k Key to search for.
					 * Member type key_type is the type elements in the container, defined as an alias of it's first
					 * template parameter (Key).
					 * @return The function returns a pair, whose member pair::first is the lower bound of the range
					 * ( the same as lower_bound), and pair:second is the upper bound (the same as upper_bound).
					 *
					 * If the map object is const_qualified, the function returns a pair of const_iterator. Otherwise
					 * a pair of iterator.
					 *
					 * Member types iterator and const_iterator are bidirectional iterator types pointing to elements
					 * (of type value_type).
					 * Notice that value_type in map containers is itself also a pair type: pair<const key_type, mapped_type>.
					 * @complixity Logarithmic in size
					 */
					pair<const_iterator, const_iterator>	equal_range (const key_type& k) const;
					pair<iterator, iterator>				equal_range (const key_type& k);




					/* --------------------------- Allocators --------------------------- */



					/** Get allocator
					 * Return a copy of the allocator object associated with the map.
					 *
					 * @param none
					 * @return The allocator.
					 * Member type allocator_type is the type of the allocator used by the container, defined in map as
					 * an alias of it's fourth template parameter (Alloc).
					 * @complixity Constant
					 */
					allocator_type		get_allocator() const;
			};
}

#endif