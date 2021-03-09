# My Lang

## できる

- 比較演算子の連鎖

```
if a < b <= c {
    ...
}
```

## できない

- 型の実装

```
let a:int;
```

- breakやcontinueの実装

```
# Endまで飛ぶ
{
    break;
}

# Beginに戻る
{
    continue;
}
```

- ブロックやifなどから値を返す

```
a = {
    break 1;
}

return if a == b { break 1; } else { break 3; }
```

- forをrangeにする

```
# n = {1, 2, 3, 4}}
for n to 5 {
    ...
}

# n = {3, 5, 7, 9}
for n from 3 to 10 step 2 {
    ...
}
```

- 関数呼び出しを()を使わずに

```
func arg1 arg2 arg3;
```

## メモ

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
