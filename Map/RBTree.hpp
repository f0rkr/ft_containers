/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:57:43 by mashad            #+#    #+#             */
/*   Updated: 2021/11/06 08:42:30 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RBT_HPP
#define RBT_HPP

# include "../utils/pair.hpp"

namespace ft {
	enum Color {RED, BLACK, DOUBLE_BLACK};
	/** @brief Read Black Tree Node
	 * Read black tree node container all necessary data
	 * to create a red black tree.
	 *
	 * @data color
	 */
	struct Node {
		int 		color;
		value_type 	data;
		struct Node *parent;
		struct Node *leftChild;
		struct Node *rightChild;

		/** @brief Construct a Read black tree 
		 *
		 */
		explicit Node(const value_type &data) {
			this->color = red;
			this->data = data;
			this->parent = this->leftChild =this->rightChild = nullptr;
			return ;
		}
	};
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
	template <class T, class Alloc = std::allocator()>
	class RBTree {
		public:
			typedef T 									value_type;
			typedef Alloc								allocator_type;

		private:
			Node 			*_rbtree;
			size_type		_size;
			allocator_type	_alloc;

			Node*	_insertBST(Node *&root, Node *&node) {
				if (root == nullptr)
					return (node);
				if (node->data < root->data) {
					root->left = _insertBST(root->left, node);
					root->left->parent = root;
				} else if (node->data > root->data) {
					root->right = _insertBST(root->right, node);
					node->right->parent = root;
				}
				return (root);
			}
	        Node*	_deleteBST(Node *&, int);
			void	_fixInsertRBTree(Node *&root);
        	void	_fixDeleteRBTree(Node *&root);
		protected:


			//------------------ Private member functions ----------------//

			/** @brief Clear content
			 * Removes all elements from the Tree (which are destroyed)
			 * @param none
			 * @return none
			 */
			void 	_clear();
		public:
			typedef struct Node	node;

			/** @brief Empty Tree constructor (Default constructor)
			 * Construct an empty container, with no elements.
			 *
			 * @param alloc Allocator object.
			 */
			RBTree (const allocator_type& alloc = allocator_type()): _rbtree(nullptr), _alloc(alloc) {
				return ;
			}
			explicit RBTree(const value_type &pair = value_type()): _rbtree(_alloc.allocate(1)) {
				return ;
			}

			~RBTree ();

			void 	insert(const value_type &val = value_type()) {
				Node *newNode = _alloc.allocate(1);
				_alloc.construct(&newNode, Node(val));
				_rbtree = _insertBST(_rbtree, newNode);
				_fixInsertRBTree(_rbtree);
			}

			void 	empty() {
				return (_size == 0);
			}
			int 	getColor(Node *&node) {
				if (node == nullptr)
					return ft::Color::Black;
				return node->color;
			}
        	void	setColor(Node *&node, int color) {
        		if (node == nullptr)
        			return ;
        		node->color = color;
        	}
	        int 	getBlackHeight(Node *node) {

	        }

	        /** @Brief Left Rotation
	         *	Left Rotate the red black tree
	         *  @param node
	         * @return none
	         */
	        void	rotateLeft(Node *&node) {
	        	Node *rightChild = node->right;
	        	node->right = rightChild->left;

	        	if (node->right != nullptr)
	        		node->right->parent = node;
	        	rightChild->parent = node->parent;
	        	if (node->parent == nullptr)
	        		root = rightChild;
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

        	void	rotateRight(Node *&node) {
        		Node *leftChild = node->left;
        		node->left = leftChild->right;

        		if (node->left != nullptr)
        			node->right->parent = node;
        		leftChild->parent = node->parent;
        		if (node->parent == nullptr)
        			root = leftChild;
        		else if (node == node->parent->right)
        			node->parent->right = leftChild;
        		leftChild->right = node;
        		node->parent = leftChild;
        		return ;
        	}
        	void	insertData(value_type &data) {
        		Node *node;

        		node = _alloc.allocate(1);
        		_alloc.construct(node, Node(data));
        		_rbtree = _insertBST(_rbtree, node);
        		_fixInsertRBTree(node);
        	}
	};
}
#endif
