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

assert 0 0
assert 42 "42"
assert 13 "8+5"
assert 3 "8-5"
assert 40 "8*5"
assert 1 "8/5"
assert 2 "8/4"
assert 13 "7+3*2"
assert 18 "3*(4+2)"
assert 42 "(1+6)*(4+2)"
assert 2 "27%5"
assert 2 "8+2*-3"

echo OK