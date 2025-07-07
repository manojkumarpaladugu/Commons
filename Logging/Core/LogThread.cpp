/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

#include "LogThread.hpp"

#include <zephyr/kernel.h>

// ----------------------------------------------------------------------------
// Macro definitions
// ----------------------------------------------------------------------------

// Define thread stack size and priority
#define LOG_THREAD_STACK_SIZE   (1024)
#define LOG_THREAD_PRIORITY     (5)

// ----------------------------------------------------------------------------
// Variable definitions
// ----------------------------------------------------------------------------

// Registered entry function for the log thread
LogThreadEntryFunction LogThread::mEntryFunction;

// Thread stack
K_THREAD_STACK_DEFINE(gLogThreadStack, LOG_THREAD_STACK_SIZE);

// Thread data structure
struct k_thread gLogThreadData;

// ----------------------------------------------------------------------------
// Private functions
// ----------------------------------------------------------------------------

static void ThreadyEntryFunction(void* arg1, void* arg2, void* arg3)
{
    LogThread::InvokeEntryFunction();
    k_yield();
}

void LogThread::InvokeEntryFunction()
{
    // Check if the entry function is set
    if (mEntryFunction != NULL)
    {
        // Call the entry function
        mEntryFunction();
    }
}

// ----------------------------------------------------------------------------
// Public functions
// ----------------------------------------------------------------------------

void LogThread::CreateThread(LogThreadEntryFunction entryFunction)
{
    // Set the entry function for the thread
    mEntryFunction = entryFunction;

    // Create and start the thread
    k_thread_create(&gLogThreadData, gLogThreadStack, LOG_THREAD_STACK_SIZE,
                    ThreadyEntryFunction, NULL, NULL, NULL,
                    LOG_THREAD_PRIORITY, 0, K_NO_WAIT);
}
