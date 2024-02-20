# EasyJsonCPP: Design Document

## Introduction

EasyJsonCPP is a C++ library designed to simplify the integration and handling of JSON configuration files in C++ projects. It provides intuitive functions for reading, writing, and managing JSON data, aiming to streamline the process of working with JSON in C++.

## Goals

- To provide an easy-to-use interface for handling JSON configuration files.
- To ensure robust error handling and clear logging for easier debugging.
- To offer a modular approach to JSON parsing, allowing flexibility in processing different JSON structures.

## Components

### Namespace

- **easyjson**: Encapsulates all the functionalities of the library to prevent naming conflicts.

### Classes

#### EasyJsonCPP

- **Purpose**: Serves as the main class for handling JSON configuration files.
- **Methods**:
  - `loadConfig`: Loads and parses the JSON configuration file.
  - `validateConfigRoot`: Validates the root element of the JSON configuration.
  - `parseConfig`: Parses the root JSON element, iterating through objects and arrays.
  - `parseArrayConfig`: Processes each object within a JSON array.
  - `parseObjectConfig`: Parses each key-value pair within a JSON object.
  - `processConfigValue`: Processes the value associated with a given key.

### Members

#### Private Members of EasyJsonCPP

- `_configFile`: Stores the path to the JSON configuration file.
- `_logger`: Shared pointer to spdlog's logger for logging purposes.

## Dependencies

- **JSONCPP**: For parsing and working with JSON data.
- **spdlog**: For logging and debugging.

## Error Handling

- The library uses `std::runtime_error` to handle and report errors during file reading, parsing, and validation.

## Logging

- Uses `spdlog` for logging various stages of configuration processing, aiding in debugging and error tracing.

## Installation and Setup

- Instructions for setting up dependencies like `JSONCPP` and `spdlog`.
- ~~Steps to include and use `easyJsonCPP` in C++ projects~~.
- Steps to compile and use `easyJsonCPP` in `C++` projects.

## Usage

- Examples demonstrating how to use the library to load and parse JSON configuration files.

## Testing

- Unit tests covering different scenarios and JSON structures.
- Integration tests to ensure compatibility with various C++ environments.

## Future Enhancements

- Addition of configuration file setters and getters.
- More detailed error messages for enhanced debugging.
- Enhanced exception safety in file and JSON operations.

## Conclusion

`easyJsonCPP` aims to be a user-friendly and efficient solution for managing JSON configurations in C++ applications, focusing on simplicity, reliability, and ease of integration.

## Contact

- EasyJsonCPP Developers: [contact@dede.dev](mailto:contact@dede.dev)

## Notes

- This document serves as a high-level overview of the easyJsonCPP library, covering its purpose, structure, components, dependencies, and usage.
- It's important to provide detailed instructions for installation, usage, and testing in the actual library documentation.
- Future enhancements and contact information are included, offering a roadmap for development and a point of contact for collaboration or issues.
