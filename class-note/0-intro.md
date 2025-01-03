# 绪论

## 1 数据结构的概念

> **计算机发展过程中数据处理的任务**
>
> 早期：数值计算
>
> 中后期：非数值计算

数据结构是一门研究（非数值计算的）程序设计问题中所出现的计算机操作对象以及它们之间的**关系**和**操作**的学科

程序=**数据结构**+**算法**

### 概念

- **数据**
- **数据元素**（数据成员）
- **数据对象**：具有相同性质的数据元素（数据成员）的集合

### **数据结构的形式定义**：

数据结构由某一数据对象及该对象中所有数据成员之间的关系组成，数学上记为

$Data\_Structure = \set{D, R}$

其中，$D$是某一数据对象，$R$是该对象中所有数据成员之间关系的**有限集合**

### 数据结构涉及的方面

- **数据的逻辑结构**：面向问题，*线性表还是树/图...*
  - 是对数据成员之间的逻辑关系的描述，它可以用一个数据成员的集合和定义在此集合上的若干关系来表示
- **数据的物理结构**：面向计算机，*堆区存储还是栈区存储？*
  - 是逻辑结构、数据在计算机中的实现
- **操作及实现**：*成员函数、接口...*

### 关系的映像方法

对关系对$<x,y>$

1. **顺序映像**（顺序存储方法）：以相对的存储位置表示后继关系。如数组
2. **链式映像**（链接存储方法）：以附加信息（指针）表示后继关系。如链表
3. **索引存储方法**：如哈希表
4. **散列存储方法**

### 数据结构的分类

- **线性结构**：表、栈、队列
- **非线性结构**
  - 层次结构：树、二叉树、堆
  - 网状结构：图
  - 其他：集合

## 2 数据结构的抽象形式

### 数据类型

一组性质相同的**值的集合**，以及定义于这个值集合上的**一组操作**的总称 

### 抽象数据类型（ADTs）

- 由用户定义，用以表示应用问题的**数据模型**
- 由**基本的数据类型**组成，并包括**一组相关的服务**（或称为操作）
- 支持了**逻辑设计**和**物理实现**的分离，支持封装和信息屏蔽

> 如：C++/Java等面向对象编程语言中的“类”；Rust/Go等编程语言中的“结构体与实现”

- 设计者可以根据问题定义ADT包含的信息，给出相关功能的实现，并提供公共接口；用户不需要考虑其物理实现，只需要使用公共界面的接口对ADT进行操作

> 如：**设计一个自然数的ADT**
>
> **object**：一个$\Z$的有序子集合，开始于0，结束于机器能表示的最大整数
>
> **function**：+, -, *, /, >=, <=, >, <, ==

### 数据抽象

- **数据抽象**：数据的使用者只需要知道对数据所能实施的**操作**以及这些**操作之间的关系**，而不必知道数据的具体表示
- **数据封装**：
  - 把数据表示及其操作作为一个**整体**来进行实现
  - 数据的**具体表示**对使用者是**不可见**的，对数据的访问只能通过**封装体**所提供的对外**接口**来完成
- **对象**是数据及其操作的封装体，对象的特征由相应的**类**来描述

## 3 算法的定义

**算法 Algorithms+数据结构 DataStructure=程序 Programs**

### 算法的描述

- 自然语言描述
- 流程图
- 伪语言
- 类语言

### 算法的重要特性

- **有输入** 有0个或多个输入
- **有输出** 有一个或多个输出
- **确定性** 每一步定义都是确切、无歧义的
- **有穷性** 算法应在执行有限步后结束
- **有效性** 每一条运算应该足够基本

### 算法的效率

**时间复杂度**与**空间复杂度**

**衡量算法效率的方法**

- 后期测试

- 事前估计

### 算法的后期测试

在算法的某些部位插装时间函数`time()`

### 算法的事前运行

**时间复杂度**

- **程序步**：语法语义上有意义的语句记为1

  > 例如：
  >
  > 表达式、赋值语句、循环体（每次）：程序步数为1

- **算法的渐进分析**

  - 算法中关键操作重复执行的次数是问题规模n的某个函数$T(n)$
  - 渐进时间复杂度$T(n)=O(f(n))$


