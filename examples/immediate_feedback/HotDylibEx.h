#pragma once

#ifndef HOTDYLIB_API
#define HOTDYLIB_API
#endif

/**
 * File data structure
 */
typedef struct
{
    long        time;
    const char* path;
} HotDylibFileTime;

/**
 * Watch for files or directories is changed
 * @note: if change the directory after received a changed event
 *        ensure call this again to update time to ignore change
 *
 * @example: 
 *        HotDylibFileTime dir = { 0, "<dirpath>" };
 *        HotDylibWatchFiles(&dir, 1); // Initialize
 *        ...
 *        if (HotDylibWatchFiles(&dir, 1))
 *        {
 *            ... some operations on <dirpath>
 *            HotDylibWatchFiles(&dir, 1); // Ignore change
 *        }
 * @return:
 *      1 - have changed
 *      0 - no changed
 */
HOTDYLIB_API int HotDylibWatchFiles(HotDylibFileTime* files, int count);
