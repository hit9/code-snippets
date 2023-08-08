识别一个简单的浮点数

* 支持正负号
* 支持小数点

合法例子:

```
'31.25'
'0.2'
'.2'
'1.'
'-5.28'
'+1.2'
'1.0'
'123'
'+123'
'-2'
```

非法例子:

```
'-.'
'-'
'+'
'-.5'
'+-1'
'1.1.1'
''
'.'
```

- [博客 - 自动机校验浮点数字符串 (DFA & NFA)](https://writings.sh/post/statemachine-validate-float)
- [NFA 状态机实现 - C++](validate-simple-float-nfa-cpp)
- [DFA 状态机实现 - C++](validate-simple-float-dfa-cpp)
