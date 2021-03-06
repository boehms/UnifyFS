#ifndef __UNIFYFS_SERVER_RPCS_H
#define __UNIFYFS_SERVER_RPCS_H

/*
 * Declarations for server-server margo RPCs
 */

#include <margo.h>
#include <mercury.h>
#include <mercury_proc_string.h>
#include <mercury_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* server_hello_rpc (server => server)
 *
 * say hello from one server to another */
MERCURY_GEN_PROC(server_hello_in_t,
                 ((int32_t)(src_rank))
                 ((hg_const_string_t)(message_str)))
MERCURY_GEN_PROC(server_hello_out_t,
                 ((int32_t)(ret)))
DECLARE_MARGO_RPC_HANDLER(server_hello_rpc)

/* server_request_rpc (server => server)
 *
 * request from one server to another */
MERCURY_GEN_PROC(server_request_in_t,
                 ((int32_t)(src_rank))
                 ((int32_t)(req_id))
                 ((int32_t)(req_tag))
                 ((hg_size_t)(bulk_size))
                 ((hg_bulk_t)(bulk_handle)))
MERCURY_GEN_PROC(server_request_out_t,
                 ((int32_t)(ret)))
DECLARE_MARGO_RPC_HANDLER(server_request_rpc)

/* chunk_read_request_rpc (server => server)
 *
 * request for chunk reads from another server */
MERCURY_GEN_PROC(chunk_read_request_in_t,
                 ((int32_t)(src_rank))
                 ((int32_t)(app_id))
                 ((int32_t)(client_id))
                 ((int32_t)(req_id))
                 ((int32_t)(num_chks))
                 ((hg_size_t)(bulk_size))
                 ((hg_bulk_t)(bulk_handle)))
MERCURY_GEN_PROC(chunk_read_request_out_t,
                 ((int32_t)(ret)))
DECLARE_MARGO_RPC_HANDLER(chunk_read_request_rpc)

/* chunk_read_response_rpc (server => server)
 *
 * response to remote chunk reads request */
MERCURY_GEN_PROC(chunk_read_response_in_t,
                 ((int32_t)(src_rank))
                 ((int32_t)(app_id))
                 ((int32_t)(client_id))
                 ((int32_t)(req_id))
                 ((int32_t)(num_chks))
                 ((hg_size_t)(bulk_size))
                 ((hg_bulk_t)(bulk_handle)))
MERCURY_GEN_PROC(chunk_read_response_out_t,
                 ((int32_t)(ret)))
DECLARE_MARGO_RPC_HANDLER(chunk_read_response_rpc)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // UNIFYFS_SERVER_RPCS_H
