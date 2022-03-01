#ifndef __TIME_RAND_HPP__
#define __TIME_RAND_HPP__

#include <sys/time.h>
#include <math.h>

namespace trand {
    /* Return a random integer between 0 and RAND_MAX inclusive.  */
    int trand(){
        timeval t;
        
        gettimeofday(&t, NULL);
        srand(t.tv_usec);

        return rand();
    }

    /* Return a random integer between a and b inclusive.  */
    int trandrange(int a, int b){
        if (a > b){
            int x = a;
            a = b;
            b = x;
        }

        return (trand() % (b-a)) + a;
    }

    /* Return a random boolean number */
    bool trandbool(){
        return trand()%2 == 0;
    }

    /* Return a random boolean number with probability p of being true*/
    bool trandbool(float p){
        p = 1/p;
        return trand()%(int)p == 0;
    }
}

#endif