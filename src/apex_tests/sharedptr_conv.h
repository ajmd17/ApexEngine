#ifndef SHAREDPTR_CONV_H
#define SHAREDPTR_CONV_H 

// Converts between shared_ptr types. Necessary for Luabind to work with shared_ptr
// Courtesy of: http://stackoverflow.com/questions/15037955/luabind-cant-return-shared-ptr

#include <boost/version.hpp>
#if BOOST_VERSION >= 105300
#include <boost/get_pointer.hpp>
namespace luabind {
	namespace detail {
		namespace has_get_pointer_ {
			template<class T>
			T * get_pointer(std::shared_ptr<T> const& p) { return p.get(); }
		}
	}
}

#else
#include <memory>
namespace std {

#if defined(_MSC_VER) && _MSC_VER < 1700
	namespace tr1 {
#endif
		template<class T>
		T * get_pointer(shared_ptr<T> const& p) { return p.get(); }

#if defined(_MSC_VER) && _MSC_VER < 1700
	}
#endif
}
#endif
#endif