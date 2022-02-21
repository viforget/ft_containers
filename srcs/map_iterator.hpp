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
		node<typename T::first_type, typename T::second_type	>	*_node;
	public:
		typedef	typename T::first_type				key_type;
		typedef	typename T::second_type				mapped_type;
		typedef node<key_type, mapped_type>			node_type;
//---------- Constructors ----------//

		map_iterator() : _node(NULL) {};
		map_iterator( const map_iterator & ref) : _node(ref._node) {};
		map_iterator( node_type * n) : _node(n) {};

//---------- Destructor ----------//

		~map_iterator() {}

//---------- Operators ----------//

		void	operator=(const map_iterator & ref)
		{
			this->_node = ref._node;
		}
	
		T&	operator*() const
		{
			return (this->_node->data);
		}

		// Operator ++ : First check if the current node has a right child, in wich case it will retrun the leftest descendant of the right child
		//	else check if the current node is a left child, in wich case return his parent
		//	else check if the current node is a right child, in wich case return the parent of the first left ancestor

		map_iterator &	operator++()
		{
			node_type	*n;

			if (!this->_node->right->leaf())
			{
				n = this->_node->right;
				while(!n->left->leaf())
					n = n->left;
				this->_node = n;
			}
			else if (this->_node->parent && this->_node->side == L)
			{
				this->_node = this->_node->parent;
			}
			else if (this->_node->parent)
			{
				n = this->_node->parent;
				while (n->parent && n->side != L)
				{
					n = n->parent;
				}
				n = n->parent;
				if (n)
					this->_node = n;
			}
			return (*this);
		}

		map_iterator 	operator++(int)
		{
			map_iterator	tmp = *this;
			++*this;
			return (tmp);
		}

		// Operator-- : the oposite algorithm of the operator++
		//		left become right and right become left

		map_iterator &	operator--()
		{
			node_type	*n;

			if (!this->_node->left->leaf())
			{
				n = this->_node->left;
				while(!n->right->leaf())
					n = n->right;
				this->_node = n;
			}
			else if (this->_node->parent && this->_node->side == R)
			{
				this->_node = this->_node->parent;
			}
			else if (this->_node->parent)
			{
				n = this->_node->parent;
				while (n->parent && n->side != R)
				{
					n = n->parent;
				}
				n = n->parent;
				if (n)
					this->_node = n;
			}
			return (*this);
		}

		map_iterator 	operator--(int)
		{
			map_iterator	tmp = *this;
			--*this;
			return (tmp);
		}

		bool	operator==(const map_iterator ref) const {return (this->_node == ref._node);}
		bool	operator!=(const map_iterator ref) const {return (this->_node != ref._node);}
		T*	operator->() const { return (&(this->node->value));}

	};
	
}

#endif