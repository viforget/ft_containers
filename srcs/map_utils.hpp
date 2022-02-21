#ifndef MAP_UTILS_HPP
# define MAP_UTILS_HPP

#include <iostream>

namespace	ft
{
	template <class T1, class T2>
	struct pair
	{
		public:
			typedef T1	first_type;	
			typedef T2	second_type;
			
			pair ()
			: first(first_type()), second(second_type()) {}
			
			template<class U, class V> pair (const pair<U,V>& pr)
			: first(pr.first), second(pr.second) {}

			pair (const first_type& a, const second_type& b)
			: first(a), second(b) {}

			void operator=( const pair & ref)
			{
				this->first = ref.first;
				this->second = ref.second;
			}
			
			first_type	first;
			second_type	second;
	};
}

#endif