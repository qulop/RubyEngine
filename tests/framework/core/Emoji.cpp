#include "Emoji.hpp"
#include <random>


namespace Ruby::Testify {
    size_t getRandomIndex(size_t max) {
        static std::mt19937 twister{ std::random_device{}() };

        return twister() % max;
    }

    String selectRandom(const Vector<String>& variants) {
        size_t index = getRandomIndex(variants.size());

        return variants.at(index);
    }


    String getSuccessEmoji() {
        static const Vector<String> variants = {
                "(≧◡≦)",
                "(ﾉ◕ヮ◕)ﾉ*:･ﾟ✧",
                "(＾▽＾)",
                "(ﾉ^_^)ﾉ"
        };

        return selectRandom(variants);
    }

    String getFailureEmoji() {
        static const Vector<String> variants = {
                "(╯︵╰,)",
                "(ಥ﹏ಥ)",
                "(ノಠ益ಠ)ノ",
                "(╬ಠ益ಠ)"
        };

        return selectRandom(variants);
    }
}