# Brief
The Commons module is a collection of shared functionality or utilities, likely intended to be reused across different parts of the project.

# Features
* Logging:
  * Prints messages with a variety of logging levels.

# Steps to integrate Commons module in a Zephyr based project
1. Add commons and pigweed repo's in west configuration
```
  remotes:
    - name: github
      url-base: ssh://git@github.com

  projects:
    - name: Commons
      remote: github
      repo-path: manojkumarpaladugu/Commons
      revision: main
      path: Modules/Commons
    - name: pigweed
      remote: github
      repo-path: google/pigweed
      revision: 90d1391ff0c2fcb4717dc578bceccb2ec38643b8 # Latest as of Apr 5, 2025
      path: ThirdParty/pigweed
```
2. Enable logging module in application's prj.conf file
```
# Enable zephyr logging
CONFIG_LOG=y
CONFIG_LOG_PRINTK=n

# Enable custom logging library
CONFIG_LIB_COMMONS_LOGGING=y
CONFIG_LIB_COMMONS_TOKENIZED_LOGGING=y
```

3. Use logging macros to print messages
```
// Define logging module name and logging level in source file
#define LOG_MODULE_NAME "main"
#define MODULE_LOG_LEVEL LOG_LEVEL_DEBUG

// Must be included after the logging module name and logging level definitions
#include "Logging.h"

int main(void)
{
    LOG_INFO("Hello world!");
    return 0;
}
```

4. Link commons library in application's CMakeLists.txt
```
target_link_libraries(app
    PRIVATE Commons
)
```
