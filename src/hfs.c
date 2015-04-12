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

#include "hfs.h"

/**
 * Open a file stream.
 */
hfs_t *
hfs_open(const char *filename, const char *mode)
{
    return fopen(filename, mode);
}

/**
 * Close a file stream.
 */
int
hfs_close(hfs_t *stream)
{
    return fclose(stream);
}

/**
 * Touch a file.
 */
int
hfs_touch(const char *filename)
{
    hfs_t *stream = hfs_open(filename, "w");
    if (stream == NULL)
        return HFS_EFILE;
    return hfs_close(stream);
}

/**
 * Read file into buffer.
 */
int
hfs_read(hbuf_t *buf, const char *path, size_t unit)
{
    assert(buf != NULL && path != NULL);
    assert(buf->size <= buf->cap);

    hfs_t *stream = hfs_open(path, "r");

    if (stream == NULL)
        return HFS_EFILE;

    int bytes;

    while (1) {
        if (hbuf_grow(buf, buf->size + unit) != HBUF_OK)
            return HFS_ENOMEM;
        bytes = fread(buf->data + buf->size, sizeof(uint8_t),
                buf->cap - buf->size, stream);

        if (bytes <= 0)
            break;

        buf->size += bytes;
    }
    return hfs_close(stream);
}

/**
 * Write buffer to file (with mode).
 */
int
_hfs_write(const char *path, hbuf_t *buf, const char *mode)
{
    assert(buf != NULL && path != NULL &&
            strcmp("r", mode) != 0);

    hfs_t *stream = hfs_open(path, mode);

    if (stream == NULL)
        return HFS_EFILE;

    if (fwrite(buf->data, sizeof(uint8_t), buf->size, stream) != buf->size)
        return HFS_EFILE;

    return hfs_close(stream);
}

/**
 * Write buffer to file (w).
 */
int
hfs_write(const char *path, hbuf_t *buf)
{
    return _hfs_write(path, buf, "w");
}

/**
 * Append buffer to file (w).
 */
int
hfs_append(const char *path, hbuf_t *buf)
{
    return _hfs_write(path, buf, "a");
}
