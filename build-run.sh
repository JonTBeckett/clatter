arm-none-eabi-gcc \
  -mcpu=cortex-m33 \
  -mthumb \
  -mfloat-abi=soft \
  -O2 -g \
  -Wall -Wextra \
  -ffreestanding \
  -nostdlib \
  -T linker.ld \
  main.c \
  -o firmware.elf

qemu-system-arm \
  -machine mps2-an521 \
  -cpu cortex-m33 \
  -kernel firmware.elf \
  -nographic
