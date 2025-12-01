#pragma once 

#include "TypeTraits.hpp"


namespace Kiwi::Details {
	struct SingletonInstanceInfo {
		std::string_view name;
        void* instance = nullptr;
		
	};
}


namespace Kiwi {
	class ManagerManger {
		using TypeHash = decltype(std::declval<std::type_info>().hash_code());

	};
}