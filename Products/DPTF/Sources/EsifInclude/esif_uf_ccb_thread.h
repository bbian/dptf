/******************************************************************************
** Copyright (c) 2013 Intel Corporation All Rights Reserved
**
** Licensed under the Apache License, Version 2.0 (the "License"); you may not
** use this file except in compliance with the License.
**
** You may obtain a copy of the License at
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
** WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**
** See the License for the specific language governing permissions and
** limitations under the License.
**
******************************************************************************/
#ifndef _ESIF_CCB_THREAD_H_
#define _ESIF_CCB_THREAD_H_

#include "esif.h"
#include "esif_rc.h"
#include "esif_ccb.h"

#ifdef __cplusplus
    extern "C" {
#endif

#ifdef ESIF_ATTR_OS_LINUX
    #include <pthread.h>
    typedef pthread_t esif_thread_t;        /* PTHREAD */
#endif
#ifdef ESIF_ATTR_OS_WINDOWS
    typedef UInt32 esif_thread_t;           /* Windows Thread */
#endif

/* Get Current Thread ID */
#ifdef ESIF_ATTR_OS_LINUX
    #define esif_ccb_thread_id_current pthread_self
#endif
#ifdef ESIF_ATTR_OS_WINDOWS
    #define esif_ccb_thread_id_current GetCurrentThreadId
#endif

/* Work Function */
typedef void* (*work_func_t)(void*);

static ESIF_INLINE eEsifError
esif_ccb_thread_create(esif_thread_t *thread_ptr,
                       work_func_t   function_ptr,
                       void          *argument_ptr)
{
    eEsifError rc = ESIF_OK;

#ifdef ESIF_ATTR_OS_LINUX
    pthread_attr_t attr;      /* Thread Attribute     */
    pthread_attr_init(&attr); /* Initialize Attributes */

    if (pthread_create(
        thread_ptr,                      /* Thread                    */
        &attr,                           /* Attributes                */
        (void* (*)(void*)) function_ptr, /* Function To Start         */
        argument_ptr                     /* Function Arguments If Any */
        ) != 0) {
            rc = ESIF_E_UNSPECIFIED;
        }
#endif /* Linux */

#ifdef ESIF_ATTR_OS_WINDOWS
    if (CreateThread(NULL,                         /* Security / Cannot NOT be inherited */
        0,                                     /* Default Stack Size                 */
        (LPTHREAD_START_ROUTINE) (ULONG_PTR) function_ptr, /* Function To Start      */
        argument_ptr,                          /* Function Arguments If Any          */
        0,                                     /* Flags = Run Immediately            */
        (LPDWORD) thread_ptr                   /* Thread                             */
        ) == NULL) {
            rc = ESIF_E_UNSPECIFIED;
        }
#endif

    THREAD_DEBUG(("%s: thread = %p entry function = %p entry args = %p rc=%s(%d)\n",
        ESIF_FUNC, thread_ptr, function_ptr, argument_ptr, esif_rc_str(rc), rc));

    return rc;
}

#ifdef __cplusplus
    }
#endif

#endif /* _ESIF_CCB_THREAD_H_ */