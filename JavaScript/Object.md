# JavaScript对象

## 创建对象

```js
person=new Object();
person.firstname="Bill";
person.lastname="Gates";
person.age=56;
person.eyecolor="blue";
```

或

```js
var person={
    firstname:"Bill",
    lastname:"Gates", 
    id:5566
    getName: function(){return firstname + " " + lastname; }
};
```

寻址方式：

```js
name = person.lastname;
name = person['lastname'];
name = person.getName()
```

