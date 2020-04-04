#ifndef REVERSE_CONTAINER_HPP
#define REVERSE_CONTAINER_HPP

namespace odin
{
	/*
		Utility class that converts a container into a reverse container to be used in a range-based for loop
		Basically, it swaps begin/end with rbegin/rend
	*/

	template <class Iterable>
	class ReverseContainer
	{
	public:
		explicit ReverseContainer(Iterable& iterable) :
			m_iterable(iterable)
		{
		}

		auto begin() { return m_iterable.rbegin(); }
		auto end() { return m_iterable.rend(); }

	private:
		Iterable& m_iterable;
	};
}

#endif