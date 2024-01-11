#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace Ruby
{
    using RubyString                        = std::string;

    template<typename Tx, typename Ty>
    using RubyHashMap                       = std::unordered_map<Tx, Ty>;

    template<typename Tx>
    using RubyVector                        = std::vector<Tx>;

}
