#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>

namespace	ft
{
	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		Category	iterator_category
		T			value_type;
		Distance	difference_type;
		Pointer		pointer;
		Reference	reference;
	};

};

#endif
