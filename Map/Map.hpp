/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <mashad@student.1337.ma>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 08:12:13 by                   #+#    #+#             */
/*   Updated: 2021/11/23 11:43:05 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once
#ifndef MAP_HPP
#define MAP_HPP

# include <iostream>
# include "pair.hpp"
# include "red_black_tree.hpp"
# include <iterator>
# include "../Vector/reverse_iterator.hpp"
// # include "../Vector/Vector.hpp"
namespace ft {
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class Map {
	public:
		typedef T			mapped_type;
		typedef Key			key_type;
		typedef Alloc		allocator_type;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
		typedef Compare		key_compare;

		typedef ft::pair<const key_type, mapped_type>	value_type;
		class value_compare {
		public:
			bool operator()(const value_type& x, const value_type& y) const {
				return key_compare()(x.first, y.first);
			}
		};
		typedef ft::Node<value_type, allocator_type>						node_type;
		typedef node_type*									node_pointer;
		typedef typename	allocator_type::pointer			pointer;
		typedef typename 	allocator_type::reference 		reference;
		typedef typename 	allocator_type::const_pointer	const_pointer;
		typedef typename 	allocator_type::const_reference	const_reference;

		// Red black tree
		typedef ft::red_black_tree<value_type, Compare, Alloc>								tree_type;
		// Iterators
		typedef ft::rbt_iterator<value_type, node_type, tree_type>				iterator;
		typedef ft::rbt_iterator<const value_type, node_type, tree_type >	const_iterator;
		typedef ft::rbt_reverse_iterator<iterator>									reverse_iterator;
		typedef ft::rbt_reverse_iterator<const_iterator>							const_reverse_iterator;

	private:
		tree_type		_rbtree;
		key_compare		_compare;
		value_compare	_value_compare;
		allocator_type	_alloc;

	public:

		explicit Map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _rbtree(), _compare(comp), _value_compare(value_compare()),_alloc(alloc) {
			return ;
		}

		template <class InputIterator>
			Map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				 const allocator_type& alloc = allocator_type()): _rbtree(), _compare(comp), _value_compare(value_compare()), _alloc(alloc) {
					for (InputIterator it = first; it != last ; it++) {
						_rbtree.insert(*it);
					}
			}

		Map (const Map& x) {
			if (this == &x)
				return ;
			_rbtree.clear();
			_rbtree = x._rbtree;
		}

		~Map() {
		}

		Map&	operator=(const Map& x) {
			if (*this != x) {
				_rbtree = x._rbtree;
				_alloc = x._alloc;
				_compare = x._compare;
				_value_compare = x._value_compare;
			}
			return (*this);
		}

		size_type		size() const {
			return (_rbtree.size());
		}

		iterator 	begin() {
			return (_rbtree.begin());
		}
		const_iterator begin() const {
			return (_rbtree.begin());
		}

		iterator 	end() {
			return (_rbtree.end());
		}
		const_iterator	end() const {
			return (_rbtree.end());
		}

		reverse_iterator	rbegin() {
			return (_rbtree.rbegin());
		}
		const_reverse_iterator rbegin() const {
			return (_rbtree.rbegin());
		}

		reverse_iterator 	rend() {
			return (_rbtree.rend());
		}
		const_reverse_iterator rend() const {
			return (_rbtree.rend());
		}

		bool 	empty() const {
			return (_rbtree.size() == 0);
		};

		size_type	max_size() const {
			return (_rbtree.max_size());
		}

		mapped_type&	operator[] (const key_type& k) {
			node_pointer node = _rbtree.find(k);
			
			if (node == nullptr) {
				ft::pair<iterator, bool> it = insert(ft::make_pair(k, mapped_type()));
				return (it.first->second);
			}
			return (node->data->second);
		}

		ft::pair<iterator, bool>	insert (const value_type& val) {
			node_pointer node = _rbtree.find(val.first);

			if (node != nullptr)
				return (ft::make_pair(iterator(node, &_rbtree), false));
			return (ft::make_pair(iterator(_rbtree.insert(val), &_rbtree), true));
		}

		iterator 	insert(iterator position, const value_type& val) {
			(void) position;
			return (iterator(_rbtree.insert(val), &_rbtree));
		}
		template <class InputIterator>
				void 	insert (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator() ) {
			for (InputIterator it = first; it != last; it++) {
				_rbtree.insert(*it);
			}
		}

		void 		erase(iterator position) {
			_rbtree.remove(position->first);
		}
		size_type	erase (const key_type& k) {
			return (_rbtree.remove(k));
		}
		void 	erase (iterator first, iterator last) {
			std::vector<key_type> keys;
			for(iterator it = first; it != last; ++it)
				keys.push_back(it->first);
			for (typename std::vector<key_type>::iterator it = keys.begin(); it != keys.end(); ++it)
				_rbtree.remove(*it);
		}

		void 	swap(Map& x) {
			std::swap(_alloc, x._alloc);
			std::swap(_compare, x._compare);
			_rbtree.swap(x._rbtree);
		}

		void 	clear() {
			_rbtree.clear();
		}

		key_compare		key_comp() const {
			return (_compare);
		}
		value_compare	value_comp() const {
			return (_value_compare);
		}

		iterator		find(const key_type& k) {
			node_pointer node = _rbtree.find(k);
			
			if (node != nullptr)
				return (iterator(node, &_rbtree));
			return (end());
		}
		const_iterator	find(const key_type& k) const {
			node_pointer node = _rbtree.find(k);
			
			if (node != nullptr)
				return (const_iterator(node, &_rbtree));
			return (end());
		}

		size_type		count(const key_type& k) const {
			if (_rbtree.find(k) != nullptr)
				return (1);
			return (0);
		}
		iterator		lower_bound(const key_type& k) {
			iterator it = find(k);

			if (it != end())
				return (it);
			return (_rbtree.findSuccessor(k));
		}
		const_iterator	lower_bound(const key_type& k) const {
			const_iterator it = find(k);

			if (it != end())
				return (it);
			return (_rbtree.findSuccessor(k));
		}
		iterator		upper_bound(const key_type& k) {
			return (_rbtree.findSuccessor(k));
		}
		const_iterator	upper_bound(const key_type& k) const {
			return (_rbtree.findSuccessor(k));
		}

		ft::pair<const_iterator, const_iterator>	equal_range(const key_type& k) const {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}
		ft::pair<iterator, iterator>				equal_range(const key_type& k) {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		allocator_type		get_allocator() const {
			return (_alloc);
		}
		void				print() {
			_rbtree.print();
		}
	};
	template<class lhit, class rhit>
	bool equal(lhit first1, lhit last1, rhit first2)
	{
		while (first1 != last1) {
		  if (!(*first1 == *first2))
		    return false;
		  ++first1; ++first2;
		}
		return true;
	}
	template <class InputIterator1, class InputIterator2>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2){
		while (first1!=last1)
		{
		  if (first2==last2 || *first2<*first1)
			  return false;
		  else if (*first1<*first2)
			  return true;
		  ++first1; ++first2;
		}
		return (first2!=last2);
	}
		template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const ft::Map<Key,T,Compare,Alloc>& lhs,
						const ft::Map<Key,T,Compare,Alloc>& rhs ) {
							if (lhs.size() != rhs.size())
								return (lhs.size() == rhs.size());
							return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
						}
	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const ft::Map<Key,T,Compare,Alloc>& lhs,
						const ft::Map<Key,T,Compare,Alloc>& rhs ) {
							return (!(lhs == rhs));
						}
	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const ft::Map<Key,T,Compare,Alloc>& lhs,
						const ft::Map<Key,T,Compare,Alloc>& rhs ) {
							return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
						}
	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const ft::Map<Key,T,Compare,Alloc>& lhs,
						const ft::Map<Key,T,Compare,Alloc>& rhs ) {
							if (lhs  < rhs || lhs == rhs)
            					return (true);
        					return (false);
						}
	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const ft::Map<Key,T,Compare,Alloc>& lhs,
						const ft::Map<Key,T,Compare,Alloc>& rhs ){
							return (!(lhs <= rhs));
						}
	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const ft::Map<Key,T,Compare,Alloc>& lhs,
						const ft::Map<Key,T,Compare,Alloc>& rhs ) {
							return (!(lhs < rhs));
						}
	template <class Key, class T, class Compare, class Alloc>
  	void swap (Map<Key,T,Compare,Alloc>& x, Map<Key,T,Compare,Alloc>& y) {
		  x.swap(y);
		  return ;
	  }

}

#endif
