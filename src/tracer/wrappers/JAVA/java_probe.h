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

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- *\
 | @file: $HeadURL: https://svn.bsc.es/repos/ptools/extrae/branches/2.4/src/tracer/wrappers/OMP/omp_wrapper.c $
 | @last_commit: $Date: 2013-09-06 14:39:32 +0200 (Fri, 06 Sep 2013) $
 | @version:     $Revision: 2098 $
\* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#ifndef PROBE_JAVA_H_INCLUDED
#define PROBE_JAVA_H_INCLUDED

void Extrae_Java_GarbageCollector_begin(void);
void Extrae_Java_GarbageCollector_end(void);

void Extrae_Java_Exception_begin(void);
void Extrae_Java_Exception_end(void);

void Extrae_Java_Object_Alloc (unsigned long long size);
void Extrae_Java_Object_Free (void);

#endif /* PROBE_JAVA_H_INCLUDED */
