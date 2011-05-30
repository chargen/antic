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

    Copyright (C) 2010 William Hart
    Copyright (C) 2010 Fredrik Johansson

******************************************************************************/

#ifndef FMPZ_MAT_H
#define FMPZ_MAT_H

#undef ulong /* interferes with system includes */
#include <stdio.h>
#define ulong unsigned long

#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "nmod_mat.h"
#include "mat_common.h"

typedef struct
{
    fmpz * entries;
    long r;
    long c;
    fmpz ** rows;
} fmpz_mat_struct;

typedef fmpz_mat_struct fmpz_mat_t[1];

/* Memory management  ********************************************************/

#define fmpz_mat_entry(mat,i,j) ((mat)->rows[i] + (j))

void fmpz_mat_init(fmpz_mat_t mat, long rows, long cols);
void fmpz_mat_init_set(fmpz_mat_t mat, const fmpz_mat_t src);
void fmpz_mat_swap(fmpz_mat_t mat1, fmpz_mat_t mat2);
void fmpz_mat_set(fmpz_mat_t mat1, const fmpz_mat_t mat2);
void fmpz_mat_clear(fmpz_mat_t mat);

int fmpz_mat_equal(fmpz_mat_t mat1, fmpz_mat_t mat2);
int fmpz_mat_is_zero(const fmpz_mat_t mat);

static __inline__ int
fmpz_mat_is_empty(const fmpz_mat_t mat)
{
    return (mat->r == 0) || (mat->c == 0);
}

static __inline__ int
fmpz_mat_is_square(const fmpz_mat_t mat)
{
    return (mat->r == mat->c);
}

void fmpz_mat_zero(fmpz_mat_t mat);
void fmpz_mat_unit(fmpz_mat_t mat);


/* Input and output  *********************************************************/

int fmpz_mat_fprint(FILE * file, const fmpz_mat_t mat);

int fmpz_mat_fprint_pretty(FILE * file, const fmpz_mat_t mat);

static __inline__
int fmpz_mat_print(const fmpz_mat_t mat)
{
    return fmpz_mat_fprint(stdout, mat);
}

static __inline__
int fmpz_mat_print_pretty(const fmpz_mat_t mat)
{
    return fmpz_mat_fprint_pretty(stdout, mat);
}

/* Random matrix generation  *************************************************/

void fmpz_mat_randbits(fmpz_mat_t mat, flint_rand_t state, mp_bitcnt_t bits);
void fmpz_mat_randtest(fmpz_mat_t mat, flint_rand_t state, mp_bitcnt_t bits);
void fmpz_mat_randtest_unsigned(fmpz_mat_t mat, flint_rand_t state, mp_bitcnt_t bits);
void fmpz_mat_randintrel(fmpz_mat_t mat, flint_rand_t state, mp_bitcnt_t bits);
void fmpz_mat_randsimdioph(fmpz_mat_t mat, flint_rand_t state, mp_bitcnt_t bits, mp_bitcnt_t bits2);
void fmpz_mat_randntrulike(fmpz_mat_t mat, flint_rand_t state, mp_bitcnt_t bits, ulong q);
void fmpz_mat_randntrulike2(fmpz_mat_t mat, flint_rand_t state, mp_bitcnt_t bits, ulong q);
void fmpz_mat_randajtai(fmpz_mat_t mat, flint_rand_t state, double alpha);
void fmpz_mat_randrank(fmpz_mat_t mat, flint_rand_t state, long rank, mp_bitcnt_t bits);
void fmpz_mat_randdet(fmpz_mat_t mat, flint_rand_t state, const fmpz_t det);
void fmpz_mat_randops(fmpz_mat_t mat, flint_rand_t state, long count);
int fmpz_mat_randpermdiag(fmpz_mat_t mat, flint_rand_t state, const fmpz * diag, long n);

/* Norms */

long fmpz_mat_max_bits(const fmpz_mat_t mat);

/* Transpose */

void fmpz_mat_transpose(fmpz_mat_t B, const fmpz_mat_t A);

/* Addition and subtraction */

void fmpz_mat_add(fmpz_mat_t C, const fmpz_mat_t A, const fmpz_mat_t B);
void fmpz_mat_sub(fmpz_mat_t C, const fmpz_mat_t A, const fmpz_mat_t B);
void fmpz_mat_neg(fmpz_mat_t B, const fmpz_mat_t A);

/* Scalar operations */
void fmpz_mat_scalar_mul_fmpz(fmpz_mat_t B, const fmpz_mat_t A, const fmpz_t c);
void fmpz_mat_scalar_mul_si(fmpz_mat_t B, const fmpz_mat_t A, long c);
void fmpz_mat_scalar_mul_ui(fmpz_mat_t B, const fmpz_mat_t A, ulong c);

void fmpz_mat_scalar_addmul_fmpz(fmpz_mat_t B, const fmpz_mat_t A, const fmpz_t c);
void fmpz_mat_scalar_addmul_si(fmpz_mat_t B, const fmpz_mat_t A, long c);
void fmpz_mat_scalar_addmul_ui(fmpz_mat_t B, const fmpz_mat_t A, ulong c);

void fmpz_mat_scalar_submul_fmpz(fmpz_mat_t B, const fmpz_mat_t A, const fmpz_t c);
void fmpz_mat_scalar_submul_si(fmpz_mat_t B, const fmpz_mat_t A, long c);
void fmpz_mat_scalar_submul_ui(fmpz_mat_t B, const fmpz_mat_t A, ulong c);

void fmpz_mat_scalar_addmul_nmod_mat_fmpz(fmpz_mat_t B, const nmod_mat_t A, const fmpz_t c);
void fmpz_mat_scalar_addmul_nmod_mat_ui(fmpz_mat_t B, const nmod_mat_t A, ulong c);

void fmpz_mat_scalar_divexact_fmpz(fmpz_mat_t B, const fmpz_mat_t A, const fmpz_t c);
void fmpz_mat_scalar_divexact_si(fmpz_mat_t B, const fmpz_mat_t A, long c);
void fmpz_mat_scalar_divexact_ui(fmpz_mat_t B, const fmpz_mat_t A, ulong c);

void fmpz_mat_scalar_mod_fmpz(fmpz_mat_t B, const fmpz_mat_t A, const fmpz_t m);

/* Multiplication */

void fmpz_mat_mul(fmpz_mat_t C, const fmpz_mat_t A, const fmpz_mat_t B);

void fmpz_mat_mul_classical(fmpz_mat_t C, const fmpz_mat_t A,
    const fmpz_mat_t B);

void fmpz_mat_mul_classical_inline(fmpz_mat_t C, const fmpz_mat_t A,
    const fmpz_mat_t B);

void _fmpz_mat_mul_multi_mod(fmpz_mat_t C, const fmpz_mat_t A,
    const fmpz_mat_t B, long bits);

void fmpz_mat_mul_multi_mod(fmpz_mat_t C, const fmpz_mat_t A,
    const fmpz_mat_t B);


/* Gaussian elimination */

int fmpz_mat_pivot(long * perm, fmpz_mat_t mat, long r, long c);

long _fmpz_mat_rowreduce(long * perm, fmpz_mat_t mat, int options);

long fmpz_mat_rref_fraction_free(long * perm, fmpz_mat_t B,
    fmpz_t den, const fmpz_mat_t A);

/* Determinant */

void fmpz_mat_det(fmpz_t det, const fmpz_mat_t A);
void fmpz_mat_det_cofactor(fmpz_t det, const fmpz_mat_t A);
void fmpz_mat_det_bareiss(fmpz_t det, const fmpz_mat_t A);
void fmpz_mat_det_multi_mod(fmpz_t det, const fmpz_mat_t A, int proved);
void fmpz_mat_det_bound(fmpz_t bound, const fmpz_mat_t A);

void _fmpz_mat_det_cofactor_2x2(fmpz_t det, fmpz ** const x);
void _fmpz_mat_det_cofactor_3x3(fmpz_t det, fmpz ** const x);
void _fmpz_mat_det_cofactor_4x4(fmpz_t det, fmpz ** const x);

/* Rank */

long fmpz_mat_rank(const fmpz_mat_t A);

/* Nonsingular solving */

void fmpz_mat_solve_bound(fmpz_t N, fmpz_t D, const fmpz_mat_t A, const fmpz_mat_t B);

void fmpz_mat_solve(fmpz * x, fmpz_t den, const fmpz_mat_t A, const fmpz * b);
void fmpz_mat_solve_cramer(fmpz * x, fmpz_t den, const fmpz_mat_t A, const fmpz * b);
void fmpz_mat_solve_fraction_free_LU(fmpz * x, fmpz_t den, const fmpz_mat_t A, const fmpz * b);
void _fmpz_mat_solve_fraction_free_LU_precomp(fmpz * b, const fmpz_mat_t LU);

void fmpz_mat_solve_mat(fmpz_mat_t X, fmpz_t den, const fmpz_mat_t A, const fmpz_mat_t B);

int fmpz_mat_solve_dixon(fmpz_mat_t X, fmpz_t mod, const fmpz_mat_t A, const fmpz_mat_t B);

/* Kernel */

long fmpz_mat_kernel(fmpz_mat_t res, const fmpz_mat_t mat);

/* Inverse */

void fmpz_mat_inv(fmpz_mat_t B, fmpz_t den, const fmpz_mat_t A);

/* Modular reduction and reconstruction  ************************************/

void fmpz_mat_set_nmod_mat(fmpz_mat_t A, const nmod_mat_t Amod);
void fmpz_mat_set_nmod_mat_unsigned(fmpz_mat_t A, const nmod_mat_t Amod);

void fmpz_mat_get_nmod_mat(nmod_mat_t Amod, const fmpz_mat_t A);

void
fmpz_mat_CRT_ui(fmpz_mat_t res, const fmpz_mat_t mat1,
                        const fmpz_t m1, const nmod_mat_t mat2);

void
fmpz_mat_CRT_ui_unsigned(fmpz_mat_t res, const fmpz_mat_t mat1,
                            const fmpz_t m1, const nmod_mat_t mat2);


#define FMPZ_MAT_ASSERT(expr, msg)       \
    if (1)                               \
    {                                    \
        if (!(expr))                     \
        {                                \
            printf(msg);                 \
            abort();                     \
        }                                \
    }                                    \

#endif

