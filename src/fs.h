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
 * if (fs_touch(..) == FS_EFILE)
 *   printf("%s", strerror(errno));
 */

#ifndef __FS_H
#define __FS_H

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "buf.h"
#include "bool.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef FILE fs_t;

typedef enum {
    FS_OK = 0,
    FS_EFILE = 1,
    FS_ENOMEM = 2,
} fs_error_t;

fs_t *fs_open(const char *, const char *);
int fs_close(fs_t *);
int fs_touch(const char *);
int fs_remove(const char *);
int fs_read(buf_t *, const char *, size_t);
int fs_write(const char *, buf_t *);
int fs_append(const char *, buf_t *);
int fs_exists(const char *);
int fs_isdir(const char *);
int fs_isfile(const char *);
int fs_rename(const char *, const char *);
int fs_mkdir(const char *, mode_t);
int fs_rmdir(const char *);
int fs_readdir(const char *);

#ifdef __cplusplus
}
#endif

#endif
