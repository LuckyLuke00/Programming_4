#include "BlowBubbleCommand.h"

namespace dae
{
	BlowBubbleCommand::BlowBubbleCommand(const std::function<void()>& blowBubbleFunction) :
		m_BlowBubbleFunction{ blowBubbleFunction }
	{}

	void BlowBubbleCommand::Execute()
	{
		if (m_BlowBubbleFunction)
			m_BlowBubbleFunction();
	}
}
