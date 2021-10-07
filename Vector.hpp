/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:11:44 by                   #+#    #+#             */
/*   Updated: 2021/09/22 09:04:52 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MAP_HPP
# define MAP_HPP

namespace ft {
	template<class T, class Alloc = allocator<T>>
	class Map {
	private:
		T   *_array;

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
		typedef allocator_type::reference       			reference;

		/**
		 * allocator_type::const_reference
		 * @For the default allocator: const value_type&
		 */
		typedef allocator_type::const_reference 			const_reference;

		/**
		 * allocator_type::pointer
		 * @for the default allocator: value_type*
		 */
		typedef allocator_type::pointer             		pointer;


		/**
		 * allocator_type::const_pointer
		 * @for the default allocator: const value_type*
		 */
		typedef allocator_type::const_pointer       		const_pointer;

		/**
		 * A random access iterator to const value_type
		 * @convertible to const_iterator
		 */
		typedef ft::random_access_iterator::iterator    	iterator;

		/**
		 * A random access iterator to const value_type
		 * @const_iterator
		 */
		typedef ft::random_access_iterator::const_iterator	const_iterator;

		/**
		 * @reverse_iterator<iterator>
		 */
		typedef ft::reverse_iterator::iterator				reverse_iterator;

		/**
		 * @reverse_iterator<const_iterator>
		 */
		typedef ft::reverse_iterator::const_iterator		const_reverse_iterator;

		/**
		 * A signed integral type, indentical to: iterator_traits<iterator>::difference_type
		 * @usualy the same as ptrdiff_t
		 */
		typedef ptrdiff_t									difference_type;


		/**
		 * An unsigned integral type that can represent any non-negative value
		 * of difference_type
		 * @usally the same as size_t
		 */
		typedef size_t										size_type;

		/** Empty container constructor ( default constructor )
		**	@Constructs an empty container, with no elements.
		 */
		explicit Vector(const allocator_type& alloc = allocator_type());


		/** Fill constructor
		** @Constructs a container with n elements. Each element is a copy of val.
		 */
		explicit Vector(size_type n, const value_type& val = value_type());

		/** Range constructor
		** @Constructs a container with as many elements as the range [first,last], with each elements
		** constructed from it's corresponding elements in that range, in the same order.
		** @param first InputIterator
		** @param last InputIterator
		** @param alloc Allocator_type
		** @return
		 */
		templat <class InputIterator>
		Vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());


		/** Copy constructor
		** @Construct a container with a copy of each of the elements in x, in the same order.
		** @param x
		 */
		Vector(const Vector &x);

		// @The container keeps an internal copy of alloc, which is used to allocate storage throughout its lifetime.
		// @The copy constructor creates a container that keeps and uses a copy of x's allocator

		/** Vector destructor
		** @Destroy the container object.
		 */
		~Vector( void );

		/** Assign operator
		 * Copies all the elements from x into the container.
		 * The container preserves it's current allocator, which is used
		 * to allocate storage in case of reallocation
		 *
		 * @param x A vector object of the same type (i.e., with the same template parameters, T and Alloc)
		 * @return *this
		 */
		Vector&			operator= (const Vector& x);

		// --------------------------- Iterators ------------------------------ //

		/** Return iterator to beginning
		 * Returns an iterator pointing to the first element in the vector
		 * If the container is empty, the returned iterator value shall not be dereferened.
		 *
		 * @return An iterator or const_iterator to the beginning of the sequence container.
		 */
		iterator 		begin();
		const_iterator 	begin() const;



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
		iterator 		end();
		const_iterator 	end();



	};
}

#endif