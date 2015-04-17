//
//  dmxMap.cpp
//  connexionUsineHydro
//
//  Created by Julien on 16/04/2015.
//
//

#include "dmxMap.h"

int	dmxMap::getChannel(int channel)
{
	if (channel == 1) 	return 73;
	if (channel == 3) 	return 74;
	if (channel == 5) 	return 75;
	if (channel == 59) 	return 76;
	if (channel == 60) 	return 77;

	return channel;
}
