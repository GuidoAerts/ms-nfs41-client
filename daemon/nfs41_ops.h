/* Copyright (c) 2010
* The Regents of the University of Michigan
* All Rights Reserved
*
* Permission is granted to use, copy and redistribute this software
* for noncommercial education and research purposes, so long as no
* fee is charged, and so long as the name of the University of Michigan
* is not used in any advertising or publicity pertaining to the use
* or distribution of this software without specific, written prior
* authorization.  Permission to modify or otherwise create derivative
* works of this software is not granted.
*
* This software is provided as is, without representation or warranty
* of any kind either express or implied, including without limitation
* the implied warranties of merchantability, fitness for a particular
* purpose, or noninfringement.  The Regents of the University of
* Michigan shall not be liable for any damages, including special,
* indirect, incidental, or consequential damages, with respect to any
* claim arising out of or in connection with the use of the software,
* even if it has been or is hereafter advised of the possibility of
* such damages.
*/

#ifndef __NFS41_NFS_OPS_H__
#define __NFS41_NFS_OPS_H__

#include "nfs41.h"
#include "pnfs.h"


/* Operation arrays */
enum nfs_opnum4 {
    OP_ACCESS               = 3,
    OP_CLOSE                = 4,
    OP_COMMIT               = 5,
    OP_CREATE               = 6,
    OP_DELEGPURGE           = 7,
    OP_DELEGRETURN          = 8,
    OP_GETATTR              = 9,
    OP_GETFH                = 10,
    OP_LINK                 = 11,
    OP_LOCK                 = 12,
    OP_LOCKT                = 13,
    OP_LOCKU                = 14,
    OP_LOOKUP               = 15,
    OP_LOOKUPP              = 16,
    OP_NVERIFY              = 17,
    OP_OPEN                 = 18,
    OP_OPENATTR             = 19,
    OP_OPEN_CONFIRM         = 20, /* Mandatory not-to-implement */
    OP_OPEN_DOWNGRADE       = 21,
    OP_PUTFH                = 22,
    OP_PUTPUBFH             = 23,
    OP_PUTROOTFH            = 24,
    OP_READ                 = 25,
    OP_READDIR              = 26,
    OP_READLINK             = 27,
    OP_REMOVE               = 28,
    OP_RENAME               = 29,
    OP_RENEW                = 30, /* Mandatory not-to-implement */
    OP_RESTOREFH            = 31,
    OP_SAVEFH               = 32,
    OP_SECINFO              = 33,
    OP_SETATTR              = 34,
    OP_SETCLIENTID          = 35, /* Mandatory not-to-implement */
    OP_SETCLIENTID_CONFIRM  = 36, /* Mandatory not-to-implement */
    OP_VERIFY               = 37,
    OP_WRITE                = 38,
    OP_RELEASE_LOCKOWNER    = 39, /* Mandatory not-to-implement */

    /* new operations for NFSv4.1 */
    OP_BACKCHANNEL_CTL      = 40,
    OP_BIND_CONN_TO_SESSION = 41,
    OP_EXCHANGE_ID          = 42,
    OP_CREATE_SESSION       = 43,
    OP_DESTROY_SESSION      = 44,
    OP_FREE_STATEID         = 45,
    OP_GET_DIR_DELEGATION   = 46,
    OP_GETDEVICEINFO        = 47,
    OP_GETDEVICELIST        = 48,
    OP_LAYOUTCOMMIT         = 49,
    OP_LAYOUTGET            = 50,
    OP_LAYOUTRETURN         = 51,
    OP_SECINFO_NO_NAME      = 52,
    OP_SEQUENCE             = 53,
    OP_SET_SSV              = 54,
    OP_TEST_STATEID         = 55,
    OP_WANT_DELEGATION      = 56,
    OP_DESTROY_CLIENTID     = 57,
    OP_RECLAIM_COMPLETE     = 58,
    OP_ILLEGAL              = 10044
};


/* OP_EXCHANGE_ID */
enum {
    EXCHGID4_FLAG_SUPP_MOVED_REFER      = 0x00000001,
    EXCHGID4_FLAG_SUPP_MOVED_MIGR       = 0x00000002,

    EXCHGID4_FLAG_BIND_PRINC_STATEID    = 0x00000100,

    EXCHGID4_FLAG_USE_NON_PNFS          = 0x00010000,
    EXCHGID4_FLAG_USE_PNFS_MDS          = 0x00020000,
    EXCHGID4_FLAG_USE_PNFS_DS           = 0x00040000,

    EXCHGID4_FLAG_MASK_PNFS             = 0x00070000,

    EXCHGID4_FLAG_UPD_CONFIRMED_REC_A   = 0x40000000,
    EXCHGID4_FLAG_CONFIRMED_R           = 0x80000000
};

typedef enum {
    SP4_NONE        = 0,
    SP4_MACH_CRED   = 1,
    SP4_SSV         = 2
} state_protect_how4;

typedef struct __state_protect4_a {
    state_protect_how4      spa_how;
} state_protect4_a;

typedef struct __nfs41_exchange_id_args {
    client_owner4           *eia_clientowner;
    uint32_t                eia_flags;
    state_protect4_a        eia_state_protect;
    nfs_impl_id4            *eia_client_impl_id; /* <1> */
} nfs41_exchange_id_args;

typedef struct __state_protect4_r {
    state_protect_how4      spr_how;
} state_protect4_r;

typedef struct __nfs41_exchange_id_res {
    uint32_t                status;
    uint64_t                clientid;
    uint32_t                sequenceid;
    uint32_t                flags;
    state_protect4_r        state_protect;
    server_owner4           server_owner;
    uint32_t                server_scope_len;
    char                    server_scope[NFS4_OPAQUE_LIMIT];
} nfs41_exchange_id_res;


/* OP_CREATE_SESSION */
typedef struct __nfs41_create_session_args {
    uint64_t                csa_clientid;
    uint32_t                csa_sequence;
    uint32_t                csa_flags;
    nfs41_channel_attrs     csa_fore_chan_attrs;
    nfs41_channel_attrs     csa_back_chan_attrs;
    uint32_t                csa_cb_program;
} nfs41_create_session_args;

typedef struct __nfs41_create_session_res {
    unsigned char           *csr_sessionid;
    uint32_t                csr_sequence;
    uint32_t                csr_flags;
    nfs41_channel_attrs     *csr_fore_chan_attrs;
    nfs41_channel_attrs     *csr_back_chan_attrs;
} nfs41_create_session_res;


/* OP_BIND_CONN_TO_SESSION */
enum channel_dir_from_client4 {
    CDFC4_FORE              = 0x1,
    CDFC4_BACK              = 0x2,
    CDFC4_FORE_OR_BOTH      = 0x3,
    CDFC4_BACK_OR_BOTH      = 0x7
};

enum channel_dir_from_server4 {
    CDFS4_FORE              = 0x1,
    CDFS4_BACK              = 0x2,
    CDFS4_BOTH              = 0x3
};

typedef struct __nfs41_bind_conn_to_session_args {
    unsigned char           *sessionid;
    enum channel_dir_from_client4 dir;
} nfs41_bind_conn_to_session_args;

typedef struct __nfs41_bind_conn_to_session_res {
    enum nfsstat4           status;
    /* case NFS4_OK: */
    enum channel_dir_from_server4 dir;
} nfs41_bind_conn_to_session_res;


/* OP_DESTROY_SESSION */
typedef struct __nfs41_destroy_session_args {
    unsigned char           *dsa_sessionid;
} nfs41_destroy_session_args;

typedef struct __nfs41_destroy_session_res {
    uint32_t                dsr_status;
} nfs41_destroy_session_res;


/* OP_SEQUENCE */
typedef struct __nfs41_sequence_args {
    unsigned char           *sa_sessionid;
    uint32_t                sa_sequenceid;
    uint32_t                sa_slotid;
    uint32_t                sa_highest_slotid;
    bool_t                  sa_cachethis;
} nfs41_sequence_args;

enum {
    SEQ4_STATUS_CB_PATH_DOWN                = 0x00000001,
    SEQ4_STATUS_CB_GSS_CONTEXTS_EXPIRING    = 0x00000002,
    SEQ4_STATUS_CB_GSS_CONTEXTS_EXPIRED     = 0x00000004,
    SEQ4_STATUS_EXPIRED_ALL_STATE_REVOKED   = 0x00000008,
    SEQ4_STATUS_EXPIRED_SOME_STATE_REVOKED  = 0x00000010,
    SEQ4_STATUS_ADMIN_STATE_REVOKED         = 0x00000020,
    SEQ4_STATUS_RECALLABLE_STATE_REVOKED    = 0x00000040,
    SEQ4_STATUS_LEASE_MOVED                 = 0x00000080,
    SEQ4_STATUS_RESTART_RECLAIM_NEEDED      = 0x00000100,
    SEQ4_STATUS_CB_PATH_DOWN_SESSION        = 0x00000200,
    SEQ4_STATUS_BACKCHANNEL_FAULT           = 0x00000400,
    SEQ4_STATUS_DEVID_CHANGED               = 0x00000800,
    SEQ4_STATUS_DEVID_DELETED               = 0x00001000
};

typedef struct __nfs41_sequence_res_ok {
    unsigned char           sr_sessionid[NFS4_SESSIONID_SIZE];
    uint32_t                sr_sequenceid;
    uint32_t                sr_slotid;
    uint32_t                sr_highest_slotid;
    uint32_t                sr_target_highest_slotid;
    uint32_t                sr_status_flags;
} nfs41_sequence_res_ok;

typedef struct __nfs41_sequence_res {
    uint32_t                sr_status;
    /* case NFS4_OK: */
    nfs41_sequence_res_ok   sr_resok4;
} nfs41_sequence_res;


/* OP_RECLAIM_COMPLETE */
typedef struct __nfs41_reclaim_complete_res {
    enum nfsstat4           status;
} nfs41_reclaim_complete_res;


/* OP_ACCESS */
enum {
    ACCESS4_READ            = 0x00000001,
    ACCESS4_LOOKUP          = 0x00000002,
    ACCESS4_MODIFY          = 0x00000004,
    ACCESS4_EXTEND          = 0x00000008,
    ACCESS4_DELETE          = 0x00000010,
    ACCESS4_EXECUTE         = 0x00000020
};

typedef struct __nfs41_access_args {
    uint32_t                access;
} nfs41_access_args;

typedef struct __nfs41_access_res {
    uint32_t                status;
    /* case NFS4_OK: */
    uint32_t                supported;
    uint32_t                access;
} nfs41_access_res;


/* OP_CLOSE */
typedef struct __nfs41_op_close_args {
//  uint32_t                seqid; // not used, always 0
    stateid4                *open_stateid; /* -> nfs41_op_open_res_ok.stateid */
} nfs41_op_close_args;

typedef struct __nfs41_op_close_res {
    uint32_t                status;
    /* case NFS4_OK: */
    stateid4                open_stateid;
} nfs41_op_close_res;


/* OP_COMMIT */
typedef struct __nfs41_commit_args {
    uint64_t                offset;
    uint32_t                count;
} nfs41_commit_args;

typedef struct __nfs41_commit_res {
    uint32_t                status;
    unsigned char           writeverf[NFS4_VERIFIER_SIZE];
} nfs41_commit_res;


/* OP_CREATE */
typedef struct __specdata4 {
    uint32_t                specdata1;
    uint32_t                specdata2;
} specdata4;

typedef struct __createtype4 {
    uint32_t                type;
    union {
    /* case NF4LNK: */
        struct __create_type_lnk {
            uint32_t        linkdata_len;
            const char      *linkdata;
        } lnk;
    /* case NF4BLK, NF4CHR: */
        specdata4           devdata;
    } u;
} createtype4;

typedef struct __createattrs4 {
    nfs41_file_info         info;
} createattrs4;

typedef struct __nfs41_create_args {
    createtype4             objtype;
    const nfs41_component   *name;
    createattrs4            createattrs;
} nfs41_create_args;

typedef struct __nfs41_create_res {
    uint32_t                status;
    /* case NFS4_OK: */
    change_info4            cinfo;
    bitmap4                 attrset;
} nfs41_create_res;


/* OP_DELEGRETURN */
typedef struct __nfs41_delegreturn_args {
    stateid4                *stateid;
} nfs41_delegreturn_args;

typedef struct __nfs41_delegreturn_res {
    uint32_t                status;
} nfs41_delegreturn_res;


/* OP_LINK */
typedef struct __nfs41_link_args {
    const nfs41_component   *newname;
} nfs41_link_args;

typedef struct __nfs41_link_res {
    uint32_t                status;
    /* case NFS4_OK */
    change_info4            cinfo;
} nfs41_link_res;


/* OP_LOCK */
enum {
    READ_LT                 = 1,
    WRITE_LT                = 2,
    READW_LT                = 3,    /* blocking read */
    WRITEW_LT               = 4     /* blocking write */
};

typedef struct __open_to_lock_owner4 {
    uint32_t                open_seqid;
    stateid4                *open_stateid;
    uint32_t                lock_seqid;
    state_owner4            *lock_owner;
} open_to_lock_owner4;

typedef struct __exist_lock_owner4 {
    stateid4                *lock_stateid;
    uint32_t                lock_seqid;
} exist_lock_owner4;

typedef struct __locker4 {
    bool_t                  new_lock_owner;
    union {
        /* case TRUE: */
        open_to_lock_owner4 open_owner;
        /* case FALSE: */
        exist_lock_owner4   lock_owner;
    } u;
} locker4;

typedef struct __nfs41_lock_args {
    uint32_t                locktype;
    bool_t                  reclaim;
    uint64_t                offset;
    uint64_t                length;
    locker4                 locker;
} nfs41_lock_args;

typedef struct __lock_res_denied {
    uint64_t                offset;
    uint64_t                length;
    uint32_t                locktype;
    state_owner4            owner;
} lock_res_denied;

typedef struct __lock_res_ok {
    stateid4                *lock_stateid;
} lock_res_ok;

typedef struct __nfs41_lock_res {
    uint32_t                status;
    union {
    /* case NFS4_OK: */
        lock_res_ok         resok4;
    /* case NFS4ERR_DENIED: */
        lock_res_denied     denied;
    /* default: void; */
    } u;
} nfs41_lock_res;


/* OP_LOCKT */
typedef struct __nfs41_lockt_args {
    uint32_t                locktype;
    uint64_t                offset;
    uint64_t                length;
    state_owner4            *owner;
} nfs41_lockt_args;

typedef struct __nfs41_lockt_res {
    uint32_t                status;
    /* case NFS4ERR_DENIED: */
    lock_res_denied         denied;
    /* default: void; */
} nfs41_lockt_res;


/* OP_LOCKU */
typedef struct __nfs41_locku_args {
    uint32_t                locktype;
    uint32_t                seqid;
    stateid4                *lock_stateid;
    uint64_t                offset;
    uint64_t                length;
} nfs41_locku_args;

typedef struct __nfs41_locku_res {
    uint32_t                status;
    /* case NFS4_OK: */
    stateid4                *lock_stateid;
} nfs41_locku_res;


/* OP_LOOKUP */
typedef struct __nfs41_lookup_args {
    const nfs41_component   *name;
} nfs41_lookup_args;

typedef struct __nfs41_lookup_res {
    uint32_t                status;
} nfs41_lookup_res;


/* OP_GETFH */
typedef struct __nfs41_getfh_res {
    uint32_t                status;
    /* case NFS4_OK: */
    nfs41_fh                *fh;
} nfs41_getfh_res;


/* OP_PUTFH */
typedef struct __nfs41_putfh_args {
    nfs41_path_fh           *file;
    bool_t                  in_recovery;
} nfs41_putfh_args;

typedef struct __nfs41_putfh_res {
    uint32_t                status;
} nfs41_putfh_res;


/* OP_PUTROOTFH */
typedef struct __nfs41_putrootfh_res {
    uint32_t                status;
} nfs41_putrootfh_res;


/* OP_GETATTR */
typedef struct __nfs41_getattr_args {
    bitmap4                 *attr_request;
} nfs41_getattr_args;

typedef struct __nfs41_getattr_res {
    uint32_t                status;
    /* case NFS4_OK: */
    fattr4                  obj_attributes;
    nfs41_file_info         *info;
} nfs41_getattr_res;


/* OP_OPEN */
enum createmode4 {
    UNCHECKED4      = 0,
    GUARDED4        = 1,
    EXCLUSIVE4      = 2,
    EXCLUSIVE4_1    = 3
};

typedef struct __creatverfattr {
    unsigned char           cva_verf[NFS4_VERIFIER_SIZE];
    fattr4                  cva_attrs;
} creatverfattr;

typedef struct __createhow4 {
    uint32_t                mode;
    union {
    /* case UNCHECKED4, GUARDED4: */
        createattrs4        createattrs;
    /* case EXCLUSIVE4: */
        unsigned char       createverf[NFS4_VERIFIER_SIZE];
    /* case EXCLUSIVE4_1: */
        creatverfattr       ch_createboth;
    } u;
} createhow4;

enum opentype4 {
    OPEN4_NOCREATE  = 0,
    OPEN4_CREATE    = 1
};

typedef struct __openflag4 {
    uint32_t                opentype;
    /* case OPEN4_CREATE: */
    createhow4              how;
} openflag4;

enum {
    OPEN4_SHARE_ACCESS_READ     = 0x00000001,
    OPEN4_SHARE_ACCESS_WRITE    = 0x00000002,
    OPEN4_SHARE_ACCESS_BOTH     = 0x00000003,

    OPEN4_SHARE_DENY_NONE       = 0x00000000,
    OPEN4_SHARE_DENY_READ       = 0x00000001,
    OPEN4_SHARE_DENY_WRITE      = 0x00000002,
    OPEN4_SHARE_DENY_BOTH       = 0x00000003,

    OPEN4_SHARE_ACCESS_WANT_DELEG_MASK      = 0xFF00,
    OPEN4_SHARE_ACCESS_WANT_NO_PREFERENCE   = 0x0000,
    OPEN4_SHARE_ACCESS_WANT_READ_DELEG      = 0x0100,
    OPEN4_SHARE_ACCESS_WANT_WRITE_DELEG     = 0x0200,
    OPEN4_SHARE_ACCESS_WANT_ANY_DELEG       = 0x0300,
    OPEN4_SHARE_ACCESS_WANT_NO_DELEG        = 0x0400,
    OPEN4_SHARE_ACCESS_WANT_CANCEL          = 0x0500,

    OPEN4_SHARE_ACCESS_WANT_SIGNAL_DELEG_WHEN_RESRC_AVAIL = 0x10000,
    OPEN4_SHARE_ACCESS_WANT_PUSH_DELEG_WHEN_UNCONTENDED = 0x20000
};

enum open_delegation_type4 {
    OPEN_DELEGATE_NONE      = 0,
    OPEN_DELEGATE_READ      = 1,
    OPEN_DELEGATE_WRITE     = 2,
    OPEN_DELEGATE_NONE_EXT  = 3
};

enum open_claim_type4 {
    CLAIM_NULL              = 0,
    CLAIM_PREVIOUS          = 1,
    CLAIM_DELEGATE_CUR      = 2,
    CLAIM_DELEGATE_PREV     = 3,
    CLAIM_FH                = 4,
    CLAIM_DELEG_CUR_FH      = 5,
    CLAIM_DELEG_PREV_FH     = 6
};

enum why_no_delegation4 {
    WND4_NOT_WANTED         = 0,
    WND4_CONTENTION         = 1,
    WND4_RESOURCE           = 2,
    WND4_NOT_SUPP_FTYPE     = 3,
    WND4_WRITE_DELEG_NOT_SUPP_FTYPE = 4,
    WND4_NOT_SUPP_UPGRADE   = 5,
    WND4_NOT_SUPP_DOWNGRADE = 6,
    WND4_CANCELED           = 7,
    WND4_IS_DIR             = 8
};

typedef struct __open_claim4 {
    uint32_t                claim;
    union {
    /* case CLAIM_NULL: */
        struct __open_claim_null {
            const nfs41_component *filename;
        } null;
    } u;
} open_claim4;

typedef struct __nfs41_op_open_args {
    uint32_t                seqid;
    uint32_t                share_access;
    uint32_t                share_deny;
    state_owner4            *owner;
    openflag4               openhow;
    open_claim4             claim;
} nfs41_op_open_args;

enum {
    OPEN4_RESULT_CONFIRM            = 0x00000002,
    OPEN4_RESULT_LOCKTYPE_POSIX     = 0x00000004,
    OPEN4_RESULT_PRESERVE_UNLINKED  = 0x00000008,
    OPEN4_RESULT_MAY_NOTIFY_LOCK    = 0x00000020
};

typedef struct __nfs41_op_open_res_ok {
    stateid4                *stateid;
    change_info4            cinfo;
    uint32_t                rflags;
    bitmap4                 attrset;
    uint32_t                delegation_type;
    stateid4                deleg_stateid;
    uint32_t                why_no_deleg;
    uint32_t                why_none_flag;
} nfs41_op_open_res_ok;

typedef struct __nfs41_op_open_res {
    uint32_t                status;
    /* case NFS4_OK: */
    nfs41_op_open_res_ok    resok4;
} nfs41_op_open_res;


/* OP_READ */
typedef struct __nfs41_read_args {
    stateid4                *stateid; /* -> nfs41_op_open_res_ok.stateid */
    uint64_t                offset;
    uint32_t                count;
} nfs41_read_args;

typedef struct __nfs41_read_res_ok {
    bool_t                  eof;
    uint32_t                data_len;
    unsigned char           *data; /* caller-allocated */
} nfs41_read_res_ok;

typedef struct __nfs41_read_res {
    uint32_t                status;
    /* case NFS4_OK: */
    nfs41_read_res_ok       resok4;
} nfs41_read_res;


/* OP_READDIR */
typedef struct __nfs41_readdir_args {
    nfs41_readdir_cookie    cookie;
    uint32_t                dircount;
    uint32_t                maxcount;
    bitmap4                 *attr_request;
} nfs41_readdir_args;

typedef struct __nfs41_readdir_entry {
    uint64_t                cookie;
    uint32_t                name_len;
    uint32_t                next_entry_offset;
    nfs41_file_info         attr_info;
    char                    name[1];
} nfs41_readdir_entry;

typedef struct __nfs41_readdir_list {
    bool_t                  has_entries;
    uint32_t                entries_len;
    unsigned char           *entries;
    bool_t                  eof;
} nfs41_readdir_list;

typedef struct __nfs41_readdir_res {
    uint32_t                status;
    /* case NFS4_OK: */
    unsigned char           cookieverf[NFS4_VERIFIER_SIZE];
    nfs41_readdir_list      reply;
} nfs41_readdir_res;


/* OP_READLINK */
typedef struct __nfs41_readlink_res {
    uint32_t                status;
    /* case NFS4_OK: */
    uint32_t                link_len;
    char                    *link;
} nfs41_readlink_res;


/* OP_REMOVE */
typedef struct __nfs41_remove_args {
    const nfs41_component   *target;
} nfs41_remove_args;

typedef struct __nfs41_remove_res {
    uint32_t                status;
    /* case NFS4_OK: */
    change_info4            cinfo;
} nfs41_remove_res;


/* OP_RENAME */
typedef struct __nfs41_rename_args {
    const nfs41_component   *oldname;
    const nfs41_component   *newname;
} nfs41_rename_args;

typedef struct __nfs41_rename_res {
    uint32_t                status;
    /* case NFS4_OK: */
    change_info4            source_cinfo;
    change_info4            target_cinfo;
} nfs41_rename_res;


/* OP_RESTOREFH */
/* OP_SAVEFH */
typedef struct __nfs41_restorefh_savefh_res {
    uint32_t                status;
} nfs41_restorefh_res, nfs41_savefh_res;


/* OP_SETATTR */
enum time_how4 {
    SET_TO_SERVER_TIME4 = 0,
    SET_TO_CLIENT_TIME4 = 1
};

typedef struct __nfs41_setattr_args {
    stateid4                *stateid;
    nfs41_file_info         *info;
} nfs41_setattr_args;

typedef struct __nfs41_setattr_res {
    uint32_t                status;
    bitmap4                 attrsset;
} nfs41_setattr_res;


/* OP_WRITE */
enum stable_how4 {
    UNSTABLE4       = 0,
    DATA_SYNC4      = 1,
    FILE_SYNC4      = 2
};

typedef struct __nfs41_write_verf {
    unsigned char           verf[NFS4_VERIFIER_SIZE];
    unsigned char           expected[NFS4_VERIFIER_SIZE];
    enum stable_how4        committed;
} nfs41_write_verf;

typedef struct __nfs41_write_args {
    stateid4                *stateid; /* -> nfs41_op_open_res_ok.stateid */
    uint64_t                offset;
    uint32_t                stable; /* stable_how4 */
    uint32_t                data_len;
    unsigned char           *data; /* caller-allocated */
} nfs41_write_args;

typedef struct __nfs41_write_res_ok {
    uint32_t                count;
    nfs41_write_verf        *verf;
} nfs41_write_res_ok;

typedef struct __nfs41_write_res {
    uint32_t                status;
    /* case NFS4_OK: */
    nfs41_write_res_ok      resok4;
} nfs41_write_res;


/* LAYOUTGET */
typedef struct __pnfs_layoutget_args {
    bool_t                  signal_layout_avail;
    enum pnfs_layout_type   layout_type;
    enum pnfs_iomode        iomode;
    uint64_t                offset;
    uint64_t                length;
    uint64_t                minlength;
    stateid4                *stateid;
    uint32_t                maxcount;
} pnfs_layoutget_args;

typedef struct __pnfs_layoutget_res_ok {
    pnfs_file_layout        *layout;
} pnfs_layoutget_res_ok;

typedef struct __pnfs_layoutget_res {
    enum nfsstat4           status;
    union {
    /* case NFS4_OK: */
        pnfs_layoutget_res_ok res_ok;
    /* case NFS4ERR_LAYOUTTRYLATER: */
        bool_t              will_signal_layout_avail;
    /* default: void; */
    } u;
} pnfs_layoutget_res;


/* LAYOUTCOMMIT */
typedef struct __pnfs_layoutcommit_args {
    uint64_t                offset;
    uint64_t                length;
    stateid4                *stateid;
    nfstime4                *new_time;
    uint64_t                *new_offset;
} pnfs_layoutcommit_args;

typedef struct __pnfs_layoutcommit_res {
    uint32_t                status;
    /* case NFS4_OK */
    bool_t                  has_new_size;
    /* case TRUE */
    uint64_t                new_size;
} pnfs_layoutcommit_res;


/* LAYOUTRETURN */
typedef struct __pnfs_layoutreturn_args {
    bool_t                  reclaim;
    enum pnfs_layout_type   type;
    enum pnfs_iomode        iomode;
    enum pnfs_return_type   return_type;
    /* case LAYOUTRETURN4_FILE: */
    uint64_t                offset;
    uint64_t                length;
    stateid4                *stateid;
} pnfs_layoutreturn_args;

typedef struct __pnfs_layoutreturn_res {
    enum nfsstat4           status;
    /* case NFS4_OK: */
    bool_t                  stateid_present;
    /* case true: */
    stateid4                stateid;
} pnfs_layoutreturn_res;


/* GETDEVICEINFO */
typedef struct __pnfs_getdeviceinfo_args {
    unsigned char           *deviceid;
    enum pnfs_layout_type   layout_type;
    uint32_t                maxcount;
    bitmap4                 notify_types;
} pnfs_getdeviceinfo_args;

typedef struct __pnfs_getdeviceinfo_res_ok {
    pnfs_file_device        *device;
    bitmap4                 notification;
} pnfs_getdeviceinfo_res_ok;

typedef struct __pnfs_getdeviceinfo_res {
    enum nfsstat4           status;
    union {
    /* case NFS4_OK: */
        pnfs_getdeviceinfo_res_ok res_ok;
    /* case NFS4ERR_TOOSMALL: */
       uint32_t             mincount;
    /* default: void; */
    } u;
} pnfs_getdeviceinfo_res;


/* nfs41_ops.c */
int nfs41_exchange_id(
    IN nfs41_rpc_clnt *rpc,
    IN client_owner4 *owner,
    IN uint32_t flags_in,
    OUT nfs41_exchange_id_res *res_out);

int nfs41_create_session(
    IN nfs41_client *clnt,
    OUT nfs41_session *session);

enum nfsstat4 nfs41_bind_conn_to_session(
    IN nfs41_rpc_clnt *rpc,
    IN const unsigned char *sessionid,
    IN enum channel_dir_from_client4 dir);

int nfs41_destroy_session(
    IN nfs41_session *session);

int nfs41_send_sequence(
    IN nfs41_session *session);

enum nfsstat4 nfs41_reclaim_complete(
    IN nfs41_session *session);

int nfs41_lookup(
    IN nfs41_root *root,
    IN nfs41_session *session,
    IN OUT nfs41_abs_path *path,
    OUT OPTIONAL nfs41_path_fh *parent_out,
    OUT OPTIONAL nfs41_path_fh *target_out,
    OUT OPTIONAL nfs41_file_info *info_out,
    OUT nfs41_session **session_out);

int nfs41_open(
    IN nfs41_session *session,
    IN uint32_t allow,
    IN uint32_t deny,
    IN uint32_t create,
    IN uint32_t mode,
    IN OUT nfs41_open_state *state,
    OUT nfs41_file_info *info);

int nfs41_create(
    IN nfs41_session *session,
    IN uint32_t type,
    IN uint32_t mode,
    IN OPTIONAL const char *symlink,
    IN nfs41_path_fh *parent,
    OUT nfs41_path_fh *file);

int nfs41_close(
    IN nfs41_session *session,
    IN nfs41_open_state *state);

int nfs41_write(
    IN nfs41_session *session,
    IN nfs41_path_fh *file,
    IN stateid4 *stateid,
    IN unsigned char *data,
    IN uint32_t data_len,
    IN uint64_t offset,
    IN enum stable_how4 stable,
    OUT uint32_t *bytes_written,
    OUT nfs41_write_verf *verf);

int nfs41_read(
    IN nfs41_session *session,
    IN nfs41_path_fh *file,
    IN stateid4 *stateid,
    IN uint64_t offset,
    IN uint32_t count,
    OUT unsigned char *data_out,
    OUT uint32_t *data_len_out,
    OUT bool_t *eof_out);

int nfs41_commit(
    IN nfs41_session *session,
    IN nfs41_path_fh *file,
    IN uint64_t offset,
    IN uint32_t count,
    IN bool_t do_getattr);

int nfs41_lock(
    IN nfs41_session *session,
    IN nfs41_open_state *open_state,
    IN stateid4 *lock_state OPTIONAL,
    IN uint32_t type,
    IN uint64_t offset,
    IN uint64_t length,
    OUT stateid4 *stateid_out);

int nfs41_test_lock(
    IN nfs41_session *session,
    IN nfs41_open_state *state,
    IN uint32_t type,
    IN uint64_t offset,
    IN uint64_t length);

int nfs41_unlock(
    IN nfs41_session *session,
    IN nfs41_open_state *open_state,
    IN OUT stateid4 *lock_state,
    IN uint64_t offset,
    IN uint64_t length);

stateid4* nfs41_lock_stateid_copy(
    IN nfs41_lock_state *lock_state,
    IN OUT stateid4 *dest);

int nfs41_readdir(
    IN nfs41_session *session,
    IN nfs41_path_fh *file,
    IN bitmap4 *attr_request,
    IN nfs41_readdir_cookie *cookie,
    OUT unsigned char *entries,
    IN OUT uint32_t *entries_len,
    OUT bool_t *eof_out);

void init_getattr_request(
    OUT bitmap4 *attr_request);

int nfs41_getattr(
    IN nfs41_session *session,
    IN OPTIONAL nfs41_path_fh *file,
    IN bitmap4 *attr_request,
    OUT nfs41_file_info *info);

/* getattr.c */
int nfs41_cached_getattr(
    IN nfs41_session *session,
    IN nfs41_path_fh *file,
    OUT nfs41_file_info *info);

int nfs41_remove(
    IN nfs41_session *session,
    IN nfs41_path_fh *parent,
    IN const nfs41_component *target);

int nfs41_rename(
    IN nfs41_session *session,
    IN nfs41_path_fh *src_dir,
    IN const nfs41_component *src_name,
    IN nfs41_path_fh *dst_dir,
    IN const nfs41_component *dst_name);

int nfs41_setattr(
    IN nfs41_session *session,
    IN nfs41_path_fh *file,
    IN stateid4 *stateid,
    IN nfs41_file_info *info);

int nfs41_link(
    IN nfs41_session *session,
    IN nfs41_path_fh *src,
    IN nfs41_path_fh *dst_dir,
    IN const nfs41_component *target,
    OUT OPTIONAL nfs41_path_fh *link_out);

/* symlink.c */
int nfs41_symlink_target(
    IN nfs41_session *session,
    IN nfs41_path_fh *file,
    OUT nfs41_abs_path *target);

int nfs41_symlink_follow(
    IN nfs41_root *root,
    IN nfs41_session *session,
    IN nfs41_path_fh *symlink,
    OUT nfs41_file_info *info);

int nfs41_readlink(
    IN nfs41_session *session,
    IN nfs41_path_fh *file,
    IN uint32_t max_len,
    OUT char *link_out,
    OUT uint32_t *len_out);

int nfs41_access(
    IN nfs41_session *session,
    IN nfs41_path_fh *file,
    IN uint32_t requested,
    OUT uint32_t *supported OPTIONAL,
    OUT uint32_t *access OPTIONAL);

int nfs41_delegreturn(
    IN nfs41_session *session,
    IN nfs41_path_fh *file,
    IN stateid4 *stateid);

enum nfsstat4 nfs41_fs_locations(
    IN nfs41_session *session,
    IN nfs41_path_fh *parent,
    IN const nfs41_component *name,
    OUT fs_locations4 *locations);


enum nfsstat4 pnfs_rpc_layoutget(
    IN nfs41_session *session,
    IN nfs41_path_fh *file,
    IN stateid4 *state,
    IN enum pnfs_iomode iomode,
    IN uint64_t offset,
    IN uint64_t length,
    OUT pnfs_file_layout *layout);

enum nfsstat4 pnfs_rpc_layoutcommit(
    IN nfs41_session *session,
    IN nfs41_path_fh *file,
    IN stateid4 *stateid,
    IN uint64_t offset,
    IN uint64_t length,
    IN OPTIONAL uint64_t *new_last_offset,
    IN OPTIONAL nfstime4 *new_time_modify);

enum nfsstat4 pnfs_rpc_layoutreturn(
    IN nfs41_session *session,
    IN nfs41_path_fh *file,
    IN pnfs_file_layout *layout);

enum nfsstat4 pnfs_rpc_getdeviceinfo(
    IN nfs41_session *session,
    IN unsigned char *deviceid,
    OUT pnfs_file_device *device);

#endif /* !__NFS41_NFS_OPS_H__ */
