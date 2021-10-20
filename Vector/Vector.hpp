/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:37:15 by mashad            #+#    #+#             */
/*   Updated: 2021/10/20 12:10:31 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef VECTOR_HPP
# define VECTOR_HPP

# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
# include "iterator_traits.hpp"
# include "../utils/utils.hpp"
# include <iostream>

namespace ft {

	template<class T, class Alloc = std::allocator<T> >
	class Vector {
	public:
		/**
		 * The first template parameter (T)
		 */
		typedef T                               			value_type;

		/**
		 * The second template parameter (Alloc)
		 * @defaults to: allocator<value_type>
		 */
		typedef Alloc                           			allocator_type;

		/**
		 * allocator_type::reference
		 * @for the default allocator: value_type&
		 */
		typedef typename allocator_type::reference       	reference;

		/**
		 * allocator_type::const_reference
		 * @For the default allocator: const value_type&
		 */
		typedef typename allocator_type::const_reference 	const_reference;

		/**
		 * allocator_type::pointer
		 * @for the default allocator: value_type*
		 */
		typedef typename allocator_type::pointer             pointer;


		/**
		 * allocator_type::const_pointer
		 * @for the default allocator: const value_type*
		 */
		typedef typename allocator_type::const_pointer		const_pointer;

		/**
		 * A random access iterator to value_type
		 * @convertible to iterator
		 */
		typedef typename ft::random_access_iterator<T>			iterator;

		/**
		 * A random access iterator to const value_type
		 * @const_iterator to const_iterator
		 */
		typedef typename ft::random_access_iterator<const T>	const_iterator;

		/**
		 * @reverse_iterator<iterator>
		 */
		typedef typename ft::reverse_iterator<iterator>		reverse_iterator;

		/**
		 * @reverse_iterator<const_iterator>
		 */
		typedef typename ft::reverse_iterator<iterator>		const_reverse_iterator;

		/**
		 * A signed integral type, identical to: iterator_traits<iterator>::difference_type
		 * @usualy the same as ptrdiff_t
		 */
		typedef ptrdiff_t										difference_type;


		/**
		 * An unsigned integral type that can represent any non-negative value
		 * of difference_type
		 * @usally the same as size_t
		 */
		typedef size_t											size_type;

	private:
		pointer   		_container;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_alloc;


	public:
		/** Empty container constructor ( default constructor )
		**	@Constructs an empty container, with no elements.
		 */
		explicit Vector(const allocator_type& alloc = allocator_type()): _container(nullptr), _size(0), _capacity(0) {
			_alloc.construct(_container, nullptr);
			return ;
		}


		/** Fill constructor
		** @Constructs a container with n elements. Each element is a copy of val.
		 */
		explicit Vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _size(n), _capacity(n * 2), _alloc(alloc) {
			_container = _alloc.allocate(_capacity);
			for (int i = 0; i < _size; i++)
				_alloc.construct(_container + i, val);
		}

		/** Range constructor
		** @Constructs a container with as many elements as the range [first,last], with each elements
		** constructed from it's corresponding elements in that range, in the same order.
		** @param first InputIterator
		** @param last InputIterator
		** @param alloc Allocator_type
		** @return
		 */
		template <class InputIterator>
			Vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) {
				_size = std::distance(first, last);
				_capacity= _size;
				_container = _alloc.allocate(_capacity);
				for (int i = 0; first != last; first++) {
					_alloc.construct(&_container[i], *first);
					i++;
				}
				return ;
			}


		/** Copy constructor
		** @Construct a container with a copy of each of the elements in x, in the same order.
		** @param x A vector object of the same type (i.e., with the same template parameters, T and Alloc)
		 */
		Vector(const Vector &x): _container(nullptr) {
			*this = x;
			return ;
		}

		// @The container keeps an internal copy of alloc, which is used to allocate storage throughout its lifetime.
		// @The copy constructor creates a container that keeps and uses a copy of x's allocator

		/** Vector destructor
		** @Destroy the container object.
		 */
		~Vector( void ) {
			if (_container != nullptr) {
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_container[i]);
				_alloc.deallocate(_container, _capacity);
			}
			return ;
		}

		/** Assign operator
		 * Copies all the elements from x into the container.
		 * The container preserves it's current allocator, which is used
		 * to allocate storage in case of reallocation
		 *
		 * @param x A vector object of the same type (i.e., with the same template parameters, T and Alloc)
		 * @return *this
		 */
		Vector&			operator= (const Vector& x) {
			if (_size < x._size)
				reserve(x._capacity);
			_size = x._size;
			_alloc = x._alloc;
			_capacity = x._capacity;
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(_container + i, x._container[i]);
			}
			return (*this);
		}

		// --------------------------- Iterators ------------------------------ //

		/** Return iterator to beginning
		 * Returns an iterator pointing to the first element in the vector
		 * If the container is empty, the returned iterator value shall not be dereferened.
		 *
		 * @return An iterator or const_iterator to the beginning of the sequence container.
		 */
		iterator 		begin() {
			return (iterator(&_container[0]));
		}
		const_iterator 	begin() const {
			return (const_iterator(&_container[0]));
		}



		/** Return iterator to end
		 * Returns an iterator referring to the past-the-end element in the vector container.
		 * The past-the-end element is the theoretical element that would follow the last element in the vector.
		 * It does not point to any element, and thus shall not be dereferenced.
		 *
		 * If  the container is empty, this function returns the same as vector::begin
		 * @param none
		 * @return An iterator to the element past the end of the sequence. If the vector object is const-qualified
		 * the function returns a const_iterator. Otherwise, it returns an iterator.
		 */
		iterator		end() {
			return (iterator(&_container[_size]));
		}
		const_iterator	end() const {
			return (const_iterator(&_container[_size]));
		}



		/** Return reverse iterator to reverse beginning
		 * Returns a reverse iterator pointing to the last element in the vector (i.e., it's reverse beginning).
		 * Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
		 *
		 * rbegin points to the element right before the one that would be pointed by member end.
		 * @return A reverse iterator to the reverse beginning of the sequence container. If the vector object is const-qualified
		 * the function returns a const_reverse_iterator. Otherwise, it returns a reverse_iterator.
		 */
		reverse_iterator		rbegin() {
			return (reverse_iterator(&_container[_size - 1]));
		}
		const_reverse_iterator	rbegin() const {
			return (const_reverse_iterator(&_container[_size - 1]));
		}



		/** Return reverse iterator to reverse end
		 * Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (which
		 * is considered it's reverse end).
		 * The range between vector::rbegin and vector::rend contains all the elements of the vector (in reverse order).
		 *
		 * @return A reverse iterator to the reverse end of the sequence container. If the vector objet is const-qualified,
		 * the function returns a const_reverse_iterator. Otherwise, it returns a reverse_iterator.
		 */
		reverse_iterator		rend(){
			return (reverse_iterator(&_container[0]));
		}
		const_reverse_iterator	rend() const{
			return (const_reverse_iterator(&_container[0]));
		}

		// ___________________________________________________________________ //
		// --------------------------- Capacity ------------------------------ //
		// ------------------------------------------------------------------- //


		/** Return size
		 * Returns the number of elements in the vector.
		 * This is the number of actual objects held in the vector, which is not necessarily equal to it's storage capacity.
		 *
		 * @return The number of elements in the container. Member type size_type is an unsigned integral type.
		 */
		size_type	size() const {
			return (_size);
		}


		/** Return maximum size
		 * Returns the maximum number of elements that the vector can hold
		 *
		 * @return The maximum number of elements a vector container can hold as content. Member type size_type
		 * is an unsigned integral type.
		 */
		size_type	max_size() const {
			return (_alloc.max_size());
		}



		/** Change size
		 * Resizes the container so that it contains n elements.
		 * If n is smaller than the current container size, the content is reduced to it's first n elements, removing
		 * those beyond (and destroying them).
		 *
		 * If n is greater than the current container size, the content is expanded by inserting at the end as many elements
		 * as needed to reach a size of n. If val is specified, the new elements are initialized as copies of val, otherwise
		 * they are value-initialized
		 *
		 * If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space
		 * takes place. Notice that this function changes the actual content of the container by inserting or erasing elements from it.
		 *
		 * @param n New container size, expressed in number of elements. Member type size_type is an unsigned integral type.
		 * @param val Object whose content is copied to the added elements in case that n is greater than the current container size.
		 * If not specified, the default constructor is used instead.
		 * Member type value_type is the type of the elements in the container, defined in vector as an alias of the first template parameter (T)
		 */
		void 		resize(size_type n, value_type val = value_type()) {
			if (n <= _size) {
				for (int i = n + 1; i < _size ; i++)
					_alloc.destroy(&_container[i]);
				_size = n;
			} else {
				if (n > _capacity)
					reserve(n * 2);
				for (size_type i = _size; i < n; i++) {
					_alloc.construct(&_container[i], val);
				}
				_size = n;
			}
		}


		/** Return size of allocated storage capacity
		 * Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
		 *
		 * The capacity is not necessarily equal to the vector size. It can be equal or greater, with the extra space allowing to
		 * accommodate for growth without the need to reallocate on each insertion.
		 *
		 * Notice that this capacity does not suppose a limit on the size of the vector. When this capacity is exhausted and more is
		 * needed, it is automatically expanded by the container (reallocating it storage space). The theoretical limit on the size of
		 * a vector is given by member max_size
		 *
		 * The capacity of a vector can be explicitly altered by calling member vector::reverse
		 *
		 * @return The size of the currently allocated storage capacity in the vector, measured in terms of the number elements
		 * it can hold. Member type size_type is an unsigned integral type.
		 */
		size_type	capacity() const {
			return (_capacity);
		}


		/** Test whether vector is empty
		 * Returns whether the vector is empty (i.e. whether it's size is 0).
		 *
		 * This function does not modify the container in any way.
		 * @return true if the container size is 0, false otherwise
		 */
		bool		empty() const {
			return (_size == 0);
		}


		/** Request a change in capacity
		 * Request that the vector capacity be at least enough to contain n elements.
		 *
		 * If n is greater than the current vector::capacity, the function causes the container to reallocate it's
		 * storage increasing it's capacity to n (or greater).
		 *
		 * In all other cases, the function call does not cause a reallocation and the vector capacity is not effected
		 * This function has no effect on the vector size and cannot alter it's elements.
		 *
		 * @param n Minimum capacity for the vector. Note that the resulting vector capacity may be equal or greater than n.
		 * Member type size_type is an unsigned integral type.
		 * @return none
		 */
		void		reserve(size_type n) {
			if (n > _capacity) {
				pointer tmp = _alloc.allocate(n);
				for (size_type i = 0; i < _size ; i++) {
					_alloc.construct(&tmp[i], _container[i]);
					_alloc.destroy(&_container[i]);
				}
				if (_container)
					_alloc.deallocate(_container, _capacity);
				_container = tmp;
				_capacity = n * 2;
			}
		}


		// ___________________________________________________________________ //
		// ------------------------- Element access -------------------------- //
		// ------------------------------------------------------------------- //


		/** Access element
		 * Returns a reference to the element at position n in the vector container.
		 *
		 * A similar member function, vector::at, has the same behavior as this operator function
		 * except that vector::at is bound checked and signals if the requested position is out of range
		 * by throwing an out_of_range exception.
		 *
		 * Portable programs should never call this function with an argument n that is out of range, since this causes
		 * undefined behavior.
		 *
		 * @param n Position of an element in the container. Notice that the first element has a position of 0 not 1. Member
		 * type size_type is an unsigned integral type.
		 * @return The element at the specified position in the vector. If the vector is const-qualified, the function
		 * returns a const_reference. Otherwise, it returns a reference.
		 * Member types reference and const_reference are the reference types to the elements of the container.
		 */
		reference			operator[] (size_type n) {
			return (this->_container[n]);
		}
		const_reference		operator[] (size_type n) const {
			return (this->_container[n]);
		}




		/** Access element
		 * Returns a reference to the element at position n in the vector.
		 * The function automatically checks whether n is within the bounds of valid elements in the vector, throwing
		 * an out_of_range exception if it is not (i.e., if n is greater than, or equal to, it's size). This is in contrast
		 * with member operator[], that does not check against bounds.
		 *
		 * @param n Position of an element in the container. If this is greater than, or equal to, the vector size,
		 * an exception of type out_of_range is thrown. Notice that the first element has a position of 0 (not 1).
		 * Member type size_type is an unsigned integral type.
		 *
		 * @return The element at the specified position in the container. If the vector object is const-qualified, the
		 * function returns a const_reference. Otherwise, it returns a reference. Member types reference and const_reference
		 * are the reference types to the elements of the container.
		 */
		reference			at (size_type n){
			if (n < 0 || n >= this->_size)
				throw std::out_of_range("ft::vector::at");
			return (this->_container[n]);
		}
		const_reference 	at (size_type n) const {
			if (n < 0 || n >= this->_size)
				throw std::out_of_range("ft::vector::at");
			return (this->_container[n]);
		}




		/** Access first element
		 * Returns a reference to the first element in the vector.
		 * Unlike member vector::begin, which returns an iterator to this same element, this function returns a direct reference.
		 * Calling this function on an empty container causes undefined behavior.
		 *
		 * @param none
		 * @return A reference to the first element in the vector container. If the vector object is const-qualified,
		 * the function returns a const_reference. Otherwise, it returns a reference.
		 * Member types reference and const_reference are the reference types to the elements of the container.
		 */
		reference			front() {
			return (this->_container[0]);
		}
		const_reference		front() const{
			return (this->_container[0]);
		}




		/** Access last element
		 * Returns a reference to the last element in the vector.
		 * Unlike member vector::end, which returns an iterator just past this element, this function returns a direct
		 * reference.
		 * Calling this function on an empty container causes undefined behavior.
		 *
		 * @param none
		 * @return A reference to the last element in the vector.
		 * If the vector object is const-qualifier, the function returns a const_reference. Otherwise, it returns a reference.
		 * Member types reference and const_reference are the reference types to the elements of the vector.
		 */
		reference 			back(){
			return (this->_container[this->_size - 1]);
		}
		const_reference		back() const{
			return (this->_container[this->_size - 1]);
		}


		// ___________________________________________________________________ //
		// -------------------------    Modifiers   -------------------------- //
		// ******************************************************************* //

		/** Assign vector content
		 * Assigns new content to the vector, replacing it's current contents, and modifying it's size accordingly.
		 *
		 * The new contents are elements constructed from each of the elements in the range between first and last, in
		 * the same order. If a reallocation happens, the storage needed is allocated using the internal allocator.
		 *
		 * Any elements held in the container before the call are destroyed and replaced by newly constructed elements (
		 * no assignments of elements take place).
		 * This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses
		 * the current vector capacity.
		 *
		 * @tparam InputIterator
		 * @param first, last Input iterators to the initial and final position in a sequence. The range used is [first, last], which
		 * includes all the elements between first and last, including the element pointed by first but not the element pointed by last
		 * The function template argument InputIterator shall be an input iterator type that points to elements of a type from which
		 * value_type object can be constructed.
		 * @return none
		 */
		template <class InputIterator>
				void	assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) {
					difference_type dis = std::distance(first, last);
					size_type position = 0;
					if (dis > _size)
						reserve(dis);
					for (position = 0; first != last; first++ ) {
						_alloc.construct(&_container[position++], *first);
					}
					for (; position < _size; position++) {
						_alloc.destroy(&_container[position]);
					}
					_size = dis;
				}



		/** Assign vector content
		 * Assigns new contents to the vector, replacing it's current contents, and modifying it's size accordingly
		 *
		 * The new contents are n elements, each initialized to a copy of val.
		 * If a reallocation happens, the storage needed is allocated using the internal allocator.
		 *
		 * Any elements held in the container before the call are destroyed and replaced by newly constructed elements (no
		 * assignments of elements take place).
		 * This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size
		 * surpasses the current vector capacity.
		 *
		 * @param n New size for the container. Member type size_type is an unsigned integral type.
		 * @param val Value to fill the container with. Each of the n elements in the container will be initialized to
		 * a copy of this value. Member type value_type is the type of elements in the container, define in vector as an
		 * alias of it's first template parameter (T).
		 * @return none
		 */
		void 			assign (size_type n, const value_type& val) {
			if (n > _size) {
				reserve(n);
			}
			_size = n;
			for (size_type i = 0; i < _size ; i++) {
				_alloc.construct(&_container[i], val);
			}
		}





		/** Add element at the end
		 * Adds a new element at the end of the vector, after it's current last element. The content of val is copied (or
		 * moved) to the new element.
		 *
		 * This effectively increase the container size by one, which causes an automatic reallocation of the allocated storage
		 * space if -and only if- the new vector size surpasses the current capacity.
		 *
		 * @param val Value to be copied (or moved) to the new element. Member type value_type is the type of the elements in
		 * the container, defined in vector as an alias of it's first template parameter (T).
		 * @return none
		 */
		void 			push_back (const value_type& val) {
			if (_size + 1 > _capacity) {
				reserve(_capacity * 2);
			}
			_alloc.construct(&_container[_size], val);
			_size++;
		}






		/** Delete last element
		 * Removes the last element in the vector, effectively reducing the container size by one.
		 * This destroys the removed element.
		 *
		 * @param none
		 * @return none
		 */
		void 			pop_back() {
			_alloc.destroy(&_container[_size - 1]);
			_size--;
		}






		/** Insert elements
		 * The vector is extended by inserting new elements before the element at the specified position, effectively
		 * increasing the container size by the number of elements inserted.
		 *
		 * This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpass
		 * the current vector capacity
		 *
		 * Because vectors use an array as their underlying storage, inserting elements in positions other than the vector end
		 * causes the container to relocate all the elements that were after position to their new positions. This is generally an
		 * inefficient operation compared to the one performed for the same operation by other kinds of sequence containers
		 *
		 * The parameters determine how many elements are inserted and to which value they are initialized
		 *
		 * @param position Position in the vector where the new elements are inserted. iterator is a member type,
		 * defined as a random access iterator type that points to elements.
		 * @param val Value to be copied (or moved) to the inserted elements. Member type value_type is the type of the
		 * elements in the container, defined in deque as an alias of it's first template parameter (T).
		 * @return An iterator that points to the first of the newly inserted elements. Member type iterator is a
		 * random access iterator type that points to elements.
		 * If reallocations happen, the storage is allocated using the container's allocator, which may throw
		 * exceptions on failure (for the default allocator, bad_alloc is thrown if the allocation request does not succeed).
		 */
		iterator	insert	(iterator position, const value_type& val) {

		}







		/** Insert elements
		 * The vector is extended by inserting new elements before the element at the specified position, effectively
		 * increasing the container size by the number of elements inserted.
		 *
		 * This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpass
		 * the current vector capacity
		 *
		 * Because vectors use an array as their underlying storage, inserting elements in positions other than the vector end
		 * causes the container to relocate all the elements that were after position to their new positions. This is generally an
		 * inefficient operation compared to the one performed for the same operation by other kinds of sequence containers
		 *
		 * The parameters determine how many elements are inserted and to which value they are initialized
		 *
		 * @param position Position in the vector where the new elements are inserted. iterator is a member type,
		 * defined as a random access iterator type that points to elements.
		 * @param n Number of elements to insert. Each element is initialized to a copy of val. Member type size_type
		 * is an unsigned integral type.
		 * @param val Value to be copied (or moved) to the inserted elements. Member type value_type is the type of the
		 * elements in the container, defined in deque as an alias of it's first template parameter (T).
		 * @return none. If reallocations happen, the storage is allocated using the container's allocator, which may throw
		 * exceptions on failure (for the default allocator, bad_alloc is thrown if the allocation request does not succeed).
		 */
		void 		insert	(iterator position, size_type n, const value_type& val) {
			difference_type index = std::distance(begin(), position);

			if (_size + n > _capacity)
				reserve(_size + n);
			for (difference_type i = index ;i < index + n;i++) {
				_alloc.construct(&_container[i + n], _container[i]);
				_alloc.construct(&_container[i], val);
			}
			_size = _size + n;
			return ;
		}


		/** Insert elements
		 * The vector is extended by inserting new elements before the element at the specified position, effectively
		 * increasing the container size by the number of elements inserted.
		 *
		 * This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpass
		 * the current vector capacity
		 *
		 * Because vectors use an array as their underlying storage, inserting elements in positions other than the vector end
		 * causes the container to relocate all the elements that were after position to their new positions. This is generally an
		 * inefficient operation compared to the one performed for the same operation by other kinds of sequence containers
		 *
		 * The parameters determine how many elements are inserted and to which value they are initialized
		 *
		 * @tparam InputIterator
		 * @param position Position in the vector where the new elements are inserted. iterated is a member type, defined
		 * as a random access iterator type that points to elements.
		 * @param (first, last) Iterators specifying a range of elements. Copies of the elements in the range [first, last]
		 * are inserted at position (in the same order).
		 * Notice that the range includes all the elements between first and last, including the element pointed by first
		 * but not the one pointed by last.
		 * The function template argument InputIterator shall be an input iterator type that points to elements of a type
		 * from which value_type objects can be constructed.
		 * @return An iterator that points to the first of the newly inserted elements. Member type iterator is a random
		 * access iterator type that points to elements.
		 * If reallocations happen, the storage is allocated using the container's allocator, which may throw
		 * exceptions on failure (for the default allocator, bad_alloc is thrown if the allocation request does not succeed).
		 */
		template <class InputIterator>
				void		insert (iterator position, InputIterator first, InputIterator last) {

				}




		/** Erase elements
		 * Removes from the vector either a single element (position) or a range of elements ([first, last]).
		 *
		 * This effectively reduces the container size by the number of elements removed, which are destroyed.
		 *
		 * Because vectors use an array as their underlying storage, erasing elements in positions other than the vector::end
		 * causes the container to relocate all the elements after the segment erased to their new position. This is generally an
		 * inefficient operation compared to the one performed for the same operation by other kinds of sequence containers
		 * @param position Iterators pointing to a single element to be removed from the vector.
		 * Member tye iterator and const_iterator are random access iterator types that point to elements.
		 * @param (first, last) Iterators specifying a range within the vector to be removed: [first, last] .i.e., the range
		 * includes all the elements between first and last, including the element pointed by first but not the one pointed by last.
		 * @return An iterator pointing to the new location of the element that followed the last element erased by the
		 * function call. This is the container end if the operation erased the last element in the sequence.
		 */
		iterator		erase (iterator position) {
			for (difference_type i = std::distance(begin(), position); i < _size - 1 ; i++ ) {
				_alloc.construct(&_container[i], _container[i + 1]);
			}
			_alloc.destroy(&_container[_size - 1]);
			_size--;
			return (position);
		}
		iterator 		erase (iterator first, iterator last) {
			// TO-DO: Destroy elements from first to last.
			difference_type start = std::distance(begin(), first);
			difference_type index = std::distance(last, end());
			for (difference_type i = start; i <  index + start ; i++) {
				_alloc.construct(&_container[i], _container[i + index]);
				_alloc.destroy(&_container[i + index]);
			}
			_size = _size - std::distance(first, last);
			return (last + 1);
		}



		/** Swap content
		 * Exchanges the content of the container by the content of x, which is another vector object of the same type.
		 * Sizes may differ
		 *
		 * After the call to this member function, the elements in this container are those which were in x before the call,
		 * and the elements of x are those which were in this. All iterators, references and pointers remain valid for the swapped
		 * objects.
		 *
		 * Notice that a non-member function exists with the same name, swap, overloading that algorithm with an optimization that
		 * behaves like this member function
		 * @param x Another vector container of the same type (i.e., instantiated with the same template parameters, T and Alloc)
		 * whose content is swapped with that of this container.
		 * @ return none
		 */
		void 			swap (Vector& x) {
			std::swap(_size, x._size);
			std::swap(_alloc, x._alloc);
			std::swap(_capacity, x._capacity);
			std::swap(_container, x._container);
		}


		/** Clear content
		 * Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.[
		 *
		 * A reallocation is not guaranteed to happen, and the vector capacity is not guaranteed to change due to calling
		 * this function. A typical alternative that forces a reallocation is to use swap.
		 *
		 * @param none
		 * @return none
		 */
		void 			clear() {
			if (!this->empty())
				return;
			for (size_type i = 0; i < _size; i++) {
				_alloc.destory(&_container[i]);
			}
			this->_size = 0;
		}


		// ___________________________________________________________________ //
		// -------------------------    Allocators  -------------------------- //
		// ******************************************************************* //



		/** Get allocator
		 * Returns a copy of the allocator object associated with the vector
		 * @param none
		 * @return The allocator.
		 * Member type allocator_type is the type of the allocator used by the container, define in vector
		 * as an alias of it's second template parameter (Alloc).
		 */
		allocator_type		get_allocator() const {
			return (allocator_type());
		}
	};

	// ___________________________________________________________________ //
	// ----------------- Non-member function overloads  ------------------ //
	// ******************************************************************* //



	/** Relation operators for vector
	 * Performs the appropriate comparison operation between the vector containers lhs and rhs.
	 * The equality comparison (operator==) is performed by first comparing sizes, and if they match, the elements
	 * are compared sequentially using operator==, stopping at the first mismatch (as if using algorithm equal).
	 *
	 * The less-than comparison (operator<) behaves as if using algorithm lexicographical_compare, which compares the elements
	 * sequentially using operator< in a reciprocal manner (i.e., checking both a<b and b<a) and stopping at the first
	 * occurrence.
	 *
	 * The other operations also use the operators == and < internally to compare the elements behaving as if the following
	 * equivalent operations were performed.
	 * @tparam T
	 * @tparam Alloc
	 * @param (lhs, rhs) vector containers (to the left- and right-hand side of the operator, respectively), having
	 * both the same template parameters (T and Alloc)
	 * @param rhs
	 * @return true if the condition holds, and false otherwise.
	 */
	template <class T, class Alloc>
		bool 	operator== (const Vector<T, Alloc>& lhs, const Vector<T,Alloc>& rhs) {
			if (lhs._size != rhs._size)
				return (false);
			for (int i = 0; i < lhs._size ; i++) {
				if (lhs._array[i] != rhs._array[i])
					return (false);
			}
			return (true);
	}
	template <class T, class Alloc>
		bool	operator!= (const Vector<T, Alloc>& lhs, const Vector<T,Alloc>& rhs) {
			return (!lhs == rhs);
		}
	template <class T, class Alloc>
		bool 	operator< (const Vector<T, Alloc>& lhs, const Vector<T,Alloc>& rhs) {
			if (lhs._size >= rhs._size)
				return (false);
			for (int i = 0; i < lhs._size ; i++) {
				if (lhs._array[i] >= rhs._array[i])
					return (false);
			}
			return (true);
		}
	template <class T, class Alloc>
		bool 	operator<= (const Vector<T, Alloc>& lhs, const Vector<T,Alloc>& rhs) {
			if (lhs._size > rhs._size)
				return (false);
			for (int i = 0; i < lhs._size ; i++) {
				if (lhs._array[i] > rhs._array[i])
					return (false);
			}
			return (true);
		}
	template <class T, class Alloc>
		bool 	operator>	(const Vector<T, Alloc>& lhs, const Vector<T,Alloc>& rhs) {
			return (!lhs >= rhs);
		}
	template <class T, class Alloc>
		bool 	operator>=	(const Vector<T, Alloc>& lhs, const Vector<T,Alloc>& rhs){
			return (!lhs < rhs);
		}






	/** Exchange contents of vectors
	 * The contents of container x are exchanged with those of y. Both objects must be of the same type (same template parameters),
	 * although sizes may differ.
	 *
	 * After the call to this member function, the elements in x are those which were in y before the call, and the
	 * elements of y are those which were in x. All iterators, references and pointers remain valid for the swapped objects.
	 *
	 * This is an overload of the generic algorithm swap that improves it's performance by mutually transferring ownership
	 * over their assets to the other container (i.e, the containers exchange references to their data, without actually
	 * performing any element copy or movement): it behaves as if x.swap(y) was called.
	 * @tparam T
	 * @tparam Alloc
	 * @param x, y vector containers of the same type (i.e, having both the same template parameters, T and Alloc).
	 * @return none
	 */
	template <class T, class Alloc>
	void 	swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y) {
		x.swap(y);
	}
}

#endif