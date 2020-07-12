#include "Node.h"

void Node::enablePositivePolarity(AD2Easy& ad2)
{ 
	if (!positiveEnabled and !negativeEnabled) {
		positiveEnabled = true;
		ad2.write(ev::ad2::dataBus, posCMD);
	}
}

void Node::enableNegativePolarity(AD2Easy& ad2)
{
	if (!negativeEnabled and !positiveEnabled) {
		negativeEnabled = true;
		ad2.write(ev::ad2::dataBus, negCMD);
	}
}