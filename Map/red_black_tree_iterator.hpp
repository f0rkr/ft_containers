//
// Created by Mohamed Ashad on 10/25/21.
//

#ifndef FT_CONTAINERS_RED_BLACK_TREE_ITERATOR_HPP
#define FT_CONTAINERS_RED_BLACK_TREE_ITERATOR_HPP

namespace ft {
	
	template <class T>
	class rbtiterator: ft::biderectional_iterator<T> {
		public:
			typedef typename ft::biderectional_iterator<T>::value_type	value_type;
			typedef typename ft::biderectional_iterator<T>::pointer		pointer;
			typedef typename ft::biderectional_iterator<T>::
	};
}
#endif //FT_CONTAINERS_RED_BLACK_TREE_ITERATOR_HPP
