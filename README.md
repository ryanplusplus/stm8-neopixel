# stm8-neopixel
Playing around with driving NeoPixels (WS2812B RGB LEDs) from an STM8.

## Setup
### Linux
- Copy `tools/Linux/udev/70-st-link.rules` to `/etc/udev/rules.d/` and run `udevadm control --reload-rules`.

## Use
### Run Tests
```
make -f test.mk
```

### Compile
```shell
make -f target.mk
```

### Clean
```shell
make -f target.mk clean
```

### Erase via SWIM
```shell
make -f target.mk erase
```

### Flash via SWIM
```shell
make -f target.mk upload
```

### Open documentation
```shell
make -f <target>.mk datasheet
```

```shell
make -f <target>.mk hardware_manual
```
