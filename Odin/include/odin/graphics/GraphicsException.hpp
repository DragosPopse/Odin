#ifndef ODIN_GRAPHICS_EXCEPTION_HPP
#define ODIN_GRAPHICS_EXCEPTION_HPP

#include <odin/Config.hpp>
#include <odin/core/Exception.hpp>

namespace odin
{
	class GraphicsException :
		public Exception
	{
	public:
		GraphicsException() = default;
		virtual ~GraphicsException() = default;
		
		GraphicsException(const std::string& message, int32_t code = 0) :
			Exception(message),
			m_code(code)
		{
		}

		int32_t code() const { return m_code; }

	private:
		int32_t m_code;
	};
}

#endif