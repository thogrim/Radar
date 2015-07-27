#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Component.h>

namespace GUI{
	class Label: public Component{
	private:
		std::vector<std::unique_ptr<Component>> components_;
	public:

		Label();
		~Label();
	};
}