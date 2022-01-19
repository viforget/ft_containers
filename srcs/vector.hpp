#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <iterator>
# include "iterator.hpp"

namespace	ft
{
	template< class T, class Alloc = std::allocator<T> >
	class vector
	{
	private:
		T*			_array;
		std::size_t	_size;
		std::size_t	_capacity;
		Alloc		_alloc;	
	public:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename Alloc::pointer						pointer;
		typedef typename Alloc::const_pointer				const_pointer;
		typedef	std::random_access_iterator_tag				iterator;
		//typedef	std::random_access_iterator_tag<const value_type>	const_iterator;
		typedef std::reverse_iterator<iterator>				reverse_iterator;
		//typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef std::ptrdiff_t								difference_type;
		typedef std::size_t									size_type;

		explicit vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc)
		{
			this->_array = this->_alloc.allocate(0);
		}

		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), _alloc(alloc)
		{
			this->_array = this->_alloc.allocate(n);
			for (unsigned int i = 0; i < n; i++)
				this->_alloc.construct(this->_array + i, val);
		}

		template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc)
		{
			InputIterator first2 = first;
			for (; first2 < last; first2++)
				this->_size++;
			this->_array = this->_alloc.allocate(this->_size++);
			this->_capacity = this->_size;
			for (std::size_t i = 0; i < this->_size; i++)
				this->_alloc.construct(this->_array + i, *(first + i));
		}

		vector (const vector& x) : _size(x._size), _capacity(x._capacity), _alloc(x._alloc)
		{
			this->_array = this->_alloc.allocate(this->_capacity);
			for (std::size_t i = 0; i < this->_size; i++)
				this->_alloc.construct(this->_array + i, x._array[i]);
		}

		~vector ()
		{
			for (std::size_t i; i < this->_size; i++)
				this->_alloc.deconstruct(this->_array + i);
			this->_alloc.deallocate(this->_array);
		}

		vector& operator= (const vector& x)
		{
			for (for (std::size_t i = 0; i < this->_size; i++)
				this->_alloc.deconstruct(this->_array + i);
			this->_alloc.deallocate(this->_array);
			this->_size = x._size;
			this->_capacity = x._capacity;
			this->_alloc = x._alloc;
			this->_array = this->_alloc.allocate(this->_capacity);
			for (std::size_t i = 0; i < this->_size; i++)
				this->_alloc.construct(this->_array + i, x._array[i]);
		}
	};

};

#endif
