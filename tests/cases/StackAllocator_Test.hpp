#include <framework/RubyTestsFramework.hpp>
#include <memory/StackAllocator.hpp>

RUBY_TESTS_SUITE {
    RUBY_DEFINE_TEST("StacAllocator - Large size allocation", StackAllocatorLargeAlloc) {
        constexpr size_t max = Ruby::Memory::Details::STACK_ALLOC_MAX;

        Memory::StackAllocator<max> alloc;

        auto mem = alloc.Allocate(max);
        alloc.Deallocate(mem);
    }


    RUBY_DEFINE_TEST("StackAllocatorTest", StackAllocator) {
        Memory::StackAllocator first;
        Memory::StackAllocator<Memory::Details::STACK_ALLOC_MAX> second;

        RUBY_TESTS_ASSERT_EQ(1024, first.Allocate(1024).size);

        auto firstAllocMem = first.Allocate(first.GetSize() - 1);
        auto secondAllocMem = second.Allocate(second.GetSize() - 1);

        RUBY_TESTS_ASSERT_TRUE(first.IsOwns(firstAllocMem));

        first.Deallocate(secondAllocMem);  // Try to deallocate foreign memory
        second.Deallocate(secondAllocMem); // Try to deallocate allocator's own memory
    }
};


