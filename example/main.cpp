#include <cstdio>

#include "struct.h"

int main() {
  user<const char *> Dedulya = {};
  userCreate(&Dedulya, "DED_LOGIN", "228");

  const char *dedLogin    = {};
  const char *dedPassword = {};

  getUserInfo(&Dedulya, &dedLogin, &dedPassword);

  printf("\nLogin: [%s]\nPassword: [%s]\n", Dedulya.login, Dedulya.password);

  user<int> Poltorashka = {};
  userCreate(&Poltorashka, 1488, 5051);

  int poltorashkaLogin            = {};
  int poltorashkaPassword         = {};

  getUserInfo(&Poltorashka, &poltorashkaLogin, &poltorashkaPassword);

  printf("\nLogin: [%d]\nPassword: [%d]\n", Poltorashka.login, Poltorashka.password);
}