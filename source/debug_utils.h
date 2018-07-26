#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#ifdef DEBUG
#define debug_log(...) puts("[LOG][DEBUG] "#__VA_ARGS__)
#else
#define debug_log(...)
#endif

#endif /* DEBUG_UTILS_H */
