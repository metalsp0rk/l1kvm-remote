# Level1Techs KVM Remote

USB Remote for the Level1Techs KVM using Raspberry Pi Pico


# Building

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

# Debugging

Include Debug symbols.
```
cmake -DCMAKE_BUILD_TYPE=Debug ..
```
I've included a GDB sample for my macros, if you want to use GDB, go for it, otherwise, vscode has a good debugger, you just need to set up OpenOCD as your debugging target.

# Enclosure

Enclosure is currently im progress, 3MF files will be provided when I'm confident in the design.  I do not want to rely on screws for this small of a component, so I'm hoping to be able to design components that will just snap together.


# Keymappings

We've got 5 buttons; 4 for directly changing inputs, one to act as a "modifier"

Here's the mapping table:
|  BTN  |  BASE  |  MOD         |
| ----- | ------ | ------------ |
|   1   |  MOD   |     NONE     |
| 2     | HEAD 1 | AUDIO FOLLOW |
| 3     | HEAD 2 | AUDIO LOCK   |
| 4     | HEAD 3 | USB FOLLOW   |
| 5     | HEAD 4 | USB LOCK     |
