//
// Created by Mohamed Ashad on 10/25/21.
//

#ifndef FT_CONTAINERS_RED_BLACK_TREE_ITERATOR_HPP
#define FT_CONTAINERS_RED_BLACK_TREE_ITERATOR_HPP

# include <iostream>
# include "../Vector/iterator_traits.hpp"
namespace ft {
	
	template <class T>
	class rbTreeIterator: public ft::iterator<std::bidirectional_iterator_tag, T> {
		public:
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type		difference_type;

			rbTreeIterator() : _ptr(nullptr), _root(nullptr) {};
			rbTreeIterator(pointer ptr, pointer root): _ptr(ptr) , _root(root){};
			rbTreeIterator	&operator=(rbTreeIterator const &other) {
				_ptr = other._ptr;
                _root = other._root;
				return (*this);
			}

			reference 	operator*() {return (*_ptr);}
			reference 	operator*() const {return (*_ptr);}
			pointer		operator->() {return (_ptr);}
			pointer 	operator->() const {return (_ptr);}

			rbTreeIterator	&operator++() {
				if (_ptr == nullptr)
						return (nullptr);
				_ptr = _ptr->_inOrderPredecessor(_ptr);
				return (*this);
			}
			rbTreeIterator		operator++(int) {
				rbTreeIterator	tmp = *this;

				if (_ptr == nullptr)
					return (nullptr);
				_ptr = _ptr->_inOrderPredecessor(_ptr);
				return (tmp);
			}
			rbTreeIterator		&operator--() {
				if (_ptr == nullptr)
					return (nullptr);
				_ptr = _ptr->_inOrderSucessor(_ptr);
				return (*this);
			}
			rbTreeIterator		operator--(int) {
				rbTreeIterator	tmp = *this;
				_ptr = _ptr->_inOrderSucessor(_ptr);
				return (tmp);
			}
			friend bool		operator==(const rbTreeIterator &lhs, const rbTreeIterator &rhs) {return (lhs._ptr == rhs._ptr);}
			friend bool 	operator!=(const rbTreeIterator &lhs, const rbTreeIterator &rhs) {return (lhs._ptr != rhs._ptr);}

		private:
			pointer		_root;
            pointer     _ptr;
	};

}
#endif //FT_CONTAINERS_RED_BLACK_TREE_ITERATOR_HPP
