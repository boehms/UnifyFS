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
#ifndef __TESTLIB_H
#define __TESTLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mpi.h>

extern int errno;

static inline
void test_print(int rank, const char* fmt, ...)
{
    va_list args;

    printf("[%d] ", rank);

    va_start(args, fmt);

    vfprintf(stdout, fmt, args);

    va_end(args);

    if (errno) {
        fprintf(stdout, " (errno=%d, %s)\n", errno, strerror(errno));
    } else {
        fprintf(stdout, "\n");
    }

    fflush(stdout);
}

static inline
void test_print_once(int rank, const char* fmt, ...)
{
    if (rank == 0) {
        va_list args;

        va_start(args, fmt);

        vfprintf(stdout, fmt, args);

        va_end(args);

        if (errno) {
            fprintf(stdout, " (errno=%d, %s)\n", errno, strerror(errno));
        } else {
            fprintf(stdout, "\n");
        }

        fflush(stdout);
    }
}

static inline
void test_pause(int rank, const char* fmt, ...)
{
    if (rank == 0) {
        va_list args;

        va_start(args, fmt);

        vfprintf(stderr, fmt, args);

        va_end(args);

        fprintf(stderr, " ENTER to continue ... ");

        (void) getchar();
    }

    MPI_Barrier(MPI_COMM_WORLD);

    /* internal accept() call from mpi may set errno */
    errno = 0;
}

static inline
double timediff_usec(struct timeval* before, struct timeval* after)
{
    if (!before || !after) {
        return -1.0F;
    }

    return 1000000.0 * (after->tv_sec - before->tv_sec) +
           1.0 * (after->tv_usec - before->tv_usec);
}

static inline
double timediff_sec(struct timeval* before, struct timeval* after)
{
    return timediff_usec(before, after) * .000001;
}

#define IO_PATTERN_N1   0
#define IO_PATTERN_NN   1

static inline int read_io_pattern(const char* pstr)
{
    int pattern = -1;

    if (strcmp(pstr, "n1") == 0) {
        pattern = IO_PATTERN_N1;
    } else if (strcmp(pstr, "nn") == 0) {
        pattern = IO_PATTERN_NN;
    }

    return pattern;
}

static inline const char* io_pattern_string(int pattern)
{
    if (pattern == IO_PATTERN_N1) {
        return "N to 1";
    } else if (pattern == IO_PATTERN_NN) {
        return "N to N";
    } else {
        return "Unknown";
    }
}

static inline int static_linked(const char* program)
{
    char* pos = strstr(program, "-static");

    return pos ? 1 : 0;
}

/*
 * Each 8 byte (uint64_t) will be sequentially numbered.
 */
static inline void lipsum_generate(char* buf, uint64_t len, uint64_t offset)
{
    uint64_t i;
    uint64_t start = offset / sizeof(uint64_t);
    uint64_t count = len / sizeof(uint64_t);
    uint64_t* ibuf = (uint64_t*) buf;

    for (i = 0; i < count; i++) {
        ibuf[i] = start + i;
    }
}

/*
 * returns 0 on successful check, -1 otherwise with @error_offset is set.
 */
static inline
int lipsum_check(const char* buf, uint64_t len, uint64_t offset,
                 uint64_t* error_offset)
{
    uint64_t i;
    uint64_t start = offset / sizeof(uint64_t);
    uint64_t count = len / sizeof(uint64_t);
    const uint64_t* ibuf = (uint64_t*) buf;

    for (i = 0; i < count; i++)
        if (ibuf[i] != start + i) {
            *error_offset = (start + i) * sizeof(uint64_t);
            return -1;
        }

    return 0;
}

#endif /* __TESTLIB_H */
