# Brief

The Commons module is a collection of shared functionality or utilities,
likely intended to be reused across different parts of the project.

## Features

* Logging:
  * Prints messages with a variety of logging levels.

## Configuration

### Zephyr Environment

  For projects that use Zephyr RTOS.

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

  1. Add Commons module to the zephyr compilation

     Note: External modules must be added before
     `find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})`

      ```cmake
      list(APPEND ZEPHYR_EXTRA_MODULES "/path/to/Commons")
      ```

  1. To enable logging module, please refer to the [Logging User Guide](Logging/README.md).

  1. Commons module need all the global compiler options and flags necessary
     for building code with zephyr environment.

     So, link the zephyr_interface a source less module with Commons module.

      ```cmake
      target_link_libraries(Commons PUBLIC zephyr_interface)
      zephyr_link_libraries(Commons)
      ```

  1. Finally, link the module with the application being built

      ```cmake
      zephyr_link_libraries(Commons)
      target_link_libraries(app PRIVATE Commons)
      ```

### Other Environment

  For projects that only use 'CMake' as a build system.

  1. Add this as a submodule in your project

      ```bash
      git submodule add git@github.com:manojkumarpaladugu/Commons.git Modules/Commons
      ```

  1. To enable logging module, please refer to the [Logging User Guide](Logging/README.md).

  1. Add the Commons module in compilation.

      ```cmake
      add_subdirectory(Commons)
      ```

  1. Finally, link the module with the application being built

      ```cmake
      target_link_libraries(app PRIVATE Commons)
      ```
