/*
 * Copyright (c) 2017, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 *
 * Copyright 2017, UT-Battelle, LLC.
 *
 * LLNL-CODE-741539
 * All rights reserved.
 *
 * This is the license for UnifyFS.
 * For details, see https://github.com/LLNL/UnifyFS.
 * Please read https://github.com/LLNL/UnifyFS/LICENSE for full license text.
 */

/*
 * Copyright (c) 2017, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * Copyright (c) 2017, Florida State University. Contributions from
 * the Computer Architecture and Systems Research Laboratory (CASTL)
 * at the Department of Computer Science.
 *
 * Written by: Teng Wang, Adam Moody, Weikuan Yu, Kento Sato, Kathryn Mohror
 * LLNL-CODE-728877. All rights reserved.
 *
 * This file is part of burstfs.
 * For details, see https://github.com/llnl/burstfs
 * Please read https://github.com/llnl/burstfs/LICENSE for full license text.
 */

#include <stdio.h>
#include <string.h>
#include "unifyfs_log.h"
#include "unifyfs_const.h"

/* one of the loglevel values */
unifyfs_log_level_t unifyfs_log_level = LOG_ERR;

/* pointer to log file stream */
FILE* unifyfs_log_stream; // = NULL

/* used within LOG macro to build a timestamp */
time_t unifyfs_log_time;
struct tm* unifyfs_log_ltime;
char unifyfs_log_timestamp[256];

/* used to reduce source file name length */
size_t unifyfs_log_source_base_len; // = 0
static const char* this_file = __FILE__;

/* open specified file as log file stream,
 * returns UNIFYFS_SUCCESS on success */
int unifyfs_log_open(const char* file)
{
    if (0 == unifyfs_log_source_base_len) {
        // NOTE: if you change the source location of this file, update string
        char* srcdir = strstr(this_file, "common/src/unifyfs_log.c");
        if (NULL != srcdir) {
            unifyfs_log_source_base_len = srcdir - this_file;
        }
    }

    FILE* logf = fopen(file, "a");
    if (logf == NULL) {
        /* failed to open file name, fall back to stderr */
        unifyfs_log_stream = stderr;
        return (int)UNIFYFS_ERROR_DBG;
    } else {
        unifyfs_log_stream = logf;
        return UNIFYFS_SUCCESS;
    }
}

/* close our log file stream,
 * returns UNIFYFS_SUCCESS on success */
int unifyfs_log_close(void)
{
    if (unifyfs_log_stream == NULL) {
        /* nothing to close */
        return (int)UNIFYFS_ERROR_DBG;
    } else {
        /* if stream is open, and its not stderr, close it */
        if (unifyfs_log_stream != stderr &&
            fclose(unifyfs_log_stream) == 0) {
            return UNIFYFS_SUCCESS;
        }
        return (int)UNIFYFS_ERROR_DBG;
    }
}
