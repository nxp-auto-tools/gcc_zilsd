/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32imc_zilsd -mabi=ilp32 -fno-inline" { target { rv32 } } } */
/* { dg-skip-if "" { *-*-* } {"-O0" "-Og" "-g" "-ansi"} } */
/* { dg-skip-if "" { riscv64*-*-* } } */

#include <stdint.h>

uint64_t in_m, in_a, in_b;

void
mulul64 (uint64_t u, uint64_t v, uint64_t * whi, uint64_t * wlo)
{
  uint64_t u0, u1, v0, v1, k, t;
  uint64_t w0;

  u1 = u >> 32;
  v1 = v >> 32;

  t = u0 * v0;
  w0 = t & 0xFFFFFFFF;
  k = t >> 32;

  *wlo = (t << 32) + w0;
  *whi = u1 * v1 + k;

  return;
}

uint64_t
modul64 (uint64_t x, uint64_t y, uint64_t z)
{
  return x;                     // Quotient is y.
}

uint64_t
foo (void)
{
  uint64_t a, b, m, hr, p1hi, p1lo, p1;

  m = in_m;                 // Must be odd.
  b = in_b;                 // Must be smaller than m.
  a = in_a;                 // Must be smaller than m.

  mulul64 (a, b, &p1hi, &p1lo);     // Compute a*b (mod m).
  p1 = modul64 (p1hi, p1lo, m);
  mulul64 (p1, p1, &p1hi, &p1lo);   // Compute (a*b)**2 (mod m).
  p1 = modul64 (p1hi, p1lo, m);

  return p1;
}

/* { dg-final { scan-assembler-times "ld\t" 2 } } */
/* { dg-final { scan-assembler-times "sd\t" 1 } } */
/* { dg-final { scan-assembler-times "mv\ta2,a0" 1 } } */
/* { dg-final { scan-assembler-times "mv\ta3,a1" 1 } } */
