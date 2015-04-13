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
hfs_open(const char *path, const char *mode)
{
    return fopen(path, mode);
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
hfs_touch(const char *path)
{
    hfs_t *stream = hfs_open(path, "w");
    if (stream == NULL)
        return HFS_EFILE;
    return hfs_close(stream);
}

/**
 * Remove a file.
 */
int
hfs_remove(const char *path)
{
    if (remove(path) != 0)
        return HFS_EFILE;
    return HFS_OK;
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

/**
 * Test if path exists.
 */
int
hfs_exists(const char *path)
{
    struct stat st;
    if (stat(path, &st) == 0)
        return true;
    return false;
}

/**
 * Test if path is a directory.
 */
int
hfs_isdir(const char *path)
{
    struct stat st;

    if (stat(path, &st) == 0 && (st.st_mode & S_IFDIR))
        return true;
    return false;
}

/**
 * Test if path is a file.
 */
int
hfs_isfile(const char *path)
{
    struct stat st;

    if(stat(path, &st) == 0 && (st.st_mode & S_IFREG))
        return true;
    return false;
}

/**
 * Rename file/directory.
 */
int
hfs_rename(const char *old, const char *new)
{
    if (rename(old, new) != 0)
        return HFS_EFILE;
    return HFS_OK;
}

/**
 * Make a directory.
 */
int
hfs_mkdir(const char *path, mode_t mode)
{
    if (mkdir(path, mode) != 0)
        return HFS_EFILE;
    return HFS_OK;
}

/**
 * Remove a directory.
 */
int
hfs_rmdir(const char *path)
{
    if (rmdir(path) != 0)
        return HFS_EFILE;
    return HFS_OK;
}
