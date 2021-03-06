/*
 * Copyright (c) 2017, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 *
 * Copyright 2017-2019, UT-Battelle, LLC.
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

#ifndef UNIFYFS_METADATA_H
#define UNIFYFS_METADATA_H

#include "unifyfs_configurator.h"
#include "unifyfs_global.h"

#define MANIFEST_FILE_NAME "mdhim_manifest_"

/**
 * Key for a file extent
 */
typedef struct {
    /** global file id */
    int fid;
    /** logical file offset */
    size_t offset;
} unifyfs_key_t;

#define UNIFYFS_KEY_SZ (sizeof(unifyfs_key_t))
#define UNIFYFS_KEY_FID(keyp) (((unifyfs_key_t*)keyp)->fid)
#define UNIFYFS_KEY_OFF(keyp) (((unifyfs_key_t*)keyp)->offset)

typedef struct {
    size_t addr;        /* data offset in server */
    size_t len;         /* length of data at addr */
    int app_id;         /* application id in server */
    int rank;           /* client id in server */
    int delegator_rank; /* delegator/server rank hosting data */
} unifyfs_val_t;

#define UNIFYFS_VAL_SZ (sizeof(unifyfs_val_t))
#define UNIFYFS_VAL_ADDR(valp) (((unifyfs_val_t*)valp)->addr)
#define UNIFYFS_VAL_LEN(valp) (((unifyfs_val_t*)valp)->len)

/**
 * key-value tuple for a file extent
 */
typedef struct {
    /** key */
    unifyfs_key_t key;
    /** value */
    unifyfs_val_t val;
} unifyfs_keyval_t;

int unifyfs_key_compare(unifyfs_key_t* a, unifyfs_key_t* b);

void debug_log_key_val(const char* ctx,
                       unifyfs_key_t* key,
                       unifyfs_val_t* val);

int meta_sanitize(void);
int meta_init_store(unifyfs_cfg_t* cfg);

void print_fsync_indices(unifyfs_key_t** unifyfs_keys,
                         unifyfs_val_t** unifyfs_vals, size_t num_entries);

/**
 * Retrieve a File attribute from the KV-Store.
 *
 * @param [in] gfid
 * @param[out] *ptr_attr_val
 * @return UNIFYFS_SUCCESS on success
 */
int unifyfs_get_file_attribute(int gfid,
                               unifyfs_file_attr_t* ptr_attr_val);

/**
 * Store a File attribute to the KV-Store.
 *
 * @param[in] *ptr_attr_val
 * @return UNIFYFS_SUCCESS on success
 */
int unifyfs_set_file_attribute(unifyfs_file_attr_t* ptr_attr_val);

/**
 * Store File attributes to the KV-Store.
 *
 * @param[in] num_entries number of key value pairs to store
 * @param[in] keys array storing the keys
 * @param[in] key_lens array with the length of the elements in \p keys
 * @param[in] vals array with the values
 * @param[in] val_lens array with the length of the elements in \p vals
 */
int unifyfs_set_file_attributes(int num_entries,
                                fattr_key_t** keys, int* key_lens,
                                unifyfs_file_attr_t** vals, int* val_lens);

/**
 * Retrieve File extents from the KV-Store.
 *
 * @param[in] num_keys number of keys
 * @param[in] keys array of keys to retrieve the values for
 * @param[in] key_lens array with the length of the key in \p keys
 * @param[out] num_values number of values in the keyval array
 * @param[out] keyval array containing the key-value tuples found
 * @return UNIFYFS_SUCCESS on success
 */
int unifyfs_get_file_extents(int num_keys,
                             unifyfs_key_t** keys, int* key_lens,
                             int* num_values, unifyfs_keyval_t** keyval);

/**
 * Store File extents in the KV-Store.
 *
 * @param [in] num_entries number of key value pairs to store
 * @param[in] keys array storing the keys
 * @param[in] key_lens array with the length of the elements in \p keys
 * @param[in] vals array with the values
 * @param[in] val_lens array with the length of the elements in \p vals
 * @return UNIFYFS_SUCCESS on success
 */
int unifyfs_set_file_extents(int num_entries, unifyfs_key_t** keys,
                             int* key_lens, unifyfs_val_t** vals,
                             int* val_lens);

#endif
