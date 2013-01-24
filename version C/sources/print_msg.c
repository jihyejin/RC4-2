#include "stdafx.h"
#include <stdarg.h>
#include "print_msg.h"

void print_msg(unsigned int uiMsgLevel, const char * fmt, ...)
{
	va_list ap;

	switch(uiMsgLevel)
	{
		case LOG_LEVEL_ERROR: printf("[ERROR] : "); break;
		case LOG_LEVEL_WARNG: printf("[WARNG] : "); break;
		case LOG_LEVEL_TRACE: printf("[TRACE] : "); break;
		case LOG_LEVEL_DEBUG: printf("[DEBUG] : "); break;
	}

	va_start(ap, fmt);
	vprintf(fmt, ap);
	printf("\n");
	va_end(ap);
}

