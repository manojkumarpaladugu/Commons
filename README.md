# Brief

The Commons module is a collection of shared functionality or utilities,
likely intended to be reused across different parts of the project.

## Features

* Logging:
  * Prints messages with a variety of logging levels.

## Configuration

### CMake Builds

  For projects that only use 'CMake' as a build system.

  1. Add this as a submodule in your project

      ```bash
      git submodule add git@github.com:manojkumarpaladugu/Commons.git Modules/Commons
      ```

  1. To enable logging library, please refer to the [Logging User Guide](Logging/README.md).

  1. Add the Commons module in compilation.

      ```cmake
      add_subdirectory(Commons)
      ```

### West Builds

  For projects that use 'west' as a build system.

  1. Add this module in west configuration

      ```yml
      remotes:
        - name: github
          url-base: ssh://git@github.com

      projects:
        - name: Commons
          remote: github
          repo-path: manojkumarpaladugu/Commons
          revision: main
          path: modules/lib/Commons
      ```

  1. To enable logging library, please refer to the [Logging User Guide](Logging/README.md).

Finally, link the module with the application being built.

```cmake
target_link_libraries(app
    PRIVATE
        Commons
)
```
