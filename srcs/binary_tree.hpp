#ifndef BINARY_TREE_HPP
# define BINARY_TREE_HPP

# include <cstdlib>
# include <stdexcept>
# include <exception>
# include <functional>
#include "map_utils.hpp"

#include <iostream>

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>,
		class Alloc = std::allocator<pair<const Key,T> >  >
	struct node
	{
		public:
			node*					parent;
			node*					left;
			node*					right;
			ft::pair<const Key, T>	*data;
			Compare					comp;
			bool					side;

			typedef	ft::pair<const Key, T>	value_type;
//---------- Constructors ----------//

			// Basic constructor; create the first node of a binary tree, no parent and both child as NULL
			node() : parent(NULL), left(NULL), right(NULL), side(0) {}

			// Leaf constructor; create a node with a parent but both child as NULL, no leaf node cannot have NULL as child
			node( node * par, bool sid ) : parent(par), left(NULL), right(NULL), side(sid) {}

			//Node constructor; create a node and give it a value
			node( node * par, const value_type& val, bool sid ) : parent(par), left(new node(this), 0), right(new node(this), 1), side(sid) {}

			// Copy constructor
			node( const node & ref ) : parent(ref.parent), left(ref.left), right(ref.right), side(ref.side) {}

//---------- Destructor ----------//

			~node()
			{
				if (data)
					delete data;
			}

//---------- Member functions ----------//
			
			//Check if the node is a leaf
			bool	leaf()
			{
				switch ((this->left != NULL) + (this->right != NULL))
				{
					case (0) :
						return (true);
					case(2):
						return (false);
					default:
						throw (std::logic_error("bad node"));
				}
			}

			//set the left or right child to child //POTENTIALLY USELESS
			void	set_child( node * child, int sid )
			{
				if (!sid)
				{
					if (!this->left.leaf())
						delete this->left;
					this->left = child;
				}
				else if (sid == 1)
				{
					if (!this->right.leaf())
						delete this->right;
					this->right = child;
				}
			}

			//transform the leaf into a node with a data and 2 leaves
			void	leaf_to_node( const value_type& val, Alloc alloc )
			{
				if (this->leaf())
				{
					this->left = new node(this, 0);
					this->right = new node(this, 1);
					// this->data = val;
					this->data = new value_type(val);
				}
			}

			//delete and free every nodes of the tree
			void	delete_tree()
			{
				if (!this->leaf())
				{
					this->left->delete_tree();
					this->right->delete_tree();
				}
				delete this;
			}

			//recursive function that insert a new element
			void	insert(const value_type& val, Alloc alloc=std::allocator<pair<const Key,T> >())
			{
				if (this->leaf())
					this->leaf_to_node(val, alloc);
				else if (this->comp(this->data->first, val.first))
				{
					this->right->insert(val, alloc);
				}
				else if (this->comp(val.first, this->data->first))
				{
					this->left->insert(val, alloc);
				}
			}
	};
}

#endif