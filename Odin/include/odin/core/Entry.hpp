#ifndef ODIN_ENTRY_HPP
#define ODIN_ENTRY_HPP

#include <odin/Config.hpp>
#include <iostream>

namespace odin
{
	class App;
	App* CreateApp();
}

extern odin::App* odin::CreateApp();

int main(int argc, char** argv);

#endif