#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "atypes.h"
#include "me_struct.h"
#include "me.h"

Void fsEstimateMotion(Uint8* pbSrc, Uint8* pbRef, MotionVector* pMotionVector)
{
	int sad = 0;
	for (int y = 0;y < PIC_HEIGHT;y += 16)
		for (int x = 0; x < PIC_WIDTH; x += 16) {
			if (x == 0 && y == 0) {
				sad = sad16(pbSrc, pbRef);
				pMotionVector->nX = x;
				pMotionVector->nY = y;
			}
			else if (x == 0 && y > 0) {
				sad = sad16(pbSrc + y * PIC_WIDTH, pbRef + (y - 16) * PIC_WIDTH);
				pMotionVector->nX = 0;
				pMotionVector->nY = -16;
			}
			else if (x > 0 && y == 0) {
				sad = sad16(pbSrc + x, pbRef + x - 16);
				pMotionVector->nX = -16;
				pMotionVector->nY = 0;
			}
			else {
				sad = sad16(pbSrc + y * PIC_WIDTH + x, pbRef + (y - 16) * PIC_WIDTH + x - 16);
				pMotionVector->nX = -16;
				pMotionVector->nY = -16;
			}

			for (int j = 0; j < 32; j++)
				for (int i = 0; i < 32; i++) {
					if (y + j - 16 >= 0 && y + j <= PIC_HEIGHT && x + i - 16 >= 0 && x + i <= PIC_WIDTH) {

						if (sad16(pbSrc + y * PIC_WIDTH + x, pbRef + (y + j - 16) * PIC_WIDTH + x - 16 + i) < sad) {
							sad = sad16(pbSrc + y * PIC_WIDTH + x, pbRef + (y + j - 16) * PIC_WIDTH + x - 16 + i);
							pMotionVector->nX = i - 16;
							pMotionVector->nY = j - 16;
						}
						pMotionVector->nSad = sad;
					}
				}
			pMotionVector++;
		}

}
