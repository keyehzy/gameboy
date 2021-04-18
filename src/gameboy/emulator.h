#ifndef EMULATOR_H
#define EMULATOR_H
#include <gameboy/cpu.h>

#define CASE_LD_B                                                              \
    case 0x40:                                                                 \
    case 0x41:                                                                 \
    case 0x42:                                                                 \
    case 0x43:                                                                 \
    case 0x44:                                                                 \
    case 0x45:                                                                 \
    case 0x46:                                                                 \
    case 0x47

#define CASE_LD_C                                                              \
    case 0x48:                                                                 \
    case 0x49:                                                                 \
    case 0x4A:                                                                 \
    case 0x4B:                                                                 \
    case 0x4C:                                                                 \
    case 0x4D:                                                                 \
    case 0x4E:                                                                 \
    case 0x4F

#define CASE_LD_D                                                              \
    case 0x50:                                                                 \
    case 0x51:                                                                 \
    case 0x52:                                                                 \
    case 0x53:                                                                 \
    case 0x54:                                                                 \
    case 0x55:                                                                 \
    case 0x56:                                                                 \
    case 0x57

#define CASE_LD_E                                                              \
    case 0x58:                                                                 \
    case 0x59:                                                                 \
    case 0x5A:                                                                 \
    case 0x5B:                                                                 \
    case 0x5C:                                                                 \
    case 0x5D:                                                                 \
    case 0x5E:                                                                 \
    case 0x5F

#define CASE_LD_H                                                              \
    case 0x60:                                                                 \
    case 0x61:                                                                 \
    case 0x62:                                                                 \
    case 0x63:                                                                 \
    case 0x64:                                                                 \
    case 0x65:                                                                 \
    case 0x66:                                                                 \
    case 0x67

#define CASE_LD_L                                                              \
    case 0x68:                                                                 \
    case 0x69:                                                                 \
    case 0x6A:                                                                 \
    case 0x6B:                                                                 \
    case 0x6C:                                                                 \
    case 0x6D:                                                                 \
    case 0x6E:                                                                 \
    case 0x6F

#define CASE_LD_HL                                                             \
    case 0x70:                                                                 \
    case 0x71:                                                                 \
    case 0x72:                                                                 \
    case 0x73:                                                                 \
    case 0x74:                                                                 \
    case 0x75:                                                                 \
    case 0x77

#define CASE_LD_A                                                              \
    case 0x78:                                                                 \
    case 0x79:                                                                 \
    case 0x7A:                                                                 \
    case 0x7B:                                                                 \
    case 0x7C:                                                                 \
    case 0x7D:                                                                 \
    case 0x7E:                                                                 \
    case 0x7F

#define CASE_ADD                                                               \
    case 0x80:                                                                 \
    case 0x81:                                                                 \
    case 0x82:                                                                 \
    case 0x83:                                                                 \
    case 0x84:                                                                 \
    case 0x85:                                                                 \
    case 0x86:                                                                 \
    case 0x87

#define CASE_ADC                                                               \
    case 0x88:                                                                 \
    case 0x89:                                                                 \
    case 0x8A:                                                                 \
    case 0x8B:                                                                 \
    case 0x8C:                                                                 \
    case 0x8D:                                                                 \
    case 0x8E:                                                                 \
    case 0x8F

#define CASE_SUB                                                               \
    case 0x90:                                                                 \
    case 0x91:                                                                 \
    case 0x92:                                                                 \
    case 0x93:                                                                 \
    case 0x94:                                                                 \
    case 0x95:                                                                 \
    case 0x96:                                                                 \
    case 0x97

#define CASE_SBC                                                               \
    case 0x98:                                                                 \
    case 0x99:                                                                 \
    case 0x9A:                                                                 \
    case 0x9B:                                                                 \
    case 0x9C:                                                                 \
    case 0x9D:                                                                 \
    case 0x9E:                                                                 \
    case 0x9F

#define CASE_SUB                                                               \
    case 0x90:                                                                 \
    case 0x91:                                                                 \
    case 0x92:                                                                 \
    case 0x93:                                                                 \
    case 0x94:                                                                 \
    case 0x95:                                                                 \
    case 0x96:                                                                 \
    case 0x97

#define CASE_SBC                                                               \
    case 0x98:                                                                 \
    case 0x99:                                                                 \
    case 0x9A:                                                                 \
    case 0x9B:                                                                 \
    case 0x9C:                                                                 \
    case 0x9D:                                                                 \
    case 0x9E:                                                                 \
    case 0x9F

#define CASE_AND                                                               \
    case 0xA0:                                                                 \
    case 0xA1:                                                                 \
    case 0xA2:                                                                 \
    case 0xA3:                                                                 \
    case 0xA4:                                                                 \
    case 0xA5:                                                                 \
    case 0xA6:                                                                 \
    case 0xA7

#define CASE_XOR                                                               \
    case 0xA8:                                                                 \
    case 0xA9:                                                                 \
    case 0xAA:                                                                 \
    case 0xAB:                                                                 \
    case 0xAC:                                                                 \
    case 0xAD:                                                                 \
    case 0xAE:                                                                 \
    case 0xAF

#define CASE_OR                                                                \
    case 0xB0:                                                                 \
    case 0xB1:                                                                 \
    case 0xB2:                                                                 \
    case 0xB3:                                                                 \
    case 0xB4:                                                                 \
    case 0xB5:                                                                 \
    case 0xB6:                                                                 \
    case 0xB7

#define CASE_CP                                                                \
    case 0xB8:                                                                 \
    case 0xB9:                                                                 \
    case 0xBA:                                                                 \
    case 0xBB:                                                                 \
    case 0xBC:                                                                 \
    case 0xBD:                                                                 \
    case 0xBE:                                                                 \
    case 0xBF

#define CASE_CB_RLC                                                            \
    case 0x00:                                                                 \
    case 0x01:                                                                 \
    case 0x02:                                                                 \
    case 0x03:                                                                 \
    case 0x04:                                                                 \
    case 0x05:                                                                 \
    case 0x06:                                                                 \
    case 0x07

#define CASE_CB_RRC                                                            \
    case 0x08:                                                                 \
    case 0x09:                                                                 \
    case 0x0A:                                                                 \
    case 0x0B:                                                                 \
    case 0x0C:                                                                 \
    case 0x0D:                                                                 \
    case 0x0E:                                                                 \
    case 0x0F

#define CASE_CB_RL                                                             \
    case 0x10:                                                                 \
    case 0x11:                                                                 \
    case 0x12:                                                                 \
    case 0x13:                                                                 \
    case 0x14:                                                                 \
    case 0x15:                                                                 \
    case 0x16:                                                                 \
    case 0x17

#define CASE_CB_RR                                                             \
    case 0x18:                                                                 \
    case 0x19:                                                                 \
    case 0x1A:                                                                 \
    case 0x1B:                                                                 \
    case 0x1C:                                                                 \
    case 0x1D:                                                                 \
    case 0x1E:                                                                 \
    case 0x1F

#define CASE_CB_SLA                                                            \
    case 0x20:                                                                 \
    case 0x21:                                                                 \
    case 0x22:                                                                 \
    case 0x23:                                                                 \
    case 0x24:                                                                 \
    case 0x25:                                                                 \
    case 0x26:                                                                 \
    case 0x27

#define CASE_CB_SRA                                                            \
    case 0x28:                                                                 \
    case 0x29:                                                                 \
    case 0x2A:                                                                 \
    case 0x2B:                                                                 \
    case 0x2C:                                                                 \
    case 0x2D:                                                                 \
    case 0x2E:                                                                 \
    case 0x2F

#define CASE_CB_SWAP                                                           \
    case 0x30:                                                                 \
    case 0x31:                                                                 \
    case 0x32:                                                                 \
    case 0x33:                                                                 \
    case 0x34:                                                                 \
    case 0x35:                                                                 \
    case 0x36:                                                                 \
    case 0x37

#define CASE_CB_SRL                                                            \
    case 0x38:                                                                 \
    case 0x39:                                                                 \
    case 0x3A:                                                                 \
    case 0x3B:                                                                 \
    case 0x3C:                                                                 \
    case 0x3D:                                                                 \
    case 0x3E:                                                                 \
    case 0x3F

#define CASE_CB_BIT                                                            \
    case 0x40:                                                                 \
    case 0x41:                                                                 \
    case 0x42:                                                                 \
    case 0x43:                                                                 \
    case 0x44:                                                                 \
    case 0x45:                                                                 \
    case 0x46:                                                                 \
    case 0x47

#define CASE_CB_SET                                                            \
    case 0xC0:                                                                 \
    case 0xC1:                                                                 \
    case 0xC2:                                                                 \
    case 0xC3:                                                                 \
    case 0xC4:                                                                 \
    case 0xC5:                                                                 \
    case 0xC6:                                                                 \
    case 0xC7

#define CASE_CB_RES                                                            \
    case 0x80:                                                                 \
    case 0x81:                                                                 \
    case 0x82:                                                                 \
    case 0x83:                                                                 \
    case 0x84:                                                                 \
    case 0x85:                                                                 \
    case 0x86:                                                                 \
    case 0x87

int emulate_rom(CPU *u);
#endif
