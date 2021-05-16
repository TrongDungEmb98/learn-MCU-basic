#ifndef __DEBUG_H__
#define __DEBUG_H__

/* Includes */
#include <stdarg.h>
#include <stdint.h>

#define DEBUG_MODE 1

extern int app_debug_rtt(const char *fmt,...);
#define os_trace 			if(DEBUG_MODE) app_debug_rtt
#define DebugPrint			os_trace

void os_trace_hex(char* TAG, uint8_t* data, uint32_t len);

#endif /* __DEBUG_H__ */
