/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Avl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 11:50:15 by                   #+#    #+#             */
/*   Updated: 2021/10/09 12:48:17 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_HPP
# define AVL_HPP


namespace ft {
	template <class T>
		struct		s_btree
		{
			struct s_btree	*right;
			struct s_btree	*left;
			size_t 			height;
			T				*key;
			T				*value;

		};
	typedef		struct s_btree<T>	t_btree;
	template <class T>
		class avl {
			private:
				t_btree		*_avlTree;
				t_btree		*_tmpInsert;
			public:


				typedef 	size_t				size_type;


				avl (void): _avlTree(nullptr), _tmpInsert(nullptr) {
					return ;
				}

				avl(const avl &x);

				~avl(void);

				size_type		height(t_btree *avlTree) {
					if (avlTree->left && avlTree->right) {
						if (avlTree->left->height < avlTree->right->height)
							return (avlTree->right->height + 1);
						else
							return (avlTree->left->height + 1);
					}
					else if (avlTree->left && avlTree->right == nullptr)
						return (avlTree->left->height + 1);
					else if (avlTree->left == nullptr && avlTree->right)
						return (avlTree->right->heigth + 1);
					return (0);
				}

		};
}