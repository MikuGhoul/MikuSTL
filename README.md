# MikuSTL

* 一个不会模板的辣鸡写的STL

#### 已完成
* list

#### 性能测试

容器                |   数量    |   时间
------------        |  ---------| --------
Miku::list<int>     | 10万      | 49ms
std::list<int>(MSVC) | 10万     | 131ms
Miku::list<int>     | 100万      | 486ms
std::list<int>(MSVC) | 100万     | 1314ms
Miku::list<int>     | 1000万      | 4851ms
std::list<int>(MSVC) | 1000万     | 13096ms

