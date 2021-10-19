//
// Created by Mohamed Ashad on 10/9/21.
//

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft {

	template <typename T>
	class random_access_iterator : public ft::iterator<std::random_access_iterator_tag, T> {
		public:    

		    typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category  iterator_category;
		    typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type         value_type;
		    typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer            pointer;
		    typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference          reference;
		    typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type    difference_type;

		    random_access_iterator() : _ptr(NULL) {};
		    random_access_iterator(pointer ptr) : _ptr(ptr) {};
		    random_access_iterator &operator=(random_access_iterator const &other) {
		        _ptr = other._ptr;
		        return (*this);
		    }

		    reference   operator*() { return *_ptr; };
		    pointer     operator->() { return _ptr; };



			/** @brief Increment iterator position
			 * Advances the reverse_iterator by one position
			 *
			 * Internally, the pre-increment version decrements the base iterator kept by the object
			 * (as if applying operator-- to it)
			 *
			 * @param none, (the second version overloads the post-increment operator).
			 * @return The pre-increment return *this.
			 * the post-increment returns the value *this had before the call.
			 */
		    random_access_iterator& operator++() { ++_ptr; return *this; }  
		    random_access_iterator operator++(int) { random_access_iterator tmp = *this; ++(*this); return tmp; }

			/** @brief Decrease iterator position
			 * Decrease the random_access_iterator by one position.
			 *
			 * Internally, the pre-decrement increments the base iterator kept by the object.
			 *
			 * @param none
			 * @return The pre-decrement return *this
			 * The post-decrement returns the value *this had before the call.
			 */
		    random_access_iterator& operator--() { --_ptr; return *this; }
		    random_access_iterator operator--(int) { random_access_iterator tmp = *this; --(*this); return tmp; }

		    bool    operator!=(const random_access_iterator & it) { return (_ptr != it._ptr); }
		    bool    operator==(const random_access_iterator & it) { return (_ptr == it._ptr); }

		    size_t   operator-(random_access_iterator rhs) {return (_ptr - rhs._ptr);}

		    random_access_iterator   operator-(int rhs) {return random_access_iterator(_ptr - rhs);}
		    random_access_iterator   operator+(int rhs) {return random_access_iterator(_ptr + rhs);}

		    bool    operator<(const random_access_iterator & it) { return (_ptr < it._ptr); }
		    bool    operator>(const random_access_iterator & it) { return (_ptr > it._ptr); }
		    bool    operator<=(const random_access_iterator & it) { return (_ptr <= it._ptr); }
		    bool    operator>=(const random_access_iterator & it) { return (_ptr >= it._ptr); }

		    random_access_iterator   operator+=(int rhs) {return (*this = *this + rhs);};
		    random_access_iterator   operator-=(int rhs) {return (*this = *this - rhs);};

		    reference   operator[](int n) { return _ptr[n]; };

		    operator random_access_iterator<const value_type> () const { return random_access_iterator<const value_type>(_ptr) ; }

		private:
	    	pointer _ptr;
};

}
#endif
