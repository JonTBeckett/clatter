gdb-multiarch firmware.elf \
  -ex "target extended-remote :1234" \
  -ex "break main" \
  -ex "continue"
