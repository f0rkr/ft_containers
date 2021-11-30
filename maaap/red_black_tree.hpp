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

/*
//
// Red Black Tree Implementation
//
#include <bits/stdc++.h>
#include "RBTree.h"
using namespace std;

Node::Node(int data) {
    this->data = data;
    color = RED;
    left = right = parent = nullptr;
}

RBTree::RBTree() {
    root = nullptr;
}

int RBTree::getColor(Node *&node) {
    if (node == nullptr)
        return BLACK;

    return node->color;
}

void RBTree::setColor(Node *&node, int color) {
    if (node == nullptr)
        return;

    node->color = color;
}

Node* RBTree::insertBST(Node *&root, Node *&ptr) {
    if (root == nullptr)
        return ptr;

    if (ptr->data < root->data) {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    } else if (ptr->data > root->data) {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }

    return root;
}

void RBTree::insertValue(int n) {
    Node *node = new Node(n);
    root = insertBST(root, node);
    fixInsertRBTree(node);
}

void RBTree::rotateLeft(Node *&ptr) {
    Node *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;
}

void RBTree::rotateRight(Node *&ptr) {
    Node *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
}

void RBTree::fixInsertRBTree(Node *&ptr) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->right) {
                    rotateLeft(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        } else {
            Node *uncle = grandparent->left;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->left) {
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK);
}

void RBTree::fixDeleteRBTree(Node *&node) {
    if (node == nullptr)
        return;

    if (node == root) {
        root = nullptr;
        return;
    }

    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node *child = node->left != nullptr ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        } else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        }
    } else {
        Node *sibling = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete(node);
        setColor(root, BLACK);
    }
}

Node* RBTree::deleteBST(Node *&root, int data) {
    if (root == nullptr)
        return root;

    if (data < root->data)
        return deleteBST(root->left, data);

    if (data > root->data)
        return deleteBST(root->right, data);

    if (root->left == nullptr || root->right == nullptr)
        return root;

    Node *temp = minValueNode(root->right);
    root->data = temp->data;
    return deleteBST(root->right, temp->data);
}

void RBTree::deleteValue(int data) {
    Node *node = deleteBST(root, data);
    fixDeleteRBTree(node);
}

void RBTree::inorderBST(Node *&ptr) {
    if (ptr == nullptr)
        return;

    inorderBST(ptr->left);
    cout << ptr->data << " " << ptr->color << endl;
    inorderBST(ptr->right);
}

void RBTree::inorder() {
    inorderBST(root);
}

void RBTree::preorderBST(Node *&ptr) {
    if (ptr == nullptr)
        return;

    cout << ptr->data << " " << ptr->color << endl;
    preorderBST(ptr->left);
    preorderBST(ptr->right);
}

void RBTree::preorder() {
    preorderBST(root);
    cout << "-------" << endl;
}

Node *RBTree::minValueNode(Node *&node) {

    Node *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

Node* RBTree::maxValueNode(Node *&node) {
    Node *ptr = node;

    while (ptr->right != nullptr)
        ptr = ptr->right;

    return ptr;
}

int RBTree::getBlackHeight(Node *node) {
    int blackheight = 0;
    while (node != nullptr) {
        if (getColor(node) == BLACK)
            blackheight++;
        node = node->left;
    }
    return blackheight;
}

// Test case 1 : 5 2 9 1 6 8 0 20 30 35 40 50 0
// Test case 2 : 3 0 5 0
// Test case 3 : 2 1 3 0 8 9 4 5 0

void RBTree::merge(RBTree rbTree2) {
    int temp;
    Node *c, *temp_ptr;
    Node *root1 = root;
    Node *root2 = rbTree2.root;
    int initialblackheight1 = getBlackHeight(root1);
    int initialblackheight2 = getBlackHeight(root2);
    if (initialblackheight1 > initialblackheight2) {
        c = maxValueNode(root1);
        temp = c->data;
        deleteValue(c->data);
        root1 = root;
    }
    else if (initialblackheight2 > initialblackheight1) {
        c = minValueNode(root2);
        temp = c->data;
        rbTree2.deleteValue(c->data);
        root2 = rbTree2.root;
    }
    else {
        c = minValueNode(root2);
        temp = c->data;
        rbTree2.deleteValue(c->data);
        root2 = rbTree2.root;
        if (initialblackheight1 != getBlackHeight(root2)) {
            rbTree2.insertValue(c->data);
            root2 = rbTree2.root;
            c = maxValueNode(root1);
            temp = c->data;
            deleteValue(c->data);
            root1 = root;
        }
    }
    setColor(c,RED);
    int finalblackheight1 = getBlackHeight(root1);
    int finalblackheight2 = getBlackHeight(root2);
    if (finalblackheight1 == finalblackheight2) {
        c->left = root1;
        root1->parent = c;
        c->right = root2;
        root2->parent = c;
        setColor(c,BLACK);
        c->data = temp;
        root = c;
    }
    else if (finalblackheight2 > finalblackheight1) {
        Node *ptr = root2;
        while (finalblackheight1 != getBlackHeight(ptr)) {
            temp_ptr = ptr;
            ptr = ptr->left;
        }
        Node *ptr_parent;
        if (ptr == nullptr)
            ptr_parent = temp_ptr;
        else
            ptr_parent = ptr->parent;
        c->left = root1;
        if (root1 != nullptr)
            root1->parent = c;
        c->right = ptr;
        if (ptr != nullptr)
            ptr->parent = c;
        ptr_parent->left = c;
        c->parent = ptr_parent;
        if (getColor(ptr_parent) == RED) {
            fixInsertRBTree(c);
        }
        else if (getColor(ptr) == RED){
            fixInsertRBTree(ptr);
        }
        c->data = temp;
        root = root2;
    }
    else {
        Node *ptr = root1;
        while (finalblackheight2 != getBlackHeight(ptr)) {
            ptr = ptr->right;
        }
        Node *ptr_parent = ptr->parent;
        c->right = root2;
        root2->parent = c;
        c->left = ptr;
        ptr->parent = c;
        ptr_parent->right = c;
        c->parent = ptr_parent;
        if (getColor(ptr_parent) == RED) {
            fixInsertRBTree(c);
        }
        else if (getColor(ptr) == RED) {
            fixInsertRBTree(ptr);
        }
        c->data = temp;
        root = root1;
    }
    return;
}
*/
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

				_ptr = _rbtree->inorderPredecessor(_ptr);
				return (*this);
			}
			rbt_iterator	operator--(int) {
				rbt_iterator tmp = *this;

				if (_rbtree == nullptr)
					return (*this);
				_ptr = _rbtree->inorderPredecessor(_ptr);
				return (tmp);
			}

			friend bool		operator==(const rbt_iterator& lhs, const rbt_iterator& rhs) {
				return ((lhs._ptr && rhs._ptr) && lhs._ptr->data == rhs._ptr->data);
			}
			friend bool 	operator!=(const rbt_iterator& lhs, const rbt_iterator& rhs) {return (!(lhs == rhs));}

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

			friend bool		operator==(const rbt_reverse_iterator& lhs, const rbt_reverse_iterator& rhs) {return ( lhs._ptr == rhs._ptr);}
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
				if (_compare(node->data->first, root->data->first)) {
					root->left = _insert(root->left, node);
					root->left->parent = root;
				} else if (_compare(root->data->first, node->data->first)) {
					root->right = _insert(root->right, node);
					root->right->parent = root;
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
			void 			setColor(node_type *&node, Color color) {
				if (node == nullptr)
					return ;
				node->color = color;
			}
			Color 			getColor(node_pointer node) {return (node->color);}
			void 			_insertFix(node_type *&ptr) {
				node_pointer parent = nullptr;
    		node_pointer grandparent = nullptr;
		    while (ptr != _root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
		        parent = ptr->parent;
		        grandparent = parent->parent;
		        if (parent == grandparent->left) {
		            node_pointer uncle = grandparent->right;
		            if (getColor(uncle) == RED) {
										setColor(uncle, BLACK);
		                setColor(parent, BLACK);
		                setColor(grandparent, RED);
		                ptr = grandparent;
		            } else {
		                if (ptr == parent->right) {
		                    rotateLeft(parent);
		                    ptr = parent;
		                    parent = ptr->parent;
		                }
		                rotateRight(grandparent);
		                std::swap(parent->color, grandparent->color);
		                ptr = parent;
		            }
		        } else {
		            node_pointer uncle = grandparent->left;
		            if (getColor(uncle) == RED) {
		                setColor(uncle, BLACK);
		                setColor(parent, BLACK);
		                setColor(grandparent, RED);
		                ptr = grandparent;
		            } else {
		                if (ptr == parent->left) {
		                    rotateRight(parent);
		                    ptr = parent;
		                    parent = ptr->parent;
		                }
		                rotateLeft(grandparent);
		                std::swap(parent->color, grandparent->color);
		                ptr = parent;
		            }
		        }
		    }
		    setColor(_root, BLACK);
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
		// 	void    _rotateLeft(Node *&pt)
        // {
        //     Node    *pt_right = pt->right;

        //     pt->right = pt_right->left;
        //     if(pt->right != NULL)
        //         pt->right->parent = pt;

        //     pt_right->parent = pt->parent;
        //     if(pt->parent == NULL)
        //         _root = pt_right;
        //     else if (pt == pt->parent->left)
        //         pt->parent->left = pt_right;
        //     else
        //         pt->parent->right = pt_right;

        //     pt_right->left = pt;
        //     pt->parent = pt_right;
        // }
			/*
			void RBTree::rotateLeft(Node *&ptr) {
		    Node *right_child = ptr->right;
		    ptr->right = right_child->left;

		    if (ptr->right != nullptr)
		        ptr->right->parent = ptr;

		    right_child->parent = ptr->parent;

		    if (ptr->parent == nullptr)
		        root = right_child;
		    else if (ptr == ptr->parent->left)
		        ptr->parent->left = right_child;
		    else
		        ptr->parent->right = right_child;

		    right_child->left = ptr;
		    ptr->parent = right_child;
}*/
			void 			rotateLeft(node_pointer &node) {
				node_type *rightChild = node->right;
	      node->right = rightChild->left;

	      if (rightChild->right != nullptr)
	        		rightChild->right->parent = node;
				if (node == _root)
					rightChild->parent = node;
				else
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

			// void    _rotateRight(Node *&pt)
			// {
			// 	Node    *pt_left = pt->left;

			// 	pt->left = pt_left->right;

			// 	if (pt->left != NULL)
			// 		pt->left->parent = pt;

			// 	pt_left->parent = pt->parent;
			// 	if (pt->parent == NULL)
			// 		_root = pt_left;
			// 	else if (pt == pt->parent->left)
			// 		pt->parent->left = pt_left;
			// 	else
			// 		pt->parent->right = pt_left;

			// 	pt_left->right = pt;
			// 	pt->parent = pt_left;
			// }
			void 			rotateRight(node_pointer &node) {
				node_type *leftChild = node->left;
        		node->left = leftChild->right;

        		if (leftChild->left != nullptr)
        			leftChild->left->parent = node;
				if (node == _root)
					leftChild->parent = node;
				else
        			leftChild->parent = node->parent;
        		if (node->parent == nullptr)
        			_root = leftChild;
        		else if (node == node->parent->left)
        			node->parent->right = leftChild;
				else
					node->parent->right = leftChild;
        		leftChild->right = node;
        		node->parent = leftChild;
        		return ;
			}


			node_pointer	insert(const value_type& data) {
				node_pointer node = _find(_root, data.first);

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

	};
}
#endif
