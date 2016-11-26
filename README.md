# 使用C++编写的正则表达式引擎

------

## 目录
[TOC]

------
## 关于本项目
这个项目开始写于2016年10月14日，当时在本科的毕业设计应该些什么，后来在知乎上看到vczh的篇介绍正则表达式的文章，就有了一些想法。整个项目没有任何现有的正则表达式库的代码，全部自己写成，同时有大量的测试，测试的基准是C++11 regex：



------

## 实现思路
整体的思路是先把输入的正则表达式通过算符优先文法判断优先级，然后根据不同的优先级的运算符按照优先级，把每一部分的正则表达翻译成对应的有限状态自动机（分确定有限状态自动机DFA和非确定有限状态自动机NFA）。翻译后的有限状态自动机对应一个有向图，有一个起点（代表起始状态），有一个终点（代表终止状态，多个终点可以把它们用空边连接到唯一的终点上）
进行匹配的时候，记录匹配的信息，通过实时的匹配信息，结合有限状态自动机就可以从一个状态跳转到下一个状态，如果能到达说明匹配成功率

### 1. 正则表达式运行符优先级
\0代表起始或者结束符

|符号|'\0'|' ('|' )'|' .'|' ?'|' *'|' *'|' +'|' {'|' }'|' ['|' ]'|
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|'\0'|'\0'|' ('|' )'|' .'|' ?'|' *'|' *'|' +'|' {'|' }'|' ['|' ]'|
|' ('|'\0'|' ('|' )'|' .'|' ?'|' *'|' *'|' +'|' {'|' }'|' ['|' ]'|
|' )'|'\0'|' ('|' )'|' .'|' ?'|' *'|' *'|' +'|' {'|' }'|' ['|' ]'|
|' .'|'\0'|' ('|' )'|' .'|' ?'|' *'|' *'|' +'|' {'|' }'|' ['|' ]'|
|' ?'|'\0'|' ('|' )'|' .'|' ?'|' *'|' *'|' +'|' {'|' }'|' ['|' ]'|
|' *'|'\0'|' ('|' )'|' .'|' ?'|' *'|' *'|' +'|' {'|' }'|' ['|' ]'|
|' *'|'\0'|' ('|' )'|' .'|' ?'|' *'|' *'|' +'|' {'|' }'|' ['|' ]'|
|' +'|'\0'|' ('|' )'|' .'|' ?'|' *'|' *'|' +'|' {'|' }'|' ['|' ]'|
|' {'|'\0'|' ('|' )'|' .'|' ?'|' *'|' *'|' +'|' {'|' }'|' ['|' ]'|
|' }'|'\0'|' ('|' )'|' .'|' ?'|' *'|' *'|' +'|' {'|' }'|' ['|' ]'|
|' ['|'\0'|' ('|' )'|' .'|' ?'|' *'|' *'|' +'|' {'|' }'|' ['|' ]'|
|' ]'|'\0'|' ('|' )'|' .'|' ?'|' *'|' *'|' +'|' {'|' }'|' ['|' ]'|

### 2. 正则表达式和NFA一一对应关系

$$E=mc^2$$

### 3. 匹配过程



---

## 使用示例及说明

您可以使用很多工具书写 Markdown，但是 Cmd Markdown 是这个星球上我们已知的、最好的 Markdown 工具——没有之一 ：）因为深信文字的力量，所以我们和你一样，对流畅书写，分享思想和知识，以及阅读体验有极致的追求，我们把对于这些诉求的回应整合在 Cmd Markdown，并且一次，两次，三次，乃至无数次地提升这个工具的体验，最终将它演化成一个 **编辑/发布/阅读** Markdown 的在线平台——您可以在任何地方，任何系统/设备上管理这里的文字。

### 1. 代码示例

```C++
#include <iostream>
#include <string>
#include <fstream>
#include "Regex/Matcher.h"

using namespace anyun_regex;
using namespace std;

#define Println(content) \
	cout<<content<<endl;

void password_validate()
{
	string passwords[] =
	{ "aaaa1111",
		"aa123",
		"123",
		"1123445690aaa",
		"abcd",
		"aabbccc",
		"11123" };
	NFA pattern("(\\w)\\1{2,}");
	for (string &password : passwords)
	{
		NFAMatcher matcher = NFAMatcher::match(password, pattern);
		Println("验证密码：" + password);
		if (matcher.find())
		{
			Println("包含重复3个以上,重复段为");
			Println(matcher.group());
		}
		else
			Println("OK");
		Println("");
	}
	cout << endl;
}
int main()
{
	password_validate();
	return 0;
}

```
运行结果：
```
验证密码：aaaa1111
包含重复3个以上,重复段为
aaaa

验证密码：aa123
OK

验证密码：123
OK

验证密码：1123445690aaa
包含重复3个以上,重复段为
aaa

验证密码：abcd
OK

验证密码：aabbccc
包含重复3个以上,重复段为
ccc

验证密码：11123
包含重复3个以上,重复段为
111
```

------
### 2. 包含文件说明
Regex/Matcher.h
Regex/NFA.h
Regex/DirectedGraph.h

------


