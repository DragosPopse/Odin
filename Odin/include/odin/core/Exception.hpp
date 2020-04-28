#ifndef ODIN_EXCEPTION_HPP
#define ODIN_EXCEPTION_HPP

#include <odin/Config.hpp>

namespace odin
{
	class Exception :
		public std::runtime_error
	{
	public:
		Exception() = default;
		virtual ~Exception() = default;

		Exception(const std::string& message) :
			std::runtime_error(message)
		{
		}
	};
}

#endif