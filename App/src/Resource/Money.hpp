#pragma once
#include <Siv3D.hpp>

class Money
{
public:
	//現在の所持金を取得
	static int getAmount() { return m_amount; }

	//将来的な増減のための関数（現在は概念のみ）
	static void add(int value)
	{
		m_amount += value;
	}

	static bool subtract(int value)
	{
		if (m_amount >= value)
		{
			m_amount -= value;
			return true;
		}
		return false;
	}

private:
	//所持金
	static int m_amount;
};
