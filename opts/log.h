#pragma once

#include <stdio.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

typedef struct log_options_s {
  bool debug;
  bool verbose;
} log_options_t;

extern log_options_t log_options;

// assumes that name is first item
#define dev_name(dev) (dev ? *(const char**)dev : "?")
#define E_LOG_ERROR(dev, _msg, ...)		do { fprintf(stderr, "%s: %s: " _msg "\n", __FILENAME__, dev_name(dev), ##__VA_ARGS__); goto error; } while(0)
#define E_LOG_PERROR(dev, _msg, ...)		do { fprintf(stderr, "%s: %s: " _msg "\n", __FILENAME__, dev_name(dev), ##__VA_ARGS__); exit(-1); } while(0)
#define E_LOG_INFO(dev, _msg, ...)		do { fprintf(stderr, "%s: %s: " _msg "\n", __FILENAME__, dev_name(dev), ##__VA_ARGS__); } while(0)
#define E_LOG_VERBOSE(dev, _msg, ...)	do { if (log_options.debug || log_options.verbose) { fprintf(stderr, "%s: %s: " _msg "\n", __FILENAME__, dev_name(dev), ##__VA_ARGS__); } } while(0)
#define E_LOG_DEBUG(dev, _msg, ...)		do { if (log_options.debug) { fprintf(stderr, "%s: %s: " _msg "\n", __FILENAME__, dev_name(dev), ##__VA_ARGS__); } } while(0)