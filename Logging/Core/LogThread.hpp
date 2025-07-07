/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Manoj Kumar Paladugu <paladugumanojkumar@gmail.com>
 */

// ----------------------------------------------------------------------------
// Header includes
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Datatype definitions
// ----------------------------------------------------------------------------

typedef bool (*LogThreadEntryFunction)(void);

// ----------------------------------------------------------------------------
// Class definition
// ----------------------------------------------------------------------------

class LogThread
{
public:

    /**
     * @brief Create a thread
     */
    static void CreateThread(LogThreadEntryFunction entryFunction);

    /**
     * @brief Thread entry function that invokes the registered entry function.
     *
     * This function is called when the thread starts and it will invoke the
     * provided entry function.
     */
    static void InvokeEntryFunction();

private:

    static LogThreadEntryFunction mEntryFunction;  // Entry function for the thread
};
