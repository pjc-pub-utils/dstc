// Copyright (C) 2018, Jaguar Land Rover
// This program is licensed under the terms and conditions of the
// Mozilla Public License, version 2.0.  The full text of the
// Mozilla Public License is at https://www.mozilla.org/MPL/2.0/
//
// Author: Magnus Feuer (mfeuer1@jaguarlandrover.com)
//
// Running example code from README.md in https://github.com/PDXOSTC/dstc
//

#include <stdio.h>
#include <stdlib.h>
#include "dstc.h"


// Generate deserializer for multicast packets sent by the client
// The deserializer decodes the incoming data and calls the
// no_argument_function() function in this file.
//
DSTC_SERVER(no_argument_function)
DSTC_SERVER(one_argument_function, int,)

int no_arg_called = 0;
int one_arg_called = 0;

//
// Print out a hello-world type message
// Invoked by deserilisation code generated by DSTC_SERVER() above.
//
void no_argument_function(void)
{
    puts("no_argument_function(): Called");
    no_arg_called = 1;
}

void one_argument_function(int nr)
{
    printf("no_argument_function(%d): Called\n", nr);
    if (nr != 4711) {
        printf("Wanted 4711 as a single argument. Got %d\n", nr);
        exit(255);
    }
    one_arg_called = 1;
}

int main(int argc, char* argv[])
{
    // Process incoming events forever
    while(!no_arg_called || !one_arg_called)
        dstc_process_events(-1);
}
