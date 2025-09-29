# Simple Breakout Game

A modern C++ implementation of the classic Breakout game, featuring clean architecture, resource management, and smooth gameplay using [SFML](https://www.sfml-dev.org/). The project is built with CMake for easy cross-platform compilation.


<img width="531" height="483" alt="image" src="https://github.com/user-attachments/assets/7f8b8c7b-790f-4439-9f94-6aec4f9d326a" />


## Features

- **Modern C++**: Utilizes C++17/20 features such as smart pointers, `std::optional`, and structured bindings.
- **Entity-Component System**: Clean separation of game logic for maintainability and scalability.
- **Resource Management**: Efficient loading and management of textures and fonts.
- **Responsive Controls**: Smooth paddle movement and collision detection.
- **Cross-Platform**: Runs on Linux, Windows, and macOS.

## Modern C++ Features Used

- `std::optional` for safe, lazy initialization of resources (textures, fonts, etc.).
- `emplace()` for in-place construction of objects.
- Range-based for loops for cleaner iteration.
- Uniform initialization (`{}`) for vectors and objects.
- Smart pointers and RAII for resource safety.
- String literals and type inference (`auto`).

## Getting Started

### Prerequisites

- C++17 or newer compiler (e.g., GCC, Clang, MSVC)
- [CMake](https://cmake.org/) 3.10+
- [SFML](https://www.sfml-dev.org/) 3.0+

### Building

```bash
git clone https://github.com/dssregi/simple-breakout-game.git
cd simple-breakout-game
mkdir build && cd build
cmake ..
make
./src/app/breakout
```

### Resources

Place your font and texture files in the `res/` directory. Example resources:
- `res/FreeSans.otf` (font)
- `res/paddle.png` (paddle texture)

## Credits

- **Code Inspiration**: Final course project from James Raynard [Modern C++: From Intermediate to Advanced](https://github.com/JamesRaynard/Learn-Modern-Advanced-Cpp) by Udemy (https://www.udemy.com/course/learn-intermediate-modern-c/).
- **SFML**: [SFML - Simple and Fast Multimedia Library](https://www.sfml-dev.org/)
- **CPPReference**: [CPPReferece - C++ Reference](https://www.cppreference.com/)
- **Font**: [FreeSans](https://www.gnu.org/software/freefont/) (GNU FreeFont, SIL Open Font License)
- **Textures**: Created by project contributors or sourced from open/free repositories (see `res/` for attributions).


## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

---
