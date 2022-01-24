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
			this->_array = this->_alloc.allocate(this->_size);
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
		void operator= (const vector& x)
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

//---------- Capacity ----------//

		size_type	size() const
		{
			return (this->_size);
		}

		size_type	max_size() const
		{
			return (this->_alloc.max_size());
		}

		//Resize : if n is bigger than the size, alloc more else, delete lasts element until the size is equal to n

		void resize (size_type n, value_type val = value_type())
		{
			if (n < this->_size)
			{
				for (size_t i = n; i < this->_size; i++)
				{
					this->_alloc.destroy(this->_array + i);
				}
			}
			else
			{
				if (n > this->_capacity)
					reserve(n);
				if (n > this->_size)
				{
					for (size_t i = this->_size; i < n; i++)
						this->_alloc.construct(this->_array + i, val);
				}
			}
			this->_size = n;
		}

		size_type capacity() const
		{
			return (this->_capacity);
		}

		bool empty() const
		{
			return (this->_size == 0 ? true : false);
		}

		void reserve (size_type n)
		{
			size_t	nb = this->_capacity == 0 ? 1 : this->_capacity;

			if (n > this->max_size())
			{
				throw(std::length_error("vector"));
			}
			if (n > this->_capacity)
			{
				T*	array;

				while(nb < n)
					nb *= 2;
				if (nb > this->max_size())
					nb = this->max_size();
				array = this->_alloc.allocate(nb);
				for (size_t i = 0; i < this->_size; i++)
				{
					this->_alloc.construct(array + i, this->_array[i]);
					this->_alloc.destroy(this->_array + i);
				}
				this->_alloc.deallocate(this->_array, this->_capacity);
				this->_array = array;
				this->_capacity = nb;
			}
		}

//---------- Element acess ----------//

		//Operator[] is not protected, if n exceed the capacity, the behavior is undefined

		reference operator[] (size_type n)
		{
			return (this->_array[n]);
		}

		const_reference operator[] (size_type n) const
		{
			return (this->_array[n]);
		}

		//at is protected, if n exceed the capacity, an out of range exception is thrown

		reference at (size_type n)
		{
			if (n >= this->_size)
				throw(std::out_of_range("vector"));
			else
				return (this->_array[n]);
		}
		
		const_reference at (size_type n) const
		{
			if (n >= this->_size)
				throw(std::out_of_range("vector"));
			else
				return (this->_array[n]);
		}

		reference front()
		{
			return (this->_array[0]);
		}

		const_reference front() const
		{
			return (this->_array[0]);
		}

		reference back()
		{
			return (this->_array[this->_size - 1]);
		}

		const_reference back() const
		{
			return (this->_array[this->_size - 1]);
		}
		
//---------- Modifiers ----------//


		// The resize is for destroy every data in the vector
		// The reserve is to allocate more capacity if needed
		template <class InputIterator>
  		void assign (InputIterator first, InputIterator last)
		{
			if (first > last)
				throw(std::length_error("vector"));
			this->resize(0);
			this->reserve(last - first);
			this->_size = last - first;
			while (first < last)
			{
				this->_alloc.construct(this->_array + (this->_size - (last - first)), *first);
				first++;
			}

		}

		void assign (size_type n, const value_type& val)
		{
			this->resize(0);
			this->reserve(n);
			this->_size = n;
			for (size_t i = 0; i < n; i++)
			{
				this->_alloc.construct(this->_array + i, val);
			}
		}

		void push_back (const value_type& val)
		{
			this->resize(this->_size + 1, val);
		}

		void pop_back()
		{
			this->resize(this->_size - 1);
		}

		iterator insert (iterator position, const value_type& val)
		{
			size_t	i = 0;
			size_t	e = this->_size;

			for (iterator it = this->begin(); it < position; it++)
			{
				i++;
			}
			this->reserve(this->_size + 1);
			this->_size += 1;
			while(e > i)
			{
				this->_array[e] = this->_array[e - 1];
				e--;
			}
			this->_alloc.construct(this->_array + i, val);
			return (position);
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			size_t	i = 0;
			size_t	e = this->_size - 1 + n;

			for (iterator it = this->begin(); it < position; it++)
			{
				i++;
			}
			this->reserve(this->_size + n);
			this->_size += n;
			while(e >= i + n)
			{
				this->_array[e] = this->_array[e - n];
				e--;
			}
			while (e >= i && e != static_cast<size_t>(-1))
			{
				this->_alloc.construct(this->_array + e, val);
				e--;
			}
		}

		template <class InputIterator>
	    void insert (iterator position, InputIterator first, InputIterator last)
		{
			size_t	n = last - first;
			size_t	i = 0;
			size_t	e = this->_size - 1 + n;

			if (first > last)
				throw(std::length_error("vector"));
			for (iterator it = this->begin(); it < position; it++)
			{
				i++;
			}
			this->reserve(this->_size + n);
			this->_size += n;
			std::cout << "a " << e << std::endl;
			while(e >= i + n)
			{
				this->_array[e] = this->_array[e - n];
				e--;
			}
			while (e >= i && e != static_cast<size_t>(-1))
			{
				this->_alloc.construct(this->_array + e, *(first + e - i));
				n--;
				e--;
			}
		}

		iterator erase (iterator position)
		{
			while(position < this->end() - 1)
			{
				*position = *(position + 1);
				position++;
			}
			this->resize(this->_size - 1);
			return(position);
		}

		iterator erase (iterator first, iterator last)
		{
			size_t	n = last - first;
			size_t	i = 0;

			if (first > last)
				throw(std::length_error("vector"));
			while (first + n < this->end())
			{
				*(first + i) = *(first + i + n);
				i++;
			}
			this->resize(this->_size - n);
			return (first);
		}

		void swap (vector& x)
		{
			vector	y(x);
			x = *this;
			*this = y;
		}

		void clear()
		{
			for (std::size_t i = 0; i < this->_size; i++)
				this->_alloc.destroy(this->_array + i);
			this->_size = 0;
		}

//---------- Allocator ----------//

		allocator_type get_allocator() const
		{
			return (this->_alloc);
		}
	};

//---------- Non-member function overloads ----------//

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
		{
			for (size_t i = 0; i < rhs.size(); i++)
			{
				if (!(lhs[i] == rhs[i]))
					return (false);
			}
			return (true);
		}
		return (false);
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		size_t i = 0;

		while(i < lhs.size() && i < rhs.size())
		{
			if (lhs[i] < rhs[i])
				return (true);
			else if (rhs[i] < lhs[i])
				return (false);
			i++;
		}
		if (lhs.size() < rhs.size())
			return (true);
		else
			return (false);
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs == rhs || lhs < rhs)
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs == rhs || rhs < lhs)
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		vector<T,Alloc>	z(x);
		x = y;
		y = z;
	}

};

#endif
