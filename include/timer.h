/*************************************************************************
  > File Name: timer.h
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年04月15日 20:18:37
***********************************************************************/

#ifndef TIMER__H_
#define TIMER__H_

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

class timer {
    public:
        /*
            默认构造函数
        */
        timer();
        
        /*
            定时回调普通函数
            @internal_value 定时时间
            @callback 回调函数，对应 timer_callback
            @data 回调函数的参数
            @rep 是否重复定时
        */
        timer(double internal_value, void* callback, void *data, int rep);

        /*
            定时回调对象有关的函数
            @internal_value 定时时间
            @callback 回调函数，对应 timer_callback
            @frame 对象指针 class_timer_callback
            @data 回调函数的参数
            @rep 是否重复定时
        */
        timer(double internal_value, void* callback, void* frame, void *data, int rep);

        /*
            拷贝函数
            @ptimer 时间对象
        */
        timer(const timer &ptimer);
        
        /*
            拷贝函数
        */
        timer & operator=(const timer &ptimer);
        
        /*
            启动定时器
        */
        int timer_start();
        
        /*
            停止定时器
        */
        int timer_stop();
        
        /*
            修改定时时间
        */
        int timer_modify_internal(double timer_internal);

    public:
    
        /*
            得到定时器的 fd
        */
        int timer_get_id();

        /*
            得到回调函数的参数
        */
        void *timer_get_userdata();

        /*
            清空指针
        */
        void timer_set_null();

        /*
            删除定时器时，需要把fd设置为无效
        */
        void timer_del();

        /*
            得到回调函数指针
        */
        void* get_user_callback() ;

        /*
            对象指针
        */
        void* get_user_frame() ;

        /*
            当前fd是否有效
        */
        bool isValidFd();

        /*
            定时器死亡
        */
        ~timer();

    private:

        /*
            设置指定的 fd为非阻塞模式
            @fd 需要设置的fd
        */
        bool setNonBlock(int fd);

    private:
        /*
            定时时间
        */
        double timer_internal;
        
        /*
            回调函数
        */
        void* cb;
        
        /*
            当前定时器的fd
        */
        int timer_id;
        
        /*
            定时器是否重复定时
        */
        bool repeat; 
        
        /*
            回调函数的参数
        */
        void *userdata;
        
        /*
            如果是对象类型的回调函数，代表对象指针
        */
        void* frame;
        
        /*
            fd是否有效
        */
        bool validFd;
};


#endif /* TIMER_H_ */
