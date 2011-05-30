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

    Copyright (C) 2011 Fredrik Johansson

******************************************************************************/

#include <stdlib.h>
#include "flint.h"
#include "fmpz_poly.h"
#include "fmpz_poly_mat.h"

void
fmpz_poly_mat_det_interpolate(fmpz_poly_t det, const fmpz_poly_mat_t A)
{
    long i, l, n, p;

    fmpz_mat_t X;
    fmpz * x;
    fmpz * d;

    n = A->r;

    if (n == 0)
    {
        fmpz_poly_one(det);
        return;
    }

    l = fmpz_poly_mat_max_length(A);

    if (l == 0)
    {
        fmpz_poly_zero(det);
        return;
    }

    /* Bound degree based on Laplace expansion */
    p = n*(l - 1) + 1;

    x = _fmpz_vec_init(p);
    d = _fmpz_vec_init(p);
    fmpz_mat_init(X, n, n);

    for (i = 0; i < p; i++)
    {
        fmpz_set_si(x + i, -p/2 + i);
        fmpz_poly_mat_evaluate_fmpz(X, A, x + i);
        fmpz_mat_det(d + i, X);
    }

    fmpz_poly_interpolate_fmpz_vec(det, x, d, p);

    _fmpz_vec_clear(x, p);
    _fmpz_vec_clear(d, p);
    fmpz_mat_clear(X);
}
