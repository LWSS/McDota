/*
 * Copyright (c) 2012-2018 Zeex
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#define _GNU_SOURCE
#include <stddef.h>
#include <unistd.h>
#include <sys/mman.h>
#include <link.h>

static int flags = 0;
static void *addr = NULL;

static int callback(struct dl_phdr_info *info, size_t size, void *data) {
  void *starting_addr = 0;
  void *ending_addr = 0;
  for( int i = 0; i < info->dlpi_phnum; i++ ){
    const ElfW(Phdr) *hdr = &info->dlpi_phdr[i];
    if( hdr->p_memsz ){
      starting_addr = (void*)info->dlpi_addr + hdr->p_vaddr;
      ending_addr = starting_addr + hdr->p_memsz;
      if( starting_addr <= addr && ending_addr >= addr ){
        /* PF_ flags and PROT_ flags are NOT the same! REEE */
        if( hdr->p_flags & PF_R ){
          flags |= PROT_READ;
        }
        if( hdr->p_flags & PF_W ){
          flags |= PROT_WRITE;
        }
        if( hdr->p_flags & PF_X ){
          flags |= PROT_EXEC;
        }
      }
    }
  }
}

/* Assuming the entire region has the same flags. */
void *subhook_unprotect(void *address, size_t size, unsigned int *orig_flags) {
  long pagesize;

  pagesize = sysconf(_SC_PAGESIZE);
  address = (void *)((long)address & ~(pagesize - 1));

  if( orig_flags ) {
    flags = 0;
    addr = address;
    dl_iterate_phdr( callback, NULL );
    *orig_flags = flags;
  }

  if (mprotect(address, size, PROT_READ | PROT_WRITE | PROT_EXEC) == 0) {
    return address;
  } else {
    return NULL;
  }
}

void *subhook_protect(void *address, size_t size, unsigned int flags) {
  long pagesize;

  pagesize = sysconf(_SC_PAGESIZE);
  address = (void *)((long)address & ~(pagesize - 1));

  if( mprotect(address, size, PF_X | PF_R) == 0 ){
    return address;
  } else {
    return NULL;
  }
}
