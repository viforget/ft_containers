#ifndef MAP_HPP
# define MAP_HPP

# include "map_utils.hpp"
# include "binary_tree.hpp"
# include "map_iterator.hpp"
# include "reverse_iterator.hpp"

# include <functional>

#include <iostream>

namespace	ft
{
	template < class Key, class T, class Compare = std::less<Key>,
		class Alloc = std::allocator<pair<const Key,T> > >
	class	map
	{
		private:
			node<Key, T> *	_root;
			Compare			_comp;
			Alloc			_alloc;

		public:
//---------- Member types ----------//

			typedef	Key											key_type;
			typedef	T											mapped_type;
			typedef	ft::pair<const key_type, mapped_type>		value_type;
			typedef	Compare										key_compare;
			typedef	Alloc										allocator_type;
			typedef	typename allocator_type::reference			reference;
			typedef	typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef	typename allocator_type::const_pointer		const_pointer;
			typedef	ft::map_iterator<pair<const Key, T> >		iterator;
			typedef	ft::map_iterator<const pair<const Key, T> >	const_iterator;
			typedef	ft::reverse_iterator<iterator> 				reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef	size_t										size_type;

//---------- Constructors ----------//

			//Basic constructor; create an empty binary tree (only a leaf)
			explicit map (const key_compare& comp = key_compare(),
            	 const allocator_type& alloc = allocator_type())
				 : _root(new node<key_type, mapped_type>), _comp(comp), _alloc(alloc)
			{
				std::allocator<node<key_type, mapped_type> >	alloca;

				this->_root = alloca.allocate(1);
				alloca.construct(this->_root, node<key_type, mapped_type>());
			}

			
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
			 		const key_compare& comp = key_compare(),
			 		const allocator_type& alloc = allocator_type())
					:  _root(new node<key_type, mapped_type>), _comp(comp), _alloc(alloc)
			{
				this->insert(first, last);
			}

			//Third constructor; take an other map
			//Create a deep copy of the first map
			map (const map& x) : _root(NULL), _comp(x._comp), _alloc(x._alloc)
			{
				*this = x;
			}

//---------- Destructor ----------//

			~map()
			{
				this->_root->delete_tree(this->_alloc);
			}

//---------- Operator= ----------//

			map& operator= (const map& x)
			{
				std::allocator<pair<const Key,T> >	alloc;
				this->clear();
				this->insert(x.begin(), x.end());
				return (*this);
			}

//---------- Iterators ----------//

			iterator begin()
			{
				node<Key, T>*	n = this->_root;

				while(n->left && !n->left->leaf())
				{
					n = n->left;
				}
				return (iterator(n));
			}

			const_iterator begin() const
			{
				node<Key, T>*	n = this->_root;

				while(!n->left->leaf())
					n = n->left;
				return (const_iterator(n));
			}

			iterator end()
			{
				node<Key, T>*	n = this->_root;

				while(n->right)
					n = n->right;
				return (iterator(n));
			}

			const_iterator end() const
			{
				node<Key, T>*	n = this->_root;

				while(n->right)
					n = n->right;
				return (const_iterator(n));
			}

			reverse_iterator rbegin()
			{
				node<Key, T>*	n = this->_root;

				while(n->right && !n->left->leaf())
					n = n->right;
				return (reverse_iterator(n));
			}

			const_reverse_iterator rbegin() const
			{
				node<Key, T>*	n = this->_root;

				while(n->right && !n->left->leaf())
					n = n->right;
				return (const_reverse_iterator(n));
			}

			reverse_iterator rend()
			{
				node<Key, T>*	n = this->_root;

				while(n->left)
				{
					n = n->left;
				}
				return (reverse_iterator(n));
			}

			const_reverse_iterator rend() const
			{
				node<Key, T>*	n = this->_root;

				while(n->left)
				{
					n = n->left;
				}
				return (const_reverse_iterator(n));
			}

//---------- Capacity ----------//

			bool empty() const
			{
				return (this->_root->leaf());
			}

			size_type size() const
			{
				if (this->_root->leaf())
					return (0);
				return (this->_root->size());
			}

			size_type max_size() const
			{
				std::allocator<node<Key, T> >	alloca;

				return(alloca.max_size());
				// return (288230376151711743);
			}

//---------- Element Acess ----------//

			mapped_type& operator[] (const key_type& k)
			{
				node<Key, T> *	n = this->_root;

				while(!n->leaf())
				{
					if (this->_comp(n->data->first, k))
						n = n->left;
					else if (this->_comp(k, n->data->first))
						n = n->right;
					else 
						return (n->data->second);
				}
				n->leaf_to_node(pair<key_type, mapped_type>(k, mapped_type()), this->_alloc);
				return (n->data->second);
			}

//---------- Modifiers ----------//

			pair<iterator,bool> insert (const value_type& val)
			{
				return (this->_root->insert(val, this->_alloc));
			}

			iterator insert (iterator position, const value_type& val)
			{
				static_cast<void>(position);
				return (this->_root->insert(val, this->_alloc).first);
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					this->_root->insert(*first, this->_alloc); // HERE
					first++;
				}
			}

			void erase (iterator position)
			{
				this->_root->erase((*position).first);
			}

			size_type erase (const key_type& k)
			{
				return (this->_root->erase(k));
			}

			void erase (iterator first, iterator last)
			{
				while (first != last)
				{
					this->erase(first);
					first++;
				}
			}

			void swap (map& x)
			{
				node<Key, T> *	tmp_root = this->_root;
				Alloc			tmp_alloc = this->_alloc;
				Compare			tmp_comp = this->_comp;

				this->_root = x._root;
				this->_alloc = x._alloc;
				this->_comp = x._comp;
				x._root = tmp_root;
				x._alloc = tmp_alloc;
				x._comp = tmp_comp;
			}

			void clear()
			{
				if (this->_root)
					this->_root->delete_tree(this->_alloc);
				this->_root = new node<key_type, mapped_type>;
			}

//---------- Observers ----------//

			// Returns a copy of the comparison object used by the container to compare keys
			key_compare key_comp() const
			{
				return (this->_comp);
			}

			class value_compare
			{
				friend class map;
				protected:

					Compare comp;
					value_compare (Compare c) : comp(c) {}

				public:

					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

			value_compare value_comp() const
			{
				return (value_compare(_comp));
			}

//---------- Operations ----------//
			
			iterator find (const key_type& k)
			{
				node<Key, T> *	n = this->_root;
				
				while(!n->leaf())
				{
					if (this->_comp(n->data->first, k))
						n = n->left;
					else if (this->_comp(k, n->data->first))
						n = n->right;
					else 
						return (iterator(n));
				}
				return (this->end());
			}

			const_iterator find (const key_type& k) const
			{
				node<Key, T> *	n = this->_root;
				
				while(!n->leaf())
				{
					if (this->_comp(n->data->first, k))
						n = n->left;
					else if (this->_comp(k, n->data->first))
						n = n->right;
					else 
						return (const_iterator(n));
				}
				return (this->end());
			}

			size_type count (const key_type& k) const
			{
				node<Key, T> *	n = this->_root;
				
				while(!n->leaf())
				{
					if (this->_comp(n->data->first, k))
						n = n->left;
					else if (this->_comp(k, n->data->first))
						n = n->right;
					else 
						return (1);
				}
				return (0);
			}

			iterator lower_bound (const key_type& k)
			{
				iterator it = this->begin();
				iterator end = this->end();

				while (it != end)
				{
					if (!(this->_comp((*it).first, k)))
						return (it);
					it++;
				}
				return (end);
			}

			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator it = this->begin();
				const_iterator end = this->end();

				while (it != end)
				{
					if (!(this->_comp((*it).first, k)))
						return (it);
					it++;
				}
				return (end);
			}

			iterator upper_bound (const key_type& k)
			{
				iterator it = this->begin();
				iterator end = this->end();

				while (it != end)
				{
					if ((this->_comp(k, (*it).first)))
						return (it);
					it++;
				}
				return (end);
			}

			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator it = this->begin();
				const_iterator end = this->end();

				while (it != end)
				{
					if ((this->_comp(k, (*it).first)))
						return (it);
					it++;
				}
				return (end);
			}

			pair<iterator,iterator>             equal_range (const key_type& k)
			{
				node<Key, T> *	n = this->_root;
				node<Key, T> *	n2 = n;
				
				while(!n->leaf())
				{
					if (this->_comp(n->data->first, k))
						n = n->left;
					else if (this->_comp(k, n->data->first))
						n = n->right;
					else 
					{
						n2 = n;
						n2++;
						return (pair<iterator,iterator>(iterator(n), iterator(n2)));
					}
				}
				n2 = this->end().get_node();
				return (pair<iterator,iterator>(iterator(n2), iterator(n2)));
			}

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				node<Key, T> *	n = this->_root;
				node<Key, T> *	n2 = n;
				
				while(!n->leaf())
				{
					if (this->_comp(n->data->first, k))
						n = n->left;
					else if (this->_comp(k, n->data->first))
						n = n->right;
					else 
					{
						n2 = n;
						n2++;
						return (pair<iterator,iterator>(iterator(n), iterator(n2)));
					}
				}
				n2 = this->end().get_node();
				return (pair<const_iterator, const_iterator>(const_iterator(n2), const_iterator(n2)));
			}

//---------- Allocator ----------//

			allocator_type get_allocator() const
			{
				return (this->_alloc);
			}
	};

//---------- Non-member function overloads ----------//

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		typename ft::map<Key, T>::const_iterator	it = lhs.begin(), ite = rhs.begin(), end = lhs.end(), en = rhs.end();

		while(it != end && ite != en)
		{
			if (*it != *ite)
				return (0);
			it++;
			ite++;
		}
		if (*it != *ite)
		{
			return (0);
		}
		return (1);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		typename ft::map<Key, T>::const_iterator	it = lhs.begin(), ite = rhs.begin(), end = lhs.end(), en = rhs.end();
	
		if (lhs.size() < rhs.size())
			return (true);
		while(it != end && ite != en)
		{
			if (*it < *ite)
				return (true);
			else if (*ite < *it)
				return (false);
			it++;
			ite++;
		}
		return (false);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs == rhs || lhs < rhs)
			return (true);
		return (false);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs > lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs == rhs || rhs < lhs)
			return (true);
		return (false);
	}
}

#endif