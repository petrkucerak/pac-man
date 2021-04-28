/*******************************************************************
  Program to read terminal to frame buffer on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  terminal_read.h      - simple program to read terminal in raw mode

  (C) Copyright 2021 by Lukas Nejezchleb
      e-mail:   nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/
#ifndef TERMINAL_READ_H
#define TERMINAL_READ_H

void *input_thread(void *);

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
*/
