#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "map_utils.hpp"
# include "binary_tree.hpp"

namespace	ft
{
	template <class T>
	class map_iterator
	{
	private:
		_node	*n;
	public:
//---------- Constructors ----------//

		map_iterator() : _node(NULL) ();
		map_iterator( const map_iterator & ref) : _node(ref.node) ();
		map_iterator( const node & ref) : _node(node) ();

//---------- Destructor ----------//

		~map_iterator() {}

//---------- Operators ----------//

		void	operator=(const map_iterator & ref)
		{
			this->_node = ref.node;
		}
	
		T*		operator*() const
		{
			return (this->node.data);
		}

		map_iterator &	operator++()
		{
			node	*n;

			this->_node;
			if (!this->node->right->leaf())
			{
				n = this->node->right;
				while(!n->left->leaf())
					n = n->left;
				this->_node = n;
				return(*this);
			}

		}
	};
	
}

#endif