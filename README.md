
# 📡 rest - a c++ rest api framework
this project was created as a personal learning experience to understand how rest apis work behind the scenes by building one from scratch in c++. it provides a lightweight, dependency-free framework for creating and managing restful apis in c++.

## example

**regular endpoint**
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

**load class controller**
```cpp
class TestController : public BaseController
{
public:
    TestController() 
    {
        registerEndpoint("/hello", HTTP_METHOD::GET, &TestController::exampleEndpoint);
    }

private:
    static Endpoint exampleEndpoint(Request& request) // GET /class/hello
    {
        request.response.setBody("hi!");
        return  Endpoint(HTTP_STATUS_CODE::OK, CONTENT_TYPE::TEXT_PLAIN);
    }
}

int main()
{
    rest::Service testService;
    TestController testController;

    // or remove the '/class' parameter and just pass in the class to not have a global route
    service.registerController("/class", &testController); 
    testService.start(3200);
    return 0;
}

```

![showcase](https://cdn.discordapp.com/attachments/1316828170573320305/1319355614895542355/image.png?ex=6765a92b&is=676457ab&hm=2f80b514acbfd6f7c08bc6b5806b0ff0a8cf849278446770994819f4de7a7d86&)

![showcase2](https://cdn.discordapp.com/attachments/1316828170573320305/1319355750140870656/image.png?ex=6765a94b&is=676457cb&hm=8aa143afa529a080c66fcb9e0eb778f1d4aa9add2f912f3ab7f73375479a309d&)

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
