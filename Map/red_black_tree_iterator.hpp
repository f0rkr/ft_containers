//
// Created by Mohamed Ashad on 10/25/21.
//

#ifndef FT_CONTAINERS_RED_BLACK_TREE_ITERATOR_HPP
#define FT_CONTAINERS_RED_BLACK_TREE_ITERATOR_HPP

# include <iostream>

namespace ft {
	
	template <class T>
	class rbTreeIterator: public ft::iterator<std::bidirectional_iterator_tag, T> {
		public:
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type		difference_type;

			rbTreeIterator() : _ptr(nullptr) {};
			rbTreeIterator(pointer ptr): _ptr(ptr) {};
			rbTreeIterator	&operator=(rbTreeIterator const &other) {
				_ptr = other._ptr;
				return (*this);
			}

			reference 	operator*();
			reference 	operator*() const;
			pointer		operator->();
			pointer 	operator->() const;


			friend bool		operator==(const rbTreeIterator &lhs, const rbTreeIterator &rhs);
			friend bool 	operator!=(const rbTreeIterator &lhs, const rbTreeIterator &rhs);

		private:
			pointer		_ptr;
	};
}
#endif //FT_CONTAINERS_RED_BLACK_TREE_ITERATOR_HPP
