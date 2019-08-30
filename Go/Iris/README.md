# Iris框架

[TOC]

# 路由

## 基本

```go
package main

import (
	"github.com/kataras/iris"

	"github.com/kataras/iris/middleware/logger"
	"github.com/kataras/iris/middleware/recover"
)

func main() {
	app := iris.New()
	app.Logger().SetLevel("debug")

	// Optionally, add two built'n handlers
	// that can recover from any http-relative panics
	// and log the requests to the terminal.
	app.Use(recover.New())
	app.Use(logger.New())

	// Method:   GET
	// Resource: http://localhost:8080
	app.Handle("GET", "/", HomePage)

	// same as app.Handle("GET", "/ping", [...])
	// Method:   GET
	// Resource: http://localhost:8080/ping
	app.Get("/ping", PingPage)

	// Method:   GET
	// Resource: http://localhost:8080/hello
	app.Get("/hello", HelloPage)

	// http://localhost:8080
	// http://localhost:8080/ping
	// http://localhost:8080/hello
	app.Run(iris.Addr(":8080"), iris.WithoutServerError(iris.ErrServerClosed))

}

func HomePage(ctx iris.Context) {
	ctx.HTML("<h1>Welcome</h1>")
}

func PingPage(ctx iris.Context) {
	ctx.WriteString("pong")
}

func HelloPage(ctx iris.Context) {
	ctx.JSON(iris.Map{"message": "Hello Iris!"})
}
```

## 获取参数

### Parameters in path

| Param Type      | Go Type | Validation                                                   | Retrieve Helper      |
| --------------- | ------- | ------------------------------------------------------------ | -------------------- |
| `:string`       | string  | anything (single path segment)                               | `Params().Get`       |
| `:int`          | int     | -9223372036854775808 to 9223372036854775807 (x64) or -2147483648 to 2147483647 (x32), depends on the host arch | `Params().GetInt`    |
| `:int8`         | int8    | -128 to 127                                                  | `Params().GetInt8`   |
| `:int16`        | int16   | -32768 to 32767                                              | `Params().GetInt16`  |
| `:int32`        | int32   | -2147483648 to 2147483647                                    | `Params().GetInt32`  |
| `:int64`        | int64   | -9223372036854775808 to 9223372036854775807                  | `Params().GetInt64`  |
| `:uint`         | uint    | 0 to 18446744073709551615 (x64) or 0 to 4294967295 (x32), depends on the host arch | `Params().GetUint`   |
| `:uint8`        | uint8   | 0 to 255                                                     | `Params().GetUint8`  |
| `:uint16`       | uint16  | 0 to 65535                                                   | `Params().GetUint16` |
| `:uint32`       | uint32  | 0 to 4294967295                                              | `Params().GetUint32` |
| `:uint64`       | uint64  | 0 to 18446744073709551615                                    | `Params().GetUint64` |
| `:bool`         | bool    | "1" or "t" or "T" or "TRUE" or "true" or "True" or "0" or "f" or "F" or "FALSE" or "false" or "False" | `Params().GetBool`   |
| `:alphabetical` | string  | lowercase or uppercase letters                               | `Params().Get`       |
| `:file`         | string  | lowercase or uppercase letters, numbers, underscore (_), dash (-), point (.) and no spaces or other special characters that are not valid for filenames | `Params().Get`       |
| `:path`         | string  | anything, can be separated by slashes (path segments) but should be the last part of the route path | `Params().Get`       |

**Usage**:

```go
app.Get("/users/{id:uint64}", func(ctx iris.Context){
    id := ctx.Params().GetUint64Default("id", 0)
    // [...]
})
```

### 参数约束 

| Built'n Func                                                 | Param Types                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `regexp`(expr string)                                        | :string                                                      |
| `prefix`(prefix string)                                      | :string                                                      |
| `suffix`(suffix string)                                      | :string                                                      |
| `contains`(s string)                                         | :string                                                      |
| `min`(minValue int or int8 or int16 or int32 or int64 or uint8 or uint16 or uint32 or uint64 or float32 or float64) | :string(char length), :int, :int8, :int16, :int32, :int64, :uint, :uint8, :uint16, :uint32, :uint64 |
| `max`(maxValue int or int8 or int16 or int32 or int64 or uint8 or uint16 or uint32 or uint64 or float32 or float64) | :string(char length), :int, :int8, :int16, :int32, :int64, :uint, :uint8, :uint16, :uint32, :uint64 |
| `range`(minValue, maxValue int or int8 or int16 or int32 or int64 or uint8 or uint16 or uint32 or uint64 or float32 or float64) | :int, :int8, :int16, :int32, :int64, :uint, :uint8, :uint16, :uint32, :uint64 |

**Usage**:

```
app.Get("/profile/{name:alphabetical max(255)}", func(ctx iris.Context){
    name := ctx.Params().Get("name")
    // len(name) <=255 otherwise this route will fire 404 Not Found
    // and this handler will not be executed at all.
})
```

#### 自定义参数约束

**Do It Yourself**:

The `RegisterFunc` can accept any function that returns a `func(paramValue string) bool`. Or just a `func(string) bool`. If the validation fails then it will fire `404` or whatever status code the `else` keyword has.

```
latLonExpr := "^-?[0-9]{1,3}(?:\\.[0-9]{1,10})?$"
latLonRegex, _ := regexp.Compile(latLonExpr)

// Register your custom argument-less macro function to the :string param type.
// MatchString is a type of func(string) bool, so we use it as it is.
app.Macros().Get("string").RegisterFunc("coordinate", latLonRegex.MatchString)

app.Get("/coordinates/{lat:string coordinate()}/{lon:string coordinate()}", func(ctx iris.Context) {
    ctx.Writef("Lat: %s | Lon: %s", ctx.Params().Get("lat"), ctx.Params().Get("lon"))
})
```

Register your custom macro function which accepts two int arguments.

```
app.Macros().Get("string").RegisterFunc("range", func(minLength, maxLength int) func(string) bool {
    return func(paramValue string) bool {
        return len(paramValue) >= minLength && len(paramValue) <= maxLength
    }
})

app.Get("/limitchar/{name:string range(1,200) else 400}", func(ctx iris.Context) {
    name := ctx.Params().Get("name")
    ctx.Writef(`Hello %s | the name should be between 1 and 200 characters length
    otherwise this handler will not be executed`, name)
})
```

Register your custom macro function which accepts a slice of strings `[...,...]`.

```go
app.Macros().Get("string").RegisterFunc("has", func(validNames []string) func(string) bool {
    return func(paramValue string) bool {
        for _, validName := range validNames {
            if validName == paramValue {
                return true
            }
        }

        return false
    }
})

app.Get("/static_validation/{name:string has([kataras,gerasimos,maropoulos])}", func(ctx iris.Context) {
    name := ctx.Params().Get("name")
    ctx.Writef(`Hello %s | the name should be "kataras" or "gerasimos" or "maropoulos"
    otherwise this handler will not be executed`, name)
})
```

## hero依赖注入

### Dependency Injection

The package [hero](https://github.com/kataras/iris/blob/master/hero) contains features for binding any object or functions that `handlers` can use, these are called dependencies.

With Iris you get truly safe bindings thanks to the [hero](https://github.com/kataras/iris/blob/master/_examples/hero) [package](https://github.com/kataras/iris/blob/master/hero). It is blazing-fast, near to raw handlers performance because Iris calculates everything before the server even goes online!

Below you will see some screenshots I prepared to facilitate understanding:

#### 1. Path Parameters - Built'n Dependencies

[![img](https://github.com/kataras/explore/raw/master/iris/hero/hero-1-monokai.png)](https://github.com/kataras/explore/raw/master/iris/hero/hero-1-monokai.png)

#### 2. Services - Static Dependencies

[![img](https://github.com/kataras/explore/raw/master/iris/hero/hero-2-monokai.png)](https://github.com/kataras/explore/raw/master/iris/hero/hero-2-monokai.png)

#### 3. Per-Request - Dynamic Dependencies

[![img](https://github.com/kataras/explore/raw/master/iris/hero/hero-3-monokai.png)](https://github.com/kataras/explore/raw/master/iris/hero/hero-3-monokai.png)

`hero funcs` are very easy to understand and when you start using them **you never go back**.

> With Iris you also get real and [blazing-fast](https://github.com/kataras/iris/blob/master/_benchmarks) [MVC support](https://github.com/kataras/iris/blob/master/_examples/mvc) which uses "hero" under the hoods.

## GET获取参数

```go
// Query string parameters are parsed using the existing underlying request object.
// The request responds to a url matching:  /welcome?firstname=Jane&lastname=Doe.
app.Get("/get_test", func(ctx iris.Context) {
    firstname := ctx.URLParamDefault("firstname", "Guest")
    // shortcut for ctx.Request().URL.Query().Get("lastname").
    lastname := ctx.URLParam("lastname")

    ctx.Writef("Hello %s %s", firstname, lastname)
})
```

## POST获取参数

```go
app.Post("/post_test", func(ctx iris.Context) {
    message := ctx.FormValue("message")
    nick := ctx.FormValueDefault("nick", "anonymous nick")
	// or `ctx.PostValue` for POST, PUT & PATCH-only HTTP Methods.
    
    ctx.JSON(iris.Map{
        "status":  "posted",
        "message": message,
        "nick":    nick,
    })
})
```

## 路由分组Grouping routes

```go
func main() {
	app := iris.Default()

	// Simple group: v1.
	v1 := app.Party("/v1")
	{
		v1.Post("/login", loginEndpoint)
		v1.Post("/submit", submitEndpoint)
		v1.Post("/read", readEndpoint)
	}

	// Simple group: v2.
	v2 := app.Party("/v2")
	{
		v2.Post("/login", loginEndpoint)
		v2.Post("/submit", submitEndpoint)
		v2.Post("/read", readEndpoint)
	}

	app.Run(iris.Addr(":8080"))
}
```

## 

# 上传文件

- [single file upload](https://github.com/kataras/iris/blob/master/_examples/http_request/upload-file/main.go)
- [multi file upload](https://github.com/kataras/iris/blob/master/_examples/http_request/upload-files)

```
const maxSize = 5 << 20 // 5MB

func main() {
    app := iris.Default()
    app.Post("/upload", iris.LimitRequestBodySize(maxSize), func(ctx iris.Context) {
        //
        // UploadFormFiles
        // uploads any number of incoming files ("multiple" property on the form input).
        //

        // The second, optional, argument
        // can be used to change a file's name based on the request,
        // at this example we will showcase how to use it
        // by prefixing the uploaded file with the current user's ip.
        ctx.UploadFormFiles("./uploads", beforeSave)
    })

    app.Run(iris.Addr(":8080"))
}

func beforeSave(ctx iris.Context, file *multipart.FileHeader) {
    ip := ctx.RemoteAddr()
    // make sure you format the ip in a way
    // that can be used for a file name (simple case):
    ip = strings.Replace(ip, ".", "_", -1)
    ip = strings.Replace(ip, ":", "_", -1)

    // you can use the time.Now, to prefix or suffix the files
    // based on the current time as well, as an exercise.
    // i.e unixTime :=	time.Now().Unix()
    // prefix the Filename with the $IP-
    // no need for more actions, internal uploader will use this
    // name to save the file into the "./uploads" folder.
    file.Filename = ip + "-" + file.Filename
}
```

# 中间件

## 不含中间件的空Iris app

Use

```
app := iris.New()
```

instead of

```
// Default with the Logger and Recovery middleware already attached.
app := iris.Default()
```

## 使用中间件

```go
import (
    "github.com/kataras/iris"

    "github.com/kataras/iris/middleware/recover"
    "github.com/kataras/iris/middleware/logger"
)

func main() {
    // Creates an application without any middleware by default.
    app := iris.New()

    // Recover middleware recovers from any panics and writes a 500 if there was one.
    app.Use(recover.New())

    requestLogger := logger.New(logger.Config{
        // Status displays status code
        Status: true,
        // IP displays request's remote address
        IP: true,
        // Method displays the http method
        Method: true,
        // Path displays the request path
        Path: true,
        // Query appends the url query to the Path.
        Query: true,

        // if !empty then its contents derives from `ctx.Values().Get("logger_message")
        // will be added to the logs.
        MessageContextKeys: []string{"logger_message"},

        // if !empty then its contents derives from `ctx.GetHeader("User-Agent")
        MessageHeaderKeys: []string{"User-Agent"},
    })
    app.Use(requestLogger)

    // Per route middleware, you can add as many as you desire.
    app.Get("/benchmark", MyBenchLogger(), benchEndpoint)

    // Authorization party /user.
    // authorized := app.Party("/user", AuthRequired())
    // exactly the same as:
    authorized := app.Party("/user")
    // per party middleware! in this case we use the custom created
    // AuthRequired() middleware just in the "authorized" group/party.
    authorized.Use(AuthRequired())
    {
        authorized.Post("/login", loginEndpoint)
        authorized.Post("/submit", submitEndpoint)
        authorized.Post("/read", readEndpoint)

        // nested group: /user/testing
        testing := authorized.Party("/testing")
        testing.Get("/analytics", analyticsEndpoint)
    }

    // Listen and serve on http://0.0.0.0:8080
    app.Run(iris.Addr(":8080"))
}
```

## log日志

```go
package main

import (
	"os"
	"time"

	"github.com/kataras/iris"
)

// Get a filename based on the date, just for the sugar.
func todayFilename() string {
    today := time.Now().Format("Jan 02 2006")
    return today + ".txt"
}

func newLogFile() *os.File {
    filename := todayFilename()
    // Open the file, this will append to the today's file if server restarted.
    f, err := os.OpenFile(filename, os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0666)
    if err != nil {
        panic(err)
    }

    return f
}

func main() {
    f := newLogFile()
    defer f.Close()

    app := iris.New()
    // Attach the file as logger, remember, iris' app logger is just an io.Writer.
    // Use the following code if you need to write the logs to file and console at the same time.
    // app.Logger().SetOutput(io.MultiWriter(f, os.Stdout))
    app.Logger().SetOutput(f)

    app.Get("/ping", func(ctx iris.Context) {
        // for the sake of simplicity, in order see the logs at the ./_today_.txt
        ctx.Application().Logger().Infof("Request path: %s", ctx.Path())
        ctx.WriteString("pong")
    })

    // Navigate to http://localhost:8080/ping
    // and open the ./logs{TODAY}.txt file.
    app.Run(
        iris.Addr(":8080"),
        iris.WithoutBanner,
        iris.WithoutServerError(iris.ErrServerClosed),
    )
}
```

# Cookies

```go
package main

import "github.com/kataras/iris"

func newApp() *iris.Application {
    app := iris.New()

    // Set A Cookie.
    app.Get("/cookies/{name}/{value}", func(ctx iris.Context) {
        name := ctx.Params().Get("name")
        value := ctx.Params().Get("value")

        ctx.SetCookieKV(name, value)

        ctx.Writef("cookie added: %s = %s", name, value)
    })

    // Retrieve A Cookie.
    app.Get("/cookies/{name}", func(ctx iris.Context) {
        name := ctx.Params().Get("name")

        value := ctx.GetCookie(name)

        ctx.WriteString(value)
    })

    // Delete A Cookie.
    app.Delete("/cookies/{name}", func(ctx iris.Context) {
        name := ctx.Params().Get("name")

        ctx.RemoveCookie(name)

        ctx.Writef("cookie %s removed", name)
    })

    return app
}

func main() {
    app := newApp()

    // GET:    http://localhost:8080/cookies/my_name/my_value
    // GET:    http://localhost:8080/cookies/my_name
    // DELETE: http://localhost:8080/cookies/my_name
    app.Run(iris.Addr(":8080"))
}
```

- Alternatively, use a regular `http.Cookie`: `ctx.SetCookie(&http.Cookie{...})`

- If you want to set custom the path: `ctx.SetCookieKV(name, value, iris.CookiePath("/custom/path/cookie/will/be/stored"))`.

- If you want to be available only to the current request path:

  ```
  ctx.SetCookieKV(name, value, iris.CookieCleanPath /* or iris.CookiePath("") */)
  ```

  - `iris.CookieExpires(time.Duration)`
  - `iris.CookieHTTPOnly(false)`

- `ctx.Request().Cookie(name)` is also available, it's the `net/http` approach

- Learn more about path parameter's types by clicking [here](https://github.com/kataras/iris/blob/master/_examples/routing/dynamic-path/main.go#L31).

# Session

此示例将说明如何存储和访问会话中的数据。

您不需要任何第三方库，但如果您需要，您可以使用任何兼容的会话管理器。

在此示例中，我们将仅允许通过了身份验证的用户在 `/secret`页面上查看我们的信息。 要获得访问权限，首先必须访问`/login`以获取有效的会话`cookie`，并将其登录。此外，他可以访问 `/logout` 以撤消对我们的信息的访问权限。

示例：

```go
package main

import (
    "github.com/kataras/iris"

    "github.com/kataras/iris/sessions"
)

var (
    cookieNameForSessionID = "mycookiesessionnameid"
    sess                   = sessions.New(sessions.Config{Cookie: cookieNameForSessionID})
)

func secret(ctx iris.Context) {

    //检查用户是否经过身份验证
    if auth, _ := sess.Start(ctx).GetBoolean("authenticated"); !auth {
        ctx.StatusCode(iris.StatusForbidden)
        return
    }

    //打印信息
    ctx.WriteString("The cake is a lie!")
}

func login(ctx iris.Context) {
    session := sess.Start(ctx)

    //身份验证就在这里
    // ...

    //将用户设置为已验证
    session.Set("authenticated", true)
}

func logout(ctx iris.Context) {
    session := sess.Start(ctx)

    //撤消用户身份验证
    session.Set("authenticated", false)
}

func main() {
    app := iris.New()

    app.Get("/secret", secret)
    app.Get("/login", login)
    app.Get("/logout", logout)

    app.Run(iris.Addr(":8080"))
}
```

运行示例：

```go
$ go get github.com/kataras/iris/sessions
$ go run main.go

$ curl -s http://localhost:8080/secret
Forbidden

$ curl -s -I http://localhost:8080/login
Set-Cookie: mycookiesessionnameid=MTQ4NzE5Mz...

$ curl -s --cookie "mycookiesessionnameid=MTQ4NzE5Mz..." http://localhost:8080/secret
The cake is a lie!
```

可以使用一个（或多个）`sessiondb`来实现会话持久性。

示例：

```go
package main

import (
    "time"
    "github.com/kataras/iris"
    "github.com/kataras/iris/sessions"
    "github.com/kataras/iris/sessions/sessiondb/redis"
    "github.com/kataras/iris/sessions/sessiondb/redis/service"
)

//使用redis 3.0.503版测试。
//对于Windows，请参阅：https：//github.com/ServiceStack/redis-windows
func main() {
    //替换正在运行的redis'服务器设置：
    db := redis.New(service.Config{
        Network:     service.DefaultRedisNetwork,
        Addr:        service.DefaultRedisAddr,
        Password:    "",
        Database:    "",
        MaxIdle:     0,
        MaxActive:   0,
        IdleTimeout: service.DefaultRedisIdleTimeout,
        Prefix:      ""}) //可选择在redis服务器之间配置网桥

    //当control + C / cmd + C时关闭连接
    iris.RegisterOnInterrupt(func() {
        db.Close()
    })

    defer db.Close() //如果应用程序出错，请关闭数据库连接。

    sess := sessions.New(sessions.Config{
        Cookie:  "sessionscookieid",
        Expires: 45 * time.Minute}, // <= 0意味着不会过期。 默认为0。
    )

    // 重要：
    sess.UseDatabase(db)

    //其余代码保持不变
    app := iris.New()

    app.Get("/", func(ctx iris.Context) {
        ctx.Writef("You should navigate to the /set, /get, /delete, /clear,/destroy instead")
    })
    app.Get("/set", func(ctx iris.Context) {
        s := sess.Start(ctx)
        //设置会话值
        s.Set("name", "iris")

        //测试获取
        ctx.Writef("All ok session value of the 'name' is: %s", s.GetString("name"))
    })

    app.Get("/set/{key}/{value}", func(ctx iris.Context) {
        key, value := ctx.Params().Get("key"), ctx.Params().Get("value")
        s := sess.Start(ctx)
        //设置会话值
        s.Set(key, value)

        //测试获取
        ctx.Writef("All ok session value of the '%s' is: %s", key, s.GetString(key))
    })

    app.Get("/get", func(ctx iris.Context) {
        //获取一个特定的键，作为字符串，如果没有找到只返回一个空字符串
        name := sess.Start(ctx).GetString("name")

        ctx.Writef("The 'name' on the /set was: %s", name)
    })

    app.Get("/get/{key}", func(ctx iris.Context) {
        //获取一个特定的键，作为字符串，如果没有找到只返回一个空字符串
        name := sess.Start(ctx).GetString(ctx.Params().Get("key"))

        ctx.Writef("The name on the /set was: %s", name)
    })

    app.Get("/delete", func(ctx iris.Context) {
        //删除特定 key
        sess.Start(ctx).Delete("name")
    })

    app.Get("/clear", func(ctx iris.Context) {
        //删除所有条目
        sess.Start(ctx).Clear()
    })

    app.Get("/destroy", func(ctx iris.Context) {
        // 销毁，删除整个会话数据和cookie
        sess.Destroy(ctx)
    })

    app.Get("/update", func(ctx iris.Context) {
        //使用新日期更新过期日期
        sess.ShiftExpiration(ctx)
    })

    app.Run(iris.Addr(":8080"), iris.WithoutServerError(iris.ErrServerClosed))
}
```



# 测试

```go
package main

import (
    "fmt"
    "testing"

    "github.com/kataras/iris/httptest"
)

// go test -v -run=TestCookiesBasic$
func TestCookiesBasic(t *testing.T) {
    app := newApp()
    e := httptest.New(t, app, httptest.URL("http://example.com"))

    cookieName, cookieValue := "my_cookie_name", "my_cookie_value"

    // Test Set A Cookie.
    t1 := e.GET(fmt.Sprintf("/cookies/%s/%s", cookieName, cookieValue)).Expect().Status(httptest.StatusOK)
    t1.Cookie(cookieName).Value().Equal(cookieValue) // validate cookie's existence, it should be there now.
    t1.Body().Contains(cookieValue)

    path := fmt.Sprintf("/cookies/%s", cookieName)

    // Test Retrieve A Cookie.
    t2 := e.GET(path).Expect().Status(httptest.StatusOK)
    t2.Body().Equal(cookieValue)

    // Test Remove A Cookie.
    t3 := e.DELETE(path).Expect().Status(httptest.StatusOK)
    t3.Body().Contains(cookieName)

    t4 := e.GET(path).Expect().Status(httptest.StatusOK)
    t4.Cookies().Empty()
    t4.Body().Empty()
}
```

# 自定义HTTP错误

`iris`开发人员能够注册自己的处理程序，如`404`未找到的`http`状态，`500`内部服务器错误等等。

示例：

```go
//当报 `404` 时候渲染自定义的 404 错误模板
app.OnErrorCode(iris.StatusNotFound, func(ctx iris.Context){
    ctx.View("errors/404.html")
})

app.OnErrorCode(500, func(ctx iris.Context){
    // 编写对500 错误的响应
})
```

# Websockets

在此示例中，我们将通过浏览器在Web套接字之间创建一个小聊天。

服务器代码示例：

```go
package main

import (
    "fmt"
    "github.com/kataras/iris"
    "github.com/kataras/iris/websocket"
)

func main() {
    app := iris.New()

    app.Get("/", func(ctx iris.Context) {
        ctx.ServeFile("websockets.html", false) //第二个参数：是否启用gzip
    })

    setupWebsocket(app)
    // x2
    // http://localhost:8080
    // http://localhost:8080
    //写点东西，按提交，查看结果。
    app.Run(iris.Addr(":8080"))
}

func setupWebsocket(app *iris.Application) {
    //创建我们的echo websocket服务器
    ws := websocket.New(websocket.Config{
        ReadBufferSize:  1024,
        WriteBufferSize: 1024,
    })
    ws.OnConnection(handleConnection)

    //在端点上注册服务器。
    //在websockets.html中查看内联javascript代码，此端点用于连接服务器。
    app.Get("/echo", ws.Handler())

    //提供javascript built'n客户端库，
    //请参阅websockets.html脚本标记，使用此路径。
    app.Any("/iris-ws.js", func(ctx iris.Context) {
        ctx.Write(websocket.ClientSource)
    })
}

func handleConnection(c websocket.Connection) {
    //从浏览器中读取事件
    c.On("chat", func(msg string) {
        //将消息打印到控制台，c .Context（）是 iris 的http上下文。
        fmt.Printf("%s sent: %s\n", c.Context().RemoteAddr(), msg)
        //将消息写回客户端消息所有者：
        // c.Emit("chat", msg)
        c.To(websocket.Broadcast).Emit("chat", msg)
    })
}
```

示例客户端（javascript）代码：

```html
<!-- websockets.html -->
<input id="input" type="text" />
<button onclick="send()">Send</button>
<pre id="output"></pre>
<script src="/iris-ws.js"></script>
<script>
    var input = document.getElementById("input");
    var output = document.getElementById("output");

    //ws.js 需要自己下载
    //ws 自动服务的'/iris-ws.js'
    var socket = new Ws("ws://localhost:8080/echo");
    socket.OnConnect(function () {
        output.innerHTML += "Status: Connected\n";
    });

    socket.OnDisconnect(function () {
        output.innerHTML += "Status: Disconnected\n";
    });

   //从服务器读取事件
    socket.On("chat", function (msg) {
        addMessage(msg)
    });

    function send() {
        addMessage("Me: "+input.value) //写自己
        socket.Emit("chat", input.value);//将聊天事件数据发送到websocket服务器
        input.value = ""; //清除输入
    }

    function addMessage(msg) {
        output.innerHTML += msg + "\n";
    }
</script>
```

# 流写入

```go
package main

import (
    "fmt" //只是一个可选的助手
    "io"
    "time" //展示延迟
    "github.com/kataras/iris"
)

func main() {
    app := iris.New()
    app.Get("/", func(ctx iris.Context) {
        ctx.ContentType("text/html")
        ctx.Header("Transfer-Encoding", "chunked")
        i := 0
        ints := []int{1, 2, 3, 5, 7, 9, 11, 13, 15, 17, 23, 29}
        //以块的形式发送响应，并在每个块之间等待半秒钟
        ctx.StreamWriter(func(w io.Writer) bool {
            fmt.Fprintf(w, "Message number %d<br>", ints[i])
            time.Sleep(500 * time.Millisecond) // simulate delay.
            if i == len(ints)-1 {
                return false //关闭并刷新
            }
            i++
            return true //继续写入数据
        })
    })

    type messageNumber struct {
        Number int `json:"number"`
    }

    app.Get("/alternative", func(ctx iris.Context) {
        ctx.ContentType("application/json")
        ctx.Header("Transfer-Encoding", "chunked")
        i := 0
        ints := []int{1, 2, 3, 5, 7, 9, 11, 13, 15, 17, 23, 29}
        //以块的形式发送响应，并在每个块之间等待半秒钟。
        for {
            ctx.JSON(messageNumber{Number: ints[i]})
            ctx.WriteString("\n")
            time.Sleep(500 * time.Millisecond) // simulate delay.
            if i == len(ints)-1 {
                break
            }
            i++
            ctx.ResponseWriter().Flush()
        }
    })
    app.Run(iris.Addr(":8080"))
}
```

