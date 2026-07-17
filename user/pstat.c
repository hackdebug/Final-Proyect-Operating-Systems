// PROYECTO OS: programa de usuario para probar la syscall de diagnostico.
// Uso: pstat
// Imprime la lista de procesos activos y su estado actual, tal como los
// ve el scheduler (kernel/proc.c). Sirve como base para una futura
// herramienta de monitoreo de un planificador por prioridades.
#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  pstat();
  exit(0);
}
