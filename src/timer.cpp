/*************************************************************************
  > File Name: timer.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年04月15日 20:22:38
***********************************************************************/

#include "timer.h"

/*
    默认构造函数
*/
timer::timer() :
        timer_internal(0.0), cb(0), timer_id(0), repeat(0), userdata(0), frame(NULL) {
    validFd = false;
}

/*
    定时回调普通函数
    @internal_value 定时时间
    @callback 回调函数，对应 timer_callback
    @data 回调函数的参数
    @rep 是否重复定时
*/
timer::timer(double internal_value, void* callback, void *data, int rep) :
        timer_internal(internal_value), cb(callback), repeat(rep), userdata(data), frame(NULL) {
    validFd = true;
    timer_id = timerfd_create(CLOCK_REALTIME, 0);
    setNonBlock(timer_id);
}

/*
    定时回调对象有关的函数
    @internal_value 定时时间
    @callback 回调函数，对应 timer_callback
    @frame 对象指针 class_timer_callback
    @data 回调函数的参数
    @rep 是否重复定时
*/
timer::timer(double internal_value, void* callback, void* frame, void *data, int rep) :
        timer_internal(internal_value), cb(callback), repeat(rep), userdata(data), frame(frame) {
    validFd = true;
    timer_id = timerfd_create(CLOCK_REALTIME, 0);
    setNonBlock(timer_id);
}

/*
    拷贝函数
    @ptimer 时间对象
*/
timer::timer(const timer& ptimer) {
    timer_internal = ptimer.timer_internal;
    cb = ptimer.cb;
    frame = ptimer.frame;
    timer_id = ptimer.timer_id;
    repeat = ptimer.repeat;
    userdata = ptimer.userdata;
    validFd = false;
}

/*
    拷贝函数
*/
timer & timer::operator =(const timer& ptimer) {
    if (this == &ptimer) {
        return *this;
    }

    timer_internal = ptimer.timer_internal;
    cb = ptimer.cb;
    frame = ptimer.frame;
    timer_id = ptimer.timer_id;
    repeat = ptimer.repeat;
    userdata = ptimer.userdata;
    validFd = false;
    return *this;
}


/*
    定时器死亡
*/
timer::~timer() {
    timer_stop();
}

/*
    启动定时器
*/
int timer::timer_start() {
    struct itimerspec ptime_internal;
    memset(&ptime_internal, 0, sizeof(ptime_internal));
    ptime_internal.it_value.tv_sec = (int) timer_internal;
    ptime_internal.it_value.tv_nsec = (timer_internal - (int) timer_internal) * 1000000;
    if (repeat) {
        ptime_internal.it_interval.tv_sec = ptime_internal.it_value.tv_sec;
        ptime_internal.it_interval.tv_nsec = ptime_internal.it_value.tv_nsec;
    }

    timerfd_settime(timer_id, 0, &ptime_internal, NULL);
    return 0;
}

/*
    停止定时器
*/
int timer::timer_stop() {
    close(timer_id);
    return 0;
}

/*
    修改定时时间
*/
int timer::timer_modify_internal(double timer_internal) {
    this->timer_internal = timer_internal;
    timer_start();
    return 0;
}


/*
    设置指定的 fd为非阻塞模式
    @fd 需要设置的fd
*/
bool timer::setNonBlock(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    if (-1 == fcntl(fd, F_SETFL, flags)) {
        return false;
    }
    return true;
}

/*
    得到定时器的 fd
*/
int timer::timer_get_id() {
    return timer_id;
}

/*
    得到回调函数的参数
*/
void * timer::timer_get_userdata() {
    return userdata;
}

/*
    清空指针
*/
void timer::timer_set_null() {
    userdata = NULL;
}

/*
    删除定时器时，需要把fd设置为无效
*/
void timer::timer_del() {
    validFd = false;
}

/*
    得到回调函数指针
*/
void* timer::get_user_callback() {
    return cb;
}

/*
    对象指针
*/
void* timer::get_user_frame() {
    return frame;
}

/*
    当前fd是否有效
*/
bool timer::isValidFd() {
    return validFd;
}
