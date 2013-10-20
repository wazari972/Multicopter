#ifdef __cplusplus
extern "C"{
#endif

void setup(void);
void loop(void);

int main(int argc, char *argv[]) {
  setup();
  loop();
  return 0;
}

#ifdef __cplusplus
}
#endif
