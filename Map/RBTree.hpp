/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:57:43 by mashad            #+#    #+#             */
/*   Updated: 2021/11/13 18:28:48 by                  ###   ########.fr       */
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
	template <class T>
	class Node {
		public:
			Node *left;
			Node *right;
			Node *parent;


			explicit Node(const value_type &data = data) {

			}
	};
	struct Node {
		int 		color;
		Pair 	*ata;
		struct node_type *parent;
		struct node_type *leftChild;
		struct node_type *rightChild;

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
	template <class T, class Alloc>
	class RBTree {
		public:
			typedef T 														value_type;
			typedef Alloc													allocator_type;
			typedef	Node													node_type;

		private:
			node_type 			*_rbtree;
			size_type		_size;
			allocator_type	_alloc;

			typename _allocator_type()::template rebind<node_type>::other  _nodeAlloc;

			node_type  *init_node(const value_type &val) {
				node_type *newNode;

				newNode = _nodeAlloc.allocate(1);
				_nodeAlloc.construct(newNode, node_type(val));
				return (newNode);
			}
	protected:
			//------------------ Private member functions ----------------//

			/** @brief Clear content
			 * Removes all elements from the Tree (which are destroyed)
			 * @param none
			 * @return none
			 */
			void 		_clear();
			node_type*	_insertBST(node_type *&root, node_type *&node) {
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
			void 	_deleteBST(node_type *&root, node_type *&node) {
				if (node == nullptr)
					return ;
				if (root->data == node->data) {
					if (!(node->left) && !(node->right)) {
						if (node == _root) {
							std::allocator<node_type>().deallocate(node, 1);
							node = nullptr;
							return ;
						}
						deleteFix(node);
						std::allocator<node_type>().deallocate(node, 1);
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
				if (root->data < node->data)
					deleteRBT(root->right, node);
				else
					deleteRBT(root->left, node);
			}

			void    insertFix(node_type *&node) {
				while (node->parent->color == RED) {
					if (node->parent->parent->left == node->parent) {
						if (node->parent->parent->right && node->parent->parent->right->color == RED) {
							node->parent->parent->right->color = BLACK;
							node->parent->parent->left->color = BLACK;
							node->parent->parent->color = RED;
							node = node->parent->parent;
						} else if (node->parent->right == node) {
							node = node->parent;
							leftRotate(node);
						} else {
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							rightRotate(node->parent->parent);
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
							rightRotate(node);
						} else {
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							leftRotate(node->parent->parent);
						}
					}
					if (node == _root)
						break ;
				}
				_root->color = BLACK;
			}

			void    deleteFix(node_type *&node) {
				if (node->color == RED)
					return ;
				if (node == _root) {
					node->color = BLACK;
					return ;
				}
				node_type *sibling = (node->parent->left == node) ? (node->parent->right) : (node->parent->left);
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
						/* case4 sibling is black and nearest sibling child to db node is red
															  1       swap sibling and red child colors
															  2       rotate sibling in opposite direction of DB node
															  3       will lead to case5 and get applied
													  */
						if ((sibling->right && sibling->right->color == RED) && (sibling->left && sibling->left->color == BLACK)) {
							std::swap(sibling->right->color, sibling->color);
							leftRotate(sibling);
						} else if (sibling->left && sibling->left->color == RED) {
							/* case5 sibling is black and farthest child from db node is red
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

			node_type 	*_findRBT(node_type *root, value_type data) {
				if (data == root->data)
					return (root);
				else if (data > root->data)
					return (find(root->right, data));
				else if (data < root->data)
					return (find(root->left, data));
				return (NULL);
			}

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
			explicit RBTree(const value_type &pair = value_type()): _rbtree(init_node(nullptr)) {
				return ;
			}

			~RBTree ();

			void 	insert(const value_type &val = value_type()) {
				node_type *newNode = _alloc.allocate(1);
				_alloc.construct(&newNode, Node(val));
				_rbtree = _insertBST(_rbtree, newNode);
				_fixInsertRBTree(_rbtree);
			}

			void 	empty() {
				return (_size == 0);
			}
			int 	getColor(node_type *&node) {
				if (node == nullptr)
					return ft::Color::Black;
				return node->color;
			}
        	void	setColor(node_type *&node, int color) {
        		if (node == nullptr)
        			return ;
        		node->color = color;
        	}
	        int 	getBlackHeight(node_type *node) {

	        }
			node_type   *minimum(node_type *node) {
				while (node->left != nullptr) {
					node = node->left;
				}
				return (node);
			}
			node_type   *maximum(node_type *node) {
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

        	void	rotateRight(node_type *&node) {
        		node_type *leftChild = node->left;
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
			node_type	*_inOrderPredecessor(node_type *node) {
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
			node_type *_inOrderSuccessor(node_type *node) {
				if (node == nullptr)
					return (nullptr);
				if (node->right != nullptr)
					return (minimum(node->right));
				node_type *parent = node->parent;
				while (parent != nullptr && parent->right == node) {
					node = parent;
					parent = parent->parent;
				}
				return (parent);
			}

			void  rbTransplant(node_type *&rnode, node_type *&lnode) {
				if (rnode->parent == nullptr) {
					_root = v;
				} else if (rnode == rnode->parent->left) {
					rnode->parent->left = v;
				} else {
					rnode->parent->right = v;
				}
				lnode->parent = lnode->parent;
			}

			void	insertData(value_type &data) {
        		node_type *node;

        		node = _alloc.allocate(1);
        		_alloc.construct(node, Node(data));
        		_rbtree = _insertBST(_rbtree, node);
        		_fixInsertRBTree(node);
			}
			void DeleteValue(const value_type &data = value_type()) {
				node_type *node = find(_root, data);

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
	};
}
#endif
