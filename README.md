
# easyJsonCPP

`easyJsonCPP` is a streamlined C++ library designed for effortless integration and management of JSON configuration files. It abstracts the complexities of JSON parsing, allowing developers to efficiently handle configuration data within their C++ applications.

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

To use `easyJsonCPP` in your project, include the `easyJsonCPP.h` header file in your source code. Ensure that JSONCPP and spdlog are properly set up in your build environment.

## Usage

Here's a quick example to get you started:

```cpp
#include "easyJsonCPP.h"

int main() {
    easyjson::EasyJsonCPP configLoader("config.json");
    configLoader.loadConfig();
    // Your code to utilize the parsed configuration...
}
```

# Possible Improvements | `TODO`

- Configuration File Setter: The library could benefit from a method to set _configFile after constructing an EasyJsonCPP object. Currently, it seems that `_configFile` must be set through the constructor only.
- Error Messages: While the error messages are clear, they could be more descriptive in some cases. For example, specifying which key or value caused an error could be helpful for debugging.
- Exception Safety: Ensure that all methods are exception-safe. For instance, when working with file streams and JSON parsing, exceptions should be handled gracefully to avoid resource leaks or undefined states.
- Method Visibility and Reusability: Some methods like processConfigValue, parseArrayConfig, and parseObjectConfig could potentially be useful as public methods, depending on the intended use cases of the library.
- Dependency Management: There's an assumption that all required libraries (like JSONCPP and spdlog) are pre-installed and configured in the user's environment. Providing a setup script or instructions for installing these dependencies could enhance user experience.
- Unit Tests: Adding unit tests for each method would be beneficial for ensuring code quality, especially for a library dealing with file parsing and configuration management.

## Contributing to easyJsonCPP

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
