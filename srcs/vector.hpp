#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <iterator>
# include <stdexcept>
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
		typedef T												value_type;
		typedef Alloc											allocator_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename Alloc::pointer							pointer;
		typedef typename Alloc::const_pointer					const_pointer;
		typedef	ft::random_iterator<value_type>					iterator;
		typedef	ft::random_iterator<const value_type>			const_iterator;
		typedef ft::reverse_random_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_random_iterator<const_iterator>	const_reverse_iterator;
		typedef std::ptrdiff_t									difference_type;
		typedef std::size_t										size_type;



//---------- Constructors ----------//

		//First constructor; don't take annything exepct a non-mandatory allocator
		//Create an empty array
		explicit vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc)
		{
			this->_array = this->_alloc.allocate(0);
		}

		//Second constructor; take a size (n) and a value (val)
		//Create an array of size n, every data in it is val
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), _alloc(alloc)
		{
			this->_array = this->_alloc.allocate(n);
			for (unsigned int i = 0; i < n; i++)
				this->_alloc.construct(this->_array + i, val);
		}

		//Third constructor; take 2 Iterator (first)(last)
		//Create an array with every data between first and last
		//If the first iterator is further than the last one; throw an exception
		template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc)
		{
			InputIterator first2 = first;
			
			if (first > last)
				throw(std::length_error("vector"));
			for (; first2 < last; first2++)
				this->_size++;
			this->_array = this->_alloc.allocate(this->_size++);
			this->_capacity = this->_size;
			for (std::size_t i = 0; i < this->_size; i++)
				this->_alloc.construct(this->_array + i, *(first + i));
		}

		//4th constructor; take an other vector
		//Create a deep copy of the first vector
		vector (const vector& x) : _size(x._size), _capacity(x._capacity), _alloc(x._alloc)
		{
			this->_array = this->_alloc.allocate(this->_capacity);
			for (std::size_t i = 0; i < this->_size; i++)
				this->_alloc.construct(this->_array + i, x._array[i]);
		}

//---------- Destructor ----------//

		//Destructor : Destroy every data and deallocate the array
		~vector ()
		{
			for (std::size_t i = 0; i < this->_size; i++)
				this->_alloc.destroy(this->_array + i);
			this->_alloc.deallocate(this->_array, this->_capacity);
		}

//---------- Operator= ----------//

		// operator = : Destroy every data and deallocate the array then make a deep copy of the other vector
		vector& operator= (const vector& x)
		{
			for (std::size_t i = 0; i < this->_size; i++)
				this->_alloc.destroy(this->_array + i);
			this->_alloc.deallocate(this->_array, this->_capacity);
			this->_size = x._size;
			this->_capacity = x._capacity;
			this->_alloc = x._alloc;
			this->_array = this->_alloc.allocate(this->_capacity);
			for (std::size_t i = 0; i < this->_size; i++)
				this->_alloc.construct(this->_array + i, x._array[i]);
		}

//---------- Iterators ----------//
		
		iterator begin()
		{
			return (iterator(this->_array));
		}

		const_iterator begin() const
		{
			return (const_iterator(this->_array));
		}

		iterator end()
		{
			return (iterator(this->_array + this->_size));
		}

		const_iterator end() const
		{
			return (const_iterator(this->_array + this->_size));
		}

		iterator rbegin()
		{
			return (iterator(this->_array + this->_size));
		}

		const_iterator rbegin() const
		{
			return (const_iterator(this->_array + this->_size));
		}

		iterator rend()
		{
			return (iterator(this->_array));
		}

		const_iterator rend() const
		{
			return (const_iterator(this->_array));
		}
	};
};

#endif
