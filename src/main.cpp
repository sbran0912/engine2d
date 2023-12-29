#include <stdio.h>
#include <tuple>
#include <vector>
#include "rl2d_core.h"
#include "rl2d_phys.h"
#include <memory>



int main() {
	std::vector<std::unique_ptr<Figure2d>> list{};
	list.push_back(std::make_unique<Box>(200.0f, 300.0f, 100.0f, 50.0f));
	list.push_back(std::make_unique<Ball>(200.0f, 300.0f, 10.0f));

	for (auto &l:list)
	{
		l->test();
	}
	
	Box box{10.f, 20.f, 100.f, 50.f};
	Ball ball{150.f, 200.f, 30.f};

}