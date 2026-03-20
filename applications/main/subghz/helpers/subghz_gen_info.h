#pragma once
#include "subghz_types.h"
#include "subghz_custom_event.h"

typedef enum {
    GenData,
    GenFaacSLH,
    GenKeeloq,
    GenCameAtomo,
    GenKeeloqBFT,
    GenAlutechAt4n,
    GenSomfyTelis,
    GenKingGatesStylo4k,
    GenBenincaARC,
    GenJarolift,
    GenNiceFlorS,
    GenSecPlus1,
    GenSecPlus2,
    GenPhoenixV2,
    GenPorscheCayenne,
    GenVAG,
    GenFordV0,
    GenMitsubishiV0,
    GenSubaru,
    GenFiatSpa,
} GenType;

typedef struct {
    GenType type;
    const char* mod;
    uint32_t freq;
    union {
        struct {
            const char* name;
            uint64_t key;
            uint8_t bits;
            uint32_t te;
        } data;
        struct {
            uint32_t serial;
            uint8_t btn;
            uint32_t cnt;
            uint32_t seed;
            const char* manuf;
        } faac_slh;
        struct {
            uint32_t serial;
            uint8_t btn;
            uint16_t cnt;
            const char* manuf;
        } keeloq;
        struct {
            uint32_t serial;
            uint16_t cnt;
        } came_atomo;
        struct {
            uint32_t serial;
            uint8_t btn;
            uint16_t cnt;
            uint32_t seed;
            const char* manuf;
        } keeloq_bft;
        struct {
            uint32_t serial;
            uint8_t btn;
            uint16_t cnt;
        } alutech_at_4n;
        struct {
            uint32_t serial;
            uint8_t btn;
            uint16_t cnt;
        } somfy_telis;
        struct {
            uint32_t serial;
            uint8_t btn;
            uint16_t cnt;
        } kinggates_stylo_4k;
        struct {
            uint32_t serial;
            uint8_t btn;
            uint32_t cnt;
        } beninca_arc;
        struct {
            uint32_t serial;
            uint8_t btn;
            uint16_t cnt;
        } jarolift;
        struct {
            uint32_t serial;
            uint8_t btn;
            uint16_t cnt;
            bool nice_one;
        } nice_flor_s;
        struct {
            uint32_t serial;
            uint8_t btn;
            uint32_t cnt;
        } sec_plus_2;
        struct {
            uint32_t serial;
            uint16_t cnt;
        } phoenix_v2;
        struct {
            uint32_t serial;
            uint8_t btn;
            uint32_t cnt;
        } porsche_cayenne;
        struct {
            uint32_t serial;
            uint32_t cnt;
            uint8_t btn;
            uint8_t vag_type;
        } vag;
        struct {
            uint32_t serial;
            uint8_t btn;
            uint32_t cnt;
            uint8_t bs_magic;
        } ford_v0;
        struct {
            uint32_t serial;
            uint8_t btn;
            uint32_t cnt;
        } mitsubishi_v0;
        struct {
            uint32_t serial;
            uint8_t btn;
            uint16_t cnt;
        } subaru;
        struct {
            uint32_t fix;
            uint32_t hop;
            uint8_t endbyte;
        } fiat_spa;
    };
} GenInfo;

void subghz_gen_info_reset(GenInfo* gen_info);

void subghz_scene_set_type_fill_generation_infos(GenInfo* infos_dest, SetType type);




