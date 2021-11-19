/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:57:43 by mashad            #+#    #+#             */
/*   Updated: 2021/11/19 18:31:22 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RBTREE_HPP
#define RBTREE_HPP

# include "../utils/pair.hpp"

namespace ft {
	enum Color {RED=1, BLACK=0, DBLACK=2};
	/** @brief Read Black Tree Node
	 * Read black tree node container all necessary data
	 * to create a red black tree.
 	 *
	 * @data color
	 */
	template <class T>
	class Node {
		public:
			Node 	*left;
			Node 	*right;
			Node 	*parent;
			T 		data;
			Color	color;

			explicit Node(const T &data): left(nullptr), right(nullptr), data(data), color(RED) {
                return ;
			}
			bool	isLeft() {
				if (parent && parent->left)
					return parent->left == this;
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
	template <class Tree, class node, class Pair>
	class rbTreeIterator {
	public:
		typedef typename std::bidirectional_iterator_tag	iterator_category;
		typedef Pair		value_type;
		typedef Pair&		reference;
		typedef Pair*		pair_pointer;
		typedef Tree		tree_type;
		typedef node		node_type;
		typedef node_type*	node_pointer;

		rbTreeIterator() : _rbtree() , _ptr(nullptr) {
			return ;
		}
		rbTreeIterator(const node_type& Node, const tree_type& rbtree) : _rbtree(rbtree), _ptr(Node) {
			return ;
		}
		rbTreeIterator(const rbTreeIterator& x) : _rbtree(x._rbtree) , _ptr(x._ptr) {
			return ;
		}
//
//		rbTreeIterator(pointer ptr): _ptr(ptr){};
//
		rbTreeIterator	&operator=(rbTreeIterator const &other) {
			if (*this == other)
				return (*this);
			_ptr = other._ptr;
			_rbtree = other._rbtree;
			return (*this);
		}

		reference 	operator*() {
			return (_ptr->data);
		}
		reference 	operator*() const {return (_ptr->data);}
		value_type	*operator->() {return (&(_ptr->data));}
		value_type 	*operator->() const {return (&(_ptr->data));}

		rbTreeIterator	&operator++() {
			if (_ptr == nullptr)
			{
				return (nullptr);
			}
			_ptr = _rbtree->_inOrderPredecessor(_ptr);
			return (*this);
		}
		rbTreeIterator		operator++(int) {
			rbTreeIterator	tmp = *this;

			if (_ptr == nullptr)
				return (nullptr);
			_ptr = _rbtree->_inOrderPredecessor(_ptr);
			return (tmp);
		}
		rbTreeIterator		&operator--() {
			if (_ptr == nullptr)
				return (nullptr);
			_ptr = _rbtree->_inOrderSucessor(_ptr);
			return (*this);
		}
		rbTreeIterator		operator--(int) {
			rbTreeIterator	tmp = *this;
			_ptr = _rbtree->_inOrderSucessor(_ptr);
			return (tmp);
		}
		friend bool		operator==(const rbTreeIterator &lhs, const rbTreeIterator &rhs) {return (lhs._ptr == rhs._ptr);}
		friend bool 	operator!=(const rbTreeIterator &lhs, const rbTreeIterator &rhs) {return (lhs._ptr != rhs._ptr);}

		operator rbTreeIterator<tree_type, ft::Node<const value_type>, const value_type> () const { return rbTreeIterator<tree_type, ft::Node<const value_type> , const value_type>(_ptr) ; }

	private:
		node_pointer _ptr;
		tree_type	_rbtree;
	};
	template <class Iterator>
	class rbTreeReverseIterator {
		public:
			typedef Iterator									iterator_type;
			typedef typename iterator_type::value_type				value_type;
			typedef typename iterator_type::iterator_category	iterator_category;
			typedef value_type&									reference;
			typedef value_type*									pair_pointer;
			typedef ptrdiff_t									difference_type;


		/** @brief Default constructor
			 * Construct a reverse iterator that points to no object.
			 * The internal base iterator is value-initialized
			 *
			 * @param none
			 * @return none
			 */
			rbTreeReverseIterator(): _ptr(iterator_type()){
				return ;
			}

			/** @brief Initialization constructor
			 * Constructs a reverse iterator from some original iterator it. The behavior of the
			 * constructed object replicates the original, except that it iterates through it's
			 * pointed elements in the reverse order.
			 *
			 * @param it An iterator, whose sense of iteration is inverted in the constructed object.
			 * @Member type iterator_type is the underlying bidirectional iterator type.
			 * @return none
			 */
			explicit	rbTreeReverseIterator(iterator_type it) {
				_ptr = --it;
				return ;
			}

			iterator_type	base() const {
				iterator_type tmp = _ptr;
				return (++tmp);
			}

			/** @brief Copy / Type-cast constructor
			 * Constructs a reverse iterator from some other reverse iterator. The constructed object
			 * keeps the same sense of iteration as rev_it.
			 *
			 * @tparam Iter
			 * @param rev_it An iterator of a reverse_iterator type, whose sense of iteration is preserved.
			 * @return none
			 */
			template <class Iter>
			rbTreeReverseIterator (const rbTreeReverseIterator<Iter>& rev_it) {
				_ptr = rev_it.base();
			}

			/** @brief Dereference iterator
			 * Returns a reference to the element pointed to by the iterator
			 *
			 * Internally, the function decreases a copy of it's base iterator and return the results
			 * of dereferencing it.
			 *
			 * The iterator shall point to some object in order to be dereferenceable.
			 *
			 * @param none
			 * @return A reference to the element pointed by the iterator
			 * Member type reference is an alias of the base iterator's own reference type
			 */
			value_type 	operator*() const {
					return (*_ptr);
			}
			pair_pointer operator->() const {
				return &(operator*());
			}
			rbTreeReverseIterator	operator=(const rbTreeReverseIterator& x) {
				if (*this == x)
					return (*this);
				_ptr = x._ptr;
				return (*this);
			}
			rbTreeReverseIterator	operator+ (difference_type n) const {
				return (rbTreeReverseIterator(_ptr - n + 1));
			}
			rbTreeReverseIterator&	operator++() {
				--_ptr;
				return *this;
			}
			rbTreeReverseIterator	operator++(int) {
				rbTreeReverseIterator tmp = *this;
				_ptr--;
				return (tmp);
			}
			rbTreeReverseIterator&	operator+= (difference_type n) {
				_ptr -= n;
				return (*this);
			}
			rbTreeReverseIterator	operator- (difference_type n) const {
				return (rbTreeReverseIterator(_ptr + (n + 1)));
			}
			rbTreeReverseIterator&	operator--() {
				++_ptr;
				return *this;
			}
			rbTreeReverseIterator	operator--(int) {
				rbTreeReverseIterator tmp = *this;
				++_ptr;
				return (tmp);
			}
			rbTreeReverseIterator&	operator-= (difference_type n) {
				_ptr += n;
				return (*this);
			}

	private:
			iterator_type	_ptr;
	};
	template <class Iterator>
	bool operator== (const rbTreeReverseIterator<Iterator>& lhs,
					 const rbTreeReverseIterator<Iterator>& rhs) {
		return (lhs.base() == rhs.base());
	}
	template <class Iterator>
	bool operator!= (const rbTreeReverseIterator<Iterator>& lhs,
					 const rbTreeReverseIterator<Iterator>& rhs) {
		return (lhs.base() != rhs.base());
	}
	template <class Iterator>
	bool operator< (const rbTreeReverseIterator<Iterator>& lhs,
					const rbTreeReverseIterator<Iterator>& rhs) {
		return (lhs.base() > rhs.base());
	}
	template <class Iterator>
	bool operator<= (const rbTreeReverseIterator<Iterator>& lhs,
					 const rbTreeReverseIterator<Iterator>& rhs) {
		return (lhs.base() >= rhs.base());
	}
	template <class Iterator>
	bool operator> (const rbTreeReverseIterator<Iterator>& lhs,
					const rbTreeReverseIterator<Iterator>& rhs) {
		return (lhs.base() < rhs.base());
	}
	template <class Iterator>
	bool operator>= (const rbTreeReverseIterator<Iterator>& lhs,
					 const rbTreeReverseIterator<Iterator>& rhs) {
		return (lhs.base() <= rhs.base());
	}
	/** @brief Red-Black Tree
	 * Red-Black tree is a self balancing binary search tree in which each node contains an extra bit for
	 * denoting the color of the node, either red or black.
	 *
	 * A red-black tree satisfies the following properties:
	 * @property Red/Black : Every node is colored, either red or black.
	 * Root property: The root is black.
	 * Leaf property: Every leaf (NIL) is black.
	 * Red property: if a red node has children then, the children are always black.
	 * Depth property: For each node, any simple path from this node to any of it's descendant leaf has the same
	 * black-depth (The number of black nodes).
	 * @tparam Key Type of the keys, Each element is a map is uniquely identified by it's key value.
	 * @tparam Alloc Type of the allocator object used to define the storage allocation model. By default the allocator
	 * class template is used, which defines the simplest memory allocation model and is value-independent.
	 * @tparam T Type of the mapped value. Each element in a map stores some data as it's mapped value.
	 */
	template <typename T, typename Compare, typename Alloc>
	class RBTree {
		public:
			typedef T																															value_type;
			typedef Alloc																														allocator_type;
			typedef size_t																														size_type;
			typedef Compare																														compare;
			typedef ft::Node<T>																													node_type;
			typedef node_type*																													pointer;
			typedef typename allocator_type::template rebind<node_type>::other																	node_allocator;
			typedef typename node_allocator::const_pointer																						const_pointer;
			typedef ft::rbTreeIterator<ft::RBTree<value_type, compare, allocator_type>, ft::Node<value_type>, value_type>						iterator;
			typedef ft::rbTreeIterator<ft::RBTree<const value_type, compare, allocator_type>, ft::Node<const value_type>, const value_type>		const_iterator;
			typedef ft::rbTreeReverseIterator<iterator>																							reverse_iterator;
			typedef ft::rbTreeReverseIterator<const_iterator>																					const_reverse_iterator;

		private:
			pointer				_root;
			size_type			_size;
			node_allocator		_node_allocator;
			allocator_type		_pair_allocator;
			compare				_compare;


			pointer 	init_node(const value_type &val) {
				pointer	newNode = _node_allocator.allocate(1);
				_node_allocator.construct(newNode, val);
				newNode->parent = nullptr;
				newNode->left = nullptr;
				newNode->right = nullptr;
				newNode->color = RED;
				return newNode;
			}
		protected:
			//------------------ Private member functions ----------------//
			void			swap(RBTree& x) {
				std::swap(_root, x._root);
				std::swap(_size, x._size);
				std::swap(_node_allocator, x._node_allocator);
				std::swap(_compare, x._compare);
			}
			node_type*		_insertBST  (pointer &root, pointer &node) {
				if (root == nullptr)
					return (node);
				if (_compare(node->data, root->data)) {
					root->left = _insertBST(root->left, node);
					root->left->parent = root;
				} else if (_compare(root->data, node->data)) {
					root->right = _insertBST(root->right, node);
					node->right->parent = root;
				}
				return (root);
			}
			void 			_deleteBST(pointer &root, pointer &node) {
				if (node == nullptr)
					return ;
				if (root->data == node->data) {
					if (!(node->left) && !(node->right)) {
						if (node == _root) {
                            _node_allocator.destory(node);
							_node_allocator.deallocate(node, 1);
							node = nullptr;
							return ;
						}
						deleteFix(node);
                        _node_allocator.destroy(node);
						_node_allocator.deallocate(node, 1);
						node = nullptr;
					}
					else {
						if (node->left) { // get predecessor
							node_type *pre = _inOrderPredecessor(node);
							node->data = pre->data;
							deleteRBT(node, pre);
						} else { // get successor
							node_type *suc = _inOrderSuccessor(node);
							node->data = suc->data;
							deleteRBT(node, suc);
						}
					}
					return ;
				}
				if (_compare(root->data, node->data)) // root->data < node->data
					deleteRBT(root->right, node);
				else
					deleteRBT(root->left, node);
			}
			void    		_insertFix(pointer &node) {
				while (node->parent->color == RED) {
					if (node->parent->parent->left == node->parent) {
						if (node->parent->parent->right && node->parent->parent->right->color == RED) {
							node->parent->parent->right->color = BLACK;
							node->parent->parent->left->color = BLACK;
							node->parent->parent->color = RED;
							node = node->parent->parent;
						} else if (node->parent->right == node) {
							node = node->parent;
							rotateLeft(node);
						} else {
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							rotateRight(node->parent->parent);
						}
					}
					else {
						if (node->parent->parent->left && node->parent->parent->left->color == RED) {
							node->parent->parent->left->color = BLACK;
							node->parent->parent->right->color = BLACK;
							node->parent->parent->color = RED;
							node = node->parent->parent;
						} else if (node->parent->left == node) {
							node = node->parent;
							rotateRight(node);
						} else {
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							rotateLeft(node->parent->parent);
						}
					}
					if (node == _root)
						break ;
				}
				_root->color = BLACK;
			}
			void    		_deleteFix(pointer &node) {
				if (node->color == RED)
					return ;
				if (node == _root) {
					node->color = BLACK;
					return ;
				}
				pointer sibling = (node->parent->left == node) ? (node->parent->right) : (node->parent->left);
				if (sibling && sibling->color == BLACK) {
					// case 3: DB sibling is black and both sibling's childs are black
					/*
					1       remove db
					2       make sibling red
					3       if db parent is red make it black else make it double black
					4       if parent becomes db then recurse
					*/
					if ((sibling->left == nullptr || sibling->left->color == BLACK ) && (sibling->right == nullptr || sibling->right->color == BLACK)) {
						node->color = BLACK;
						sibling->color = RED;
						if (node->parent->color == BLACK) {
							node->parent->color = DBLACK;
							deleteFix(node->parent);
						} else {
							node->parent->color = BLACK;
						}
						return ;
					}
					if (node->parent->left == node) {
						/* case4 sibling is black and nearest sibling child to db node is red
															  1       swap sibling and red child colors
															  2       rotate sibling in opposite direction of DB node
															  3       will lead to case5 and get applied
													  */
						if ((sibling->left && sibling->left->color == RED) && (sibling->right && sibling->right->color == BLACK)) {
							std::swap(sibling->left->color, sibling->color);
							rightRotate(sibling);
						} else if ((sibling->right && sibling->right->color == RED)){
							/* case5 sibling is black and farthest child from db node is red
																1       swap parent and sibling colors
																2       rotate parent in direction of DB
																3       remove DB
																4       change sibling's far red child to black
														 */
							std::swap(node->parent->color, sibling->color);
							leftRotate(node->parent);
							node->color = BLACK;
							sibling->right->color = BLACK;

						}
					} else {
						/** case4 sibling is black and nearest sibling child to db node is red
															  1       swap sibling and red child colors
															  2       rotate sibling in opposite direction of DB node
															  3       will lead to case5 and get applied
													  */
						if ((sibling->right && sibling->right->color == RED) && (sibling->left && sibling->left->color == BLACK)) {
							std::swap(sibling->right->color, sibling->color);
							leftRotate(sibling);
						} else if (sibling->left && sibling->left->color == RED) {
							/** case5 sibling is black and farthest child from db node is red
															   1       swap parent and sibling colors
															   2       rotate parent in direction of DB
															   3       remove DB
															   4       change sibling's far red child to black
														*/
							std::swap(node->parent->color, sibling->color);
							rightRotate(node->parent);
							node->color = BLACK;
							sibling->left->color = BLACK;
						}
					}
				}
					/*        Sibling is red
											   swap sibling and parent colors
											   rotate parent is direction of DB node
											   recurse
									   */
				else if (sibling && sibling->color == RED) {
					std::swap(node->parent->color, sibling->color);
					if (node->parent->left == node) {
						leftRotate(node->parent);
					} else {
						rightRotate(node->parent);
					}
					deleteFix(node->parent);
					return;
				}

			}
			node_type	*_findRBT(node_type *root, value_type data) {
				if (root == nullptr)
					return (nullptr);
				if (data == root->data)
					return (root);
				else if (_compare(root->data, data))
					return (_findRBT(root->right, data));
				else if (_compare(data, root->data))
					return (_findRBT(root->left, data));
				return (nullptr);
			}

		public:
			/** @brief Empty Tree constructor (Default constructor)
			 * Construct an empty container, with no elements.
			 *
			 * @param alloc Allocator object.
			 */
			RBTree (): _root(nullptr), _compare(compare()) {
				return ;
			}
			RBTree(const value_type &pair): _root(init_node(pair)) {
				return ;
			}
            RBTree(const RBTree& x) {
					clear();
					_root = x._root;
					_node_allocator = x._node_allocator;
					_pair_allocator = x._pair_allocator;
					_compare = x._compare;
            }
			~RBTree () {
                return ;
            }
            RBTree& operator=(const RBTree& x) {
                if (*this == x)
                    return (*this);
                clear();
                _node_allocator = x._node_allocator;
                _pair_allocator = x._pair_allocator;
                _compare = x._compare;
                clone(x._root);
            }

            void        clone(pointer root) {
                if (root == nullptr) {
                    insert(root->data);
                    if (root->right != nullptr)
                        insert(root->right->data);
                    clone(root->left);
                    clone(root->right);
                }
            }
			void 		clear() {
				if (_root && _root != nullptr) {
					destroyNode(_root);
					_size = 0;
					_root = nullptr;
				}
			}
			void 	empty() {
				return (_size == 0);
			}
			int 	getColor(node_type *&node) {
				if (node == nullptr)
					return BLACK;
				return node->color;
			}
        	void	setColor(node_type *&node, int color) {
        		if (node == nullptr)
        			return ;
        		node->color = color;
        	}
			node_type   *minimum(node_type *node) {
				if (node == nullptr)
					return (nullptr);
				while (node->left != nullptr) {
					node = node->left;
				}
				return (node);
			}
			node_type   *maximum(node_type *node) {
				if (node == nullptr)
					return (nullptr);
				while (node->right != nullptr) {
					node = node->right;
				}
				return (node);
			}
		/** @Brief Left Rotation
	         *	Left Rotate the red black tree
	         *  @param node
	         * @return none
	         */
	        void	rotateLeft(node_type *&node) {
	        	node_type *rightChild = node->right;
	        	node->right = rightChild->left;

	        	if (node->right != nullptr)
	        		node->right->parent = node;
	        	rightChild->parent = node->parent;
	        	if (node->parent == nullptr)
	        		_root = rightChild;
	        	else if (node == node->parent->left)
	        		node->parent->left = rightChild;
	        	rightChild->left = node;
	        	node->parent = rightChild;
	        }
	        /** @Brief Right rotate
	         * Right rotate the red black tree
	         *
	         * @param node
	         * @return none
	         */

        	void	rotateRight(node_type *&node) {
        		node_type *leftChild = node->left;
        		node->left = leftChild->right;

        		if (node->left != nullptr)
        			node->right->parent = node;
        		leftChild->parent = node->parent;
        		if (node->parent == nullptr)
        			_root = leftChild;
        		else if (node == node->parent->right)
        			node->parent->right = leftChild;
        		leftChild->right = node;
        		node->parent = leftChild;
        		return ;
        	}
			pointer 	_inOrderPredecessor(pointer node) {
				if (node == nullptr)
					return (nullptr);
				if (node->left != nullptr)
					return (maximum(node->left));
				node_type *parent = node->parent;
				while (parent != nullptr && parent->left == node) {
					node = parent;
					parent = parent->parent;
				}
				return (parent);
			}
			/** @brief Find the Successor of node
			 * Find the minimum value of the right sub-tree which is the inorder successor
			 *
			 * If node has no right child then iterator back to the first ancestor.
			 *
			 * @param node
			 * @return in-order successor of node.
			 */
			pointer	_inOrderSuccessor(pointer 	node) {
				if (node == nullptr)
					return (nullptr);
				if (node->right != nullptr)
					return (minimum(node->right));
				pointer	parent = node->parent;
				while (parent != nullptr && parent->right == node) {
					node = parent;
					parent = parent->parent;
				}
				return (parent);
			}
			ft::pair<iterator,bool>	insert(const value_type &data) {

				node_type *node = _findRBT(_root, data);

				if (node != nullptr)
					return (ft::make_pair(iterator(node, *this), false));
        		node = _node_allocator.allocate(1);
        		_node_allocator.construct(node, data);

        		_root = _insertBST(_root, node);
        		_insertFix(node);
				return (ft::make_pair(iterator(node, *this), true));
			}
			void deleteValue(const value_type &data = value_type()) {
				node_type *node = _findRBT(_root, data);

				if (node == nullptr)
					return ;
				_deleteRBT(_root, node);  
			}
			void printall() {
				if (empty())
					return ;
				PrintTree(_root);
				return ;
			}
			value_type &find(const value_type &data) {
				return (_findRBT(_root, data));
			}
			void	destroyNode(pointer node) {
				if (node != nullptr) {
					destroyNode(node->left);
					destroyNode(node->right);
					_node_allocator.destroy(node);
					_node_allocator.deallocate(node, 1);
				}
			}

			/** @brief Return iterator to beginning
			 * Returns an iterator referring to the first element in the map container.
			 *
			 * Because map containers keep their elements ordered at all times, begin points to the element that
			 * goes first following the container's sorting criterion.
			 *
			 * If the container is empty, the returned iterator value shall not be dereferenced.
			 * @return An iterator
			 */
			iterator 	begin() {
				pointer tmp = _root;

				if (_root == nullptr)
					return (iterator(nullptr, *this));
				while (tmp->left)
					tmp = tmp->left;
				return (iterator(tmp, *this));
			}
			const_iterator	begin() const {
				pointer tmp = _root;

				if (_root == nullptr)
					return (nullptr);
				while (tmp->left)
					tmp = tmp->left;
				return (const_iterator(tmp, *this));
			}
			size_type	getSize() const {
				return (_size);
			}
			/** @brief Return iterator to end
			 * Returns an iterator referring to the past-the-end element in the red black tree
			 *
			 * The past-the-end element is the theoretical element that would follow the last element
			 * in the red black tree container. It does not point ot any element, thus shall not be dereferenced.
			 *
			 * @return An iterator to the past-the-end element in the red black tree.
			 */
			 iterator	end() {return (iterator(nullptr, *this));}
			 const_iterator	end() const {return (const_iterator(nullptr, *this));}

			 iterator	rbegin() {return (reverse_iterator(end()));}
			 const_iterator rbegin() const {return (const_reverse_iterator(end()));}

			 iterator	rend() {
				 return (reverse_iterator(begin()));
			 }
			 const_iterator rend() const {
				 return (const_reverse_iterator(begin()));
			 }

			 size_type		max_size() const {
				 return (node_allocator().max_size());
			 }
	};

}
#endif
