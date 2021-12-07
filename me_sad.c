#include <stdlib.h>

#include "atypes.h"
#include "me_struct.h"
#include "me.h"

Int g_nSadCount = 0;

Int sad16(Uint8 *pbSrc, Uint8 *pbRef)
{
	Int i, j;
	Int sad = 0;

	for (j = 0; j < 16; j++)
	{
		for (i = 0; i < 16; i++)
		{
			sad += abs(pbSrc[j * PIC_WIDTH + i] - pbRef[j * PIC_WIDTH + i]);
		}
	}
	
	g_nSadCount++;

	return sad;
}
