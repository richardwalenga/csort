# C Sort

This code was a way for me to practice writing C code by implementing common sorting algorithms using [what I created with Typescript](https://github.com/richardwalenga/typescriptsort) as a guide. I have logging in [main.c](main.c) which times the implementations against the same large array of random ints.

## First Steps

This project now requires version 3.10 or greater of the cross-platform build tool CMake. This command, if it returns something, will tell one which versionss .10)It is already installed if this returns something:
```
cmake --version
```

A normal build involves running:
```
mkdir build
cd build
cmake ..
cmake --build .
```

For Visual Studio Code users, there are tasks to build and clean which can only be effective if the [CMake Tools extension is installed](https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/build.md). [Visual Studio users should follow these directions for building](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170).

## Running

To run it, just execute this:
```
cd build && ./csort
```

For convenience I added a VSCode task called "run" which effectively does the same thing.