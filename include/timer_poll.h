/*************************************************************************
  > File Name: timer_poll.h
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年04月15日 20:16:00
***********************************************************************/
#ifndef TIMER_POLL_H_
#define TIMER_POLL_H_

#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include <pthread.h>
#include <map>

#define MAXFDS 128
#define EVENTS 100


#include "timer.h"


typedef timer* timer_type;
typedef int (*timer_callback)(timer_type); //user callback
typedef int (*class_timer_callback)(void* frame, timer_type); //user callback

class timers_poll {
    public:
        /*
            生成定时器对象
        */
        timers_poll();

        /*
            初始化定时器
        */
        void init(int max_num = MAXFDS);

        /*
            增加一个定时任务
        */
        int timers_poll_add_timer(timer* ptimer);
        
        /*
            删除定时任务
        */
        int timers_poll_del_timer(timer* ptimer);
        
        /*
            定时器开始运行
        */
        int run();

        /*
            关闭定时器
        */
        int timers_poll_deactive();

        /*
            定时器死亡了
        */
        ~ timers_poll();

        /*
            当前存在的定时任务个数
        */
        int size();

    private:
        /*
            epoll定时器fd
        */
        int epfd;
        
        /*
            定时器是否有效
        */
        int active;
        
        /*
            定时器字典表
        */
        std::map<int, timer*> timersMap;
};

#endif /* TIMER_POLL_H_ */
