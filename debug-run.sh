qemu-system-arm \
  -machine mps2-an521 \
  -cpu cortex-m33 \
  -kernel firmware.elf \
  -nographic \
  -s -S
