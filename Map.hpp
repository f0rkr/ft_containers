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
            typedef T                               			value_type;
            typedef Alloc                           			allocator_type;
            typedef allocator_type::reference       			reference;
            typedef allocator_type::const_reference 			const_reference;
            typedef allocator_type::pointer             		pointer;
            typedef allocator_type::const_pointer       		const_pointer;
            typedef ft::random_access_iterator::iterator    	iterator;
			typedef ft::random_access_iterator::const_iterator	const_iterator;
			typedef ft::reverse_iterator::iterator				reverse_iterator;
			typedef ft::reverse_iterator::const_iterator		const_reverse_iterator;
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;

            explicit Vector(const allocator_type& alloc = allocator_type());
			explicit Vector(size_type n, const value_type& val = value_type());
			templat <class InputIterator>
					Vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			Vector(const Vector &x);

            Map(Map const &);

            ~Map(void);

            mapped_tye &operator[](const key_type &k); // Element operator overload
            // Capacity Function declaration
            bool empty(void) const;

            size_type size(void) const;

            size_type max_size(void) const;

            // End of capacity Function declaration
            void swap(map &x);

            void clear(void);

            // Observers compare function declaration
            key_compare key_comp(void) const;

            value_compare value_comp(void) const;
            // Operations function declaration
    };
}

#endif