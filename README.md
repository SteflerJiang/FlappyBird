# FlappyBird


一直要搭建一个cocos lua的工程，可是怎么搞都有问题，太麻烦了，还是决定用c++来写吧，不过开发效率上还是lua快多了，不用编译，不用被各种简单的问题所困扰。
讲讲c++优缺点吧

## 优点
1. c++的api说明比较清楚，官方[api链接](http://api.cocos.com/cn/index.html)中c++的更加明确。
2. c++的使用的人更多一些，网上的资料也更多一些，出了问题更容易找到帮助和答案。
3. c++的api可以直接看代码，如果是用vs或者Xcode写代码的话，直接进入到源码看实现，比起lua来说方便太多。
4. 代码在每次更改后都需要重新编译，这样有代码问题在运行前就会暴露出来。
5. 可以打断点，单步调试。

## 缺点
1. 太慢太慢了
2. 很繁琐，写一个类都需要从头文件开始，各种include还有命名空间。定义一个函数要现在头文件中定义，再去cpp文件中去实现。脚本写多了，再去写cpp确实不太习惯。
3. 我之前在cpp中想用一个`string.format()`函数都没找到，搞了好久还是用曲线救过的方法，这里顺便也记录一下吧。是把字符串和数字相加的，等以后找到更好的方法我再来记录吧。

```cpp
std::string s = "score : ";
std::ostringstream os;
os << s << score;
s = os.str();
scoreLabel->setString(s);
```

不容易啊，找到一个可以格式化输出的方法，使用cocos提供的__String类，如果采用cocos提供的类的话，最好用create的方式，区别于c++本身的new
```cpp
    static __String* create(const std::string& str);
    static __String* createWithFormat(const char* format, ...) CC_FORMAT_PRINTF(1, 2);
    static __String* createWithData(const unsigned char* pData, size_t nLen);
    static __String* createWithContentsOfFile(const std::string& filename);
```
这样的话，用下面的方式，哎，终于可以格式化输出了，曲线救国啊
```cpp
auto ss = __String::createWithFormat("score : %d", score);
scoreLabel->setString(ss->getCString());
```
先这样，关于游戏的内容等有空了再写。

