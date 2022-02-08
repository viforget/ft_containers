#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>
# include <memory>
# include "vector.hpp"
namespace	ft
{
	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};
	
	template < class T >
	class random_iterator
	{
		private:
			T*	_pointer;
		public:
template< class T2 > struct remove_const                { typedef T2 type; };
template< class T2 > struct remove_const<const T2>       { typedef T2 type; };
			typedef typename ft::iterator<random_iterator, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<random_iterator, T>::value_type			value_type;
			typedef typename ft::iterator<random_iterator, T>::difference_type		difference_type;
			typedef typename ft::iterator<random_iterator, T>::pointer				pointer;
			typedef typename ft::iterator<random_iterator, T>::reference			reference;
			
//---------- Constructors ----------//

			random_iterator( void ) : _pointer(NULL) {}
			//random_iterator( const random_iterator & ref ) : _pointer(ref._pointer) {}
			random_iterator( const random_iterator<typename remove_const<T>::type > & ref ) : _pointer(ref.get_pointer()) {}
			random_iterator( pointer pointer ) : _pointer(pointer) {}

//---------- Destructor ----------//

			~random_iterator( void ) {};
			
//---------- Operators ----------//
	

			// random_iterator &  operator= (const random_iterator & rhs)
			// {
			// 	this->_pointer = rhs._pointer;
			// 	return (*this);
			// }

			random_iterator<T> &  operator= (const random_iterator<typename remove_const<T>::type > & rhs)
			{
				this->_pointer = rhs.get_pointer();
				return (*this);
			}

			reference operator*() const
			{
				return(*this->_pointer);
			}
			
			typename remove_const<T>::type* get_pointer() const
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

			bool				operator<(random_iterator const & ref) {return ((this->_pointer) < (ref._pointer));}
			bool				operator<=(random_iterator const & ref) {return ((this->_pointer) <= (ref._pointer));}
			bool				operator>(random_iterator const & ref) {return ((this->_pointer) > (ref._pointer));}
			bool				operator>=(random_iterator const & ref) {return ((this->_pointer) >= (ref._pointer));}
			bool				operator==(random_iterator const & ref) {return ((this->_pointer) == (ref._pointer));}
			bool				operator!=(random_iterator const & ref) {return ((this->_pointer) != (ref._pointer));}
			
			friend random_iterator operator-(random_iterator const & a, random_iterator const & b);
			friend bool	operator<(random_iterator const & a, random_iterator const & ref) {return ((a._pointer) < (ref._pointer));}
			friend bool	operator<=(random_iterator const & a, random_iterator const & ref) {return ((a._pointer) <= (ref._pointer));}
			friend bool	operator>(random_iterator const & a, random_iterator const & ref) {return ((a._pointer) > (ref._pointer));}
			friend bool	operator>=(random_iterator const & a, random_iterator const & ref) {return ((a._pointer) >= (ref._pointer));}

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

	/*template < class T >
	std::ostream&	operator<<( std::ostream &flux, random_iterator<T> const & a )
	{
		flux << a;
    	return flux;
	}*/

	template < class T >
	class reverse_random_iterator
	{
		public:
			typedef typename T::iterator_category	iterator_category;
			typedef typename T::value_type		value_type;
			typedef typename T::difference_type	difference_type;
			typedef typename T::pointer			pointer;
			typedef typename T::reference		reference;
			
//---------- Constructors ----------//

			reverse_random_iterator( void ) : _pointer(NULL) {}
			reverse_random_iterator( pointer pointer ) : _pointer(pointer) {}

//---------- Destructor ----------//

			~reverse_random_iterator( void ) {};
			
//---------- Operators ----------//

			void operator=( reverse_random_iterator const & ref )
			{
				this->_pointer = ref._pointer;
			}
			
			reference operator*() const
			{
				return(*this->_array);
			}
			
			reverse_random_iterator&	operator++()
			{
				this->_pointer--;
				return (*this);
			}
			reverse_random_iterator		operator++(int)
			{
				reverse_random_iterator tmp = *this;
				this->_pointer--;
				return (tmp);
			}

			reverse_random_iterator&	operator--()
			{
				this->_pointer++;
				return (*this);
			}

			reverse_random_iterator		operator--(int)
			{
				reverse_random_iterator tmp = *this;
				this->_pointer++;
				return (tmp);
			}

		private:
			pointer	_pointer;
	};
	
};

#endif
