# Gameboy emulator

Usage:
```
gameboy -d PATH: Disassemble ROM in PATH
gameboy -e PATH: Emulate ROM in PATH
gameboy -D PATH: Debugger
gameboy --info:  Dump ROM information
gameboy -h:      Help message
```

# Disassembler example

A snippet of the disassembler for the tetris ROM:
```
ROM loaded: roms/tetris.gb
ADDRESS         OPCODE          INSTRUCTION
$0150           $c3 $020c       JP $020c
$0153           $cd $29e3       CALL $29e3
$0156           $f0 $41         LDH A,($41)
$0158           $e6 $03         AND A,$03
$015a           $20 $fa         JR NZ (Z),$fa
$015c           $46             LD B, (HL)
$015d           $f0 $41         LDH A,($41)
$015f           $e6 $03         AND A,$03
$0161           $20 $fa         JR NZ (Z),$fa
```

# References

The table of opcodes can be found [here](https://pastraiser.com/cpu/gameboy/gameboy_opcodes.html)
and their respective descriptions in the [Gameboy CPU Manual](https://realboyemulator.files.wordpress.com/2013/01/gbcpuman.pdf).
