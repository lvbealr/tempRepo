#ifndef STRUCT_H_
#define STRUCT_H_

#include <cstdlib>
#include <memory.h>

static const size_t MAX_LOGIN    = 50;
static const size_t MAX_PASSWORD = 50;

template<typename T>
struct user {
  T login    = {};
  T password = {};
};

template<typename T>
void userCreate(user<T> *user, T login, T password) {
  user->login    = login;
  user->password = password;
}

template<typename T>
void userChangeLogin(user<T> *user, T newLogin) {
  user->login = newLogin;
}

template<typename T>
void userChangePassword(user<T> *user, T newPassword) {
  user->password = newPassword;
}

template<typename T>
void getUserInfo(user<T> *user, T *getLogin, T *getPassword) {
  *getLogin    = user->login;
  *getPassword = user->password;
}

#endif // STRUCT_H_