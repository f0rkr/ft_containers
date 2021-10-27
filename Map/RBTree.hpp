/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:26:55 by                   #+#    #+#             */
/*   Updated: 2021/10/25 08:27:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RBT_HPP
#define RBT_HPP

# include "../utils/pair.hpp"

namespace ft {
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
			typedef T 									value_type;
			typedef Alloc								allocator_type;

		private:
			enum Color {RED = 0, BLACK = 1, };
			/** @brief Read Black Tree Node
			 * Read black tree node container all necessary data
			 * to create a red black tree.
			 *
			 * @data color
			 */
			struct Node {
				Color		color;
				value_type 	key;
				struct Node parent;
				struct Node leftChild;
				struct Node rightChild;
			};

			struct Node 	*_rbtree;
			size_type		_size;
			allocator_type	_alloc;



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
			explicit RBTree(const value_type &pair = value_type());

			~RBTree ();

			void 	insert(const value_type &val = value_type()) {
				if (empty()) { // If empty insert newNode as a root node and color it black

				} else {

				}
			}

			void 	empty() {
				return (_size == 0);
			}
	};
}
#endif
