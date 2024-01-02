#include <iostream>
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
		std::cout << l << " " << l->typ << " mit pos.x: " << l->location.pos.x << " und Radius: " << l->radius << "\n";
	}
	for (auto& l : list)
	{
		l->test();
		std::cout << l << " " << l->typ << " mit pos.x: " << l->location.pos.x << " und Radius: " << l->radius << "\n";
	}

	std::cout << " Zufall " << core::random(30, 80);
	std::cout << " Zufall " << core::random(10, 20);
	std::cout << " Zufall " << core::random(10, 20);
}