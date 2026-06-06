# Snake Game

A classic Snake game developed in C++ using the SFML graphics library.

## Features

* Multiple difficulty levels:

  * Easy
  * Medium
  * Hard
* Obstacle generation based on selected difficulty
* Score tracking
* High score saving
* Collision detection
* Game Over and Victory screens
* Keyboard controls

## Technologies

* C++
* SFML
* CMake
* Object-Oriented Programming (OOP)

## Project Structure

* `Game` – main game loop and state management
* `GameMode` – difficulty selection and obstacle configuration
* `SnakeBody` – snake movement, growth, and collision handling

## Controls

| Key    | Action            |
| ------ | ----------------- |
| W      | Move Up           |
| A      | Move Left         |
| S      | Move Down         |
| D      | Move Right        |
| Enter  | Confirm selection |
| Escape | Exit game         |

## Requirements

* C++17 or newer
* SFML 2.6+
* CMake 3.10+

## Build Instructions

### Linux

```bash
git clone https://github.com/MateuszMiskiewicz/Snake.git
cd Snake

mkdir build
cd build

cmake ..
make

./Snake
```

### Windows

```bash
git clone https://github.com/MateuszMiskiewicz/Snake.git
```

Open the project in CLion or Visual Studio with CMake support and build the project.

## Learning Objectives

This project was created to practice:

* Object-Oriented Programming
* Game development fundamentals
* Event handling
* Collision detection
* Working with external libraries (SFML)
* Project organization using CMake

## Screenshots

Add screenshots of the gameplay here.

## Author

Mateusz Miśkiewicz
