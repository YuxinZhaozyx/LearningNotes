# I/O操作

## File类(java.io.File)

File类可以是文件也可以是目录  

构造方法 | 参数说明 | 示例
------- | ------- | ----
File(String pathname) | pathname:路径名 | File("d:/1.txt")
File(String parent,String child) | parent:父路径<br>child:子路径 | File("d:/","1.txt")
File(File f,String child) | f:父路径的File对象<br>child:子路径字符串 | File(new File("d:/"),"1.txt")true

方法 | 返回值 | 说明
---- | ----- | ----
getName() | String | 获取文件的名称
length() | long | 获取文件的长度(以字节为单位)
getAbsolutePath() | String | 获取文件的绝对路径
getParent() | String | 获取文件的父路径
getTotalSpace() | long | 获取文件所在处的总大小(以字节为单位)
getFreeSpace() | long | 获取文件所在处的空闲空间大小(以字节为单位)
getUsableSpace() | long | 获得文件所在处的可用空间大小(以字节为单位)
lastModified() | long | 获取文件的最后修改时间
list() | String[] | 获取目录下所有文件(包括子目录)的名称，若调用对象不是目录则返回null
listFiles() | File[] | 获得目录下的所有文件(包括子目录)的File对象，若调用对象不是目录则返回null
canRead() | boolean | 判断文件是否可读
canWrite() | boolean | 判断文件是否可写
canExecute() | boolean | 判断文件是否可执行
exists() | boolean | 判断文件是否存在
isFile() | boolean | 判断文件是否为文件
isDirectory() | boolean | 判断文件是否为目录
isHidden() | boolean | 判断文件是否为隐藏文件
setReadOnly() | boolean | 设置文件为只读文件，成功返回true，失败返回false
delete() | boolean | 删除文件，成功返回true，失败返回false
deleteOnExit() | void | 当程序结束时自动删除该文件 
createNewFile() | boolean | 创建文件，成功返回true，失败返回false
mkdir() | boolean | 创建目录(要求父目录已存在)，成功返回true，失败返回false
mkdirs() | boolean | 创建目录(若父目录不存在则自动创建父目录)，成功返回true，失败返回false
toURL() | URL | 获取该位置的URL

``` Java
package myTest;

import java.io.File;

public class IOTest {
	
	public static void FileTest() {
		File file = new File("F:/tempFiles/words/");
		if(file.exists()) {
			String name = file.getName();
			long length = file.length();
			boolean hidden = file.isHidden();
			boolean canread = file.canRead();
			boolean canwrite = file.canWrite();
			String absolutePath = file.getAbsolutePath();
			String parent = file.getParent();
			boolean isFile = file.isFile();
			boolean isDir = file.isDirectory();
			long lastModified = file.lastModified();
			long total= file.getTotalSpace();
			long free = file.getFreeSpace();
			long usable = file.getUsableSpace();
			
			System.out.println("name:"+name );
			System.out.println("length:"+length);
			System.out.println("absolutePath:"+absolutePath);
			System.out.println("parent:"+parent);
			System.out.println("lastModified:"+lastModified);
			System.out.println("total:"+total);
			System.out.println("free:"+free);
			System.out.println("usable:"+usable);
			
		}
		else {
			try {
				file.mkdirs(); // 创建文件
				System.out.println("文件已创建");
				file.delete(); // 删除文件
				System.out.println("文件已删除");
			}
			catch(Exception e){
				e.printStackTrace();
			}
		}
	}
	
	
	
	public static void main(String[] args) {
		FileTest();
	}
}
```

## 输入流

### InputStream类

InputStream类是字节输入流的抽象类，是所有字节输入流的父类。  
该类中所有方法遇到错误时都会引发IOException异常。  

方法 | 放回值 | 说明
---- | ----- | -----
read() | int | 从输入流中读取数据的下一个字节，返回[0,255]内的int字节值。 遇文件尾返回-1
read(byte[] b, int off, int len) | int | 从输入流中读取数据到b，off指定开始读取的位置，len指定读取的长度，返回读取到的byte数。 遇文件尾返回-1
read(byte[] b) | int | 相当于`read(b,0,b.length)`
mark(int readlimit) | int | 在输入流的当前位置放置一个标记，readlimit参数告知此输入流在标记位置失效前允许读取的字节数
reset() | void | 将输入指针返回到当前所做的标记处
skip(long n) | long | 跳过指定字节数,返回实际跳过字节数
markSupported() | boolean | 判断该字符流是否支持mark()/reset()操作
close() | void | 关闭流并释放资源

### Reader类

Reader是字符输入流的抽象类，所有字符输入流都是它的子类。  

## 输出流

### OuputStream类

OutputStream类是字节输出流的抽象类，是所有字节输出流的父类。  

方法 | 返回值 | 说明
---- | ----- | -----
write(int b) | void | 将指定字节写入输出流
write(byte[] b) | void | 相当于write(b,0,b.length)
write(byte[] b, int off, int len) | void | 将b中的数据从off处写入流中，写入长度为len
flush() | void | 彻底完成输出并清空缓冲区
close() | void | 关闭流

## 文件输出/输入流

### FileInputStream类 和 FileOutputStream类

``` Java
package myTest;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;

public class IOTest {
	
	public static void FileTest(){
		File file = new File("F:/tempFiles/word.txt");
		try {
			FileOutputStream out = new FileOutputStream(file);
			
			byte[] data = "我有一个苹果".getBytes();
			out.write(data);
			out.close();
		}catch(Exception e) {
			e.printStackTrace();
		}
		
		try {
			FileInputStream in = new FileInputStream(file);
			
			byte[] data = new byte[1024];
			int len = in.read(data);
			System.out.println("文件信息: "+ new String(data,0,len));
			in.close();
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	
	
	
	public static void main(String[] args) {
		FileTest();
	}
}
```

### FileReader类 和 FileWriter类

按字符读取和写入文件  

``` Java
package myTest;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.InputStream;
import java.io.OutputStream;

public class IOTest {
	
	public static void FileTest(){
		File file = new File("F:/tempFiles/word.txt");
		try {
			FileWriter out = new FileWriter(file);
			
			String data = "我有一个苹果";
			out.write(data);
			out.close();
		}catch(Exception e) {
			e.printStackTrace();
		}
		
		try {
			FileReader in = new FileReader(file);
			
			char[] data = new char[1024];
			int len = in.read(data);
			System.out.println("文件信息: "+ new String(data,0,len));
			in.close();
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	
	
	
	public static void main(String[] args) {
		FileTest();
	}
}

```

## 带缓冲的输入/输出流

### BufferedInputStream类 和 BufferedOutputStream类

#### BufferedInputStream类

BufferedInputStream类可以对所有InputStream类进行带缓存区的包装以达到性能的优化。

构造方法 | 说明
------- | ----
BufferedInputStream(InputStream in) | 相当于BufferedInputStream(in,32)
BufferedInputStream(InputStream in, int size) | 创建一个带有size个字节的缓存流。

#### BufferedOutputStream类

使用BufferedOutputStream输出信息和OutputStream完全相同，只不过BufferedOutputStream有一个flush()方法用来将缓存区的数据强制输出完  

构造方法 | 说明
------- | ----
BufferedOutputStream(OutputStream out) | 相当于BufferedOutputStream(out,32)
BufferedOutputStream(OutputStream out, int size) | 创建一个带有size个字节的缓存流。

### BufferedReader类 和 BufferedWriter类

BufferReader类和BufferedWriter类分别继承Reader类和Writer类  

#### BufferedReader类

构造方法 | 说明
------- | ---
BufferedReader(Reader in) | 相当于BufferedReader(in,32)
BufferedReader(Reader in, int size) | 创建一个带有size个字节的缓存流。

方法 | 返回值 | 说明
--- | ------ | -----
read() | int | 读取单个字符
readLine() | String | 读取一行，若无数据可读则返回null


#### BufferedWriter类

构造方法 | 说明
------- | ---
BufferedWriter(Writer out) | 相当于BufferedWriter(out,32)
BufferedWriter(Writer out, int size) | 创建一个带有size个字节的缓存流。

方法 | 返回值 | 说明
--- | ------ | ----
write(String s,int off,int len) | void | 写入字符串的某一部分
flush() | void | 刷新缓存
newLine() | void | 写入一个行分隔符

## 数据输入/输出流

### DataInputStream类

构造方法 | 说明
------ | ------
DataInputStream(InputStream in) | 使用指定的基础InputStream创建一个DataInputStream。  

方法 | 返回值 | 说明
readUTF() | String | 读取一个字符串

由于`writeBytes`,`writeChars`,`writeUTF`中只有`writeUTF`写入了字符串的长度，故只有`readUTF`方法可成功返回字符串。  

### DataOutputStream类

构造方法 | 说明
------ | ------
DataOutputStream(OutputStream out) | 使用指定的基础OutputStream创建一个DataOutputStream。  

方法 | 返回值 | 说明
--- | ----- | -----
writeBytes(String s) | void | 将每个字符的低字节写入设备
writeChars(String s) | void | 将每个字符的两个字节都写入设备
writeUTF(String s) | void | 将字符串按照UTF编码后的字节长度写入设备，再写入每个字节的UTF编码