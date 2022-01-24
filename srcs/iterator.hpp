#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>
# include <memory>

namespace	ft
{
	template</*class Category, */class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		//typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};
	
	template < class T >
	class random_iterator
	{
		public:
			//typedef ft::iterator<T>::iterator_category	iterator_category;
			typedef typename ft::iterator<T>::value_type		value_type;
			typedef typename ft::iterator<T>::difference_type	difference_type;
			typedef typename ft::iterator<T>::pointer			pointer;
			typedef typename ft::iterator<T>::reference			reference;
			
//---------- Constructors ----------//

			random_iterator( void ) : _pointer(NULL) {}
			random_iterator( pointer pointer ) : _pointer(pointer) {}

//---------- Destructor ----------//

			~random_iterator( void ) {};
			
//---------- Operators ----------//

			void operator=(random_iterator const & ref)
			{
				this->_pointer = ref._pointer;
			}
			
			reference operator*() const
			{
				return(*this->_pointer);
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

			random_iterator		operator-(difference_type n)
			{
				return(random_iterator(this->_pointer - n));
			}

			difference_type		operator-(random_iterator const & b)
			{
				return(this->_pointer - b._pointer);
			}

			bool				operator<(random_iterator const & ref) {return (*(this->_pointer) < *(ref._pointer));}
			bool				operator<=(random_iterator const & ref) {return (*(this->_pointer) <= *(ref._pointer));}
			bool				operator>(random_iterator const & ref) {return (*(this->_pointer) > *(ref._pointer));}
			bool				operator>=(random_iterator const & ref) {return (*(this->_pointer) >= *(ref._pointer));}
			bool				operator==(random_iterator const & ref) {return (*(this->_pointer) == *(ref._pointer));}
			bool				operator!=(random_iterator const & ref) {return (*(this->_pointer) != *(ref._pointer));}

		private:
			pointer	_pointer;
	};

	template < class T >
	class reverse_random_iterator
	{
		public:
			//typedef ft::iterator<T>::iterator_category	iterator_category;
			typedef typename ft::iterator<T>::value_type		value_type;
			typedef typename ft::iterator<T>::difference_type	difference_type;
			typedef typename ft::iterator<T>::pointer			pointer;
			typedef typename ft::iterator<T>::reference			reference;
			
//---------- Constructors ----------//

			reverse_random_iterator( void ) : _pointer(NULL) {}
			reverse_random_iterator( pointer pointer ) : _pointer(pointer) {}

//---------- Destructor ----------//

			~reverse_random_iterator( void ) {};
			
//---------- Operators ----------//

			void operator=( reverse_random_iterator const & ref )
			{
				this->_pointer = ref._pointer;
				return (this);
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
