/*******************************************************************
  Program to read terminal to frame buffer on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  terminal_read.c      - simple program to read terminal in raw mode

  (C) Copyright 2021 by Lukas Nejezchleb
      e-mail:   nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/
#include "terminal_read.h"
#include "data_structures.h"
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <fcntl.h>

pthread_mutex_t mtx;
#define TERMINAL_TIMEOUT_MS 100

//inside function to read terminal in nonblocking regime
int serial_getc_timeout(int fd, int timeout_ms, unsigned char *c);

void *input_thread(void *d)
{
    read_thread_data_type *data = (read_thread_data_type *)d;
    bool end = false;
    //put terminal into raw mode
    struct termios tio, tioOld;
    tcgetattr(STDIN_FILENO, &tio);
    tioOld = tio; // backup
    cfmakeraw(&tio);
    tio.c_oflag |= OPOST;
    tcsetattr(STDIN_FILENO, TCSANOW, &tio);

    //start reading terminal
    unsigned char c;
    while (!end)
    {
        int r = serial_getc_timeout(STDIN_FILENO, TERMINAL_TIMEOUT_MS, &c);
        if (r > 0)
        {
            pthread_mutex_lock(&mtx);
            data->last_read = c;
            pthread_mutex_unlock(&mtx);
        }
        else if (r < 0)
        {
            //error reading from stdin
            fprintf(stderr, "Error occured when trying to read from stdin\n");
            end = true;
        }
        pthread_mutex_lock(&mtx);
        end = end || data->quit; // check for quit
        pthread_mutex_unlock(&mtx);
    }

    //reset terminal to original mode
    tcsetattr(STDIN_FILENO, TCSANOW, &tioOld);
    return NULL;
}

//inside function to read terminal in nonblocking regime
int serial_getc_timeout(int fd, int timeout_ms, unsigned char *c)
{
    struct pollfd ufdr[1];
    int r = 0;
    ufdr[0].fd = fd;
    ufdr[0].events = POLLIN | POLLRDNORM;
    if ((poll(&ufdr[0], 1, timeout_ms) > 0) &&
        (ufdr[0].revents & (POLLIN | POLLRDNORM)))
    {
        r = read(fd, c, 1);
    }
    return r;
}
