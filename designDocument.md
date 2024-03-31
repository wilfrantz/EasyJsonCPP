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
  - `loadConfiguration`: Loads and parses the JSON configuration file, returning a map containing the parsed data.
  - `validateRootObject`: Validates the root element of the JSON configuration.
  - `parseArrayMemberData`: Parses an array of objects from the configuration file.
  - `parseObjectMemberData`: Parses key-value pairs within a JSON object.
  - `processMemberData`: Processes the value associated with a given key within an object.
  - `setLogLevel`: Sets the logging level based on the provided string.
  - `getFromConfigMap`: Retrieves a value from the provided configuration map based on the given key.
  - `showLibraryInfo`: Displays information about the library, project, version, description, and author.
  - `readInfoData`: Reads and parses information data from a JSON file.
  - `processConfigValue`: Processes the value associated with a given key within the configuration.
  - `parseObjectConfig`: Parses key-value pairs within the root JSON element.
  - `parseArrayConfig`: Processes each object within a JSON array.
  - `loadConfig`: Legacy method for loading and parsing the JSON configuration file (deprecated).

## Dependencies

- **JSONCPP**: For parsing and working with JSON data.
- **spdlog**: For logging and debugging.

## Error Handling

- The library uses `std::runtime_error` to handle and report errors during file reading, parsing, and validation.

## Logging

- Uses `spdlog` for logging various stages of configuration processing, aiding in debugging and error tracing.
- **setLogLevel**: Sets the logging level based on the provided string. Allows developers to control the verbosity of logging messages.

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

- Addition of support for more configuration file object formats.
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
