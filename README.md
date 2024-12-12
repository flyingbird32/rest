
# rest - a c++ rest api framework
this project was created as a personal learning experience to understand how rest apis work behind the scenes by building one from scratch in c++. it provides a lightweight, dependency-free framework for creating and managing restful apis in c++.

## example

```cpp
Endpoint testMethod(Request& request)
{
    request.response.setBody("hello");
    return Endpoint(HTTP_STATUS_CODE::OK, CONTENT_TYPE::TEXT_PLAIN);
}

int main()
{
    rest::Service testService;
    testService.registerEndpoint("/test", HTTP_METHOD::GET, testMethod);
    testService.start(3200);
    return 0;
}
```

![showcase](https://cdn.discordapp.com/attachments/1316828170573320305/1316828179087753298/image.png?ex=675c774f&is=675b25cf&hm=3bde87d167bccfa16582184c494416dfd882252a2116885a524241a7f3540763&)

![showcase2](https://cdn.discordapp.com/attachments/1316828170573320305/1316828327851593778/image.png?ex=675c7772&is=675b25f2&hm=1c4f4c535e4750881155914d3918420412e4a32eabf6959fa7b71ac6f54860a0&)

see more examples in the [tests](https://github.com/flyingbird32/rest/tree/main/tests) folder

## features

- only POST & GET supported; may add more in the future.
- static directory: serve static HTML and other assets.
- 404 handling: automatic fallback for unmatched routes.
- 38 supported content types: comprehensive MIME type handling.
- supports all HTTP/1.1 status codes.

## dependencies
none. the project is written entirely from scratch.

## installation
to use this project, follow these steps:

1. download the required files from the [releases](https://github.com/flyingbird32/rest/releases) page:
    - `rest.h`: header file containing the api definitions.
    - `rest.lib`: library file required for linking.

2. include the files in your project:
    - place `rest.h` in your project's include directory.
    - link `rest.lib` in your project's build system.

### linking instructions

#### for visual studio
- go to **project settings > linker > input > additional dependencies**.
- add the path to `rest.lib`.

#### for cmake
- add the following to your `CMakeLists.txt`:
    ```cmake
    target_include_directories(your_target PRIVATE rest.h)
    target_link_libraries(your_target PRIVATE rest.lib)
    ```
