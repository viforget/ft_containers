#ifndef BINARY_TREE_HPP
# define BINARY_TREE_HPP

# include <cstdlib>
# include <stdexcept>
# include <exception>
# include <functional>

# include "map_utils.hpp"
// # include "map_iterator.hpp"

# define L 0
# define R 1

namespace ft
{

	template <class T>class map_iterator;

	template<class Key, class T, class Compare = std::less<Key>,
		class Alloc = std::allocator<pair<const Key,T> >  >
	struct node
	{
		public:
			typedef typename ft::map_iterator<pair< const Key, T> >	iterator;
			typedef ft::pair<const Key, T>							value_type;
			
			node*					parent;
			node*					left;
			node*					right;
			ft::pair<const Key, T>	*data;
			Compare					comp;
			bool					side;

//---------- Constructors ----------//

			// Basic constructor; create the first node of a binary tree, no parent and both child as NULL
			node() : parent(NULL), left(NULL), right(NULL), data(NULL), side(-1) {}

			// Leaf constructor; create a node with a parent but both child as NULL, no leaf node cannot have NULL as child
			node( node * par, bool sid ) : parent(par), left(NULL), right(NULL), data(NULL), side(sid) {}

			//Node constructor; create a node and give it a value
			// node( node * par, const value_type& val, bool sid ) : parent(par), left(new node(this), L), right(new node(this), R), side(sid) {}

			// Copy constructor
			node( const node & ref ) : parent(ref.parent), left(ref.left), right(ref.right), data(ref.data), side(ref.side) {}

//---------- Destructor ----------//

			~node()
			{
				std::allocator<pair<const Key,T> >	alloc;

				if (this->data)
				{
					alloc.destroy(this->data);
					alloc.deallocate(data, 1);
				}
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
				if (sid == L)
				{
					if (!this->left.leaf())
						delete this->left;
					this->left = child;
				}
				else if (sid == R)
				{
					if (!this->right.leaf())
						delete this->right;
					this->right = child;
				}
			}

			//transform the leaf into a node with a data and 2 leaves
			void	leaf_to_node( const value_type& val, Alloc alloc )
			{
				std::allocator<node>	alloca;
				
				if (this->leaf())
				{
					this->left = alloca.allocate(1);
					alloca.construct(this->left, node(this, L));

					this->right = alloca.allocate(1);
					alloca.construct(this->right, node(this, R));
					this->data = alloc.allocate(1);
					alloc.construct(this->data, val);
				}
			}

			//delete and free every nodes of the tree
			void	delete_tree( Alloc alloc )
			{
				std::allocator<node>	alloca;

				if (!this->leaf())
				{
					this->left->delete_tree(alloc);
					this->right->delete_tree(alloc);
				}
				// if (this->data)
				// {
				// 	alloc.destroy(this->data);
				// 	alloc.deallocate(this->data, 1);
				// }
				// std::cout << this->data->second << std::endl << std::endl;
				alloca.destroy(this);
				alloca.deallocate(this, 1);
				//delete this;
			}

			//recursive function that insert a new element
			pair<iterator,bool>	insert(const value_type& val, Alloc alloc=std::allocator<pair<const Key,T> >())
			{
				if (this->leaf())
				{
					this->leaf_to_node(val, alloc);
					return (pair<iterator,bool>(iterator(this), true));
				}
				else if (this->comp(this->data->first, val.first))
				{
					return (this->right->insert(val, alloc));
				}
				else if (this->comp(val.first, this->data->first))
				{
					return (this->left->insert(val, alloc));
				}
				else
					return (pair<iterator, bool>(iterator(this), false));
			}

			//recursive function that count de number of non-leaf nodes
			size_t	size()
			{
				if (this->leaf())
					return (0);
				return(this->left->size() + this->right->size() + 1);
			}

			void	insert_node(node * n)
			{
				if (!this->data)
					return ;
				if (this->comp(this->data->first, n->data->first))
				{
					if (this->right->leaf())
					{
						delete this->right;
						this->right = n;
						n->parent = this;
					}
					else
						this->right->insert_node(n);
				}
				else if (this->comp(n->data->first, this->data->first))
				{
					if (this->left->leaf())
					{
						delete this->left;
						this->left = n;
						n->parent = this;
					}
					else
						this->left->insert_node(n);
				}
			}


			//Erase the node with de data with the key k. set his longest child at his place and insert is shortest child in the longest one
			size_t	erase(Key k)
			{
				std::allocator<node>	alloc;

				if (this->leaf())
					return(0);
				else if (this->comp(this->data->first, k))
				{
					return (this->right->erase(k));
				}
				else if (this->comp(k, this->data->first))
				{
					return (this->left->erase(k));
				}
				else
				{
					if (this->left->size() > this->right->size())
					{
						this->left->parent = this->parent;
						if (this->parent && this->side == R)
							this->parent->right = this->left;
						else if (this->parent && this->side == L)
							this->parent->left = this->left;
						//else
						this->left->insert_node(this->right);
					}
					else
					{
						this->right->parent = this->parent;
						if (this->parent && this->side == R)
							this->parent->right = this->right;
						else if (this->parent && this->side == L)
							this->parent->left = this->right;
						this->left->insert_node(this->left);
					}
					alloc.destroy(this);
					alloc.deallocate(this, 1);
					return (1);
				}

			}
	};
}

#endif