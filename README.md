# \<HTMCXX\/> - A HTML library for C++23

## Description

**HTMCXX** is a lightweight header-only library for building HTML with C++ syntax. Each HTML tag and attribute has its own class with a name that matches those tags and attributes ([except for a few exceptions](#name-exceptions-and-special-tags)).

## Getting started
### Requirements
- C++ supported compiler:

    | Compiler                                      | Minimun Version      |
    |:---------------------------------------------:|:--------------------:|
    | [gcc](https://gcc.gnu.org/releases.html)      | 14                   |  
    | [clang](https://releases.llvm.org/)           | 18                   |

- [CMake](https://cmake.org/download/) >= 3.28.
- [vcpkg](https://github.com/microsoft/vcpkg?tab=readme-ov-file) to manage dependencies. Note: *VCPKG_ROOT* environment variable must be set as the root of the vcpkg instance [to run vcpkg with CMake Presets](https://learn.microsoft.com/en-us/vcpkg/users/buildsystems/cmake-integration#cmake_toolchain_file).

### Building

Once you have obtained the necessary tools, you will need to download the project:
```
$ git clone https://github.com/ChrisMarLie/HTMCXX.git
$ cd HTMCXX
```
And build it with following command:
```
$ cmake --workflow --preset default
```

## Usage

Building HTML is very easy. To create a tag, you simply need to create an object of the type you need, and when doing so, you can pass as many HTML attributes as you want, also as objects. To add nested tags within the tag, you simply call your HTML tag as if it were a function, and its parameters are those nested tags. Example:
```
namespace attr = htmcxx::attributes;
namespace tag = htmcxx::tags;

//Create new section tag with id attribute, and a paragraph inside
auto tag =  tag::section{attr::id("hello-world-container")}
            (
                tag::p{attr::style("color: red;")}
                (
                    "Hello World!"
                )
            );
            
```
Finally, HTML tags can be easily cast to a string:
```
//Print elements with its attributes and nested tags
std::cout << (std::string)tag << std::endl;
```

Check more usages in [examples](/examples) and documentation in [HTMCXX](https://chrismarlie.github.io/HTMCXX/)

## Name exceptions and special tags

As some HTML names coincide with reserved words of C++, some names change in relation to their homonyms:

 - **TAGS**

    | ORIGINAL      | RENAMED              |
    |:-------------:|:--------------------:|
    | template      | template_name        |

 - **ATTRIBUTES**

    | ORIGINAL      | RENAMED              |
    |:-------------:|:--------------------:|
    | for           | for_name             |
    | default       | default_name         |
    | class         | class_name           |
    
Also, there are some special HTML tags for **special functionality**:

| NAME          | DESCRIPTION          |
|:-------------:|----------------------|
| box           | Used to wrap HTML elements that are not associated with a specific tag, formatting their children into a column             |
| text       | Used to indicate plain text         |


