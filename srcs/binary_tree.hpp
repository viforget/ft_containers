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
			node( const node & ref ) : parent(ref.parent), left(ref.left), right(ref.right), side(ref.side)
			{
				std::allocator<pair<const Key,T> >	alloc;

				this->data = alloc.allocate(1);
				if (ref.data)
					alloc.construct(this->data, *(ref.data));
				else
					this->data = NULL;
			}

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

//---------- Operator= ----------//

			node& operator= (const node& x)
			{
				std::allocator<pair<const Key,T> >	alloc;

				this->parent = x.parent;
				this->left = x.left;
				this->right = x.right;
				this->side = x.side;
				this->comp = x.comp;
				if (this->data)
					alloc.destroy(this->data);
				else
					this->data = alloc.allocate(1);
				alloc.construct(this->data, *(x.data));
			}


//---------- Member functions ----------//
			
			//Check if the node is a leaf
			bool	leaf()
			{
				//std::cout << this << std::endl;
				if (static_cast<void *>(this) == NULL)
					return (true);
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

			void	node_to_leaf( Alloc alloc=std::allocator<pair<const Key,T> >() )
			{
				std::allocator<node>	alloca;
			
				if (!this->leaf())
				{
					alloca.destroy(this->left);
					alloca.deallocate(this->left, 1);
					alloca.destroy(this->right);
					alloca.deallocate(this->right, 1);
					alloc.destroy(this->data);
					alloc.deallocate(this->data, 1);
					this->data = NULL;
					this->left = NULL;
					this->right = NULL;
				}
			}

			//delete and free every nodes of the tree
			void	delete_tree( Alloc alloc )
			{
				std::allocator<node>	alloca;
				
				//std::cout << "A" << std::endl;
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
					node					*nd = this;
					ft::pair<const Key, T>	*tmp;

					if (this->left->size() > this->right->size())
					{
						if (!nd->leaf())
							nd = this->left;
						while(!nd->right->leaf())
							nd = nd->right;
						tmp = this->data;
						this->data = nd->data;
						nd->data = tmp;
						if (nd->parent)
							nd->parent->right->node_to_leaf();
						else
							this->node_to_leaf();
					}
					else
					{
						if (!nd->leaf())
							nd = nd->right;
						while(!nd->left->leaf())
							nd = nd->left;
						tmp = this->data;
						this->data = nd->data;
						nd->data = tmp;
						if (nd->parent)
						{
							nd->node_to_leaf();
						}
						else
							nd->node_to_leaf();
					}
					//alloc.destroy(this);
					//alloc.deallocate(this, 1);
					return (1);
				}

			}
	};
}

#endif