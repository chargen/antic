/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2012 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"
#include "qfb.h"

int main(void)
{
    int result;
    flint_rand_t state;
    qfb * forms;
    qfb * forms2;
    slong i, j, k, num, num2;

    printf("reduced_forms....");
    fflush(stdout);

    flint_randinit(state);

    for (i = 1; i < 30000; i++) 
    {
        num = qfb_reduced_forms(&forms, -i);
        num2 = qfb_reduced_forms_large(&forms2, -i);
        
        result = (num == num2);
        for (j = 0; result == 1 && j < num; j++)
        {
            for (k = 0; k < num; k++)
               if (qfb_equal(forms + j, forms2 + k))
                   break;

            result &= (k != num);

            if (!result) break;
        }
        
        if (!result)
        {
            printf("FAIL:\n");
            
            if (num == num2)
            {
                qfb_print(forms + j);
                printf(" != ");
                qfb_print(forms2 + j);
                printf("\n");
             } else
                printf("%ld != %ld\n", num, num2);
            
            abort();
        }

        qfb_array_clear(&forms, num);
        qfb_array_clear(&forms2, num2);
    }

    flint_randclear(state);
    _fmpz_cleanup();
    printf("PASS\n");
    return 0;
}
