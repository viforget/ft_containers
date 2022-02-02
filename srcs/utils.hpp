#ifndef UTILS_HPP
# define UTILS_HPP

namespace	ft
{

	// enable_if : is void if the first templat is false
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	// integral_constant : the value is equal to <v> 

	template <class T, T v>
	struct integral_constant
	{
	  static const T	value = v;
	  typedef T			value_type;	
	};

	// is_integral :: value is true if T is an integral
	template<class T> struct is_integral : public ft::integral_constant<bool, false> {};
	template<> struct is_integral<bool> : public ft::integral_constant<bool, true> {};
	template<> struct is_integral<char> : public ft::integral_constant<bool, true> {};
	template<> struct is_integral<char16_t> : public ft::integral_constant<bool, true> {};
	template<> struct is_integral<char32_t> : public ft::integral_constant<bool, true> {};
	template<> struct is_integral<wchar_t> : public ft::integral_constant<bool, true> {};
	template<> struct is_integral<signed char> : public ft::integral_constant<bool, true> {};
	template<> struct is_integral<short int> : public ft::integral_constant<bool, true> {};
	template<> struct is_integral<int> : public ft::integral_constant<bool, true> {};
	template<> struct is_integral<long int> : public ft::integral_constant<bool, true> {};
	template<> struct is_integral<long long int> : public ft::integral_constant<bool, true> {};
	template<> struct is_integral<unsigned char> : public ft::integral_constant<bool, true> {};
	template<> struct is_integral<unsigned short int> : public ft::integral_constant<bool, true> {};
	template<> struct is_integral<unsigned int> : public ft::integral_constant<bool, true> {};
	template<> struct is_integral<unsigned long int> : public ft::integral_constant<bool, true> {};
	template<> struct is_integral<unsigned long long int> : public ft::integral_constant<bool, true> {};

	//is_integral<int>

}

#endif
