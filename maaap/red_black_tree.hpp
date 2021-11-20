/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 08:23:10 by                   #+#    #+#             */
/*   Updated: 2021/11/20 20:51:37 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

# include <iostream>
# include "pair.hpp"

namespace ft {
	enum Color {RED=1, BLACK=0, DBLACK=2};
	template <class Pair, class Alloc>
	struct Node {
	public:
		typedef Pair		value_type;
		typedef value_type*	pair_pointer;
		typedef Node*		node_pointer;
		typedef Node		node_type;
		typedef Node&		node_reference;
		typedef Alloc		allocator_type;


		node_pointer	left;
		node_pointer	right;
		node_pointer	parent;
		pair_pointer	data;
		Color			color;


		pair_pointer	create_pair(const value_type& data) {
			pair_pointer	pair_node = allocator_type().allocate(1);

			allocator_type().construct(pair_node, data);
			return (pair_node);
		}
		explicit Node(const value_type& data) : left(nullptr), right(nullptr), parent(nullptr), data(create_pair(data)), color(RED) {
			return ;
		}

		~Node() {

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
			if (parent && parent->isLeft())
				return getGrandParent()->right;
			if (parent && !parent->isLeft())
				return getGrandParent()->left;
			return NULL;
		}
	};

	template <class Pair, class Tree, class Alloc = std::allocator<Pair> >
	class rbt_iterator {
		public:
			typedef Pair							value_type;
			typedef value_type*						pair_pointer;
			typedef value_type&						pair_reference;
			typedef ft::Node<value_type, Alloc>		node_type;
			typedef Tree							tree_type;
			typedef tree_type*						tree_pointer;
			typedef node_type*						node_pointer;

			typedef std::bidirectional_iterator_tag	iterator_category;

		private:
			node_pointer	_ptr;
			tree_pointer	_rbtree;

		public:
			rbt_iterator(): _ptr(nullptr), _rbtree(nullptr){
				return ;
			}

			rbt_iterator(node_pointer node, tree_pointer rbtree) : _ptr(node), _rbtree(rbtree) {
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

			pair_reference 	operator*() {
				return (*(_ptr->data));
			}
			pair_pointer	operator->() {
				return (&(operator*()));
			}
			rbt_iterator	operator++() {
				if (_rbtree == nullptr)
					return (*this);
				_ptr = _rbtree->inorderPredecessor(_ptr);
				return (*this);
			}

			rbt_iterator	operator++(int) {
				rbt_iterator tmp = *this;

				if (_rbtree == nullptr)
					return (*this);
				_ptr = _rbtree->inorderPredecessor(_ptr);
				return (tmp);
			}

			rbt_iterator	operator--() {
				if (_rbtree == nullptr)
					return (*this);
				_ptr = _rbtree->inorderSuccessor(_ptr);
				return (*this);
			}
			rbt_iterator	operator--(int) {
				rbt_iterator tmp = *this;

				if (_rbtree == nullptr)
					return (*this);
				_ptr = _rbtree->inorderSuccessor(_ptr);
				return (tmp);
			}

			friend bool		operator==(const rbt_iterator& lhs, const rbt_iterator& rhs) {return (lhs._ptr->data == rhs._ptr->data);}
			friend bool 	operator!=(const rbt_iterator& lhs, const rbt_iterator& rhs) {return (!(lhs == rhs));}

			operator		rbt_iterator<const value_type, const tree_type> () const {
				return (rbt_iterator<const value_type, const tree_type>());
			}
			
	};
	template <typename Iterator>
	class reverse_iterator {
		public:
			typedef Iterator						iterator_type;
			typedef typename iterator_type::value_type	value_type;
			typedef value_type*							pair_pointer;
			typedef value_type&							reference;

			reverse_iterator() : _ptr(iterator_type()) {
				return ;
			}

			reverse_iterator(iterator_type it) : _ptr(--it) {
				return ;
			}

			template <class Iter>
					reverse_iterator (const reverse_iterator<Iter>& rev_it) {
						_ptr = rev_it.base();
			}

			iterator_type	base() const {
				iterator_type tmp = _ptr;
				return (++tmp);
			}

			reference		operator*() const {
				return (*_ptr);
			}

			pair_pointer	operator->() const {
				return &(operator*());
			}

			reverse_iterator&	operator++() {
				--_ptr;
				return (*this);
			}

			reverse_iterator&	operator++(int) {
				reverse_iterator	tmp = *this;
				_ptr--;
				return (tmp);
			}

			reverse_iterator&	operator--(int) {
				reverse_iterator	tmp = *this;
				++_ptr;
				return (tmp);
			}

			reverse_iterator&	operator--() {
				++_ptr;
				return (*this);
			}

		private:
			iterator_type	_ptr;
	};
	template <class Pair, class Compare, typename Alloc>
	class red_black_tree {
		public:
			typedef Pair							value_type;
			typedef Compare							key_compare;
			typedef ft::Node<value_type, Alloc>		node_type;
			typedef node_type*						node_pointer;
			typedef Alloc							allocator_type;
			typedef size_t 							size_type;

			typedef typename allocator_type::template rebind<node_type>::other	node_allocator;

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
					_destroy(node->left);
					_destroy(node->right);
					_node_allocator.destroy(node);
					_node_allocator.deallocate(node, 1);
				}
				return (nullptr);
			}
			node_type*		_insert(node_pointer &root, node_pointer &node) {
				if (root == nullptr)
					return (node);
				if (node->data < root->data) {
					root->left = _insert(root->left, node);
					root->left->parent = root;
				} else if (root->data < node->data) {
					root->right = _insert(root->right, node);
					node->right->parent = root;
				}
				return (root);
			}
			void 			_remove(node_pointer &root, node_pointer &node) {
				if (node == nullptr)
					return ;
				if (root->data == node->data) {
					if (!(node->left) && !(node->right)) { // if node has no children then simply delete it
						if (node == _root) {
							node = _destroy(node);
							return ;
						}
						_removeFix(node);
						node = _destroy(node);
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
				if (root->data < node->data)
					_remove(root->right, node);
				else
					_remove(root->left, node);
				return ;
			}

			void 			_insertFix(node_type *&node) {
				while (node->parent->color == RED) {
					if (node->parent->isLeft()) {
						if (node->getGrandParent()->right && node->getGrandParent()->right->color == RED) {
							node->parent->parent->right->color = BLACK;
							node->parent->parent->left->color = BLACK;
							node->parent->parent->color = RED;
							node = node->parent->parent;
						} else if (node->isRight()) {
							node = node->parent;
							rotateLeft(node);
						} else {
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							rotateRight(node->parent->parent);
						}
					} else {
						if (node->getGrandParent()->left && node->getGrandParent()->left->color == RED) {
							node->parent->parent->left->color = BLACK;
							node->parent->parent->right->color = BLACK;
							node->parent->parent->color = RED;
							node = node->getGrandParent();
						} else if (node->isLeft()) {
							node = node->parent;
							rotateRight(node);
						} else {
							node->parent->color = BLACK;
							node->getGrandParent()->color = RED;
							rotateLeft(node->parent->parent);
						}
					}
					if (node == _root)
						break ;
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

				node_pointer sibling = (node->isLeft()) ? (node->parent->right) : (node->parent->left);
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
					} if (node->isLeft()) {
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

			node_pointer	_find(node_pointer root, value_type data) {
				if (root == nullptr)
					return (nullptr);
				if (data == *(root->data))
					return (root);
				else if (*(root->data) < data)
					return (_find(root->right, data));
				else if (*(root->data) > data)
					return (_find(root->left, data));
				return (nullptr);
			}

		public:
			red_black_tree(): _root(nullptr), _size(0), _node_allocator(node_allocator()), _compare(key_compare()) {
				return ;
			}

			red_black_tree(const value_type &pair, const node_allocator& alloc = node_allocator(), const key_compare& compare = key_compare()): _root(create_node(pair)), _size(0), _node_allocator(alloc), _compare(compare) {
				return ;
			}

			red_black_tree(const red_black_tree& x) {
				return ;
			}

			~red_black_tree() {
				return ;
			}

			red_black_tree&		operator=(const red_black_tree& x) {
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
			node_pointer	max(node_pointer node) {
				if (node == nullptr)
					return (node);
				while (node->right != nullptr)
					node = node->right;
				return (node);
			}
			node_pointer	min(node_pointer node) {
				if (node == nullptr)
					return (nullptr);
				while (node->left != nullptr)
					node = node->left;
				return (node);
			}
			node_pointer	inorderPredecessor(node_pointer node) {
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
			node_pointer	inorderSuccessor(node_pointer node) {
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
				else if (node->isLeft())
					node->parent->left = rightChild;
				rightChild->left = node;
				node->parent = rightChild;
				return ;
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
					node->right->parent = node;
				leftChild->parent = node->parent;
				if (node->parent == nullptr)
					_root = leftChild;
				else if (node->isRight())
					node->parent->right = leftChild;
				leftChild->right = node;
				node->parent = leftChild;
				return ;
			}


			node_pointer	insert(const value_type& data) {
				node_pointer node = _find(_root, data);

				if (node != nullptr)
					return (node);
				node = create_node(data);
				_root = _insert(_root, node);
				if (node->parent == nullptr) {
					node->color = BLACK;
					return (node);
				}
				if (node->parent->parent == nullptr) {
					return (node);
				}
				_insertFix(node);
				_size++;
				return (node);
			}
			void 			remove(const value_type& data) {
				node_pointer node = _find(_root, data);

				if (node != nullptr)
					_remove(_root, node);
				return ;
			}

			node_pointer	begin() {
				node_pointer tmp = _root;

				if (_root == nullptr)
					return (nullptr);
				while (tmp->left)
					tmp = tmp->left;
				return (tmp);
			}
			node_pointer	end() {
				return (nullptr);
			}
			node_pointer	rbegin() {

				return (end());
			}
			node_pointer	rend() {
				return (begin());
			}

	};
}
#endif
