/**
 * @file mzapo_phys.c
 * @author Pavel Pisa (pisa@cmp.felk.cvut.cz)
 * @brief Module for mapping the the peripheral adresses to the memory
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define _POSIX_C_SOURCE 200112L

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "mzapo_phys.h"

const char *map_phys_memdev = "/dev/mem";

void *map_phys_address(off_t region_base, size_t region_size, int opt_cached)
{
  unsigned long mem_window_size;
  unsigned long pagesize;
  unsigned char *mm;
  unsigned char *mem;
  int fd;

  fd = open(map_phys_memdev, O_RDWR | (!opt_cached ? O_SYNC : 0));
  if (fd < 0)
  {
    fprintf(stderr, "cannot open %s\n", map_phys_memdev);
    return NULL;
  }

  pagesize = sysconf(_SC_PAGESIZE);

  mem_window_size = ((region_base & (pagesize - 1)) + region_size + pagesize - 1) & ~(pagesize - 1);

  mm = (unsigned char *)mmap(NULL, mem_window_size, PROT_WRITE | PROT_READ,
                             MAP_SHARED, fd, region_base & ~(pagesize - 1));
  mem = mm + (region_base & (pagesize - 1));

  if (mm == MAP_FAILED)
  {
    fprintf(stderr, "mmap error\n");
    return NULL;
  }

  return (void *)mem;
}
