#pragma once

enum eGenerationSteps{
    walls,
    door,
    floors
};

namespace std {
    template <>
    struct hash<eGenerationSteps> {
        std::size_t operator()(const eGenerationSteps& step) const {
            return static_cast<std::size_t>(step);
        }
    };
}