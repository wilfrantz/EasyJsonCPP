
# easyJsonCPP

`easyJsonCPP` is a streamlined `C++` library designed for effortless integration and management of `JSON` configuration files. It abstracts the complexities of JSON parsing, allowing developers to efficiently handle configuration data within their `C++` applications.

Table of Contents

- [easyJsonCPP](#easyjsoncpp)
  - [Features](#features)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Progress | `TODO`](#progress--todo)
  - [Contribution](#contribution)
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

1- Include EasyJsonCPP in Your Project: Add EasyJsonCPP as a dependency in your CMakeLists.txt file: (Refer to the tester `CMakeLists.txt` file)

```cmake
find_package(easyjson REQUIRED)
```

2- Link EasyJsonCPP: Link EasyJsonCPP library to your target:

```cmake
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

3.1 - Json configuration sample

```json
[
  {
    "info": {
      "mode": "debug",
      "project": "MyProject",
      "version": "(v2.0.0)",
      "note": "Sample data for testing.",
      "filename": "config.json",
      "author": "John Doe",
      "description": "Sample Configuration File.",
      "targets": "telegram, instagram, twitter, tiktok"
    }
  },
  {
    "server": {
      "port": "8080",
      "domain": "example.com",
      "address": "192.168.1.1"
    }
  },
  {
    "telegram": {
      "endpoint": "https://api.telegram.org/bot",
      "webHookUrl": "https://example.com:8080",
      "token": "1234567890:ABCDEFGHIJKLMN"
    }
  },
  {
    "twitter": {
      "action": "POST",
      "output_path": "/output/twitter/",
      "api_key": "TwitterAPIKey123",
      "media_endpoint": "https://api.twitter.com/2/media/",
      "api_url": "https://api.twitter.com/1.1/statuses/show.json?id=",
      "api_secret": "TwitterAPISecret456",
      "access_token": "TwitterAccessToken789",
      "access_token_secret": "TwitterAccessTokenSecretXYZ",
      "media_url": "https://twitter.com/example/status/123456789",
      "bearer_token": "TwitterBearerTokenABC"
    }
  },
  {
    "instagram": {
      "Action": "GET",
      "OutputPath": "/output/instagram/",
      "ApiUrl": "https://www.instagram.com/p/",
      "MediaUrl": "https://www.instagram.com/reel/1234567890/",
      "Media2": "https://www.instagram.com/p/ABC123XYZ/",
      "MediaEndpoint": "https://www.instagram.com/p/1234567890/?__a=1",
      "Token": "InstagramToken123",
      "AppSecret": "InstagramAppSecret456"
    }
  },
  {
    "tiktok": {
      "Action": "POST",
      "app_id": "TikTokAppID123",
      "metaEndpoint": "https://www.tiktok.com/api/item/detail/?itemId=",
      "MediaUrl": "https://www.tiktok.com/@example/video/1234567890/",
      "client_secret": "TikTokClientSecret456",
      "client_key": "TikTokClientKeyXYZ"
    }
  }
]
```

3.1.1 - Library metadata

```json
{
  "info": {
    "mode": "info",
    "project": "EasyJson",
    "version": "(v0.0.1)",
    "description": "Simplify configuration data integration",
    "filename": "metadata.json",
    "author": "(C) 2023 Wilfrantz Dede"
  }
}
```

3.2 - Output sample

```bash
./build/easyjson_tester                                                                                                                                                                                                  ─╯
[2024-03-30 21:13:38.760] [EasyJson] [info] EasyJson (v0.0.1)
[2024-03-30 21:13:38.760] [EasyJson] [info] Simplify configuration data integration
[2024-03-30 21:13:38.760] [EasyJson] [info] Author: (C) 2023 Wilfrantz Dede
[2024-03-30 21:13:38.760] [EasyJson] [info] Log level set to: info

[2024-03-30 21:13:38.760] [EasyJson] [info] Log level set to: debug

[2024-03-30 21:13:38.760] [Tester] [debug] access_token : TwitterAccessToken789
[2024-03-30 21:13:38.760] [Tester] [debug] access_token_secret : TwitterAccessTokenSecretXYZ
[2024-03-30 21:13:38.760] [Tester] [debug] action : POST
[2024-03-30 21:13:38.760] [Tester] [debug] api_key : TwitterAPIKey123
[2024-03-30 21:13:38.760] [Tester] [debug] api_secret : TwitterAPISecret456
[2024-03-30 21:13:38.760] [Tester] [debug] api_url : https://api.twitter.com/1.1/statuses/show.json?id=
[2024-03-30 21:13:38.760] [Tester] [debug] bearer_token : TwitterBearerTokenABC
[2024-03-30 21:13:38.760] [Tester] [debug] media_endpoint : https://api.twitter.com/2/media/
[2024-03-30 21:13:38.760] [Tester] [debug] media_url : https://twitter.com/example/status/123456789
[2024-03-30 21:13:38.760] [Tester] [debug] output_path : /output/twitter/
[2024-03-30 21:13:38.760] [Tester] [debug] Action : POST
[2024-03-30 21:13:38.760] [Tester] [debug] MediaUrl : https://www.tiktok.com/@example/video/1234567890/
[2024-03-30 21:13:38.760] [Tester] [debug] app_id : TikTokAppID123
[2024-03-30 21:13:38.760] [Tester] [debug] client_key : TikTokClientKeyXYZ
[2024-03-30 21:13:38.760] [Tester] [debug] client_secret : TikTokClientSecret456
[2024-03-30 21:13:38.760] [Tester] [debug] metaEndpoint : https://www.tiktok.com/api/item/detail/?itemId=
[2024-03-30 21:13:38.760] [Tester] [debug] Action : GET
[2024-03-30 21:13:38.760] [Tester] [debug] ApiUrl : https://www.instagram.com/p/
[2024-03-30 21:13:38.760] [Tester] [debug] AppSecret : InstagramAppSecret456
[2024-03-30 21:13:38.760] [Tester] [debug] Media2 : https://www.instagram.com/p/ABC123XYZ/
[2024-03-30 21:13:38.760] [Tester] [debug] MediaEndpoint : https://www.instagram.com/p/1234567890/?__a=1
[2024-03-30 21:13:38.760] [Tester] [debug] MediaUrl : https://www.instagram.com/reel/1234567890/
[2024-03-30 21:13:38.760] [Tester] [debug] OutputPath : /output/instagram/
[2024-03-30 21:13:38.760] [Tester] [debug] Token : InstagramToken123
[2024-03-30 21:13:38.761] [Tester] [debug] endpoint : https://api.telegram.org/bot
[2024-03-30 21:13:38.761] [Tester] [debug] token : 1234567890:ABCDEFGHIJKLMN
[2024-03-30 21:13:38.761] [Tester] [debug] webHookUrl : https://example.com:8080
```

4- Build Your Project: After integrating EasyJsonCPP into your project, build it using CMake:

```bash
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

## Contribution

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
