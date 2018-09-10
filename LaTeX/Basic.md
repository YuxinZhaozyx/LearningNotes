# LaTeX基础

## 标题、作者、日期、正文

```latex
\documentclass{article}

\usepackage{ctex}

% 标题信息
\title{My Title}
\author{My Name}
\date{\today}

% 注释
\begin{document}
	\maketitle % 只有使用这个才会将标题信息打印出来
	hello world
\end{document}
```

## 字体属性

在 $\LaTeX$ 中，一个字体有5种属性：

+ 字体编码
  + 正文字体编码：OT1、T1、EU1等
  + 数学字体编码：OML、OMS、OMX等

+ 字体族
  + 罗马字体：笔画起始处有装饰
  + 无衬线字体：笔画起始处无装饰
  + 打字机字体：每个字符宽度相同，又称等宽字体
+ 字体系列
  + 粗体
  + 宽度
+ 字体形状
  + 直立
  + 斜体
  + 伪斜体
  + 小型大写
+ 字体大小

```late
\documentclass[9pt]{article} % 9pt指定标准字体大小为9pt

\usepackage{ctex}

\begin{document}
% 字体族设置（罗马字体、无衬字字体、打字机字体）
	
	% 仅对本句有效
	\textrm{Roman Family} 
	\textsf{Sans Serif Family}
	\texttt{Typewriter Family} 
	
	% 对后续内容都有效
	\rmfamily Roman Family 
	\sffamily Sans Serif Family
	\ttfamily Typewriter Family 
	
%字体系列设置(宽度、粗体)

	% 仅对本句有效
	\textmd{Medium Series}
	\textbf{Boldface Series}
	
	% 对后续内容都有效
	\mdseries Medium Series
	\bfseries Boldface Series
	
% 字体形状(直立、斜体、伪斜体、小型大写)

	% 仅对本句有效
	\textup{Upright Shape}
	\textit{Italic Shape}
	\textsl{Slanted Shape}
	\textsc{Small Caps Shape}
	
	% 对后续内容都有效
	\upshape Upright Shape
	\itshape Italic Shape
	\slshape Slanted Shape
	\scshape Small Cap Shape
	
% 中文字体(注意需使用ctex包)
	\songti 宋体 \quad
	\heiti  黑体 \quad
	\fangsong 仿宋 \quad
	\kaishu 楷书 \quad
	
	% 设置中文字体大小
	\zihao{4} 四号 
	\zihao{-4} 小四号 
	
% 字体大小
	\tiny			Hello \\
	\scriptsize		Hello \\
	\footnotesize	Hello \\
	\small			Hello \\
	\normalsize 	Hello \\
	\large			Hello \\
	\Large			Hello \\
	\LARGE			Hello \\
	\huge			Hello \\
	\Huge			Hello \\
	
\end{document}
```

## 篇章结构

`\tableofcontents` 生成目录

`section` 一级标题

`subsection` 二级标题

`subsubsection` 三级标题

```latex
\documentclass{ctexart} % ctexart类型文档


% \ctexset{} 此命令中可以设置格式

\usepackage{ctex}

\begin{document}	
	\tableofcontents % 生成目录
	
	\section{引言}
	\section{实验方法}
	\section{实验结果}
	\subsection{数据}
	\subsection{图表}
	\subsubsection{实验条件}
	\section{总结}
\end{document}
```

## 特殊字符

### 空白

英文中多个空格将只显示一个空格

+ `\quad` 1em(当前字体中M的宽度)的空白
+ `\qquad` 2em的空白
+ `\,` 约1/6em
+ `\enspace` 0.5em
+ `\ ` 空格
+ `~` 硬空格
+ `\kern 1pc ` 1pc (1pc =12pt=4.218mm)
+ `\kern -1em` -1em
+ `\hspace{35pt}` 35pt
+ `hphantom{xyz}` 占位宽度
+ `hfill` 弹性宽度

## 插图

需使用 `graphicx`包

`graphicspath{{<path1>}, {<path2>}}`设置图片文件夹路径

`includegraphics[<options>]{<filename>}`插入图片，`<filename>`可不加后缀名



