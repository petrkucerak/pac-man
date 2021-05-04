/**
 * @file mzapo_parlcd.h
 * @author Pavel Pisa (pisa@cmp.felk.cvut.cz)
 * @brief Module for setting the LCD screen and writing data to it
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MZAPO_PARLCD_H
#define MZAPO_PARLCD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

   void parlcd_write_cr(unsigned char *parlcd_mem_base, uint16_t data);

   void parlcd_write_cmd(unsigned char *parlcd_mem_base, uint16_t cmd);

   void parlcd_write_data(unsigned char *parlcd_mem_base, uint16_t data);

   void parlcd_write_data2x(unsigned char *parlcd_mem_base, uint32_t data);

   void parlcd_delay(int msec);

   void parlcd_hx8357_init(unsigned char *parlcd_mem_base);

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif /*MZAPO_PARLCD_H*/
