# MikuSTL

* 一个不会模板的辣鸡写的STL

#### 已完成
* list
* vector
* array
* deque

#### 性能测试

##### list
* `push_back`

    数量        |  Miku::list   |    std::list (MSVC)
    ----------- | --------      |    ----------
    10万        |  49ms         | 131ms
    100万       | 486ms         | 1314ms
    1000万      | 4851ms        | 13096ms


##### vector
* `push_back`

    数量        |  Miku::vector  |    std::vector (MSVC)
    ----------- | --------      |    ----------
    10万        |  ~~62ms~~ 100ms         | 90ms
    100万       | ~~614ms~~ 987ms         | 905ms
    1000万      | ~~6267ms~~  9988ms        | 9108ms

##### deque
* `push_back`

    数量        |  Miku::deque   |    std::deque (MSVC)
    ----------- | --------      |    ----------
    10万        |  19ms         | 119ms
    100万       | 186ms         | 1187ms
    1000万      | 1827ms        | 11861ms

* `push_front`

    数量        |  Miku::deque   |    std::deque (MSVC)
    ----------- | --------      |    ----------
    10万        |  18ms         | 118ms
    100万       | 181ms         | 1185ms
    1000万      | 1809ms        | 11764ms

#### 进度备忘
* rb-tree的base iterator 和 iterator的重载时候怎么转型

#### 挖的坑
* 自己的Iterator_Traits目前废了，在用std的
* 由于自己的Iterator_Traits废了，导致那几个iterator的tag也没得法子
* 在用std的一些algorithm，uninitialized_copy/uninitialized_fill啥的，等以后弄自己的algorithm再重构吧（可能吧
* [const_]reverse_iterator（我感觉我大概率不会添这个坑...
* 用SFINAE实现的区分重载函数写的有点不优雅（TODO写在MikuList.h了）？
* 测试数据有点弱（能跑就行...(掀桌 ︵┻━┻
* list内存泄漏了？
* ~~deque的特判情况太多啦，我设计的问题？？~~
* deque的insert效率有点低，会先copy ctor，然后立刻copy assignment覆盖
    * 这么做是因为真的好写多了（不然真的太多特判了。。
* 重构性能测试的时候发现，我vector的push_back时间增加了**1/2**左右!!!，因为之前是用手写的赋值，现在改成了std::copy, std::fill啥的了。。多了几百万个函数调用，该怎么权衡？
* 看一些stl的实现里，有的迭代器用双层结构，我这有的container没有这样设计
    * [stl中一些迭代器为什么要采用双层结构呢？](https://www.zhihu.com/question/28680184)