// Copyright (c) 2015-2016 Nuxi, https://nuxi.nl/
//
// SPDX-License-Identifier: BSD-2-Clause

#include <common/errno.h>

#include <wasi/core.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#ifdef __wasilibc_unmodified_upstream // Rename for AT_FDCWD support
int symlinkat(const char *path1, int fd, const char *path2) {
#else
int __wasilibc_nocwd_symlinkat(const char *path1, int fd, const char *path2) {
#endif
  __wasi_errno_t error =
#ifdef __wasilibc_unmodified_upstream
      __wasi_file_symlink(path1, strlen(path1), fd, path2, strlen(path2));
#else
      __wasi_path_symlink(path1, strlen(path1), fd, path2, strlen(path2));
#endif
  if (error != 0) {
    errno = errno_fixup_directory(fd, error);
    return -1;
  }
  return 0;
}
