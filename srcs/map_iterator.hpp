#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "binary_tree.hpp"
# include "map_utils.hpp"
# include "utils.hpp"

namespace	ft
{
	// template<class Key, class T, class Compare = std::less<Key>,
	// 	class Alloc
	//struct node;

	template <class T>
	class map_iterator
	{
	private:
		typedef node<typename remove_const<typename T::first_type>::type, typename T::second_type> node_type;
	public:
		node_type	*_node;
		bool		_lst;												
		typedef	typename T::first_type				key_type;
		typedef	typename T::second_type				mapped_type;
		typedef typename ft::iterator<map_iterator, T>::iterator_category	iterator_category;
		typedef typename ft::iterator<map_iterator, T>::value_type			value_type;
		typedef typename ft::iterator<map_iterator, T>::difference_type		difference_type;
		typedef typename ft::iterator<map_iterator, T>::pointer				pointer;
		typedef typename ft::iterator<map_iterator, T>::reference			reference;
//---------- Constructors ----------//

		map_iterator() : _node(NULL), _lst(0) {};

		map_iterator( const map_iterator<typename remove_const<T>::type> & ref) : _lst(ref._lst)
		{
			*this = ref;
			if (this->_node->leaf())
				this->_lst = 1;
		}

		map_iterator( node_type * n ) : _node(n), _lst(0)
		{
			if (this->_node->leaf())
				this->_lst = 1;
			//std::cout << this->_lst << std::endl;
		}

//---------- Destructor ----------//

		~map_iterator() {}

//---------- Operators ----------//

		node_type *	get_node() const
		{
			return (this->_node);
		}

		void	operator=(const map_iterator<typename remove_const<T>::type> & ref)
		{
			this->_node = ref.get_node();
			if (this->_node->leaf())
				this->_lst = 1;	
		}
	
		T&	operator*() const
		{
			return (*(this->_node->data));
		}

		// Operator ++ : First check if the current node has a right child, in wich case it will retrun the leftest descendant of the right child
		//	else check if the current node is a left child, in wich case return his parent
		//	else check if the current node is a right child, in wich case return the parent of the first left ancestor

		map_iterator &	operator++()
		{
			node_type	*n;

			if (this->_node->leaf())
			{
				if (this->_node->parent)
					this->_node = this->_node->side == L ? this->_node->parent : this->_node;
			}
			else if (!this->_node->right->leaf())
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
				else if (this->_node->right)
					this->_node = this->_node->right;
			}
			else if (this->_node->right)
				this->_node = this->_node->right;
			if (this->_node->leaf())
				this->_lst = 1;
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

			if (this->_node->leaf())
			{
				if (this->_node->parent)
					this->_node = this->_node->side == R ? this->_node->parent : this->_node;
			}
			else if (!this->_node->left->leaf())
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
				else if (this->_node->left)
					this->_node = this->_node->left;
			}
			else if (this->_node->left)
				this->_node = this->_node->left;
			if (this->_node->leaf())
				this->_lst = 1;
			return (*this);
		}

		map_iterator 	operator--(int)
		{
			map_iterator	tmp = *this;
			--*this;
			return (tmp);
		}

		bool	operator==(const map_iterator ref) const
		{
			if ((this->_lst == 1 && ref._lst == 1) || 
				(this->_node->leaf() && ref._node->leaf()))
			{
				return (1);
			}
			return (this->_node == ref._node);
		}

		bool	operator!=(const map_iterator ref) const 
		{
			return (!(*this == ref));
		}

		T*		operator->() const 
		{
			return ((this->_node->data));
		}

		bool	leaf( void )
		{
			return (this->_node->leaf());
		}
	};
}

#endif