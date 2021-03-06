# My Lang

自作言語の話です

```
def main {
    printf "Hello, world!";
    let a:int;
    a = 10;
    if 6 <= a < 13 {
        a = a + 6;
    } else {
        a = a - 2;
    }
    printf "a = %d\n" a;
    printf "a*2 = %d\n" (a * 2);
    return 0;
}

def func a:int b:int {
    return (a + b) * b;
}
```

```
* : pointer
int
char

int
char
*int
**char
```

```
def
let
if
else
while
for
to
downto
while
return
```

```
!"#$%&'()-=^~\|@`[]{};+:*,<>./?

!#$~@?,`

()
[]
{}
"'
+-*/%=&|^<>
\
.
;
:

( ... ) : 括弧
[ ... ] : 
{ ... } : 命令セット
" ... " : 文字列
'.'     : 文字
` ... ` : 
a + b   : 和
a - b   : 差
a * b   : 積
a / b   : 商
a % b   : 余
a ** b  : 累乗
a & b   : ビットand
a | b   : ビットor
a ^ b   : ビットxor
a = b   : 代入
a == b  : 等価
a != b  : 非等価
a >= b  : 以下
a <= b  : 以上
a > b   : より大きい
a < b   : より小さい
a && b  : and
b || b  : or
a ^^ b  : xor
* a     : aポイント先の値
& a     : aの参照
\.      : 特殊文字
a . b   : a内のb
;       : 文末
:       : 型指定
# ...   : コメント
#-...-# : 範囲コメント
```
