/**
 * Copyright (c) 2015, Chao Wang (hit9 <hit9@icloud.com>)
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/**
 * File handling utils.
 *
 * if (hfs_touch(..) == HFS_EFILE)
 *   printf("%s", strerror(errno));
 */

#ifndef __HFS_H
#define __HFS_H

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "hbuf.h"
#include "hbool.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef FILE hfs_t;

typedef enum {
    HFS_OK = 0,
    HFS_EFILE = 1,
    HFS_ENOMEM = 2,
} hfs_error_t;

hfs_t *hfs_open(const char *, const char *);
int hfs_close(hfs_t *);
int hfs_touch(const char *);
int hfs_remove(const char *);
int hfs_read(hbuf_t *, const char *, size_t);
int hfs_write(const char *, hbuf_t *);
int hfs_append(const char *, hbuf_t *);
int hfs_exists(const char *);
int hfs_isdir(const char *);
int hfs_isfile(const char *);
int hfs_rename(const char *, const char *);
int hfs_mkdir(const char *, mode_t);
int hfs_rmdir(const char *);
int hfs_readdir(const char *);

#ifdef __cplusplus
}
#endif

#endif
