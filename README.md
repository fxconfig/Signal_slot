# Signal_slot
C++ Signal and Slot between two classes  

原文链接：http://blog.csdn.net/ilvu999/article/details/7948429  
若原文作者觉得不适，请联系本人删除本仓库  

使用 C++ 简单实现 信号与槽，用于两个不同的类实例之间订阅信号，实现回调。
在原作者基础上做了简单修改，使 Signal 能携带变长参数。 

请使用支持 C++11 标准的编译器，若没有，则请参见原作者文章

#### 特点
+ 一个信号可被多个槽（也就是回调）订阅
+ 信号支持变长参数
+ 单个头文件

#### 不足
+ 无法绑定静态函数
+ 实例指针有效性未作判断，当实例生命周期结束，需删除 slot

 
如有不对之处请指出。 

只有一个头文件。 
请使用支持 C++11 标准的编译器编译。。。 

### 使用方法  

~~~cpp
int main()
{
  A* pA = new A;
	B* pB = new B;
	C* pC = new C;
	CONNECT_SOLOT_TO_SIGNAL(pC, ValueChanged, pA, &A::FuncOfA);
	CONNECT_SOLOT_TO_SIGNAL(pC, ValueChanged, pB, &B::FuncOfB);
	pC->SetValue(10,1.1); /* A::FuncOfA(10)
	                     B::FuncOfB(10) */
	pC->SetValue(5,1.1);  /* A::FuncOfA(5)
	                     B::FuncOfB(5) */
	pC->SetValue(5,1.2);
	delete pC;
	delete pB;
	delete pA;
	return 0;
}
···

#### 结果如下
![image](https://github.com/fxconfig/Signal_slot/master/image.png)  
