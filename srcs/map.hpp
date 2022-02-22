#ifndef MAP_HPP
# define MAP_HPP

# include "map_utils.hpp"
# include "binary_tree.hpp"
# include "map_iterator.hpp"

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
			Alloc			_alloc;
			Compare			_comp;

		public:
//---------- Member types ----------//

			typedef	Key											key_type;
			typedef	T											mapped_type;
			typedef	ft::pair<const key_type, mapped_type>		value_type;
			typedef	Compare										key_compare;
			// typedef		value_compare
			typedef	Alloc										allocator_type;
			typedef	typename allocator_type::reference			reference;
			typedef	typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef	typename allocator_type::const_pointer		const_pointer;
			typedef	ft::map_iterator<pair<const Key, T> >		iterator;
			typedef	ft::map_iterator<pair<const Key, T> >		const_iterator;
			// typedef	reverse_iterator;
			// typedef	const_reverse_iterator;
			typedef	size_t								size_type;

//---------- Constructors ----------//

			//Basic constructor; create an empty binary tree (only a leaf)
			explicit map (const key_compare& comp = key_compare(),
            	 const allocator_type& alloc = allocator_type())
				 : _root(new node<key_type, mapped_type>), _comp(comp) {}

			
			// template <class InputIterator>
			// map (InputIterator first, InputIterator last,
			// 		const key_compare& comp = key_compare(),
			// 		const allocator_type& alloc = allocator_type());

			//Third constructor; take an other map
			//Create a deep copy of the first map
			map (const map& x);

//---------- Destructor ----------//

			~map()
			{
				this->_root->delete_tree();
			}

//---------- Operator= ----------//

			map& operator= (const map& x)
			{
				
			}

//---------- Iterators ----------//

			iterator begin()
			{
				node<Key, T>*	n = this->_root;

				while(!n->left->leaf())
					n = n->left;
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

				while(!n->right->leaf())
					n = n->right;
				return (iterator(n));
			}

			const_iterator end() const
			{
				node<Key, T>*	n = this->_root;

				while(!n->right->leaf())
					n = n->right;
				return (const_iterator(n));
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
				return(this->alloc.max_size());
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
						return (n->data->first);
				}
				n->leaf_to_node(make_pair(k, mapped_type()), k);
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
					this->_root->insert(*first, this->_alloc);
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
				this->_root->delete_tree();
				this->_root = new node<key_type, mapped_type>;
			}
	};
}

#endif