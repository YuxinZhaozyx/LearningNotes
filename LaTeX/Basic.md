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
+ `\hphantom{xyz}` 占位宽度
+ `\hfill` 弹性宽度

## 插图

需使用 `graphicx`包

`\graphicspath{{<path1>}, {<path2>}}`设置图片文件夹路径

`\includegraphics[<options>]{<filename>}`插入图片，`<filename>`可不加后缀名

```latex
\documentclass{article}

\usepackage{ctex,graphicx}

\graphicspath{{figure/}}

\begin{document}	
	\includegraphics{Guilty_Crown.jpg} % 按图片原大小
	
	\includegraphics[scale=0.2]{Guilty_Crown.jpg} % 缩放到20%
	
	\includegraphics[height=2cm]{Guilty_Crown} % 等比例限制高度为2cm
	
	\includegraphics[width=2cm]{Guilty_Crown} % 等比例限制高度为2cm
	
	\includegraphics[width=10cm, height=10cm]{Guilty_Crown} % 同时指定高度和宽度
	
	\includegraphics[height=10cm, angle=45]{Guilty_Crown} % 先改变高度，再旋转45度

\end{document}
```

## 表格

```latex
\documentclass{article}

\usepackage{ctex}

\begin{document}	

\begin{tabular}{l||c|r|p{1.5cm}} % l,c,r分别为左、居中、右对齐， |指定分割竖线(可选) p{1.5cm} 固定宽度，超过时自动换行
	\hline % 分割横线(可选)
	Name & A & B & C \\
	\hline \hline
	Anne & 12 & 33 & 34 \\
	Bob & 60 & 89 & 100 \\
	\hline
\end{tabular}

\end{document}
```

## 浮动体环境

figure浮动体与table浮动体

+ 常用浮动格式[!htbp]
  + h：here当前位置。将图形放置在正文文本中给出该图形环境的地方。如果本页所剩的页面不够，这一参数将不起作用。
  + t：top顶部。将图形放置在页面的顶部。
  + b：bottom底部。将图形放置在页面的底部。
  + p：page of its own浮动页。将图形放置在一只允许有浮动对象的页面上。
  + ！：忽略美观因素，尽可能按照参数指定的方式来处理表格浮动位置。 
  + 表格将会按照所给参数，依次尝试按照每个参数进行排版，当无法排版时，将会按照下一个参数

```latex
\documentclass{article}

\usepackage{ctex,graphicx}

\graphicspath{{figure/}}
	
\begin{document}

	图片详见图\ref{myfigure}
\begin{figure}[htbp]
	\centering
	\includegraphics[height=5cm]{Guilty_Crown.jpg}
	\caption{图名称} \label{myfigure}
\end{figure}	

	表格详见表\ref{mytable}

\begin{table}[htbp]
	\caption{表格名称} \label{mytable}
	\centering % 由于在table环境中，所以只对table环境中的下文居中对齐
	\begin{tabular}{l||c|r|p{1.5cm}}
		\hline
		Name & A & B & C \\
		\hline \hline
		Anne & 12 & 33 & 34 \\
		\hline
		Bob & 60 & 89 & 100 \\
		\hline
	\end{tabular} 
\end{table} 

\end{document}
```

