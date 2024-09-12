# STL source code学习随笔

### [🚀效率提升] std::vector的==运算符中使用的bool运算短路

##### STL代码小摘

```c++
template <class _Tp, class _Allocator>
_LIBCPP_CONSTEXPR_SINCE_CXX20 inline _LIBCPP_HIDE_FROM_ABI bool
operator==(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y) {
  const typename vector<_Tp, _Allocator>::size_type __sz = __x.size();
  return __sz == __y.size() && std::equal(__x.begin(), __x.end(), __y.begin());
}
```

##### 分析

通过先决运算`__sz == __y.size()`，若为`false`，则bool运算短路，无需执行相对耗时的`std::equal()`函数

### [🔨语言特性] std::vector中的<=>运算符重载

##### STL代码小摘

```c++
template <class _Tp, class _Allocator>
_LIBCPP_HIDE_FROM_ABI constexpr __synth_three_way_result<_Tp>
operator<=>(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y) {
  return std::lexicographical_compare_three_way(
      __x.begin(), __x.end(), __y.begin(), __y.end(), std::__synth_three_way<_Tp, _Tp>);
}
```

##### 分析

> *from [cpp_reference](https://en.cppreference.com/w/cpp/language/default_comparisons)*
>
> ### Three-way comparison
>
> An operator`<=>` for a class type can be defined as defaulted with any return type.

`static_cast<T>(<=>)`，

对a和b的比较

```c++
return (a == b) ? T::equal :
		(a < b) ? T::less :
				T::greater;
```

其中`T`可为：`std::strong_ordering`/`std::less_ordering`/`std::partial_ordering`

