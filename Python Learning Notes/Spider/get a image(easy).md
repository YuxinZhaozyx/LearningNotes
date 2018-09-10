# 爬虫

```
# 下载图片

import requests

# 加载地址
pic = requests.get('https://ss1.baidu.com/6ONXsjip0QIZ8tyhnq/it/u=3895760368,3790151653&fm=179&w=114&h=161&img.JPEG')

# 确认是否读入成功，成功时 statu_code==200
print (pic.status_code)

# 将图片内容写入文件
f = open('E:/tempFiles/webtest0.jpeg','wb')
f.write(pic.content)
f.close()

```

```
# 模拟浏览器渲染读取

import selenium
from selenium import webdriver

driver = webdriver.Chrome()
driver = webdriver.get('http://www.zhihu.com')

print (driver.page_source)

```

```
# requests 带参数GET请求

import requests

# 参数
data = {
	'name':'germey',
	'age':22
}

# 发送请求
response = request.get('http://httpbin.org/get', params=data)
print (response.text)

```

```
# requests解析json

import requests

response = requests.get('http://httpbin.org/get')
print (response.json())

```

```
# requests 添加headers

import requests

headers = {
	'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.87 Safari/537.36'
}

response = requesets.get('http://www.zhihu.com/explore', headers = headers)
print (response.text)

```

```
# requests 基本POST请求

import requests

data = {
	'name' : 'germey',
	'age':22
}

headers = {
	'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.87 Safari/537.36'
}

response = requests.post('http://httpbin.org/post', data = data, headers = headers)
print (response.text)

```

```
# request 响应的属性

import requests

response = requests.get('http://www.jianshu.com')
print (response.status_code)
print (response.headers)
print (response.cookies)
print (response.url)
print (response.history)

```

```
# 状态码判断

import requests

response = request.get('http://www.baidu.com')
if not response.status_code == requests.codes.ok :
	exit()
else:
	print('Request Successfully')

```

```
# 文件上传

import requests

file = {
	'file': open('E:/tempFiles/webtest0.jpeg','rb')
}

response = requests.post('http://httpbin.org/post',files=file)
print(response.text)

```

```
# 获取cookie

import requests

response = requests.get('https://www.baidu.com')

# print(response.cookies)
for key,value in response.cookies.items():
	print(str(key) + ' = ' + str(value) )

```

```
# 会话维持

import requests

s = requests.Session()
s.get('http://httpbin.org/cookies/set/number/123456789')
response = s.get('http://httpbin.org/cookies')
print(response.text)

```

```
# 证书验证

import requests

# verify关闭验证证书，cert设置证书
response = requests.get('http://www.12306.cn', verify = False, cert=('/path/server.crt','/path/key')) 
```

```
# 代理设置

import requests

# 普通代理
proxies1 = {
	'http':'http://127.0.0.1:9743',
	'https':'https://127.0.0.1:9743',
}

# 带密码的代理
proxies2 = {
	'http':'http://user:password@127.0.0.1:9743/'
}

response = requests.get('http://www.taobao.com',proxies=proxies1)

```

```
# 超时设置+异常处理

import requests
from requests.exceptions import ReadTimeout, ConnectionError, RequestException

try:
	# 0.5秒未响应则触发异常
	response = requests.get('http://httpbin.org/get',timeout = 0.5) 
except ReadTimeout:
	print('Timeout')
except ConnectionError:
	print('Connection error')
except RequestException:
	print('Error')

```

```
# 认证设置(登陆账号密码)

import requests
from requests.auth import HTTPBasicAuth

response = requests.get('http://120.27.34.24:9001',auth=HTTPBasicAuth('user','password'))

```

