/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32imc_zilsd -mabi=ilp32" { target { rv32 } } } */
/* { dg-skip-if "" { *-*-* } {"-O0" "-Og" "-g" "-ansi"} } */
/* { dg-skip-if "" { riscv64*-*-* } } */
typedef int T;
typedef long long int LT;
typedef struct {
  int w;
  int x;
  int y;
  int z;
} S;

T peep_load_4 (S *p)
{
  return p->x + p->w + p->y + p->z;
}

T peep_load_3 (S *p)
{
  return p->x + p->w + p->y;
}

void peep_store_4 (S *p, int w, int x, int y, int z)
{
  p->w = w;
  p->x = x;
  p->y = y;
  p->z = z;
}

void peep_store_2 (int a, int b, S *p)
{
  p->w = a;
  p->x = b;
}

void peep_constant_2 (S *p)
{
  p->w = 0x55;
  p->x = 0xAA;
}

LT data64 (LT a)
{
  volatile LT x;
  volatile LT y;

  x = a;
  return x + y;
}

/* { dg-final { scan-assembler-times "ld\t" 1 } } */
/* { dg-final { scan-assembler-times "sd\t" 3 } } */
