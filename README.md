
# easyJsonCPP

`easyJsonCPP` is a streamlined `C++` library designed for effortless integration and management of `JSON` configuration files. It abstracts the complexities of JSON parsing, allowing developers to efficiently handle configuration data within their `C++` applications.

Table of Contents

- [easyJsonCPP](#easyjsoncpp)
  - [Features](#features)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Progress | `TODO`](#progress--todo)
  - [Contributing to `easyJsonCPP`](#contributing-to-easyjsoncpp)
  - [License](#license)
  - [Contact](#contact)
    - [Notes](#notes)

## Features

- Simplified parsing of JSON configuration files
- Robust error handling with detailed exceptions
- Modular and readable code structure
- Cross-platform compatibility
- Integrated logging capabilities using `spdlog`

## Prerequisites

Before you begin, ensure you have met the following requirements:

- C++ compiler with C++11 support
- [JSONCPP](https://github.com/open-source-parsers/jsoncpp) library installed
- [spdlog](https://github.com/gabime/spdlog) library installed

## Installation

To use the `EasyJsonCPP` library in your `C++` project, follow these steps:

1- Include EasyJsonCPP in Your Project: Add EasyJsonCPP as a dependency in your CMakeLists.txt file:
cmake

```bash
find_package(easyjson REQUIRED)
```

2- Link EasyJsonCPP: Link EasyJsonCPP library to your target:

```bash
target_link_libraries(your_target easyjson)
```

3- Use EasyJsonCPP APIs: Include the necessary headers in your source files and start using EasyJsonCPP APIs to handle JSON configuration files. For example:

```c
#include <easyjson.h>

int main() 
{
    EasyJsonCPP easyjson("config.json");
    auto configMap = easyjson.loadConfiguration();

    // Access and process configuration data
    auto value = easyjson.getFromConfigMap("key", configMap);
    // Do something with the value...

    return 0;
}
```

4- uild Your Project: After integrating EasyJsonCPP into your project, build it using CMake:

```c
mkdir build && cd build
cmake ..
cmake --build .
```

5- un Your Application: Once built successfully, run your application to see EasyJsonCPP in action:

```bash
./your_application
```

## Progress | `TODO`

- [x] Create [design document](https://dede.dev/posts/Building-Compiled-Libraries/){: target="_blank"}.
- [x] Build the Structure.
  - [x] Implement core functionality.
  - [x] Load configuration data into each interface.
- [x] Create Build Management `cmakefile.txt`.
- [ ] Build Unit Test.

## Contributing to `easyJsonCPP`

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are greatly appreciated.

1. Fork the Project.
2. Create your Feature Branch (git checkout -b feature/AmazingFeature)
3. Commit your Changes (git commit -m 'Add some AmazingFeature')
4. Push to the Branch (git push origin feature/AmazingFeature)
5. Open a Pull Request.

## License

Distributed under the GNU General Public License v3.0. See LICENSE for more information.

## Contact

EasyJsonCPP Developers - `contact@dede.dev`

Project Link:

### Notes

- The README includes a brief introduction to the library, its features, prerequisites for use, installation instructions, a basic usage example, contribution guidelines, licensing information, and contact details.
- Make sure to replace the links and contact information with the actual ones related to your project.
- The code block within the markdown has been closed properly; make sure that your markdown renderer supports nested code blocks.
