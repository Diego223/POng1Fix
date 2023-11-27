#pragma once
#include <glm/glm.hpp>
#include <iostream>
#define vprint(var) print(#var ":", var)

/*
// overload for glm::vec3
void print(const glm::vec3& v) {
    std::cout << "glm::vec3(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}

// overload for glm::vec4
void print(const glm::vec4& v) {
    std::cout << "glm::vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")" << std::endl;
}

// overload for glm::ivec2
void print(const glm::ivec2& v) {
    std::cout << "glm::vec2(" << v.x << ", " << v.y << ")" << std::endl;
}

// overload for glm::mat4
void print(const glm::mat4& m) {
    std::cout << "glm::mat4(\n";
    for(int i = 0; i < 4; ++i) {
        std::cout << "  ";
        for(int j = 0; j < 4; ++j) {
            std::cout << m[i][j];
            if (j != 3) {
                std::cout << ", ";
            }
        }
        std::cout << (i == 3 ? "\n" : ",\n");
    }
    std::cout << ")" << std::endl;
}
*/

// empty function to print newlines
void print() {
    std::cout << std::endl;
}

// base case function to end the recursion
void print(auto one, bool last = true) {
    std::cout << one;
    if (last) {
        std::cout << std::endl;
    }
}

// recursive variadic template function
void print(auto first, auto... args) {
    print(first, false);  // call the appropriate print function

    if constexpr (sizeof...(args) > 0) {
        std::cout << ' ';  // print a space only if there are more arguments
        print(args...);    // call print with remaining arguments
    } else {
        std::cout << std::endl;
    }
}