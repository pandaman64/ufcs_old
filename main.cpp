#include "ufcs.h"

#include <iostream>
#include <initializer_list>
#include <vector>
#include <iterator>
#include <algorithm>

#include "algorithm.h"
#include "make_ufcs_wrapper.h"
#include "boost_range_adapt.h"

struct map_impl{
	template<typename T,typename F>
	typename std::remove_reference<T>::type operator ()(T && seq,F &&f){
		using std::begin;
		using std::end;
		typename std::remove_reference<T>::type ret(seq.size());
		std::transform(begin(seq),end(seq),begin(ret),f);
		return ret;
	}
};
MAKE_UFCS_WRAPPER(map_impl,map);

struct print_impl{
	template<typename T>
	void operator ()(T &&seq){
		for(auto &it : seq){
			std::cout << it << std::endl;
		}
	}
};
MAKE_UFCS_WRAPPER(print_impl,print);

int main(){
	auto l = {1,2,3,4,5,6};
	std::vector<int> v(l.begin(),l.end());
	v->*map([](int i){ return i*2; })->*print();
	return 0;
}
