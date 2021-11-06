//
// Created by Mohamed Ashad on 10/19/21.
//

#ifndef SET_HPP
#define SET_HPP
# include "../utils/utils.hpp"
# include "../utils/pair.hpp"
# include "../Vector/iterator_traits.hpp"
# include "../Map/red_black_tree_iterator.hpp"

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
	template < class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
		class set {
		public:
			typedef T															value_type;
			typedef T															key_type;
			typedef Compare														key_compare;
			typedef Compare														value_compare;
			typedef Alloc														allocator_type;
			typedef allocator_type::reference									reference;
			typedef allocator_type::const_reference								const_reference;
			typedef allocator_type::pointer										pointer;
			typedef allocator_type::const_pointer								const_pointer;
			typedef ft::rbTreeIterator<value_type>								iterator;
			typedef ft::rbTreeIterator<const value_type> 						const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> 						const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
			typedef size_t														size_type;

			/******************** Constructors **************************/
			/** @brief Construct set
			 * Empty container constructor, with no elements.
			 *
			 * The container keeps an internal copy of alloc and comp, which are used to allocate storage and to sort
			 * eht elements throughout its lifetime.
			 *
			 * @param comp
			 * @param alloc
			 */
			explicit set( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

			template <class InputIterator>
					set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

			set (const set& x);

			/** @brief Set destructor
			 * Destroy the container object
			 *
			 * This destroys all container elements, and deallocates all the storage capacity allocated by the set
			 * container using it's allocator.
			 *
			 * @compelixity Linear in set::size (destructors).
			 */
			~set();

			/** @brief Copy container content
			 * Assigns new contents to the container, replacing it's current content.
			 *
			 * Copies all the elements from x into the container, changing it's size accordingly.
			 *
			 * The container preserves it's current allocator, which is used to allocate additional storage
			 * if needed.
			 *
			 * The elements stored in the container before the call are either assigned to or destroyed.
			 *
			 * @param x A set object of the same type (i.e., with the same template parameters, T, Compare and Alloc).
			 * @return  *this
			 */
			set& operator= (const set& x);


			/** @brief Return iterator to beginning
			 *
			 * Returns an iterator referring to the first element in the set container.
			 *
			 * Because set containers keep their elements ordered at all times, begin points to the element that goes
			 * first following the container's sorting criterion.
			 *
			 * If the container is empty, the returned iterator value shall not be dereferenced.
			 *
			 * @param none
			 * @return An iterator to the first element in the container. If the set object is const-qualified, the function
			 * returns a const_iterator. Otherwise, it returns an iterator.
			 *
			 * Member types iterator and const_iterator are bidirectional iterator types pointing to elements.
			 */
			iterator	begin();
			const_iterator 	begin() const;


			/** @brief Return iterator to end
			 * Returns an iterator referring to the past-the-end element in the set container.
			 *
			 * The past-the-end element is the theoretical element that would follow the last element in the set container
			 * It does not point to any element, and thus shall not be dereferenced.
			 *
			 * Because the ranges used by functions of the standard library do not include the element pointed by their closing
			 * iterator, this function is often used in combination with set::begin to specify a range including all the elements
			 * in the container.
			 *
			 * If the container is empty, this function returns the same as set::begin.
			 *
			 * @param none
			 * @return An iterator to the past-the-end element in the container.
			 * If the set object is const-qualified, the function returns a const_iterator. Otherwise, it return an iterator.
			 */
			iterator	end();
			const_iterator end() const;



			/** @brief Return reverse iterator to reverse beginning
			 * Returns a reverse iterator pointing to the last element in the container (i.e., it's reverse beginning).
			 *
			 * Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
			 * rbegin points to the element preceding the on that would be pointed to by member end.
			 *
			 * @param none
			 * @return A reverse iterator to the reverse beginning of the sequence container.
			 * If the set object is const-qualified, the function returns a const_reverse_iterator. Otherwise, it returns
			 * a reverse_iterator.
			 *
			 */
			reverse_iterator 	rbegin();
			const_reverse_iterator rbegin() const;

			/** @brief Return reverse iterator to reverse end
			 * Returns a reverse iterator pointing to the theoretical element right before the first element in the set
			 * container (which is considered it's reverse end).
			 *
			 * The range between set::rbegin and set::rend contains all the elements of the container (in reverse order).
			 *
			 * @param none
			 * @return A reverse iterator to the reverse end of the sequence container.
			 * If the set object is const-qualified, the function returns a const_reverse_iterator. Otherwise, it returns a
			 * reverse_iterator.
			 */
			reverse_iterator 	rend();
			const_reverse_iterator rend();


			/** Test whether container is empty
			 * Returns whether the set container is empty (i.e. whether it's size is 0).
			 *
			 * This function does not modify the container in any way. To clear the content of a set container
			 *
			 * @param none
			 * @return  true if the container size is 0, false otherwise.
			 */
			bool empty() {return (_size == 0);}

			/** @brief Return container size
			 * Returns the number of elements in the set container.
			 *
			 * @param none
			 * @return The number of elements in the container
			 */
			size_type	size() const {return (_size);}


			/** @brief Return maximum size
			 * Returns the maximum number of elements that the set container can hold.
			 *
			 * This is the maximum potential size the container can reach due to known system or library implementation
			 * limitations, but the container is by no means guaranteed to be able to reach that size: it can still fail
			 * to allocate storage at any point before that size is reached.
			 *
			 * @param none
			 * * @return The maximum number of elements a set container can hold as content.
			 */
			size_type	max_size() const {return (allocator_type::max_size());}



			/** @brief Insert element
			 * Extends the container by inserting new elements, effectifely increasin the container size by the number
			 * of elements inserted.
			 *
			 * Because elements in a set are unique, the insertion operation checks whether each inserted element is
			 * equivalent to an element already in the container, and if so, the element is not inserted, returning an
			 * iterator to this existing element (if the function returns a value).
			 *
			 * For a similar container allowing for duplicate elements, see multiset.
			 * @param val Value to be copied (or moved) to the inserted elements.
			 * @param position Hint fot the position where the element can be inserted.
			 * @param first, last Iterators specifying a range of elements. Copies of the elements in the range [first, last[
			 * @return
			 */
			ft::pair<iterator, bool>	insert (const value_type& val);
			iterator 					insert (iterator position, const value_type& val);
			template <class InputIterator>
					void 				insert (InputIterator first, InputIterator last);


			/** @brief Erase elements
			 * Removes from the set container either a single element or a range of elements ([first, last]).
			 *
			 * This effectively reduces the container size by the number of elements removed, which are destroyed.
			 *
			 * @param position Iterator pointing to a single element to be removed from the set.
			 * @param val Value to be removed from the set.
			 * @param first, last Iterators specifying a range within the set container to be removed: [first, last].
			 * i.e., the range includes all the elements between first and last, including the element pointed by first
			 * but not the one pointed by last.
			 * @return For the value-based version, the function returns the number of elements erased.
			 */
			 void 	erase(iterator position);
			 size_type	erase(const value_type &val);
			 void 		erase(iterator first, iterator last);

			 /** @brief Swap content
			  * Exchange the content of the container by the content of x, which is another set of
			  * the same type. Sizes may differ.
			  *
			  * After the call to this member function, the element in this container are those which
			  * are in x before the call, and the elements of x are those which were in this. All iterators,
			  * references and pointers remain valid for the swapped objects.
			  *
			  * @param x Another set container of the same type as this (i.e., with the same template
			  * parameters, T, Compare and Alloc) whose content is swapped with that of this container.
			  * @return none
			  * @complixity Constant.
			  */
			  void 	swap(set& x);


			  /** @brief Clear content
			   * Removes all elements from the set container (which are destroyed), leaving the container
			   * with a size of 0.
			   *
			   * @param none
			   * @return none
			   * @complixity Linear in size (destructions)
			   */
			   void clear();


			   /** @brief Returns comparison object
			    * Returns a copy of the comparison object used by the container.
			    *
			    * By default, this a less object, which returns the same as operator<.
			    *
			    * This object determines the order of the elements iin the container: it is a function
			    * pointer or a function object that takes two arguments of the same type as the container
			    * elements, and returns true if the first argument is considered to go before the second in
			    * the strict weak ordering it defines, and false otherwise.
			    *
			    * Two elements of a set are considered equivalent if key_comp returns false reflexively(i.e no matter
			    * the order in which the elements are passed as arguments).
			    *
			    * In set containers, the keys to sort the elements are the values themselves, therefore key_comp
			    * and it's sibling member function value_comp are equivalent.
			    *
			    * @param none
			    * @return The comparison object.
			    */
			    key_compare		key_comp() const;

				/** @brief Return comparison object
				 *
				 * Returns a copy of the comparison object used by the container.
				 *
				 * By default, this is a less object, which returns the same as operator<.
				 *
				 * This object determines the order of the elements in the container: it is a function
				 * pointer or a function object that takes two arguments of the saame type as the container
				 * elements, and returns true if the first argument is considered to o before the second in the
				 * strict weak ordering it defines, and false otherwise.
				 *
				 * Two elements of a set are considered equivalent if value_comp returns false reflexively (i.e.,
				 * no matter the order in which the elements are passed as arguments).
				 *
				 * In set containers, the keys to sort the element are the values themselves, therefore value_comp
				 * and it's sibling member function key_comp are equivalent.
				 *
				 * @param none
				 * @return The comparison object
				 * @complixity Constant
				 */
				 value_compare	value_comp() const;


				 /** @brief Get iterator to element
				  * Searches the container for an element equivalent to val and returns an iterator to it if found
				  * otherwise it returns an iterator to set:end.
				  *
				  * Two elements of a set are considered equivalent if the container's comparison object returns false
				  * reflexively (i.e., no matter the order in which the elements are passed as arguments).
				  *
				  * @param val Value to be searched for.
				  * @return An iterator to the element, if val is found, or set::end otherwise.
				  * @Complexity Logarithmic in size.
				  */
				  iterator		find(const value_type& val) const;


				  /** @brief Count elements with a specific value
				   * Searches the container for elements equivalent to val and returns the number of matches
				   *
				   * Because all elements in a set container are unique, the function can only return 1 (if the element is found)
				   * or zero (otherwise).
				   *
				   * Two elements of a set are considered equivalent if the container's comparison object
				   * returns false reflexively (i.e., no matter the order in which the elements are passed as arguments).
				   *
				   * @param val Value to search for.
				   * @return 1 if the container contains an element to val, or zero otherwise.
				   * @complixity Logarithmic in size.
				   */
				   size_type	count (const value_type& val) const;


				   /** @brief Return iterator to lower bound
				    * Returns an iterator pointing to th first element in the container which is not considered
				    * to go before val (i.e., either it is equivalent or goes after).
				    *
				    * The function uses it's internal comparison object (key_comp) to determine this, returning
				    * an iterator to the first element for which key_comp(element, val) would return false.
				    *
				    * If the set class is instantiated with the default comparison type (less), the function returns
				    * an iterator to the first element that i s not less than val.
				    *
				  	* @param val Value to compare.
				    * @return An iterator to the first element in the container which is not considered to go
				    * before val, or set::end if all elements are considered to go before val.
				    * @complixity Logarithmic in size.
				    */
				    iterator lower_bound(const value_type& val) const;


					/** @brief Return iterator to upper bound
					 * Return an iterator pointing to the first element in the container which is considered to
					 * go after val.
					 *
					 * The function uses it's internal comparison object (key_comp) to determine this,
					 * returning an iterator to the first element for which key_comp(val, element) would return true.
					 *
					 * If the set class is instantiated with the default comparison type (less), the function
					 * returns an iterator to the first element that is greater than val.
					 *
					 * @param val Value to compare.
					 * @return An iterator to the first element in the container which is considered to go after val, or set:end
					 * @complixity Logarithmic in size.
					 */
					 iterator 	upper_bound (const value_type& val) const;

					/** @brief Get range of equal elements
					 * Returns the bounds of a range that includes all the elements in the container that are equivalent
					 * to val.
					 *
					 * Because all elements in a set container are unique, the range returned will contain a single element
					 * at most.
					 *
					 * If no matches are found, the range returned has a length of zero, with both iterators pointing
					 * to the first element that is considered to ggo after val according to the container's internal comparison object
					 * (key_comp).
					 *
					 * Two elements of a set are considered equivalent if the container's comparison object
					 * returns false reflexively (i.e., no matter the order in which the elements are passed as arguments).
					 *
					 * @param val Value to search for.
					 * @return The function returns a pair, whose member pair::first is the lower bound of the range
					 * (the same as lower_bound), and pair::second is the upper bound (the same as upper_bound).
					 */
					 pair<iterator, iterator> equal_range (const value_type& val) const;


					 /** @brief Get allocator
					  * Returns a copy of the allocator object associated with the set.
					  *
					  * @param none
					  * @return The allocator.
					  */
					  allocator_type	get_allocator() const { return (_alloc)};
	};
}
#endif
