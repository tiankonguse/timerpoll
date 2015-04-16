# epoll定时器

这是一个简单易用的epoll定时器。  


## 使用说明

这里仅显示核心代码，线程相关的暂时不考虑了。  

```cpp
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
```

```text
t(39) = 1429103486
t(43) = 1429103486
t(45) = 1429103486
t(47) = 1429103486
timer id=4:hello 1
timer id=5:hello 2
t(49) = 1429103491
t(54) = 1429103491
```

具体可以参考 [demo](demo/demo.cpp)。

## 不足

目前，这个定时器需要用户自己开一个线程来管理这个epoll定时器。  
后续可以考虑把线程封装起来，让用户直接定义对象，添加时间和回调函数即可。  

目标是下面的样子  

```cpp
timers_poll my_timers(128);

my_timers.add(3.05, (void* )callback, (void *) "hello 1", 0);
```

这样的话，将会非常简单了。  

或者可以考虑定义一个定时器全局变量，需要的时候直接添加回调函数即可。  

那就是下面的样子  

```cpp
my_timers.add(3.05, (void* )callback, (void *) "hello 1", 0);
```

如果支持动态生成函数的话，就是这个样子了。  

```javascript
setTimeout(function(){
    string data = "hello 1";    
}, 3.05)
```

## 依赖知识

目前不考虑多线程的话，只需要epoll和timerfd两个知识点。  

关于 epoll 可以参考这里学习 [epoll初级笔记1][epoll-base-study-one].  

关于 timerfd 可以参考这里学习 [timerfd 初级笔记1][timerfd-base-stydy-one]  

[timerfd-base-stydy-one]: http://github.tiankonguse.com/blog/2015/04/15/timerfd-base-stydy-one/
[epoll-base-study-one]: http://github.tiankonguse.com/blog/2015/04/14/epoll-base-study-one/
