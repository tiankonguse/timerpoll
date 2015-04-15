/*************************************************************************
  > File Name: timer_poll.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年04月15日 20:23:31
***********************************************************************/

#include "timer_poll.h"


/*
    增加一个定时任务
*/
int timers_poll::timers_poll_add_timer(timer* ptimer) {
    int timer_id = ptimer->timer_get_id();
    
    struct epoll_event ev;
    ev.data.fd = timer_id;
    ev.events = EPOLLIN | EPOLLET;
    
    timersMap[timer_id] = ptimer;
    
    epoll_ctl(epfd, EPOLL_CTL_ADD, timer_id, &ev);
    
    ptimer->timer_start();
    
    return 0;
}


/*
    删除定时任务
*/
int timers_poll::timers_poll_del_timer(timer* ptimer) {
    int timer_id = ptimer->timer_get_id();
    
    struct epoll_event ev;
    ev.data.fd = timer_id;
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_DEL, timer_id, &ev);
    
    timersMap.erase(timer_id);
    
    return 0;
}

/*
    定时器开始运行
*/
int timers_poll::run() {
    char buf[MAXFDS] = { 0 };
    for (; active;) {
        struct epoll_event events[MAXFDS];

        memset(events, 0, sizeof(events));
        int nfds = epoll_wait(epfd, events, MAXFDS, 0);
        for (int i = 0; i < nfds; ++i) {
            std::map<int, timer*>::iterator itmp = timersMap.find(events[i].data.fd);
            if (itmp != timersMap.end()) {
                //timer ptimer = itmp->second;
                while (read(events[i].data.fd, buf, MAXFDS) > 0) {
                    //read all data
                }
                
                if (itmp->second->get_user_frame() == NULL) {
                    ((timer_callback) itmp->second->get_user_callback())(itmp->second);
                } else {
                    ((class_timer_callback) itmp->second->get_user_callback())(itmp->second->get_user_frame(),itmp->second);
                }

            }
        }
    }
    return 0;
}

/*
    生成定时器对象
*/
timers_poll::timers_poll() {
    active = 1;
}

/*
    初始化定时器
*/
void timers_poll::init(int max_num) {
    epfd = epoll_create(max_num);
}




/*
    关闭定时器
*/
int timers_poll::timers_poll_deactive() {
    active = 0;
    return 0;
}

/*
    定时器死亡了
*/
timers_poll::~timers_poll() {
}

/*
    当前存在的定时任务个数
*/
int timers_poll::size() {
    return timersMap.size();
}