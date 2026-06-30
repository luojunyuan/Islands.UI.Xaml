#pragma once

#define TRACE_MSG_METH L"%s[0x%p]()\n"
#define TRACE_MSG_METH_DBL L"%s[0x%p](%lf)\n"
#define TRACE_MSG_METH_DBL_DBL L"%s[0x%p](%lf, %lf)\n"
#define TRACE_MSG_METH_DBL_INT L"%s[0x%p](%lf, %d)\n"
#define TRACE_MSG_METH_DBL_DBL_INT L"%s[0x%p](%lf, %lf, %d)\n"
#define TRACE_MSG_METH_DBL_DBL_FLT L"%s[0x%p](%lf, %lf, %f)\n"
#define TRACE_MSG_METH_DBL_DBL_STR L"%s[0x%p](%lf, %lf, %s)\n"
#define TRACE_MSG_METH_FLT L"%s[0x%p](%f)\n"
#define TRACE_MSG_METH_FLT_FLT L"%s[0x%p](%f, %f)\n"
#define TRACE_MSG_METH_FLT_FLT_FLT L"%s[0x%p](%f, %f, %f)\n"
#define TRACE_MSG_METH_FLT_FLT_FLT_FLT L"%s[0x%p](%f, %f, %f, %f)\n"
#define TRACE_MSG_METH_FLT_FLT_STR_INT L"%s[0x%p](%f, %f, %s, %d)\n"
#define TRACE_MSG_METH_INT L"%s[0x%p](%d)\n"
#define TRACE_MSG_METH_INT_INT L"%s[0x%p](%d, %d)\n"
#define TRACE_MSG_METH_PTR L"%s[0x%p](0x%p)\n"
#define TRACE_MSG_METH_PTR_PTR L"%s[0x%p](0x%p, 0x%p)\n"
#define TRACE_MSG_METH_PTR_DBL L"%s[0x%p](0x%p, %lf)\n"
#define TRACE_MSG_METH_PTR_INT L"%s[0x%p](0x%p, %d)\n"
#define TRACE_MSG_METH_PTR_STR L"%s[0x%p](0x%p, %s)\n"
#define TRACE_MSG_METH_STR L"%s[0x%p](%s)\n"
#define TRACE_MSG_METH_IND_STR L"%s[0x%p](%*s)\n"
#define TRACE_MSG_METH_IND_STR_STR L"%s[0x%p](%*s, %s)\n"
#define TRACE_MSG_METH_IND_STR_STR_INT L"%s[0x%p](%*s, %s, %d)\n"
#define TRACE_MSG_METH_IND_STR_STR_INT_INT L"%s[0x%p](%*s, %s, %d, %d)\n"
#define TRACE_MSG_METH_IND_STR_STR_FLT L"%s[0x%p](%*s, %s, %f)\n"
#define TRACE_MSG_METH_IND_STR_STR_FLT_FLT L"%s[0x%p](%*s, %s, %f, %f)\n"
#define TRACE_MSG_METH_IND_STR_STR_FLT_FLT_FLT_FLT L"%s[0x%p](%*s, %s, %f, %f, %f, %f)\n"
#define TRACE_MSG_METH_IND_STR_STR_INT_FLT_FLT_FLT_FLT L"%s[0x%p](%*s, %s, %d, %f, %f, %f, %f)\n"
#define TRACE_MSG_METH_STR_STR L"%s[0x%p](%s, %s)\n"
#define TRACE_MSG_METH_STR_DBL L"%s[0x%p](%s, %lf)\n"
#define TRACE_MSG_METH_STR_DBL_DBL L"%s[0x%p](%s, %lf, %lf)\n"
#define TRACE_MSG_METH_STR_FLT L"%s[0x%p](%s, %f)\n"
#define TRACE_MSG_METH_STR_INT L"%s[0x%p](%s, %d)\n"
#define TRACE_MSG_METH_STR_STR_PTR L"%s[0x%p](%s, %s, 0x%p)\n"
#define TRACE_MSG_METH_STR_STR_DBL L"%s[0x%p](%s, %s, %lf)\n"
#define TRACE_MSG_METH_STR_STR_INT L"%s[0x%p](%s, %s, %d)\n"
#define TRACE_MSG_METH_STR_STR_STR L"%s[0x%p](%s, %s, %s)\n"
#define TRACE_MSG_METH_STR_INT_INT L"%s[0x%p](%s, %d, %d)\n"
#define TRACE_MSG_METH_STR_FLT_FLT L"%s[0x%p](%s, %f, %f)\n"
#define TRACE_MSG_METH_STR_STR_FLT_FLT L"%s[0x%p](%s, %s, %f, %f)\n"
#define TRACE_MSG_METH_STR_STR_FLT_FLT_FLT_FLT L"%s[0x%p](%s, %s, %f, %f, %f, %f)\n"
#define TRACE_MSG_METH_STR_STR_FLT L"%s[0x%p](%s, %s, %f)\n"
#define TRACE_MSG_METH_STR_STR_INT_INT L"%s[0x%p](%s, %s, %d, %d)\n"
#define TRACE_MSG_METH_STR_STR_DBL_DBL L"%s[0x%p](%s, %s, %lf, %lf)\n"
#define TRACE_MSG_METH_METH L"%s[0x%p] - calls %s()\n"
#define TRACE_MSG_METH_METH_INT L"%s[0x%p] - calls %s(%d)\n"
#define TRACE_MSG_METH_METH_STR L"%s[0x%p] - calls %s(%s)\n"
#define TRACE_MSG_METH_METH_STR_STR L"%s[0x%p] - calls %s(%s, %s)\n"
#define TRACE_MSG_METH_METH_FLT_STR L"%s[0x%p] - calls %s(%f, %s)\n"
#define TRACE_MSG_METH_METH_FLT_FLT_FLT L"%s[0x%p] - calls %s(%f, %f, %f)\n"

#define METH_NAME L""

#define SCROLLPRESENTER_TRACE_INFO(...) ((void)0)
#define SCROLLPRESENTER_TRACE_INFO_ENABLED(...) ((void)0)
#define SCROLLPRESENTER_TRACE_INFO_DBG(...) ((void)0)
#define SCROLLPRESENTER_TRACE_VERBOSE(...) ((void)0)
#define SCROLLPRESENTER_TRACE_VERBOSE_ENABLED(...) ((void)0)
#define SCROLLPRESENTER_TRACE_VERBOSE_DBG(...) ((void)0)
#define SCROLLPRESENTER_TRACE_PERF(...) ((void)0)
#define SCROLLPRESENTER_TRACE_PERF_DBG(...) ((void)0)

#define SCROLLVIEW_TRACE_INFO(...) ((void)0)
#define SCROLLVIEW_TRACE_INFO_ENABLED(...) ((void)0)
#define SCROLLVIEW_TRACE_INFO_DBG(...) ((void)0)
#define SCROLLVIEW_TRACE_VERBOSE(...) ((void)0)
#define SCROLLVIEW_TRACE_VERBOSE_ENABLED(...) ((void)0)
#define SCROLLVIEW_TRACE_VERBOSE_DBG(...) ((void)0)
#define SCROLLVIEW_TRACE_PERF(...) ((void)0)
#define SCROLLVIEW_TRACE_PERF_DBG(...) ((void)0)

#define TraceLoggingProviderWrite(...) ((void)0)

#define __RP_Marker_ClassById(typeindex) \
    do \
    { \
        static volatile LONG __RuntimeProfiler_Counter = -1; \
        if (0 == interlockedIncrement(&__RuntimeProfiler_Counter)) \
        { \
            RuntimeProfiler::RegisterMethod(RuntimeProfiler::PG_Class, static_cast<UINT16>(typeindex), 9999, &__RuntimeProfiler_Counter); \
        } \
    } while (false)
