# Proyecto Final — Sistemas Operativos (xv6-riscv modificado)

Este repositorio es un fork de [xv6-riscv](https://github.com/mit-pdos/xv6-riscv) (MIT PDOS)
con dos modificaciones sobre el planificador de CPU y el gestor de memoria.

## Cómo ejecutar (con Docker)

```bash
docker build -t xv6-proyecto-os .
docker run -it --rm xv6-proyecto-os
```

Al arrancar verás el mensaje de memoria libre agregado en `kernel/kalloc.c`.
Dentro del shell de xv6, corre el nuevo comando de diagnóstico:

```
$ pstat
```

Para salir de QEMU: `Ctrl+A` y luego `X`.

## Cómo ejecutar (sin Docker, con el toolchain instalado)

```bash
make TOOLPREFIX=riscv64-linux-gnu- qemu
```

## Modificaciones realizadas

### 1. Planificador de CPU — nueva syscall `pstat` (herramienta de diagnóstico)

- **Archivos:** `kernel/syscall.h`, `kernel/syscall.c`, `kernel/sysproc.c`,
  `user/user.h`, `user/usys.pl`, `user/pstat.c`, `Makefile`.
- Se agregó la syscall número 23 (`SYS_pstat`), implementada en `sys_pstat()`
  (`kernel/sysproc.c`), que reutiliza la función interna `procdump()` de
  `kernel/proc.c` para imprimir el PID, estado (`RUNNABLE`, `RUNNING`,
  `SLEEPING`, etc.) y nombre de cada proceso activo en la tabla de procesos.
- Se agregó el programa de usuario `pstat` (`user/pstat.c`) para invocarla
  desde el shell.
- **Justificación (informe):** da visibilidad en tiempo real del estado de
  la cola de procesos que recorre el `scheduler()` (Round Robin, `kernel/proc.c`
  línea ~425). Es la base para instrumentar y comparar el comportamiento de
  un futuro planificador por prioridades frente al Round Robin original.

### 2. Gestor de memoria — reporte de memoria física libre al arrancar

- **Archivo:** `kernel/kalloc.c`, función `kinit()`.
- Justo después de poblar `kmem.freelist` (la lista enlazada de páginas
  libres), se recorre la lista para contar las páginas disponibles y se
  imprime el total en KB durante el boot.
- **Justificación (informe):** hace visible el estado inicial del asignador
  físico de páginas (`kalloc()`/`kfree()`), sin alterar su lógica interna,
  como primer paso hacia la instrumentación de una futura política de
  asignación distinta a la lista enlazada simple.

## Evidencia de ejecución

```
xv6 kernel is booting

memoria fisica libre: 130928 KB (32732 paginas de 4096 bytes)
$ pstat
1 sleep  init
2 sleep  sh
3 run    pstat
```

Ver también `cambios_proyecto_os.diff` para el diff completo de los cambios.
