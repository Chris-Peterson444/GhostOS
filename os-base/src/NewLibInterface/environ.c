// No environment provided by the OS. Minimal implementation
char *__env[1] = { 0 };
char **environ = __env;