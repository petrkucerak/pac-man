/**
 * @file mzapo_phys.h
 * @author Pavel Pisa (pisa@cmp.felk.cvut.cz)
 * @brief Module for mapping the the peripheral adresses to the memory
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MZAPO_PHYS_H
#define MZAPO_PHYS_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

   void *map_phys_address(off_t region_base, size_t region_size, int opt_cached);

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif /*MZAPO_PHYS_H*/
