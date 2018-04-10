# MikuSTL

* 一个不会模板的辣鸡写的STL

#### 已完成
* list
* vector

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
    10万        |  62ms         | 90ms
    100万       | 614ms         | 905ms
    1000万      | 6267ms        | 9108ms


#### 进度备忘
* deque的那个模板构造里uninitialized_copy会失败，已经找到原因了，uninitialized_copy实现里要求random_access_iterator_tag(...说起来traits又是一阵心疼)和operator+

#### 挖的坑
* 自己的Iterator_Traits目前废了，在用std的
* 由于自己的Iterator_Traits废了，导致那几个iterator的tag也没得法子
* 在用std的一些algorithm，uninitialized_copy/uninitialized_fill啥的，等以后弄自己的algorithm再重构吧（可能吧
* [const_]reverse_iterator（我感觉我大概率不会添这个坑...
* 用SFINAE实现的区分重载函数写的有点不优雅（TODO写在MikuList.h了）？
* 测试数据有点弱（能跑就行...(掀桌 ︵┻━┻