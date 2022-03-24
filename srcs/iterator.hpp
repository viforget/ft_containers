#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>
# include <memory>
# include "vector.hpp"
//# include "reverse_iterator.hpp"
# include "utils.hpp"
# include "map_utils.hpp"


namespace	ft
{
	template <class T2>
	class reverse_random_iterator;

	template < class T >
	class random_iterator
	{
		private:
			T*	_pointer;
		public:
			typedef typename ft::iterator<random_iterator, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<random_iterator, T>::value_type			value_type;
			typedef typename ft::iterator<random_iterator, T>::difference_type		difference_type;
			typedef typename ft::iterator<random_iterator, T>::pointer				pointer;
			typedef typename ft::iterator<random_iterator, T>::reference			reference;
			
//---------- Constructors ----------//

			random_iterator( void ) : _pointer(NULL) {}
			random_iterator( const random_iterator<typename remove_const<T>::type > & ref ) : _pointer(ref.base()) {}
			random_iterator( const reverse_random_iterator<typename remove_const<T>::type > & ref ) : _pointer(ref.base()) {}
			random_iterator( pointer pointer ) : _pointer(pointer) {}

//---------- Destructor ----------//

			~random_iterator( void ) {};
			
//---------- Operators ----------//

			random_iterator<T> &  operator= (const random_iterator<typename remove_const<T>::type > & rhs)
			{
				this->_pointer = rhs.base();
				return (*this);
			}

			reference operator*() const
			{
				return(*this->_pointer);
			}
			
			T* base() const
			{
				return(this->_pointer);
			}	

			random_iterator&	operator++()
			{
				this->_pointer++;
				return (*this);
			}

			random_iterator		operator++(int)
			{
				random_iterator tmp = *this;
				this->_pointer++;
				return (tmp);
			}

			random_iterator&	operator--()
			{
				this->_pointer--;
				return (*this);
			}
			random_iterator		operator--(int)
			{
				random_iterator tmp = *this;
				this->_pointer--;
				return (tmp);
			}

			random_iterator		operator+(difference_type n)
			{
				return(random_iterator(this->_pointer + n));
			}

			reference		operator[](size_t n)
			{
				return(*(this->_pointer + n));
			}

			random_iterator		operator-(difference_type n)
			{
				return(random_iterator(this->_pointer - n));
			}

			difference_type		operator-(random_iterator const & b)
			{
				return(this->_pointer - b._pointer);
			}

			random_iterator	&	operator-=(difference_type n)
			{
				this->_pointer -= n;
				return(*this);
			}

			random_iterator	 &	operator+=(difference_type n)
			{
				this->_pointer += n;
				return(*this);
			}

			pointer 			operator->(void)
			{
				return &(this->operator*());
			}

			bool				operator<(random_iterator const & ref) {return ((this->_pointer) < (ref._pointer));}
			bool				operator<=(random_iterator const & ref) {return ((this->_pointer) <= (ref._pointer));}
			bool				operator>(random_iterator const & ref) {return ((this->_pointer) > (ref._pointer));}
			bool				operator>=(random_iterator const & ref) {return ((this->_pointer) >= (ref._pointer));}
			bool				operator==(random_iterator const & ref) {return ((this->_pointer) == (ref._pointer));}
			bool				operator!=(random_iterator const & ref) {return ((this->_pointer) != (ref._pointer));}
			
			template < class T2 >
			friend size_t operator-(random_iterator<T2> const & a, random_iterator<T2> const & b);
			friend bool	operator<(random_iterator const & a, random_iterator const & ref) {return ((a._pointer) < (ref._pointer));}
			friend bool	operator<=(random_iterator const & a, random_iterator const & ref) {return ((a._pointer) <= (ref._pointer));}
			friend bool	operator>(random_iterator const & a, random_iterator const & ref) {return ((a._pointer) > (ref._pointer));}
			friend bool	operator>=(random_iterator const & a, random_iterator const & ref) {return ((a._pointer) >= (ref._pointer));}
			friend bool	operator==(random_iterator const & a, random_iterator const & ref) {return ((a._pointer) == (ref._pointer));}
			friend bool	operator!=(random_iterator const & a, random_iterator const & ref) {return ((a._pointer) != (ref._pointer));}
			
	};

	template < class T >
	size_t		operator-(random_iterator<T> const & a, random_iterator<T> const & b)
	{
		return(a._pointer - b._pointer);
	}

	template < class T >
	random_iterator<T>		operator+(int n, random_iterator<T> it)
	{
		return(it + n);
	}

	template < class T >
	bool	operator<(random_iterator<T> const & a, random_iterator<T> const & ref) {return ((a._pointer) < (ref._pointer));}

	template < class T >
	bool	operator<=(random_iterator<T> const & a, random_iterator<T> const & ref) {return ((a._pointer) <= (ref._pointer));}

	template < class T >
	bool	operator>(random_iterator<T> const & a, random_iterator<T> const & ref) {return ((a._pointer) > (ref._pointer));}

	template < class T >
	bool	operator>=(random_iterator<T> const & a, random_iterator<T> const & ref) {return ((a._pointer) >= (ref._pointer));}

	template < class T >
	bool	operator==(random_iterator<T> const & a, random_iterator<T> const & ref) {return ((a._pointer) == (ref._pointer));}
	
	template < class T >
	bool	operator!=(random_iterator<T> const & a, random_iterator<T> const & ref) {return ((a._pointer) != (ref._pointer));}


};

#endif
