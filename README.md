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