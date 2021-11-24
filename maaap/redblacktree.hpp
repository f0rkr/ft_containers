#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP


# include <iostream>
# include "../utils/pair.hpp"

namespace ft {
	enum Color	{RED=1, BLACK=0, DBLACK=2};
	template <class Pair, class Alloc>
	struct Node {
		typedef	Pair			value_type;
		typedef value_type*		pointer;
		typedef value_type&		reference;
		typedef Node*			node_pointer;
		typedef Node			node_type;
		typedef Node&			node_reference;

		node_pointer	left;
		node_pointer	right;
		node_pointer	parent;
		pointer			data;
		Color			color;

		pair_pointer	create_pair(const value_type& data) {
			pointer	pair_node = allocator_type().allocate(1);

			allocator_type().construct(pair_node, data);
			return (pair_node);
		}
		void			destroy() {
			allocator_type().destroy(data);
			allocator_type().deallocate(data, 1);
			return ;
		}
		explicit Node(const value_type& data) : left(nullptr), right(nullptr), parent(nullptr), data(create_pair(data)), color(RED) {
			return ;
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
	template <class Key, class T, class Alloc = std::allocator<Pair> >
	class rbt_iterator {
		public:
			typedef Key								key_type;
			typedef T								mapped_type;
			typedef ft::pair<const Key, T>			value_type;
			typedef value_type*						pointer;
			typedef value_type&						reference;
			typedef ft::Node<value_type, Alloc>		node_type;
			typedef ft::red_black_tree<Key, T>		tree_type;
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

			reference 	operator*() {
				return (*(_ptr->data));
			}
			pointer	operator->() {
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

			operator		rbt_iterator<const value_type, const ft::red_black_tree<Key, const T>> () const {
				return (rbt_iterator<const value_type, const ft::red_black_tree<Key, const T>>(_ptr));
			}	
	};
	template <class Key, class T, Class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T>> >
	class red_black_tree {
		public:

			typedef Key										key_type;
			typedef T										mapped_type;
			typedef Alloc									allocator_type;
			typedef size_t									size_type;
			typedef Compare									key_compare;
			typedef ft::Node<value_type, allocator_type>	node_type;
			typedef node_type*								node_pointer;
			typedef node_type&								node_reference;
			typedef ft::pair<const key_type, mapped_type>	value_type;
			typedef value_type*								pointer;
			typedef value_type&								reference;
			typedef ft::rbt_iterator<Key, T>				iterator;
			typedef typename allocator_type::template rebind<node_type>::other	node_allocator;
			

			node_pointer	create_node(const value_type& pair) {
				node_pointer node = _node_allocator.allocate(1);
				_node_allocator.construct(node, pair);
				return (node);
			}
			void			delete_node(node_pointer node) {
				node->destroy();
				_node_allocator.destroy(1);
				_node_allocator.deallocate(node, pair);
				return (node);
			}
			private:
				node_pointer	_root;
				size_type		_size;
				node_allocator	_node_allocator;

				node_pointer	_destroy(node_pointer node) {
					if (node != nullptr) {
						_destroy(node->left);
						_destroy(node->right);
						_node_allocator.destroy(node);
						_node_allocator.deallocate(node, 1);
					}
					return (nullptr);
				}
				node_type*		_insert(node_pointer &root, node_pointer &node);
				void 			_remove(node_pointer &root, node_pointer &node);
				void 			_insertFix(node_type *&node);
				void 			_removeFix(node_pointer &node);
				node_pointer	_find(node_pointer root, value_type data);

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
				void 		clear();
				node_pointer	max(node_pointer node) {

				}
				node_pointer	min(node_pointer node) {

				}
				node_pointer	inorderPredecessor(node_pointer node) {

				}
				node_pointer	inorderSuccessor(node_pointer node) const {

				}
				void 			rotateLeft(node_pointer &node) {

				}
				void 			rotateRight(node_pointer &node) {

				}
				node_pointer	insert(const value_type& data) {

				}
				void 			remove(const value_type& data) {

				}
				node_pointer	find(const value_type& data) {

				}


				iterator	begin() {
					if (_root == nullptr)
						return (iterator(nullptr, this));
					return (iterator(_root, this));
				}
				const_iterator	begin() const {
					if (_root == nullptr)
						return (iterator(nullptr, this));
					return (iterator(_root, this));
				}

				iterator end() {

				}
				const_iterator	end() {

				}
				reverse_iterator	rbegin() {

				}
				const_reverse_iterator	rbegin() const {

				}
				reverse_iterator		rend() {

				}
				const_reverse_iterator	rend() const {
					
				}
	};
}