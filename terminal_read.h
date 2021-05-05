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

/* Initialisation of the thread:
initialising mutex

    pthread_mutex_t mtx;

inside main function calling

    pthread_mutex_init(&mtx, NULL); // initialize mutex with default attributes
    read_thread_data_type read_thread_data = {.quit = false, .last_read = ' '};
    pthread_t read_thread;
    pthread_create(read_thread, NULL, input_thread, &read_thread_data);

to acces read_data from terminal
    pthread_mutex_lock(&mtx);
    variable_to_load_into = read_thread_data.last_read;
    pthread_mutex_unlock(&mtx);
here the data from variable_to_load_into can be used
    
to terminate thread:
    pthread_mutex_lock(&mtx);
    read_thread_data.quit = true; 
    pthread_mutex_unlock(&mtx);
    pthread_join(read_thread, NULL); //wait for thread to join
    pthread_mutex_destroy(&mtx);
*/
