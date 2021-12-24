# Level1Techs KVM Remote

USB Remote for the Level1Techs KVM using Raspberry Pi Pico


# Building

```
mkdir build
cd build
cmake ..
make
```

more to come...

...now!

# Software Architecture

While this is a very simple program, I thought it best to write out what I'm doing and why, rather than just throwing up some code.

# Keymappings

We've got 5 buttons; 4 for directly changing inputs, one to act as a "modifier"

Here's the mapping table:
|  BTN  |  BASE  |  MOD         |
| ----- | ------ | ------------ |
|   1   |  MOD   |  NONE        |
|   2   | HEAD 1 | AUDIO LOCK   |
|   3   | HEAD 2 | AUDIO FOLLOW |
|   4   | HEAD 3 | USB LOCK     |
|   5   | HEAD 4 | USB FOLLOW   |
