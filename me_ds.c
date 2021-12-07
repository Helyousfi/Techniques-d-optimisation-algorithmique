#include <stdio.h>
#include <stdlib.h>

#include "atypes.h"
#include "me_struct.h"
#include "me.h"
#define MAX_ITER 16

static int index_min_SAD(int* SAD, int* bord)
{
	int index = 0;
	int min = SAD[0];
	for (int i = 1; i < 5; i++)
		if (SAD[i] < min && bord[i] == 1)
		{
			min = SAD[i];
			index = i;
		}
	return index;
}

Void dsEstimateMotion(Uint8* pbSrc, Uint8* pbRef, MotionVector* pMotionVector)
{
	int index;
	int sad;
	int SAD[5];
	int xRef, yRef;

	int var_x_ref[5];
	int var_y_ref[5];
	int bord[5];
	int k = 0;

	for (int y = 0;y < PIC_HEIGHT;y += 16) {
		for (int x = 0; x < PIC_WIDTH; x += 16) {
			int nX = 0, nY = 0;
			// Calcul du sad pour la centrale
			sad = sad16(pbSrc + y * PIC_WIDTH + x, pbRef + y * PIC_WIDTH + x);
			xRef = x;
			yRef = y;

			for (int k = 0; k < MAX_ITER; k++)
			{
				// Calcul pour la Gauche, Haute, Droite, Basse
				for (int r = 0; r < 5; r++)
				{
					if (r == 0) {
						var_x_ref[r] = xRef;
						var_y_ref[r] = yRef;
					}
					else if (r == 1) {
						var_x_ref[r] = xRef - 1;
						var_y_ref[r] = yRef;
					}
					else if (r == 2) {
						var_x_ref[r] = xRef;
						var_y_ref[r] = yRef - 1;
					}
					else if (r == 3) {
						var_x_ref[r] = xRef + 1;
						var_y_ref[r] = yRef;
					}
					else if (r == 4) {
						var_x_ref[r] = xRef;
						var_y_ref[r] = yRef + 1;
					}

					if (var_x_ref[r] >= 0 && var_y_ref[r] >= 0 && var_x_ref[r] <= PIC_WIDTH - 16 && var_y_ref[r] <= PIC_HEIGHT - 16)
						bord[r] = 1; //Pas de pb de bord
					else
						bord[r] = 0;
					if (bord[r])
						SAD[r] = sad16(pbSrc + y * PIC_WIDTH + x, pbRef + var_y_ref[r] * PIC_WIDTH + var_x_ref[r]);
				}

				index = index_min_SAD(SAD, bord);
				if (SAD[index] < sad)
				{
					xRef = var_x_ref[index];
					yRef = var_y_ref[index];


					if (index == 1) {
						nX -= 1;
					}
					else if (index == 2) {
						nY -= 1;
					}
					else if (index == 3) {
						nX += 1;
					}
					else if (index == 4) {
						nY += 1;
					}
					sad = SAD[index];
				}
				else break;
			}
			pMotionVector[k].nX = nX;
			pMotionVector[k].nY = nY;
			pMotionVector[k].nSad = sad;
			k++;
		}
	}
}
