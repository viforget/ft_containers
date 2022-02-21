#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "map_utils.hpp"
# include "binary_tree.hpp"

namespace	ft
{
	template <class Key, class T>
	class map_iterator
	{
	private:
		node<const Key, T>	*_node;
	public:
//---------- Constructors ----------//

		map_iterator() : _node(NULL) {};
		map_iterator( const map_iterator & ref) : _node(ref.node) {};
		map_iterator( const node<const Key, T> & n) : _node(n) {};

//---------- Destructor ----------//

		~map_iterator() {}

//---------- Operators ----------//

		void	operator=(const map_iterator & ref)
		{
			this->_node = ref.node;
		}
	
		T*		operator*() const
		{
			return (this->_node.data);
		}

		map_iterator &	operator++()
		{
			node<const Key, T>	*n;

			this->_node;
			if (!this->_node->right->leaf())
			{
				n = this->_node->right;
				while(!n->left->leaf())
					n = n->left;
				this->_node = n;
			}
			else if (this->parent && this->_node.side == 0)
			{
				this = this.parent;
			}
			else if (this->parent)
			{
				n = this->_node->parent;
				while (n->parent && n->side != 0)
				{
					n = n->parent;
				}
				if (n && n->parent && n->side == 0)
					this->_node = n;
			}
			return (*this);

		}
	};
	
}

#endif