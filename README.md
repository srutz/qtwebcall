# qtwebcall


# Developing and running a Qt application with VSCode

## Prerequisites

- Qt installed
- Cmake installed
- CMakeLists.txt file
- CMakePresets.json file
- .vscode/c_cpp_properties.json file
- .vscode/launch.json file
- .vscode/settings.json file
. .vscode/tasks.json file



## Cmake

- Setup

```bash
cmake --preset Desktop-Debug -B build/Desktop-Debug -S .
```

- Building

```bash
cmake --build build/Desktop-Debug --target clean
cmake --build build/Desktop-Debug --target all
```

