# C_C++-_WSTP_Example
## C/C++和Wolfram交互的初级教程和实例
+  WSTP 介绍
 >  在许多情况下，在高层与外部程序通信，交换结构数据将是很方便的.
在几乎所有计算机系统上，Wolfram 系统支持 Wolfram Symbolic Transfer Protocol (WSTP) 通信标准，它允许 Wolfram 系统和外部程序进行较高层的通信. 为了使用 WSTP，外部程序必须引入一些特殊源代码和 WSTP 库，这些通常由 Wolfram 系统分发.
WSTP 既允许外部程序调用 Wolfram 语言，也允许 Wolfram 语言调用外部程序. "WSTP 和外部程序通讯" 会讨论 WSTP 的一些细节. 通过使用 WSTP，基本上可以像嵌入在外部程序中的子过程一样处理 Wolfram 语言. 或者用户可以建立一个前端实现自己的用户界面，并且通过 WSTP 与 Wolfram 语言内核进行通信.
+ Ubuntu Linux下使用WSTP和C交互编程
  + 支持的开发平台  


|       $System  | C compiler |   C++ compiler  |
|  ------------    |   ----------     |   -----------        |
|     "Linux"	   | gcc (GCC) 4.4.6 20110731 (Red Hat 4.4.6-3) |   g++ (GCC) 4.4.6 20110731 (Red Hat 4.4.6-3) |  
|    "Linux-x86-64" |  gcc (GCC) 4.4.6 20110731 (Red Hat 4.4.6-3) |  g++ (GCC) 4.4.6 20110731 (Red Hat 4.4.6-3) |    
 
 
本文介绍在Ubuntu下使用  
+ 安装 WSTP 组件  
> WSTP 开发工具包（WSDK）位于 Wolfram 系统目录内的$InstallationDirectory/SystemFiles/Links/WSTP/DeveloperKit/$SystemID 目录中.
建议安装
CompilerAdditions 安装
构建 WSTP 程序所需要的 WSTP 组件已由 Wolfram 系统安装器安装. 使用这些组件的一种方法是让它们保留在 Wolfram 系统目录中，当调用编译器时指定它们的完整路径. 该方法列在“构建 WSTP 程序”章节中的范例“makefiles”中.
另一种方法是把这些组件 (wstp.h、libWSTP32i4.a、libWSTP32i4.so、libWSTP64i4.a 和 libWSTP64i4.so) 复制到编译器会自动搜索这些文件的目录中. 这些目录一般是 /usr/include 和 /usr/lib，但是你的系统可能会有所不同. 在许多系统中，不是所有用户都可以读写这些目录.
WSTPExamples 安装
把 WSTPExamples 目录复制到主目录.
WSTP 框架组件
下面是 WSDK 中每个文件或目录的说明.
CompilerAdditions 目录
wstp.h
wstp.h 是一个必须包含在 C 和 C++ 源文件中的头文件. 它应该放在你的编译器可以找到的地方. 你可以把它复制到和源文件同样的目录下，或复制到和标准头文件同样的目录下，或者不用管它，但是把 WSTP 目录添加到头文件的搜索路径中.
libWSTP32i4.a/libWSTP64i4.a
这是一个包含所有 WSTP 函数的静态库. 你的项目应该包含它. 你可以把该库复制到与源文件同样的目录下或不做任何改变，但是把 WSTP 目录添加到库文件的搜索路径中. 32/64 表明库是 WSTP 库的 32 位或 64 位版本.
libWSTP32i4.so/libWSTP64i4.so
这是一个包含 WSTP 所有函数的动态共享库. 你的项目应该包含它. 你可以把该库复制到与源文件同样的目录下，或复制到系统位置，例如 /lib 或 /usr/lib，或不做任何改变，但是把 WSTP 目录添加到库搜索路径中. 32/64 表明库是 WSTP 库的 32 位或 64 位版本.
wsprep
wsprep 是一个应用程序，通过处理模板文件自动编写 WSTP 程序. 把该应用程序复制到你的项目目录中或创建一个别名会方便应用.
wscc
wscc 是一个预处理和编译 WSTP 源文件的脚本.
WSTPExamples 目录
该目录包含一些非常简单的 WSTP 程序源代码. 通过使用源代码，你可以学习如何构建和运行 WSTP 程序，而无需自己编写任何代码.
PrebuiltExamples 文件夹
该目录包含范例程序的预建版本. “运行 WSTP 程序”描述了如何运行两个这样的程序. “构建 WSTP 程序”描述了如何使用 WSTPExamples 文件夹中的源代码构建自己的程序.

> WSTP可以双向通讯，也就是说WOLFRAM中可以使用C/C++编的函数，C/C++也可以后端调用WOLFRAM。
所以C代码有两种编程风格，本文我只介绍WOLFRAM调用C/Wolfram混编的语言。  

+ 构建WSTP程序  
> 首先要写模板文件（.tm）。模板文件分成两个部分
我用一个快速排序函数为一个例子 ，先写一个模板文件  
``` c
:Begin: /*开头，必须书写*/
:Function:	sort   /* C语言所对应的函数名   */
:Pattern:	sort[arr_List]    /* Wolfram调用的函数模式   */
:Arguments:	{arr}        /*  变量名 */
:ArgumentTypes:	{IntegerList}     /*   参数类型     */
:ReturnType:	Manual       /*      返回类型     */
:End: /* End */
```   
剩下就是写C代码了。我强调一下如何将模板文件转换成源文件，然后源文件与静动态库编译链接。  
``` shell 
wsprep filenames.tm -o filenames.c
``` 
wsprep是Wolfram的WSTP文件夹下的一个应用程序，用来将模板文件翻译成C/C++文件，注意把程序放到系统环境变量能找到的地方或者添加环境变量能让系统找到它。 
接下来最重要的一步，将源文件编译与静动态库链接  
``` shell
gcc  filenames.c -lWSTP64i4 -lm -lpthread -lrt -lstdc++ -ld
l -luuid -o filenames  
``` 
注意静动态库能被系统找到，找不到放到能找到的地方，如果你会写Makefile更好  
或者写一个C++ 编译小工具 
``` c++ 
#include<string>
#include<iostream>
#include<cstdlib>
int main(int argc,char **argv)
{
    if(argc==2)
    {
            std::string s=" -lWSTP64i4 -lm -lpthread -lrt -lstdc++ -ldl -luuid -o";
            std::string s1=argv[1];
            std::string cmd="gcc "+s1+".c"+s+s1;
            system(cmd.c_str());
    }
}
``` 
更多源代码和文件请看Example/quick_sort文件。


