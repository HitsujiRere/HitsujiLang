#!/bin/bash

cc -c test/lib-c.c -o tmp-lib-c.o

assert() {
  expected="$1"
  input="$2"

  ./HitsujiLang "$input" > tmp.s
  cc -o tmp tmp.s tmp-lib-c.o
  ./tmp
  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

assert 0 "0;"
assert 42 "42;"
assert 13 "8+5;"
assert 3 "8-5;"
assert 40 "8*5;"
assert 1 "8/5;"
assert 2 "8/4;"
assert 13 "7+3*2;"
assert 18 "3*(4+2);"
assert 42 "(1+6)*(4+2);"
assert 2 "27%5;"
assert 2 "8+2*-3;"
assert 1 "5==5;"
assert 0 "5==4;"
assert 1 "5!=4;"
assert 0 "5!=5;"
assert 1 "5>=4;"
assert 1 "5>=5;"
assert 0 "4>=5;"
assert 1 "5>4;"
assert 0 "5>5;"
assert 1 "5<=5;"
assert 1 "4<=5;"
assert 0 "5<=4;"
assert 1 "4<5;"
assert 0 "5<5;"
assert 8 "4;8;"
assert 8 "a=5+3;"
assert 10 "a=5+3;a+2;"
assert 23 "a=5+3;b=a*2;a+b-1;"
assert 11 "var1=7;var2=4;var3=var1+var2;var3;"
assert 7 "6;return 7;return 8;"
assert 1 "1 && 1;"
assert 0 "1 && 0;"
assert 0 "0 && 1;"
assert 0 "0 && 0;"
assert 1 "1 && 1 && 1;"
assert 0 "0 && 1 && 1;"
assert 0 "1 && 0 && 1;"
assert 0 "1 && 1 && 0;"
assert 1 "1 || 1;"
assert 1 "1 || 0;"
assert 1 "0 || 1;"
assert 0 "0 || 0;"
assert 1 "1 || 0 || 0;"
assert 1 "0 || 1 || 0;"
assert 1 "0 || 0 || 1;"
assert 0 "0 || 0 || 0;"
assert 1 "1 < 3 < 5 == 5 <= 9 >= 3 > 2 != 0;"
assert 0 "3 < 3 < 5 == 5 <= 9 >= 3 > 2 != 0;"
assert 0 "1 < 1 < 5 == 5 <= 9 >= 3 > 2 != 0;"
assert 0 "1 < 5 < 5 == 5 <= 9 >= 3 > 2 != 0;"
assert 0 "1 < 3 < 2 == 2 <= 9 >= 3 > 2 != 0;"
assert 0 "1 < 3 < 7 == 5 <= 9 >= 3 > 2 != 0;"
assert 0 "1 < 3 < 5 == 6 <= 9 >= 3 > 2 != 0;"
assert 0 "1 < 3 < 5 == 5 <= 4 >= 3 > 2 != 0;"
assert 0 "1 < 3 < 5 == 5 <= 1 >= 3 > 2 != 0;"
assert 0 "1 < 3 < 5 == 5 <= 8 >= 9 > 2 != 0;"
assert 0 "1 < 3 < 5 == 5 <= 9 >= 0 > 2 != 0;"
assert 0 "1 < 3 < 5 == 5 <= 9 >= 3 > 7 != 0;"
assert 0 "1 < 3 < 5 == 5 <= 9 >= 3 > 2 != 2;"
assert 5 "a = 4; if 1 { a = 5; } a;"
assert 4 "a = 4; if 0 { a = 5; } a;"
assert 5 "if 7==7 { return 5; } else { return 3; }"
assert 3 "if 3==7 { return 5; } else { return 3; }"
assert 9 "a=4;while a < 9 {a = a + 1;} a;"
assert 3 "a=4;while a < 9 {a = a + 1;} else {a = 3;} a;"
assert 10 "a=3;b=0;for {a = 1; a <= 4; a = a+1} {b = b + a;} b;"
assert 20 "a=3;b=0;for {a = 1; a <= 4; a = a+1} {b = b + a;} else {b = b + 10;} b;"
assert 17 "ret17();"
assert 14 "add(5, 9);"

echo OK