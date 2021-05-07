/**
 * @file terminal_read.h
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz)
 * @brief Module housing the thread function for reading the terminal in nonblocking mode and setting the last key pressed variable
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef TERMINAL_READ_H
#define TERMINAL_READ_H

/**
 * @brief 
 * 
 * @return void* 
 */
void *input_thread(void *);

/**
 * @brief 
 * 
 * @param fd
 * @param timeout_ms
 * @param c
 * @return int 
 */
int serial_getc_timeout(int fd, int timeout_ms, unsigned char *c);

#endif
