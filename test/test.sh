#!/bin/bash
assert() {
  expected="$1"
  input="$2"

  ./HitsujiLang "$input" > tmp.s
  cc -o tmp tmp.s
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

echo OK