#ifndef STACK_HPP
# define STACK_HPP

namespace	ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
//---------- Member types ----------//
			typedef T			value_type;
			typedef	Container	container_type;
			typedef size_t		size_type;
//---------- Member functions ----------//
			explicit stack (const container_type& ctnr = container_type()) : _C(ctnr) {}
			//~stack();
			bool empty() const
			{
				return (this->_C.empty());
			}

			size_type size() const
			{
				return (this->_C.size());
			}

			value_type& top()
			{
				return (this->_C.back());
			}

			const value_type& top() const
			{
				return (this->_C.back());
			}

			void push (const value_type& val)
			{
				this->_C.push_back(val);
			}

			void pop()
			{
				this->_C.pop_back();
			}
		
		private :
//---------- Member functions ----------//
			template <class Tn, class Containern>
			friend bool operator== (const stack<Tn,Containern>& lhs, const stack<Tn,Containern>& rhs);
			template <class Tn, class Containern>
			friend bool operator!= (const stack<Tn,Containern>& lhs, const stack<Tn,Containern>& rhs);
			template <class Tn, class Containern>
			friend bool operator<  (const stack<Tn,Containern>& lhs, const stack<Tn,Containern>& rhs);
			template <class Tn, class Containern>
			friend bool operator<= (const stack<Tn,Containern>& lhs, const stack<Tn,Containern>& rhs);
			template <class Tn, class Containern>
			friend bool operator>  (const stack<Tn,Containern>& lhs, const stack<Tn,Containern>& rhs);
			template <class Tn, class Containern>
			friend bool operator>= (const stack<Tn,Containern>& lhs, const stack<Tn,Containern>& rhs);
		
		protected:
			container_type	_C;
	};

//---------- Member functions ----------//
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._C == rhs._C);
	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._C != rhs._C);
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._C < rhs._C);
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._C <= rhs._C);
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._C > rhs._C);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._C >= rhs._C);
	}

}

#endif