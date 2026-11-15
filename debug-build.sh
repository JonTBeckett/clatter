arm-none-eabi-gcc \
  -mcpu=cortex-m33 \
  -mthumb \
  -mfloat-abi=soft \
  -O0 -g \
  -Wall -Wextra \
  -ffreestanding \
  -nostdlib \
  -T linker.ld \
  main.c \
  -o firmware.elf
