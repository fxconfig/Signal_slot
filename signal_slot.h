/********************************************************
*  信号与槽：
*        两个类之间互相回调的实现
*
*   来源： 网络
*   修改：Peter Yang
*         将Slot 参数由固定个数 class T1 修改为 变长参数模板 class ... Args
*
*
*
*
*********************************************************/


#pragma once
#include <vector>

template<class ... Args>
class SlotBase
{
public:
	virtual void Exec(Args ... params) = 0;
	virtual ~SlotBase() {};
};

template<class T, class ... Args>
class SlotImpl : public SlotBase<Args ...>
{
public:
	SlotImpl(T* pObj, void (T::*func)(Args ...))
	{
		m_pObj = pObj;
		m_Func = func;
	}
	void Exec(Args ... params)
	{
		if (0 == m_pObj || 0 == m_Func) return;   //添加以防止意外访问
		(m_pObj->*m_Func)(params ...);
	}
private:
	T* m_pObj;
	void (T::*m_Func)(Args ...);
};


template<class ... Args>
class Signal
{
public:
	template<class T>
	void Bind(T* pObj, void (T::*func)(Args ...))
	{
		m_pSlotSet.push_back(new SlotImpl<T, Args ...>(pObj, func));
	}
	~Signal()
	{
		for (int i = 0; i<(int)m_pSlotSet.size(); i++)
		{
			delete m_pSlotSet[i];
		}
	}
	void operator()(Args ... params)
	{
		for (int i = 0; i<(int)m_pSlotSet.size(); i++)
		{
			m_pSlotSet[i]->Exec(params ...);
		}
	}
private:
	std::vector< SlotBase<Args ...>* > m_pSlotSet;
};

#define CONNECT_SOLOT_TO_SIGNAL( sender, signal, receiver, method) ( (sender)->signal.Bind(receiver, method) )
