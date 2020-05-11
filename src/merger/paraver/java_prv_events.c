/*****************************************************************************\
 *                        ANALYSIS PERFORMANCE TOOLS                         *
 *                                   Extrae                                  *
 *              Instrumentation package for parallel applications            *
 *****************************************************************************
 *     ___     This library is free software; you can redistribute it and/or *
 *    /  __         modify it under the terms of the GNU LGPL as published   *
 *   /  /  _____    by the Free Software Foundation; either version 2.1      *
 *  /  /  /     \   of the License, or (at your option) any later version.   *
 * (  (  ( B S C )                                                           *
 *  \  \  \_____/   This library is distributed in hope that it will be      *
 *   \  \__         useful but WITHOUT ANY WARRANTY; without even the        *
 *    \___          implied warranty of MERCHANTABILITY or FITNESS FOR A     *
 *                  PARTICULAR PURPOSE. See the GNU LGPL for more details.   *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public License  *
 * along with this library; if not, write to the Free Software Foundation,   *
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA          *
 * The GNU LEsser General Public License is contained in the file COPYING.   *
 *                                 ---------                                 *
 *   Barcelona Supercomputing Center - Centro Nacional de Supercomputacion   *
\*****************************************************************************/

#include "common.h"

#ifdef HAVE_STDLIB_H
# include <stdlib.h>
#endif
#ifdef HAVE_STDIO_H
# include <stdio.h>
#endif

#include "events.h"
#include "mpi2out.h"
#include "options.h"

#define ENABLE_JAVA_EVENT(type, event) \
	if (type == event##_EV) inuse[event##_INDEX] = TRUE;

#define JAVA_JVMTI_GARBAGECOLLECTOR_INDEX 0
#define JAVA_JVMTI_EXCEPTION_INDEX        1
#define JAVA_JVMTI_OBJECT_ALLOC_INDEX     2
#define JAVA_JVMTI_OBJECT_FREE_INDEX      3
#define JAVA_JVMTI_THREAD_RUN_INDEX       4
#define JAVA_JVMTI_WAIT_INDEX             5
#define JAVA_ASPECTS_THREAD_START_INDEX   6
#define JAVA_ASPECTS_OBJECT_NOTIFY_INDEX  7
#define MAX_JAVA_INDEX                    8

static int inuse[MAX_JAVA_INDEX] = { FALSE };

void Enable_Java_Operation (int type)
{
	ENABLE_JAVA_EVENT(type, JAVA_JVMTI_GARBAGECOLLECTOR);
	ENABLE_JAVA_EVENT(type, JAVA_JVMTI_EXCEPTION);
	ENABLE_JAVA_EVENT(type, JAVA_JVMTI_OBJECT_ALLOC);
    ENABLE_JAVA_EVENT(type, JAVA_JVMTI_OBJECT_FREE);
    ENABLE_JAVA_EVENT(type, JAVA_JVMTI_THREAD_RUN);
    ENABLE_JAVA_EVENT(type, JAVA_JVMTI_WAIT);
    ENABLE_JAVA_EVENT(type, JAVA_ASPECTS_THREAD_START);
    ENABLE_JAVA_EVENT(type, JAVA_ASPECTS_OBJECT_NOTIFY);
}

#if defined(PARALLEL_MERGE)

#include <mpi.h>
#include "mpi-aux.h"

void Share_Java_Operations (void)
{
	int res, i, tmp[MAX_JAVA_INDEX];

	res = MPI_Reduce (inuse, tmp, MAX_JAVA_INDEX, MPI_INT, MPI_BOR, 0,
		MPI_COMM_WORLD);
	MPI_CHECK(res, MPI_Reduce, "While sharing Java enabled operations");

	for (i = 0; i < MAX_JAVA_INDEX; i++)
		inuse[i] = tmp[i];
}

#endif

void JavaEvent_WriteEnabledOperations (FILE * fd)
{
	if (inuse[JAVA_JVMTI_GARBAGECOLLECTOR_INDEX])
	{
		fprintf (fd, "EVENT_TYPE\n%d %d Java Garbage collector\n", 0, JAVA_JVMTI_GARBAGECOLLECTOR_EV);
		fprintf (fd, "VALUES\n0 Garbage collector disabled\n1 Garbage collector enabled\n\n");
	}

	if (inuse[JAVA_JVMTI_EXCEPTION_INDEX])
	{
		fprintf (fd, "EVENT_TYPE\n%d %d Java exception\n", 0, JAVA_JVMTI_EXCEPTION_EV);
		fprintf (fd, "VALUES\n0 No exeception or last exception caught\n1 In-flight exception\n\n");
	}

	if (inuse[JAVA_JVMTI_OBJECT_ALLOC_INDEX])
	{
		fprintf (fd, "EVENT_TYPE\n%d %d Java object allocation\n\n", 0, JAVA_JVMTI_OBJECT_ALLOC_EV);
	}

	if (inuse[JAVA_JVMTI_OBJECT_FREE_INDEX])
	{
		fprintf (fd, "EVENT_TYPE\n%d %d Java object free\n\n", 0, JAVA_JVMTI_OBJECT_FREE_EV);
	}

	if (inuse[JAVA_JVMTI_THREAD_RUN_INDEX])
	{
		fprintf (fd, "EVENT_TYPE\n%d %d Java thread running\n\n", 0, JAVA_JVMTI_THREAD_RUN_EV);
		fprintf (fd, "VALUES\n0 Thread ended \n1 Thread started\n\n");
	}
	
	if (inuse[JAVA_JVMTI_WAIT_INDEX])
	{
		fprintf (fd, "EVENT_TYPE\n%d %d Java thread waiting on an object (it may be a Thread join)\n\n", 0, JAVA_JVMTI_WAIT_EV);
		fprintf (fd, "VALUES\n0 Wait ended\n1 Started waiting\n\n");
	}
    
    if (inuse[JAVA_ASPECTS_THREAD_START_INDEX])
	{
		fprintf (fd, "EVENT_TYPE\n%d %d Java thread started\n\n", 0, JAVA_ASPECTS_THREAD_START_EV);
		fprintf (fd, "VALUES\n0 Thread created\n1 Thread creation started\n\n");
	}
    
    if (inuse[JAVA_ASPECTS_OBJECT_NOTIFY_INDEX])
	{
		fprintf (fd, "EVENT_TYPE\n%d %d An Object's monitor is being notified\n\n", 0, JAVA_ASPECTS_OBJECT_NOTIFY_EV);
		fprintf (fd, "VALUES\n0 Starts notifying\n1 Notify ended\n\n");
	}
}

