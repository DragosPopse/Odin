#ifndef ODIN_VERTEX_HPP
#define ODIN_VERTEX_HPP

#include <odin/Config.hpp>
#include <odin/graphics/Color.hpp>
#include <gmath/vec.hpp>

namespace odin
{
	struct Vertex
	{
		gm::Vec3f position;
		gm::Vec2f texCoords;
		//Color color;
	};
}

#endif