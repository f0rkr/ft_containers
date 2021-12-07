/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <@student.42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 08:23:10 by                   #+#    #+#             */
/*   Updated: 2021/11/30 14:37:23 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

# include <iostream>
# include "pair.hpp"
# include "../Vector/iterator_traits.hpp"


namespace ft {
	enum Color	{RED=1, BLACK=0, DBLACK=2};
	template <class Pair, class Alloc>
	struct Node {
		typedef	Pair			value_type;
		typedef value_type*		pointer;
		typedef value_type&		reference;
		typedef Alloc			allocator_type;
		typedef Node*			node_pointer;
		typedef Node			node_type;
		typedef Node&			node_reference;

		node_pointer	left;
		node_pointer	right;
		node_pointer	parent;
		pointer			data;
		Color			color;

		pointer	create_pair(const value_type& data) {
			pointer	pair_node = allocator_type().allocate(1);

			allocator_type().construct(pair_node, data);
			return (pair_node);
		}
		node_pointer			destroy() {
			if (!data) {
				allocator_type().destroy(data);
				allocator_type().deallocate(data, 1);
			}
			return (nullptr);
		}
		Node() : left(nullptr), right(nullptr), parent(nullptr), data(nullptr), color(RED) {
			return ;
		}
		explicit Node(const value_type& data) : left(nullptr), right(nullptr), parent(nullptr), data(create_pair(data)), color(RED) {
			return ;
		}
		explicit Node(const Node *node) {
			if (!node || node == this)
				return ;
			left = node->left;
			right = node->right;
			parent = node->parent;
			data = allocator_type().allocate(1);
			allocator_type().construct(data, *(node->data));
			return ;
		}
		~Node() {
			// if (!this)
			// 	return ;
			// if (left)
			// 	left = left->destroy();
			// if (right)
			// 	right = right->destroy();
			// this->destroy();
		}
		bool	isLeft() {
			if (parent && parent->left)
				return (parent->left == this);
			return false;
		}
		bool	isRight() {
			if (parent && parent->right)
				return parent->right == this;
			return false;
		}
		Node*	getGrandParent() {
			if (parent && parent->parent)
				return parent->parent;
			return NULL;
		}

		Node*	getUncle() {
			if (parent->parent && parent->isLeft())
				return getGrandParent()->right;
			if (parent->parent && !parent->isLeft())
				return getGrandParent()->left;
			return NULL;
		}
	};
	template <class Pair, class node,  class Tree>
	class rbt_iterator {
		public:
			typedef Pair							value_type;
			typedef value_type*						pointer;
			typedef value_type&						reference;
			typedef node							node_type;
			typedef Tree							tree_type;
			typedef tree_type*						tree_pointer;
			typedef node_type*						node_pointer;

			typedef std::bidirectional_iterator_tag	iterator_category;

		private:
			node_pointer	_ptr;
			tree_type const	*_rbtree;

		public:
			rbt_iterator(): _ptr(nullptr), _rbtree(nullptr){
				return ;
			}

			rbt_iterator(node_pointer dnode, tree_type const *rbtree) : _ptr(dnode), _rbtree(rbtree) {
				return ;
			}

			rbt_iterator(const rbt_iterator& x) : _ptr(x._ptr), _rbtree(x._rbtree) {
				return ;
			}

			rbt_iterator&	operator=(const rbt_iterator& x) {
				if (*this != x) {
					_ptr = x._ptr;
					_rbtree = x._rbtree;
				}
				return (*this);
			}

			reference 	operator*() const {
					if (_ptr == nullptr)
						return ((reference)*_ptr);
					return (*(_ptr->data));
			}
			pointer	operator->() const {
				return (&(operator*()));
			}
			rbt_iterator	operator++() {
				if (_rbtree == nullptr)
					return (*this);
				_ptr = _rbtree->inorderSuccessor(_ptr);
				return (*this);
			}

			rbt_iterator	operator++(int) {
				rbt_iterator tmp = *this;

				if (_rbtree == nullptr)
					return (*this);
				_ptr = _rbtree->inorderSuccessor(_ptr);
				return (tmp);
			}

			rbt_iterator	operator--() {
				if (_rbtree == nullptr)
					return (*this);

				if (_ptr == nullptr)
					_ptr = _rbtree->max(_rbtree->getRoot());
				else
					_ptr = _rbtree->inorderPredecessor(_ptr);
				return (*this);
			}
			rbt_iterator	operator--(int) {
				rbt_iterator tmp = *this;

				if (_rbtree == nullptr)
					return (*this);
				if (_ptr == nullptr)
					_ptr = _rbtree->max(_rbtree->getRoot());
				else
					_ptr = _rbtree->inorderPredecessor(_ptr);
				return (tmp);
			}

			friend bool		operator==(const rbt_iterator& lhs, const rbt_iterator& rhs) {
				return (lhs._ptr == rhs._ptr);
			}
			friend bool 	operator!=(const rbt_iterator& lhs, const rbt_iterator& rhs) {
				return (lhs._ptr != rhs._ptr);
			}

			operator		rbt_iterator<const value_type, node_type, tree_type> () const {
				return (rbt_iterator<const value_type, node_type, tree_type>(_ptr, _rbtree));
			}
	};
	template <class Iterator> class rbt_reverse_iterator {
		public:
			/* ------------------- Member types ------------------- */

			/** @brief Iterator's type
			 * @definition Iterator to iterator_type
			 */
			typedef Iterator													iterator_type;


			/** @brief Category Iterator
			 * Preserves Iterator's category
			 */
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;

			/** @brief value type
			 * Preserves Iterator's value type
			 */
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;

			/** @brief difference type
			 * Preservers Iterator's difference type
			 */
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;

			/** @brief pointer
			 * Preserves Iterator's pointer type
			 */
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			/** @brief reference
			 * Preserves Iterator's reference type
			 */
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

			rbt_reverse_iterator(): _ptr(iterator_type()){
				return ;
			}
			explicit	rbt_reverse_iterator (iterator_type it) {
				_ptr = --it;
				return ;
			}
			template <class Iter>
			rbt_reverse_iterator (const rbt_reverse_iterator<Iter>& rev_it) {
				_ptr = rev_it.base();
			}
			iterator_type	base() const {
				iterator_type tmp = _ptr;
				return (++tmp);
			}
			reference	operator*() const {
				return (*_ptr);
			}
			pointer				operator->() const {
				return &(operator*());
			}
			rbt_reverse_iterator&	operator++() {
				--_ptr;
				return *this;
			}
			rbt_reverse_iterator	operator++(int) {
				rbt_reverse_iterator tmp = *this;
				_ptr--;
				return (tmp);
			}
			rbt_reverse_iterator&	operator--() {
				++_ptr;
				return *this;
			}
			rbt_reverse_iterator	operator--(int) {
				rbt_reverse_iterator tmp = *this;
				++_ptr;
				return (tmp);
			}
			reference			operator[] (difference_type n) const {return (_ptr[n]);}

			friend bool		operator==(const rbt_reverse_iterator& lhs, const rbt_reverse_iterator& rhs) {return ( lhs.base() == rhs.base());}
			friend bool 	operator!=(const rbt_reverse_iterator& lhs, const rbt_reverse_iterator& rhs) {return (!(lhs == rhs));}
		protected:
			iterator_type	_ptr;
	};

	template <class Pair, class Compare, typename Alloc>
	class red_black_tree {
		public:
			typedef typename Pair::first_type		key_type;
			typedef Pair							value_type;
			typedef Compare							key_compare;
			typedef ft::Node<value_type, Alloc>		node_type;
			typedef node_type*						node_pointer;
			typedef Alloc							allocator_type;
			typedef size_t 							size_type;

			typedef typename allocator_type::template rebind<node_type>::other	node_allocator;
			typedef ft::rbt_iterator<value_type, node_type, red_black_tree>		iterator;
			typedef ft::rbt_iterator<const value_type, node_type, red_black_tree>	const_iterator;
			typedef ft::rbt_reverse_iterator<iterator>											reverse_iterator;
			typedef ft::rbt_reverse_iterator<const_iterator>									const_reverse_iterator;

			node_pointer	create_node(const value_type& pair) {
				node_pointer node = _node_allocator.allocate(1);
				_node_allocator.construct(node, pair);
				return (node);
			}
		private:
			node_pointer	_root;
			size_type		_size;
			node_allocator	_node_allocator;
			key_compare 	_compare;


			node_pointer	_destroy(node_pointer node) {
				if (node != nullptr) {
					node->left = _destroy(node->left);
					node->right = _destroy(node->right);
					_node_allocator.destroy(node);
					_node_allocator.deallocate(node, 1);
				}
				return (nullptr);
			}
			node_type*		_insert(node_pointer &root, node_pointer &node) {
				if (root == nullptr)
					return (node);
				if (_compare(node->data->first, root->data->first)) {
					root->left = _insert(root->left, node);
					root->left->parent = root;
				} else if (_compare(root->data->first, node->data->first)){
					root->right = _insert(root->right, node);
					root->right->parent = root;
				}
				return (root);
			}
			void 			_remove(node_type *&root, node_type *&node) {
				if (node == nullptr)
					return ;
				if (root && root->data == node->data) {
					if (!(node->left) && !(node->right)) { // if node has no children then simply delete it
						if (node == _root) {
							node = _destroy(node);
							return ;
						}
						_removeFix(node);
						// node->left = _destroy(node->left);
						// node->right = _destroy(node->right);
						// _node_allocator.destroy(&(*node));
						// _node_allocator.deallocate(&(*node), 1);
						node = nullptr;
					} else { // if not get either it's predecessor or successor
						if (node->left) {
							node_pointer pre = inorderPredecessor(node);
							node->data = pre->data;
							_remove(node, pre);
						} else {
							node_pointer suc = inorderSuccessor(node);
							node->data = suc->data;
							_remove(node, suc);
						}
					}
					return ;
				}
				if (_compare(root->data->first, node->data->first))
					_remove(root->right, node);
				else if (_compare(node->data->first, root->data->first))
					_remove(root->left, node);
				return ;
			}
			void 			setColor(node_type *&node, Color color) {
				if (node == nullptr)
					return ;
				node->color = color;
			}
			Color 			getColor(node_pointer node) {
				if (!node)
					return BLACK;
				return (node->color);
			}
			void 			_insertFix(node_type *&node) {
				node_pointer parent = nullptr;
				node_pointer grandparent = nullptr;
				while (node != _root && getColor(node) == RED && getColor(node->parent) == RED) {
					parent = node->parent;
					grandparent = parent->parent;
					if (parent == grandparent->left) {
						node_pointer uncle = grandparent->right;
						if (getColor(uncle) == RED) {
							uncle->color = BLACK;
							parent->color = BLACK;
							grandparent->color = RED;
							node = grandparent;
						} else {
							if (node == parent->right) {
								rotateLeft(parent);
								node = parent;
								parent = node->parent;
							}
							rotateRight(grandparent);
							std::swap(parent->color, grandparent->color);
							node = parent;
						}
					} else {
						node_pointer uncle = grandparent->left;
						if (getColor(uncle) == RED) {
							uncle->color = BLACK;
							parent->color = BLACK;
							grandparent->color = RED;
							node = grandparent;
						} else {
							if (node == parent->left) {
								rotateRight(parent);
								node = parent;
								parent = node->parent;
							}
							rotateLeft(grandparent);
							std::swap(parent->color, grandparent->color);
							node = parent;
						}
					}
				}
		    	_root->color = BLACK;
			}
			void 			_removeFix(node_pointer &node) {
				if (node->color == RED) {
					return ;
				}
				if (node == _root) {
					node->color = BLACK;
					return ;
				}

				node_pointer sibling = (node && node->parent->left == node) ? (node->parent->right) : (node->parent->left);
				if (sibling && sibling->color == BLACK) {
					/** case 3: DB sibling is black and both sibling's childs are black
					 *
					 * 1	remove db
					 * 2	make sibling red
					 * 3	if db parent is red make it black else make it double black
					 * 4	if parent becomes db then recurse
					 */
					if ((!sibling->left || sibling->left->color == BLACK) && (!sibling->right || sibling->right->color == BLACK)) {
						node->color = BLACK;
						sibling->color = RED;
						if (node->parent->color == BLACK) {
							node->parent->color = DBLACK;
							_removeFix(node->parent);
						} else {
							node->parent->color = BLACK;
						}
						return;
					} if (node && node->parent->left == node) {
						/**case4 sibling is black and nearest sibling child to db node is red
						 * 1       swap sibling and red child colors
						 * 2       rotate sibling in opposite direction of DB node
						 * 3       will lead to case5 and get applied
						 */
						if ((sibling->left && sibling->left->color == RED) && (sibling->right && sibling->right->color == BLACK)) {
							std::swap(sibling->left->color, sibling->color);
							rotateRight(sibling);
						} else if ((sibling->right && sibling->right->color == RED)){
							/** case5 sibling is black and farthest child from db node is red
							 * 1       swap parent and sibling colors
							 * 2       rotate parent in direction of DB
							 * 3       remove DB
							 * 4       change sibling's far red child to black
							 */
							std::swap(node->parent->color, sibling->color);
							rotateLeft(node->parent);
							node->color = BLACK;
							sibling->right->color = BLACK;
						}
					} else {
						/** case4 sibling is black and nearest sibling child to db node is red
						 * 1       swap sibling and red child colors
						 * 2       rotate sibling in opposite direction of DB node
						 * 3       will lead to case5 and get applied
						 */
						if ((sibling->right && sibling->right->color == RED) && (sibling->left && sibling->left->color == BLACK)) {
							std::swap(sibling->right->color, sibling->color);
							rotateLeft(sibling);
						} else if (sibling->left && sibling->left->color == RED) {
							/** case5 sibling is black and farthest child from db node is red
							 * 1       swap parent and sibling colors
							 * 2       rotate parent in direction of DB
							 * 3       remove DB
							 * 4       change sibling's far red child to black
							 */
							std::swap(node->parent->color, sibling->color);
							rotateRight(node->parent);
							node->color = BLACK;
							sibling->left->color = BLACK;
						}
					}
				}
				/** Sibling is red
				 * swap sibling and parent colors
				 * rotate parent is direction of DB node
				 * recurse
				 */
				else if (sibling && sibling->color == RED) {
					std::swap(node->parent->color, sibling->color);
					if (node->parent->left == node) {
						rotateLeft(node->parent);
					} else {
						rotateRight(node->parent);
					}
					_removeFix(node->parent);
					return;
				}
			}

			node_pointer	_find(node_pointer root, const key_type& data) const {
				if (root == nullptr)
					return (nullptr);
				else if (_compare(root->data->first, data))
					return (_find(root->right, data));
				else if (_compare(data, root->data->first))
					return (_find(root->left, data));
				return (root);
			}

		public:
			red_black_tree(): _root(nullptr), _size(0), _node_allocator(node_allocator()), _compare(key_compare()) {
				return ;
			}

			red_black_tree(const value_type &pair, const node_allocator& alloc = node_allocator(), const key_compare& compare = key_compare()): _root(create_node(pair)), _size(0), _node_allocator(alloc), _compare(compare) {
				return ;
			}

			red_black_tree(const red_black_tree& x) {
				if (this != &x)
					*this = x;
				return ;
			}

			~red_black_tree() {
				return ;
			}

			red_black_tree&		operator=(const red_black_tree& x) {
				if (_root != nullptr) {
					_node_allocator.destroy(_root);
					_node_allocator.deallocate(_root, 1);
				}
				_root = _node_allocator.allocate(1);
				_node_allocator.construct(_root, x._root);
				_size = x._size;
				_compare = x._compare;
				_node_allocator = x._node_allocator;
				return (*this);
			}

			size_type	size() const {
				return (_size);
			}

			size_type	max_size() const {
				return (node_allocator().max_size());
			}

			void 		empty() {
				return (_size == 0);
			}
			void 		clear() {
				if (_root != nullptr) {
					_root = _destroy(_root);
					_size = 0;
				}
				return ;
			}
			node_pointer	max(node_pointer node) const {
				if (node == nullptr)
					return (node);
				while (node->right != nullptr)
					node = node->right;
				return (node);
			}
			node_pointer	min(node_pointer node) const {
				if (node == nullptr)
					return (nullptr);
				while (node->left != nullptr)
					node = node->left;
				return (node);
			}
			node_pointer	inorderPredecessor(node_pointer node) const {
				if (node == nullptr)
					return (nullptr);
				if (node->left != nullptr)
					return (max(node->left));
				node_pointer	parent = node->parent;
				while (parent != nullptr && parent->left == node) {
					node = parent;
					parent = parent->parent;
				}
				return (parent);
			}
			node_pointer	inorderSuccessor(node_pointer node) const {
				if (node == nullptr)
					return (nullptr);
				if (node->right != nullptr)
					return (min(node->right));
				node_pointer	parent = node->parent;
				while (parent != nullptr && parent->right == node) {
					node = parent;
					parent = parent->parent;
				}
				return (parent);
			}

			/** @brief Implementing Tree Left rotation
			 * Left rotating the node
			 *
			 * @param node
			 * @return none
			 */
			void 			rotateLeft(node_pointer &node) {
				node_pointer rightChild = node->right;

				node->right = rightChild->left;
				if (node->right != nullptr)
					node->right->parent = node;
				rightChild->parent = node->parent;
				if (node->parent == nullptr)
					_root = rightChild;
				else if (node == node->parent->left)
					node->parent->left = rightChild;
				else
					node->parent->right = rightChild;
				rightChild->left = node;
				node->parent = rightChild;
			}

			/** @brief Implementing Tree Right rotation
			 * Right rotating the node
			 *
			 * @param node
			 * @return none
			 */
			void 			rotateRight(node_pointer &node) {
				node_pointer leftChild = node->left;

				node->left = leftChild->right;
				if (node->left != nullptr)
					node->left->parent = node;
				leftChild->parent = node->parent;
				if (node->parent == nullptr)
					_root = leftChild;
				else if (node == node->parent->left)
					node->parent->left = leftChild;
				else
					node->parent->right = leftChild;
				leftChild->right = node;
				node->parent = leftChild;
			}


			node_pointer	insert(const value_type& data) {
				node_pointer node = _find(_root, data.first);

				if (node != nullptr)
					return (node);
				node = create_node(data);
				_root = _insert(_root, node);
				_size++;
				if (node->parent == nullptr) {
					node->color = BLACK;
					return (node);
				}
				if (node->parent->parent == nullptr) {
					return (node);
				}
				_insertFix(node);
				return (node);
			}
			size_type		remove(const key_type& data) {
				node_pointer node = _find(_root, data);

				if (node != nullptr) {
					_remove(_root, node);
					return (1);
				}
				return (0);
			}

			node_pointer	find(const key_type& data) const {
				return (_find(_root, data));
			}
			iterator		begin() {
				return (iterator(min(_root), this));
			}
			const_iterator	begin() const {
				return (iterator(min(_root), this));
			}
			iterator 	end() {
				return (iterator(nullptr, this));
			}
			const_iterator 	end() const {
				return (iterator(nullptr, this));
			}
			reverse_iterator	rbegin(){
				return (reverse_iterator(end()));
			}
			const_reverse_iterator rbegin() const {
				return (const_reverse_iterator(end()));
			}
			reverse_iterator 	rend() {
				return (reverse_iterator(begin()));
			}
			const_reverse_iterator rend() const {
				return (const_reverse_iterator(begin()));
			}
			void print_helper(const std::string &prefix, const node_pointer node, bool isLeft)
			{
				if (node != NULL)
				{
					std::cout << prefix;

					std::cout << (isLeft ? "├──" : "└──");

					// print the value of the node
					std::cout << node->data->first << " ";

					if (node == this->_root)
						std::cout << "(Root)" << std::endl;
					else
						std::cout << (isLeft ? "(R)" : "(L)") << ((node->color == 1) ? "(Red)" : "(Black)") << std::endl;
					// enter the next tree level - left and right branch
					print_helper(prefix + (isLeft ? "│   " : "    "), node->right, true);
					print_helper(prefix + (isLeft ? "│   " : "    "), node->left, false);
				}
			}
			node_pointer	getRoot() const {
				return (_root);
			}
			void print()
			{
				if (_root == nullptr)
					return ;
				print_helper("", _root, false);
			}
	};
}
#endif
