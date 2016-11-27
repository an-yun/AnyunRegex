# 使用C++编写的正则表达式引擎

------

## 目录
[TOC]

------
## 关于本项目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这个项目开始写于2016年10月14日，当时在本科的毕业设计应该些什么，后来在知乎上看到vczh的篇介绍正则表达式的文章，就有了一些想法。整个项目没有任何现有的正则表达式库的代码，全部自己写成，同时有大量的测试，测试的基准是C++11 regex。
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;在后来的项目中，使用正则表达式结合爬虫分析招标公告，招标文件在和小组成员完成了一个招投标系统，系统可以自动分析抓取政府网站公开的招标公告，然后通过爬虫抓取下来，利用正则表达式进行分析，将分析结果存入数据库，然后通过web网站展示出来



------

## 实现思路
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;因为正则表达式和非确定有限状态自动机NFA是完全等价的[^footnote]，所以可以把一个正则表达式一一对应的翻译成一个NFA（下面会详细说明）
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;整体上，先把输入的正则表达式通过算符优先文法判断优先级，然后根据不同的优先级的运算符按照优先级，把每一部分的正则表达翻译成对应的有限状态自动机（分确定有限状态自动机DFA和非确定有限状态自动机NFA）。翻译后的有限状态自动机对应一个有向图，有一个起点（代表起始状态），有一个终点（代表终止状态，多个终点可以把它们用空边$\epsilon$连接到唯一的终点上）
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;进行匹配的时候，记录匹配的信息，通过实时的匹配信息，结合有限状态自动机就可以从一个状态跳转到下一个状态，如果能到达说明匹配成功率

### 1. 正则表达式运行符和优先级
#### 优先级表： ####
 -  `-1`代表左边的优先级小于右边
 -  `0` &nbsp;代表左边的优先级等于右边(对应的操作是出栈)
 -   `+1` 代表左边的优先级大于右边
 -   `error` 代表出错，一般的情况是缺少括号
 -   有些非运算符没有画出,如：`,`,`'`,`.`等等

|符号    |'\0' |' \' |' (' |' )' |' ?' |' *' |' ^' |'\$' |' +' |' {' |' }' |' [' |' ]' |'\|' |
|:--:    |:--: |:--: |:--: |:--: |:--: |:--: |:--: |:--: |:--: |:--: |:--: |:--: |:--: |:--: |
|**'\0'**|  0  | -1  | -1  |error| -1  | -1  | -1  | -1  | -1  | -1  |error| -1  |error| -1  |
|**' \'**| +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  |
|**' ('**|error| -1  | -1  |  0  | -1  | -1  | -1  | -1  | -1  | -1  |error| -1  |error| -1  |
|**' )'**| +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  |error| +1  |error| +1  |
|**' ?'**| +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  |error| +1  | +1  | +1  |
|**' *'**| +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  |error| +1  | +1  | +1  |
|**' ^'**| +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  |error| +1  |error| +1  |
|**' $'**| +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  |error| +1  |error| +1  |
|**' +'**| +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  |error| +1  | +1  | +1  |
|**' {'**|error|error|error|error|error|error|error|error|error|error|  0  |error|error|error|
|**' }'**| +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  |error| +1  |error| +1  |
|**' ['**|error| -1  | -1  |error| -1  | -1  | -1  | -1  | -1  |error|error| -1  |error| -1  |
|**' ]'**| +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  | +1  |error| +1  |  0  | +1  |
|**'\|'**| +1  | -1  | -1  | -1  | -1  | -1  | -1  | -1  | -1  | -1  |error| -1  | -1  | +1  |

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`\0`代表起始或者结束符
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`\`&nbsp;代表转义符号（和大多数编程语言中一样）
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`^`&nbsp;在`[]`外代表取补集，其它地方代表行起始位置

### 2. 正则表达式和NFA一一对应关系
#### 说明： ####
 -  小写字母代表单个的终结符如a,b,c，表示输入的一个字符`'a'`,`'1'`等等
 -  正则表达式统一用`e`加下标表示,如$e_1$,$e_2$,$a$等等

$$E=mc^2$$

### 3. 匹配过程



---

## 使用示例及说明

### 1. 功能和代码示例

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

[^footnote]: 这是一个 *注脚* 的 **文本**。
