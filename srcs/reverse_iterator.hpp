#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <iostream>
# include <memory>
//# include "vector.hpp"
//# include "iterator.hpp"
# include "utils.hpp"

namespace	ft
{
	template < class Iterator >
	class reverse_iterator
	{
		private:
			Iterator	_it;
		public:
//---------- Member types ----------//
			typedef Iterator								iterator_type;
			typedef typename Iterator::iterator_category	iterator_category;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
	
//---------- Constructors ----------//
		reverse_iterator() : _it() {}
		explicit reverse_iterator(iterator_type it) : _it(it) {}
		explicit reverse_iterator(pointer p) : _it(iterator_type(p)) {}
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> & ref) : _it(ref.base()) {}
		~reverse_iterator() {}


//---------- Other Function ----------//

		iterator_type	base() const
		{
			return (this->_it);
		}

//---------- Operators ----------//

		reverse_iterator &  operator= (const reverse_iterator & rhs)
		{
			this->_it = rhs.base();
			return (*this);
		}

		reference operator*() const
		{
			iterator_type	tmp = this->_it;
			tmp--;
			return(*tmp);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator	tmp = *this;
			this->_it--;
			return (tmp);
		}

		reverse_iterator operator++()
		{
			--this->_it;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator	tmp = *this;
			this->_it++;
			return (tmp);
		}

		reverse_iterator operator--()
		{
			++this->_it;
			return (*this);
		}

		reverse_iterator		operator+(difference_type n)
		{
			return(reverse_iterator(Iterator(this->_it - n)));
		}

		reference		operator[](size_t n)
		{
			return(*(this->_it - n - 1));
		}

		reverse_iterator		operator-(difference_type n)
		{
			return(reverse_iterator(this->_it + n));
		}

		difference_type		operator-(reverse_iterator const & b)
		{
			return(b._it.base() - this->_it.base());
		}

		reverse_iterator	&	operator-=(difference_type n)
		{
			this->_it += n;
			return(*this);
		}

		reverse_iterator	&	operator+=(difference_type n)
		{
			this->_it -= n;
			return(*this);
		}

		pointer				operator->( void ) const
		{
			return &(this->operator*());
		}

		// bool				operator<(reverse_iterator const & ref) {return ((this->_it) > (ref._it));}
		// bool				operator<=(reverse_iterator const & ref) {return ((this->_it) >= (ref._it));}
		// bool				operator>(reverse_iterator const & ref) {return ((this->_it) < (ref._it));}
		// bool				operator>=(reverse_iterator const & ref) {return ((this->_it) <= (ref._it));}
		// bool				operator==(reverse_iterator const & ref) {return ((this->_it) == (ref._it));}
		// bool				operator!=(reverse_iterator const & ref) {return ((this->_it) != (ref._it));}
			
		friend bool	operator<(reverse_iterator const & a, reverse_iterator const & ref) {return ((a._it) > (ref._it));}
		friend bool	operator<=(reverse_iterator const & a, reverse_iterator const & ref) {return ((a._it) >= (ref._it));}
		friend bool	operator>(reverse_iterator const & a, reverse_iterator const & ref) {return ((a._it) < (ref._it));}
		friend bool	operator>=(reverse_iterator const & a, reverse_iterator const & ref) {return ((a._it) <= (ref._it));}
		friend bool	operator==(reverse_iterator const & a, reverse_iterator const & ref) {return ((a._it) == (ref._it));}
		friend bool	operator!=(reverse_iterator const & a, reverse_iterator const & ref) {return ((a._it) != (ref._it));}

	};

	template < class Iterator >
	reverse_iterator<Iterator>		operator+(int n, reverse_iterator<Iterator> it)
	{
		return(it + n);
	}

	template < class Iterator >
	bool	operator<(reverse_iterator<Iterator> const & a, reverse_iterator<Iterator> const & ref) {return ((a._it) > (ref._it));}

	template < class Iterator1, class Iterator2 >
	bool	operator<(reverse_iterator< Iterator1> const & a, reverse_iterator< Iterator2 > const & ref) {return ((a.base()) > (ref.base()));}

	template < class Iterator >
	bool	operator<=(reverse_iterator<Iterator> const & a, reverse_iterator<Iterator> const & ref) {return ((a._it) >= (ref._it));}

	template < class Iterator1, class Iterator2 >
	bool	operator<=(reverse_iterator< Iterator1> const & a, reverse_iterator< Iterator2 > const & ref) {return ((a.base()) >= (ref.base()));}

	template < class Iterator >
	bool	operator>(reverse_iterator<Iterator> const & a, reverse_iterator<Iterator> const & ref) {return ((a._it) < (ref._it));}

	template < class Iterator1, class Iterator2 >
	bool	operator>(reverse_iterator< Iterator1> const & a, reverse_iterator< Iterator2 > const & ref) {return ((a.base()) < (ref.base()));}

	template < class Iterator >
	bool	operator>=(reverse_iterator<Iterator> const & a, reverse_iterator<Iterator> const & ref) {return ((a._it) <= (ref._it));}

	template < class Iterator1, class Iterator2 >
	bool	operator>=(reverse_iterator< Iterator1> const & a, reverse_iterator< Iterator2 > const & ref) {return ((a.base()) <= (ref.base()));}


	template < class Iterator >
	bool	operator==(reverse_iterator<Iterator> const & a, reverse_iterator<Iterator> const & ref) {return ((a._it) == (ref._it));}
	
	template < class Iterator1, class Iterator2 >
	bool	operator==(reverse_iterator< Iterator1> const & a, reverse_iterator< Iterator2 > const & ref) {return ((a.base()) == (ref.base()));}


	template < class Iterator >
	bool	operator!=(reverse_iterator<Iterator> const & a, reverse_iterator<Iterator> const & ref) {return ((a._it) != (ref._it));}

	template < class Iterator1, class Iterator2 >
	bool	operator!=(reverse_iterator< Iterator1> const & a, reverse_iterator< Iterator2 > const & ref) {return ((a.base()) != (ref.base()));}


};

#endif
