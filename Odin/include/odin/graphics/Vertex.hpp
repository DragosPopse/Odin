#ifndef ODIN_VERTEX_HPP
#define ODIN_VERTEX_HPP

#include <odin/Config.hpp>
#include <odin/graphics/Color.hpp>
#include <odin/math/Vec2.hpp>
#include <odin/math/Vec3.hpp>

namespace odin
{
	struct Vertex
	{
		Vec3f position;
		Vec2f texCoords;
		//Color color;
	};
}

#endif