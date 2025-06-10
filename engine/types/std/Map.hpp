/*
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! DONT TOUCH THIS FILE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    Red-Black Map(Binary Three) implementation
*/

#pragma once

#include "StdInc.hpp"
#include "STL.hpp"



namespace Ruby::Std {
    namespace Details::Map {
        
    }


    struct MapConstIterator {

    };


    struct MapIterator {

    };


    struct MapReverseIterator {

    };




    template<typename Key, typename Value, typename Alloc>
    class Map : public STL::IBasicContainer<MapIterator, MapConstIterator, Alloc>, STL::IContainsPair<Key, Value> 
    {
    public:
        using KeyType = key_type;
        using ValueType = value_type;
        using AllocatorType = allocator_type;

    public:
        
        


    };
} 
