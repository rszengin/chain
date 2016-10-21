# cmp::chain
### The Chained Comparison
In C++ chained comparisons like ‘X<=Y<=Z’ do not have their mathematical meaning. The standard describes this behaviour (§5.9.1) about relational operators. But normal human intention while writing and intended meaning while reading an expression like this is equivalent to mathematical. We can observe this fact on beginners' errors. Meeting this expectation is easy with addition of a simple code. Compiler optimizes away the abstraction. So, the end result is the same.

### Example Usage
Comparison chain is starts with the initiator object. It constructs the first comparator object with the first comparison operand.  Comparison operator of the comparator object returns result of the comparison operation with the second operand and a reference to the second operand as another comparator object. The process continues until the end of the comparison chain. At last, bool conversion operator of the last created comparator object returns the result of the comparison. It works with any type if there is a relational operator defined.

```C++
for (int inx = 0; inx < 20; ++inx) {
  if (cmp::chain < 5 <= inx < 15)
    std::cout << inx << " ";
}
```

```C++
std::vector<std::string> words { "aback", "abaft", ...};
for (auto& x : words) {
  if (cmp::chain < "abb" <= x < "abe")
    std::cout << x << " ";
}
```

```C++
std::srand(std::time(nullptr));
for (int inx = 0; inx < 1000; ++inx) {
  double a = double(std::rand()) / RAND_MAX;
  double b = double(std::rand()) / RAND_MAX;
  double c = double(std::rand()) / RAND_MAX;

  if(cmp::chain < 0.4 < a <= b <= c < 0.6) {
    std::cout << "Round "<< inx << ") Variables in the range : " <<
        a << " <= " << b << " <= " << c << "\n";
  }
}
```
