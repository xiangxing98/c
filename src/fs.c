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

#include "fs.h"

/**
 * Open a file stream.
 */
fs_t *
fs_open(const char *path, const char *mode)
{
    return fopen(path, mode);
}

/**
 * Close a file stream.
 */
int
fs_close(fs_t *stream)
{
    return fclose(stream);
}

/**
 * Touch a file.
 */
int
fs_touch(const char *path)
{
    fs_t *stream = fs_open(path, "w");
    if (stream == NULL)
        return FS_EFILE;
    return fs_close(stream);
}

/**
 * Remove a file.
 */
int
fs_remove(const char *path)
{
    if (remove(path) != 0)
        return FS_EFILE;
    return FS_OK;
}

/**
 * Read file into buffer.
 */
int
fs_read(buf_t *buf, const char *path, size_t unit)
{
    assert(buf != NULL && path != NULL);
    assert(buf->size <= buf->cap);

    fs_t *stream = fs_open(path, "r");

    if (stream == NULL)
        return FS_EFILE;

    int bytes;

    while (1) {
        if (buf_grow(buf, buf->size + unit) != BUF_OK)
            return FS_ENOMEM;
        bytes = fread(buf->data + buf->size, sizeof(uint8_t),
                buf->cap - buf->size, stream);

        if (bytes <= 0)
            break;

        buf->size += bytes;
    }
    return fs_close(stream);
}

/**
 * Write buffer to file (with mode).
 */
int
_fs_write(const char *path, buf_t *buf, const char *mode)
{
    assert(buf != NULL && path != NULL &&
            strcmp("r", mode) != 0);

    fs_t *stream = fs_open(path, mode);

    if (stream == NULL)
        return FS_EFILE;

    if (fwrite(buf->data, sizeof(uint8_t), buf->size, stream) != buf->size)
        return FS_EFILE;

    return fs_close(stream);
}

/**
 * Write buffer to file (w).
 */
int
fs_write(const char *path, buf_t *buf)
{
    return _fs_write(path, buf, "w");
}

/**
 * Append buffer to file (w).
 */
int
fs_append(const char *path, buf_t *buf)
{
    return _fs_write(path, buf, "a");
}

/**
 * Test if path exists.
 */
bool
fs_exists(const char *path)
{
    struct stat st;
    if (stat(path, &st) == 0)
        return true;
    return false;
}

/**
 * Test if path is a directory.
 */
bool
fs_isdir(const char *path)
{
    struct stat st;

    if (stat(path, &st) == 0 && (st.st_mode & S_IFDIR))
        return true;
    return false;
}

/**
 * Test if path is a file.
 */
bool
fs_isfile(const char *path)
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
fs_rename(const char *old, const char *new)
{
    if (rename(old, new) != 0)
        return FS_EFILE;
    return FS_OK;
}

/**
 * Make a directory.
 */
int
fs_mkdir(const char *path, mode_t mode)
{
    if (mkdir(path, mode) != 0)
        return FS_EFILE;
    return FS_OK;
}

/**
 * Remove a directory.
 */
int
fs_rmdir(const char *path)
{
    if (rmdir(path) != 0)
        return FS_EFILE;
    return FS_OK;
}
