#include "common.h"

#ifdef HAVE_STDIO_H
# include <stdio.h>
#endif
#ifdef HAVE_STDLIB_H
# include <stdlib.h>
#endif
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <wrapper.h>

#include "es_bsc_cepbatools_extrae_JavaProbes.h"
#include "extrae_user_events.h"
#include "trace_macros.h"
//#include "java_probe.h"

JNIEXPORT void JNICALL Java_es_bsc_cepbatools_extrae_JavaProbes_ThreadStartBegin(
    JNIEnv *env, jclass jc)
{
    UNREFERENCED(env);
    UNREFERENCED(jc);

    Backend_Enter_Instrumentation ();

    TRACE_MISCEVENTANDCOUNTERS(LAST_READ_TIME, JAVA_ASPECTS_THREAD_START_EV, EVT_BEGIN, EMPTY);
    //Extrae_AnnotateCPU (LAST_READ_TIME);
}


JNIEXPORT void JNICALL Java_es_bsc_cepbatools_extrae_JavaProbes_ThreadStartEnd(
    JNIEnv *env, jclass jc)
{
    UNREFERENCED(env);
    UNREFERENCED(jc);

    TRACE_MISCEVENTANDCOUNTERS(TIME, JAVA_ASPECTS_THREAD_START_EV, EVT_END, EMPTY)

    Backend_Leave_Instrumentation ();
}


JNIEXPORT void JNICALL Java_es_bsc_cepbatools_extrae_JavaProbes_ObjectNotifyBegin(
    JNIEnv *env, jclass jc)
{
    UNREFERENCED(env);
    UNREFERENCED(jc);

    Backend_Enter_Instrumentation ();

    TRACE_MISCEVENTANDCOUNTERS(LAST_READ_TIME, JAVA_ASPECTS_OBJECT_NOTIFY_EV, EVT_BEGIN, EMPTY);
    //Extrae_AnnotateCPU (LAST_READ_TIME);
}


JNIEXPORT void JNICALL Java_es_bsc_cepbatools_extrae_JavaProbes_ObjectNotifyEnd(
    JNIEnv *env, jclass jc)
{
    UNREFERENCED(env);
    UNREFERENCED(jc);

    TRACE_MISCEVENTANDCOUNTERS(TIME, JAVA_ASPECTS_OBJECT_NOTIFY_EV, EVT_END, EMPTY)

    Backend_Leave_Instrumentation ();
}
