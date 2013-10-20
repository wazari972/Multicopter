#ifdef __cplusplus
extern "C"{
#endif

void setup(void);
void loop(void);

int stqrt(int argc, char *argv[]) {
  setup();
  loop();
  return 0;
}

#ifdef __cplusplus
}
#endif
