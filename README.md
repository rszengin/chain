# chain
### The Chained Comparison
In C++ chained comparisons like "X<=Y<=Z" do not have their mathematical meaning. The standard describes this behaviour (§5.9.1) about relational operators. But normal human intention while writing and intended meaning while reading an expression like this is equivalent to mathematical. We can observe this fact on beginners' errors. Meeting this expectation is possible via this simple chained comparison code. Compiler optimizes away the abstraction. So, the end result is the same.

### Usage
Mixed ordering of comparison operators are not allowed. Comparisons can be chained only Ascending or Descending. "chain" is a default defined "Initiator" object for convenience. Every comparison chain starts with an Initiator object. 

"<<" operator following "Initiator" starts and forces an Ascending ordered comparison. In an Ascending ordered chain only operators of "<" and "<=" are allowed.

">>" operator following "Initiator" starts and forces a Descending ordered comparison. In a Descending ordered chain only operators of ">" and ">=" are allowed.

Violation of these rules will result in a compile time error.

The process continues until the end of the comparison chain. At last, bool conversion operator of the last created object returns the result of the comparison. It works with any type if there is a relational operator defined.

### Examples


```C++
for (int inx = 0; inx < 20; ++inx) {
  if (cmp::chain << 5 <= inx < 15)
    std::cout << inx << " ";
  if (cmp::chain >> 15 > x >= 5)
    std::cout << x << " ";
}
```

```C++
std::vector<std::string> words { "aback", "abaft", ...};
for (auto& x : words) {
  if (cmp::chain << "abb" <= x < "abe")
    std::cout << x << " ";
  if (cmp::chain >> "abe" > x >= "abb")
	std::cout << x << " ";
}
```

```C++
std::srand(std::time(nullptr));
for (int inx = 0; inx < 1000; ++inx) {
  double a = double(std::rand()) / RAND_MAX;
  double b = double(std::rand()) / RAND_MAX;
  double c = double(std::rand()) / RAND_MAX;

  if(cmp::chain << 0.4 < a <= b <= c < 0.6) {
    std::cout << "Round "<< inx << ") Variables in the range : " <<
        a << " <= " << b << " <= " << c << "\n";
  }
}
```

### Comparison of resulting machine code (using GCC -O1 flag)

    | chained |     | standard
--- | ------- | --- | ---
0x401678:|   mov     (%rdi),%edx          |0x4016be:|   mov     (%rbx),%edx
 35      |`if (cmp::chain << 5 <= x < 15)`   | 40      |`if (5 <= x && x < 15)`
0x40167a:|   lea     -0x5(%rdx),%eax      |0x4016c0:|   lea     -0x5(%rdx),%eax
0x40167d:|   cmp     $0x9,%eax            |0x4016c3:|   cmp     $0x9,%eax
0x401680:|   ja      0x40169b `<main()+213>`|0x4016c6:|   ja      0x4016e1 `<main()+283>`

    | chained |     | standard
--- | ------- | --- | ---
102|`if(cmp::chain << 0.4 < a <= b <= c < 0.6)`|114|`if(0.4 < a && a <= b && b <= c && c < 0.6)`
0x402e0e:|   ucomisd 0xa99b2(%rip),%xmm7 # 0x4ac7c8 |0x402f51:|   ucomisd %xmm7,%xmm6
0x402e16:|   seta    %dl                            |0x402f55:|   setae   %dl
0x402e19:|   ucomisd %xmm7,%xmm6                    |0x402f58:|   ucomisd 0xa9868(%rip),%xmm7 # 0x4ac7c8
0x402e1d:|   setae   %al                            |0x402f60:|   seta    %al
0x402e20:|   and     %edx,%eax                      |0x402f63:|   and     %edx,%eax
0x402e22:|   ucomisd %xmm6,%xmm8                    |0x402f65:|   ucomisd %xmm6,%xmm8
0x402e27:|   setae   %dl                            |0x402f6a:|   setae   %dl
0x402e2a:|   test    %dl,%al                        |0x402f6d:|   test    %dl,%al
0x402e2c:|   je      0x402ee2 <main()+6428>         |0x402f6f:|   je      0x403025 <main()+6751>
0x402e32:|   ucomisd %xmm8,%xmm10                   |0x402f75:|   ucomisd %xmm8,%xmm10
0x402e37:|   jbe     0x402ee2 <main()+6428>         |0x402f7a:|   jbe     0x403025 <main()+6751>
