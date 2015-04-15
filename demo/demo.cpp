/*************************************************************************
  > File Name: demo.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年04月15日 20:57:51
***********************************************************************/
#include <cstdlib>
#include <iostream>

#include "timer_poll.h"

using namespace std;

timers_poll my_timers;

int callback(timer* ptimer) {
    printf("timer id=%d:%s\n", ptimer->timer_get_id(), (char *) ptimer->timer_get_userdata());
    my_timers.timers_poll_del_timer(ptimer);
    return 0;
}

void *thread_fun(void *data) {
    timers_poll *my_timers = (timers_poll *) data;
    my_timers->run();
}

#ifndef DEMO_LOG
#define DEMO_LOG(t)  do { printf("t(%u) = %u\n", __LINE__, (uint) time(NULL)); } while (0)
#endif
/*
 *
 */
int main(int argc, char** argv) {

    my_timers.init(128);
    pthread_t thread_id = 0;
    pthread_create(&thread_id, NULL, thread_fun, &my_timers);

    DEMO_LOG(0);

    timer timer1(3.05, (void* )callback, (void *) "hello 1", 0);
    timer timer2(4.10, (void* )callback, (void *) "hello 2", 0);
    DEMO_LOG(0);
    my_timers.timers_poll_add_timer(&timer1);
    DEMO_LOG(0);
    my_timers.timers_poll_add_timer(&timer2);
    DEMO_LOG(0);
    sleep(5);
    DEMO_LOG(0);


    my_timers.timers_poll_deactive();
    pthread_join(thread_id, NULL);
    DEMO_LOG(0);
    return 0;
}
