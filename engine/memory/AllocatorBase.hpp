#pragma once

#include <memory/AllocatorTraits.hpp>
#include <memory/Memory.hpp>

#include <types/Errors.hpp>


namespace Kiwi::Memory {
    template<typename T>
    class AllocatorBase : public AAllocatorTraits {
    public:
        AllocatorBase() = default;

        AllocatorBase(const AllocatorBase& other) = delete;
        AllocatorBase(AllocatorBase&& other) = default;

        KIWI_NODISCARD AllocatorBase& operator=(const AllocatorBase& other) = delete;
        KIWI_NODISCARD AllocatorBase& operator=(AllocatorBase&& other) = default;

    public:
        virtual Status<Error<EGeneralError>> Init() { return {}; }

        KIWI_NODISCARD Result<AllocatedBlock, EGeneralError> Allocate(size_t n) override {
            if (void* res = Malloc(n); res) {
                // I have no idea why fucking clang refuse to compile this with just `return AllocatedBlock{ n, res };`
                // So we have to use this ugly return statement
                return Result<AllocatedBlock, EGeneralError>(std::in_place, n, res);
            }

            return Unexpected(Error {
                .kind = EGeneralError::OUT_OF_MEMORY,
                .desc = "Failed to allocate memory"
            });
        }

        void Deallocate(AllocatedBlock block) override {
            Free(block.ptr);
        }


        ~AllocatorBase() override = default;
    };

}
