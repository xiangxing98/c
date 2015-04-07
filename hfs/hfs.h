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
 */

#ifndef __HFS_H
#define __HFS_H

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "hbuf.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HFS_BUF_UNIT 128
#define HFS_FILE_BUF_UNIT 1024

typedef FILE hfs_t;

hfs_t *hfs_open(const char *, const char *);
int hfs_close(hfs_t *);
int hfs_touch(const char *);
int hfs_read(hbuf_t *, const char *);
int hfs_write(const char *, hbuf_t *);

#ifdef __cplusplus
}
#endif

#endif
