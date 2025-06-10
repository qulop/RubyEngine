#pragma once 

#include "TypeTraits.hpp"


namespace Ruby::Details {
	struct SingletonInstanceInfo {
		std::string_view name;
        void* instance = nullptr;
		
	};
}


namespace Ruby {
	class ManagerManger {
		using TypeHash = decltype(std::declval<std::type_info>().hash_code());

	};
}