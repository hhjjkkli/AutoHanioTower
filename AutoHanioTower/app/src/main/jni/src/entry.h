//
// Created by asus on 2018/3/21.
//

#ifndef AUTOHANIOTOWER_ENTRY_H
#define AUTOHANIOTOWER_ENTRY_H

/*这里必须用define来extern "C"，否则报一个错误，直接extern "C"的话，在main.c的include里面会出问题*/
#ifdef __cplusplus
  extern "C" {
#endif
int entry(int argc, char* argv[]);
#ifdef __cplusplus
  }
#endif

#endif //AUTOHANIOTOWER_ENTRY_H
