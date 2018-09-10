# 模块

## 模块导入

`import` `from ... import`

- 整个模块导入 `import somemodule`
- 从某个模块中导入某个函数 `from somemodule import somefunction`
- 从某个模块中导入多个函数 `from somemodule import func1, func2, func3 `
- 将模块中的全部函数导入 `from somemodule import *`

## `__name__`属性

一个模块被另一个程序第一次引入时，其主程序将运行。如果我们想在模块被引入时，模块中的某一程序块不执行，我们可以用`__name__`属性来使该程序块仅在该模块自身运行时执行 

```python
if __name__ == '__main__':
   print('the module is running')
else:
   print('called by another module')
```

## `dir()`

内置的函数 `dir()` 可以找到模块内定义的所有名称。以一个字符串列表的形式返回:

```python
import sys

dir(sys) # 查看sys
dir() # 查看本身
```

## 包

```
sound/                          顶层包
      __init__.py               初始化 sound 包
      formats/                  文件格式转换子包
              __init__.py
              wavread.py
              wavwrite.py
              aiffread.py
              aiffwrite.py
              auread.py
              auwrite.py
              ...
      effects/                  声音效果子包
              __init__.py
              echo.py
              surround.py
              reverse.py
              ...
      filters/                  filters 子包
              __init__.py
              equalizer.py
              vocoder.py
              karaoke.py
              ...
```

`__init__.py`文件可为空，但最好在其中设置`__all__`

```python
# sound包有三个子包
# sound/__init__.py
__all__ = ['formats','effects','filters']
```



## `random` 模块

### `randint(a,b)`

返回 [a, b] 之间的int值

