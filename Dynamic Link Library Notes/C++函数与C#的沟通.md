# Dynamic Link Library
# C++函数与C#的沟通

## C++与C#基本数据类型的传递

C/C++ | C# | length
----- | -- | ------
short | short | 2 Bytes
int | int | 4 Bytes
long | int | 4 Bytes
bool | bool | 1 Byte
char(ASCII码字符) | byte | 1 Byte
wchar_t(Unicode字符,该类型与C#中的char兼容) | char | 2 Bytes
float | float | 4 Bytes
double | double | 8 Bytes

## C函数与C#的交互

### dll文件

``` cpp

#ifndef FUNC_H
#define FUNC_H

extern "C" __declspec(dllexport) int func();

extern "C" __declspec(dllexport) int anotherFunc();
 
#endif

```

``` cpp

#include"func.h"

int func()
{
	return 123456;
}

int anotherFunc()
{
	int ans = static_cast<int>('A');
	return ans;
}
```

要导出的函数开头应加上`extern "C"`指明以C语言方式编译和链接，保证该函数定义的名字相同；否则默认以c++方式导出，函数的名字会变得乱七八糟，在C#里就找不到入口点(以函数名为入口点)。  

要导出的函数前还需加上`__declspec(dllexport)`指明该函数要导出  

### Unity C#调用dll

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;

public class TestModule : MonoBehaviour {

	[DllImport("Project11")]
	extern public static int func ();

	[DllImport("Project11", EntryPoint = "anotherFunc")]
	extern public static int Func();

	// Use this for initialization
	void Start () {
		int num;
		num = func ();
		Debug.Log (num);
		num = Func ();
		Debug.Log (num);
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}

```

加上`using System.Runtime.InteropServices;`以使用`DllImport()`   
使用`[DllImport("Project11")]`导入指定dll(该dll文件名为Project11.dll)  
`[DllImport("Project11")]`下声明重新声明导入的函数`extern public static int func ();`   

`[DllImport("Project11",EntryPoint = "anotherFunc")]`中用EntryPoint特别指明了调用的C++函数的名称,特别指明后声明的函数名称就不必与C++中的函数名称相同。  

### 字符串之间的交互

```
#ifndef FUNC_H
#define FUNC_H

extern "C" __declspec(dllexport) wchar_t* func(wchar_t* str);
 
#endif
```

```
#include"func.h"
wchar_t* func(wchar_t* str)
{
	str[0] = 'H';
	return str;
}
```

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;

public class TestModule : MonoBehaviour {

	[DllImport("Project14",EntryPoint = "func")]
	extern unsafe public static char* PrintString (char* str);


	// Use this for initialization
	void Start () {

		string outputString;
		char[] str = "hello world".ToCharArray();

		unsafe{
			fixed ( char* p = &(str[0]) ) {
				PrintString (p);
				outputString = new string (p);
			}
		}
		Debug.Log (outputString);
		Debug.Log ("success");
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
```

字符串之间的传递通过指针，C++的`wchar_t*`与C#的`char*`对应。  
在C#中操作指针需使用`unsafe`指明是非安全的，`extern unsafe public static char* PrintString (char* str)`。  
使用指针需用`unsafe{...}`，使用`fixed (char* p = &（str[0]))`对该地址的内容进行固化，防止在调用c++过程中该字符串的地址被C#改变。  
使用`new string(char*)`或`new string(char[])`获得处理后的字符串。  
由于修改的地址里的内容，故`str`里的内容也发生了改变，应小心此用法导致的问题。  

### 结构的交互

```
#ifndef FUNC_H
#define FUNC_H

struct Node {
	int a;
	int b;
	char c[2];
};

extern "C" __declspec(dllexport) void func(Node* node,int nLen);
 
#endif
```

```
#include"func.h"
#include<iostream>

void func(Node* node,int nLen)
{
	
	for (int i = 0; i < nLen; i++)
	{
		node[i].a = i;
		node[i].b = i * 2;
		node[i].c[0] = 64;
		node[i].c[1] = 65;
	}
}
```

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;

[StructLayout(LayoutKind.Sequential)]
struct Node{
	public int a;
	public int b;

	[MarshalAs(UnmanagedType.ByValArray,SizeConst = 2)]
	public byte[] c;
}

public class TestModule : MonoBehaviour {

	[DllImport("Project17",EntryPoint = "func")]
	extern public static void GetNode(IntPtr node,int nLen);

	Node[] node=new Node[2];

	// Use this for initialization
	void Start () {

		for (int i = 0; i < node.Length; i++) {
			node [i] = new Node ();
		}

		IntPtr[] ptArr = new IntPtr[1];
		ptArr [0] = Marshal.AllocHGlobal (Marshal.SizeOf (typeof(Node)) * 2); 
		IntPtr pt = Marshal.AllocHGlobal (Marshal.SizeOf (typeof(Node)));
		Marshal.Copy (ptArr, 0, pt, 1);
		GetNode (pt, 2);

		for (int i = 0; i < 2; i++) {
			node [i] = (Node)Marshal.PtrToStructure ((IntPtr)(pt.ToInt32 () + i * Marshal.SizeOf (typeof(Node))), typeof(Node));
			Debug.Log ("a=" + node[i].a + " b=" + node[i].b + " c=" + node[i].c [0] + ' ' + node[i].c [1]);
		}

	
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
```

C#中需使用`[MarshalAs(UnmanagedType.ByValArray,SizeConst = 2)]`将数组的大小锁定。  
C#中`IntPtr`是平台通用指针，可用来表示任意类型的指针。  
`IntPtr.ToInt32`可获得具体地址  
使用`Marshal.AllocHGlobal`分配内存  
使用`Marshal.PtrToStructure`将指定地址的内容转化成指定大小的结构，在通过强制类型转化即可获得结构。  

