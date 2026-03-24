#include "../subghz_i.h"
#include "../helpers/subghz_txrx_create_protocol_key.h"

#include <machine/endian.h>

#define TAG "SubGhzSetCounter"


void subghz_scene_set_counter_byte_input_callback(void* context) {
    SubGhz* subghz = context;

    view_dispatcher_send_custom_event(subghz->view_dispatcher, SubGhzCustomEventByteInputDone);
}

void subghz_scene_set_counter_on_enter(void* context) {
    SubGhz* subghz = context;

    uint8_t* byte_ptr = NULL;
    uint8_t byte_count = 0;

    switch(subghz->gen_info->type) {
    case GenFaacSLH:
        byte_ptr = (uint8_t*)&subghz->gen_info->faac_slh.cnt;
        byte_count = sizeof(subghz->gen_info->faac_slh.cnt);
        break;
    case GenKeeloq:
        byte_ptr = (uint8_t*)&subghz->gen_info->keeloq.cnt;
        byte_count = sizeof(subghz->gen_info->keeloq.cnt);
        break;
    case GenCameAtomo:
        byte_ptr = (uint8_t*)&subghz->gen_info->came_atomo.cnt;
        byte_count = sizeof(subghz->gen_info->came_atomo.cnt);
        break;
    case GenKeeloqBFT:
        byte_ptr = (uint8_t*)&subghz->gen_info->keeloq_bft.cnt;
        byte_count = sizeof(subghz->gen_info->keeloq_bft.cnt);
        break;
    case GenAlutechAt4n:
        byte_ptr = (uint8_t*)&subghz->gen_info->alutech_at_4n.cnt;
        byte_count = sizeof(subghz->gen_info->alutech_at_4n.cnt);
        break;
    case GenSomfyTelis:
        byte_ptr = (uint8_t*)&subghz->gen_info->somfy_telis.cnt;
        byte_count = sizeof(subghz->gen_info->somfy_telis.cnt);
        break;
    case GenKingGatesStylo4k:
        byte_ptr = (uint8_t*)&subghz->gen_info->kinggates_stylo_4k.cnt;
        byte_count = sizeof(subghz->gen_info->kinggates_stylo_4k.cnt);
        break;
    case GenBenincaARC:
        byte_ptr = (uint8_t*)&subghz->gen_info->beninca_arc.cnt;
        byte_count = sizeof(subghz->gen_info->beninca_arc.cnt);
        break;
    case GenJarolift:
        byte_ptr = (uint8_t*)&subghz->gen_info->jarolift.cnt;
        byte_count = sizeof(subghz->gen_info->jarolift.cnt);
        break;
    case GenNiceFlorS:
        byte_ptr = (uint8_t*)&subghz->gen_info->nice_flor_s.cnt;
        byte_count = sizeof(subghz->gen_info->nice_flor_s.cnt);
        break;
    case GenSecPlus2:
        byte_ptr = (uint8_t*)&subghz->gen_info->sec_plus_2.cnt;
        byte_count = sizeof(subghz->gen_info->sec_plus_2.cnt);
        break;
    case GenPhoenixV2:
        byte_ptr = (uint8_t*)&subghz->gen_info->phoenix_v2.cnt;
        byte_count = sizeof(subghz->gen_info->phoenix_v2.cnt);
        break;
    case GenPorscheCayenne:
        byte_ptr = (uint8_t*)&subghz->gen_info->porsche_cayenne.cnt;
        byte_count = sizeof(subghz->gen_info->porsche_cayenne.cnt);
        break;
    case GenFordV0:
        byte_ptr = (uint8_t*)&subghz->gen_info->ford_v0.cnt;
        byte_count = sizeof(subghz->gen_info->ford_v0.cnt);
        break;
    case GenVAG:
        byte_ptr = (uint8_t*)&subghz->gen_info->vag.cnt;
        byte_count = sizeof(subghz->gen_info->vag.cnt);
        break;
    case GenFiatSpa:
        byte_ptr = (uint8_t*)&subghz->gen_info->fiat_spa.hop;
        byte_count = sizeof(subghz->gen_info->fiat_spa.hop);
        break;
    case GenKiaV0:
        byte_ptr = (uint8_t*)&subghz->gen_info->kia_v0.cnt;
        byte_count = sizeof(subghz->gen_info->kia_v0.cnt);
        break;
    case GenKiaV1:
        byte_ptr = (uint8_t*)&subghz->gen_info->kia_v1.cnt;
        byte_count = sizeof(subghz->gen_info->kia_v1.cnt);
        break;
    case GenKiaV2:
        byte_ptr = (uint8_t*)&subghz->gen_info->kia_v2.cnt;
        byte_count = sizeof(subghz->gen_info->kia_v2.cnt);
        break;
    case GenKiaV3:
    case GenKiaV4:
        byte_ptr = (uint8_t*)&subghz->gen_info->kia_v3v4.cnt;
        byte_count = sizeof(subghz->gen_info->kia_v3v4.cnt);
        break;
    case GenKiaV5:
        byte_ptr = (uint8_t*)&subghz->gen_info->kia_v5.cnt;
        byte_count = sizeof(subghz->gen_info->kia_v5.cnt);
        break;
    case GenKiaV6:
        byte_ptr = (uint8_t*)&subghz->gen_info->kia_v6.cnt;
        byte_count = sizeof(subghz->gen_info->kia_v6.cnt);
        break;
    case GenMitsubishiV0:
        byte_ptr = (uint8_t*)&subghz->gen_info->mitsubishi_v0.cnt;
        byte_count = sizeof(subghz->gen_info->mitsubishi_v0.cnt);
        break;
    case GenSubaru:
        byte_ptr = (uint8_t*)&subghz->gen_info->subaru.cnt;
        byte_count = sizeof(subghz->gen_info->subaru.cnt);
        break;
    case GenSuzuki:
        byte_ptr = (uint8_t*)&subghz->gen_info->suzuki.cnt;
        byte_count = sizeof(subghz->gen_info->suzuki.cnt);
        break;
    // Not needed for these types
    case GenData:
    case GenSecPlus1:
    default:
        furi_crash("Not implemented");
        break;
    }

    furi_assert(byte_ptr);
    furi_assert(byte_count > 0);

    if(byte_count == 2) {
        *((uint16_t*)byte_ptr) = __bswap16(*((uint16_t*)byte_ptr)); // Convert
    } else if(byte_count == 4) {
        *((uint32_t*)byte_ptr) = __bswap32(*((uint32_t*)byte_ptr)); // Convert
    }

    // Setup view
    ByteInput* byte_input = subghz->byte_input;
    if(subghz->gen_info->type == GenVAG) {
        byte_input_set_header_text(byte_input, "VAG Counter (24-bit)\nTop byte ignored!\nStart low e.g. 0001");
    } else if(subghz->gen_info->type == GenPorscheCayenne) {
        byte_input_set_header_text(byte_input, "Porsche Counter\n(16-bit) e.g. 0001");
    } else if(subghz->gen_info->type == GenFordV0) {
        byte_input_set_header_text(byte_input, "Ford Counter (20-bit)\nMax: 000FFFFF");
    } else if(subghz->gen_info->type == GenMitsubishiV0) {
        byte_input_set_header_text(byte_input, "Mitsubishi Counter\n(16-bit) Max: 0000FFFF");
    } else if(subghz->gen_info->type == GenSubaru) {
        byte_input_set_header_text(byte_input, "Subaru Counter\n(16-bit) Max: 0000FFFF");
    } else if(subghz->gen_info->type == GenSuzuki) {
        byte_input_set_header_text(byte_input, "Suzuki Counter\n(20-bit) Max: 000FFFFF");
    } else {
        byte_input_set_header_text(byte_input, "Enter COUNTER in hex");
    }

    byte_input_set_result_callback(
        byte_input,
        subghz_scene_set_counter_byte_input_callback,
        NULL,
        subghz,
        byte_ptr,
        byte_count);
    view_dispatcher_switch_to_view(subghz->view_dispatcher, SubGhzViewIdByteInput);
}

bool subghz_scene_set_counter_on_event(void* context, SceneManagerEvent event) {
    SubGhz* subghz = context;
    bool consumed = false;
    bool generated_protocol = false;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == SubGhzCustomEventByteInputDone) {
            // Swap bytes
            switch(subghz->gen_info->type) {
            case GenFaacSLH:
                subghz->gen_info->faac_slh.cnt = __bswap32(subghz->gen_info->faac_slh.cnt);
                break;
            case GenKeeloq:
                subghz->gen_info->keeloq.cnt = __bswap16(subghz->gen_info->keeloq.cnt);
                break;
            case GenCameAtomo:
                subghz->gen_info->came_atomo.cnt = __bswap16(subghz->gen_info->came_atomo.cnt);
                break;
            case GenKeeloqBFT:
                subghz->gen_info->keeloq_bft.cnt = __bswap16(subghz->gen_info->keeloq_bft.cnt);
                break;
            case GenAlutechAt4n:
                subghz->gen_info->alutech_at_4n.cnt =
                    __bswap16(subghz->gen_info->alutech_at_4n.cnt);
                break;
            case GenSomfyTelis:
                subghz->gen_info->somfy_telis.cnt = __bswap16(subghz->gen_info->somfy_telis.cnt);
                break;
            case GenKingGatesStylo4k:
                subghz->gen_info->kinggates_stylo_4k.cnt =
                    __bswap16(subghz->gen_info->kinggates_stylo_4k.cnt);
                break;
            case GenBenincaARC:
                subghz->gen_info->beninca_arc.cnt = __bswap32(subghz->gen_info->beninca_arc.cnt);
                break;
            case GenJarolift:
                subghz->gen_info->jarolift.cnt = __bswap16(subghz->gen_info->jarolift.cnt);
                break;
            case GenNiceFlorS:
                subghz->gen_info->nice_flor_s.cnt = __bswap16(subghz->gen_info->nice_flor_s.cnt);
                break;
            case GenSecPlus2:
                subghz->gen_info->sec_plus_2.cnt = __bswap32(subghz->gen_info->sec_plus_2.cnt);
                break;
            case GenPhoenixV2:
                subghz->gen_info->phoenix_v2.cnt = __bswap16(subghz->gen_info->phoenix_v2.cnt);
                break;
            case GenPorscheCayenne:
                subghz->gen_info->porsche_cayenne.cnt = __bswap32(subghz->gen_info->porsche_cayenne.cnt);
                break;
            case GenFordV0:
                subghz->gen_info->ford_v0.cnt = __bswap32(subghz->gen_info->ford_v0.cnt);
                break;
            case GenVAG:
                subghz->gen_info->vag.cnt = __bswap32(subghz->gen_info->vag.cnt);
                break;
            case GenFiatSpa:
                subghz->gen_info->fiat_spa.hop = __bswap32(subghz->gen_info->fiat_spa.hop);
                break;
            case GenKiaV0:
                subghz->gen_info->kia_v0.cnt = __bswap16(subghz->gen_info->kia_v0.cnt);
                break;
            case GenKiaV1:
                subghz->gen_info->kia_v1.cnt = __bswap16(subghz->gen_info->kia_v1.cnt);
                break;
            case GenKiaV2:
                subghz->gen_info->kia_v2.cnt = __bswap16(subghz->gen_info->kia_v2.cnt);
                break;
            case GenKiaV3:
            case GenKiaV4:
                subghz->gen_info->kia_v3v4.cnt = __bswap16(subghz->gen_info->kia_v3v4.cnt);
                break;
            case GenKiaV5:
                subghz->gen_info->kia_v5.cnt = __bswap16(subghz->gen_info->kia_v5.cnt);
                break;
            case GenKiaV6:
                subghz->gen_info->kia_v6.cnt = __bswap32(subghz->gen_info->kia_v6.cnt);
                break;
            case GenMitsubishiV0:
                subghz->gen_info->mitsubishi_v0.cnt =
                    __bswap32(subghz->gen_info->mitsubishi_v0.cnt);
                break;
            case GenSubaru:
                subghz->gen_info->subaru.cnt =
                    __bswap16(subghz->gen_info->subaru.cnt);
                break;
            case GenSuzuki:
                subghz->gen_info->suzuki.cnt =
                    __bswap32(subghz->gen_info->suzuki.cnt);
                break;
                // Not needed for these types
            case GenData:
            case GenSecPlus1:
            default:
                furi_crash("Not implemented");
                break;
            }

            switch(subghz->gen_info->type) {
            case GenFaacSLH:
            case GenKeeloqBFT:
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSetSeed);
                return true;
            case GenKeeloq:
                generated_protocol = subghz_txrx_gen_keeloq_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->keeloq.serial,
                    subghz->gen_info->keeloq.btn,
                    subghz->gen_info->keeloq.cnt,
                    subghz->gen_info->keeloq.manuf);
                break;
            case GenCameAtomo:
                generated_protocol = subghz_txrx_gen_came_atomo_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->came_atomo.serial,
                    subghz->gen_info->came_atomo.cnt);
                break;
            case GenAlutechAt4n:
                generated_protocol = subghz_txrx_gen_alutech_at_4n_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->alutech_at_4n.serial,
                    subghz->gen_info->alutech_at_4n.btn,
                    subghz->gen_info->alutech_at_4n.cnt);
                break;
            case GenSomfyTelis:
                generated_protocol = subghz_txrx_gen_somfy_telis_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->somfy_telis.serial,
                    subghz->gen_info->somfy_telis.btn,
                    subghz->gen_info->somfy_telis.cnt);
                break;
            case GenKingGatesStylo4k:
                generated_protocol = subghz_txrx_gen_kinggates_stylo_4k_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->kinggates_stylo_4k.serial,
                    subghz->gen_info->kinggates_stylo_4k.btn,
                    subghz->gen_info->kinggates_stylo_4k.cnt);
                break;
            case GenBenincaARC:
                generated_protocol = subghz_txrx_gen_beninca_arc_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->beninca_arc.serial,
                    subghz->gen_info->beninca_arc.btn,
                    subghz->gen_info->beninca_arc.cnt);
                break;
            case GenJarolift:
                generated_protocol = subghz_txrx_gen_jarolift_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->jarolift.serial,
                    subghz->gen_info->jarolift.btn,
                    subghz->gen_info->jarolift.cnt);
                break;
            case GenNiceFlorS:
                generated_protocol = subghz_txrx_gen_nice_flor_s_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->nice_flor_s.serial,
                    subghz->gen_info->nice_flor_s.btn,
                    subghz->gen_info->nice_flor_s.cnt,
                    subghz->gen_info->nice_flor_s.nice_one);
                break;
            case GenSecPlus2:
                generated_protocol = subghz_txrx_gen_secplus_v2_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->sec_plus_2.serial,
                    subghz->gen_info->sec_plus_2.btn,
                    subghz->gen_info->sec_plus_2.cnt);
                break;
            case GenPhoenixV2:
                generated_protocol = subghz_txrx_gen_phoenix_v2_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->phoenix_v2.serial,
                    subghz->gen_info->phoenix_v2.cnt);
                break;
            case GenPorscheCayenne:
                generated_protocol = subghz_txrx_gen_porsche_cayenne_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->porsche_cayenne.serial,
                    subghz->gen_info->porsche_cayenne.btn,
                    subghz->gen_info->porsche_cayenne.cnt);
                break;
            case GenFordV0:
                if(subghz->gen_info->ford_v0.cnt > 0x000FFFFF) {
                    furi_string_set(
                        subghz->error_str,
                        "Counter too large!\nMax: 0x000FFFFF\n(20-bit only)");
                    scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
                    return true;
                }
                generated_protocol = subghz_txrx_gen_ford_v0_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->ford_v0.serial,
                    subghz->gen_info->ford_v0.btn,
                    subghz->gen_info->ford_v0.cnt,
                    subghz->gen_info->ford_v0.bs_magic);
                break;
            case GenKiaV3:
                generated_protocol = subghz_txrx_gen_kia_v3_v4_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->kia_v3v4.serial,
                    subghz->gen_info->kia_v3v4.btn,
                    subghz->gen_info->kia_v3v4.cnt,
                    1);
                break;
            case GenKiaV4:
                generated_protocol = subghz_txrx_gen_kia_v3_v4_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->kia_v3v4.serial,
                    subghz->gen_info->kia_v3v4.btn,
                    subghz->gen_info->kia_v3v4.cnt,
                    0);
                break;
            case GenKiaV5:
                generated_protocol = subghz_txrx_gen_kia_v5_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->kia_v5.serial,
                    subghz->gen_info->kia_v5.btn,
                    subghz->gen_info->kia_v5.cnt);
                break;
            case GenKiaV6:
                generated_protocol = subghz_txrx_gen_kia_v6_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->kia_v6.serial,
                    subghz->gen_info->kia_v6.btn,
                    subghz->gen_info->kia_v6.cnt,
                    subghz->gen_info->kia_v6.fx);
                break;
                break;
            case GenKiaV2:
                generated_protocol = subghz_txrx_gen_kia_v2_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->kia_v2.serial,
                    subghz->gen_info->kia_v2.btn,
                    subghz->gen_info->kia_v2.cnt);
                break;
            case GenKiaV1:
                generated_protocol = subghz_txrx_gen_kia_v1_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->kia_v1.serial,
                    subghz->gen_info->kia_v1.btn,
                    subghz->gen_info->kia_v1.cnt);
                break;
            case GenKiaV0:
                generated_protocol = subghz_txrx_gen_kia_v0_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->kia_v0.serial,
                    subghz->gen_info->kia_v0.btn,
                    subghz->gen_info->kia_v0.cnt);
                break;
            case GenFiatSpa:
                generated_protocol = subghz_txrx_gen_fiat_spa_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->fiat_spa.fix,
                    subghz->gen_info->fiat_spa.hop,
                    subghz->gen_info->fiat_spa.endbyte);
                break;
            case GenVAG:
                if(subghz->gen_info->vag.cnt > 0x00FFFFFF) {
                    furi_string_set(
                        subghz->error_str,
                        "Counter too large!\nMax: 0x00FFFFFF\n(24-bit only)");
                    scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
                    return true;
                }
                generated_protocol = subghz_txrx_gen_vag_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->vag.serial,
                    subghz->gen_info->vag.cnt,
                    subghz->gen_info->vag.btn,
                    subghz->gen_info->vag.vag_type);
                break;
            case GenMitsubishiV0:
                if(subghz->gen_info->mitsubishi_v0.cnt > 0x0000FFFF) {
                    furi_string_set(
                        subghz->error_str,
                        "Counter too large!\nMax: 0x0000FFFF\n(16-bit only)");
                    scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
                    return true;
                }
                generated_protocol = subghz_txrx_gen_mitsubishi_v0_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->mitsubishi_v0.serial,
                    subghz->gen_info->mitsubishi_v0.btn,
                    subghz->gen_info->mitsubishi_v0.cnt);
                break;
            case GenSubaru:
                generated_protocol = subghz_txrx_gen_subaru_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->subaru.serial,
                    subghz->gen_info->subaru.btn,
                    subghz->gen_info->subaru.cnt);
                break;
            case GenSuzuki:
                if(subghz->gen_info->suzuki.cnt > 0x000FFFFF) {
                    furi_string_set(
                        subghz->error_str,
                        "Counter too large!\nMax: 0x000FFFFF\n(20-bit only)");
                    scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
                    return true;
                }
                generated_protocol = subghz_txrx_gen_suzuki_protocol(
                    subghz->txrx,
                    subghz->gen_info->mod,
                    subghz->gen_info->freq,
                    subghz->gen_info->suzuki.serial,
                    subghz->gen_info->suzuki.btn,
                    subghz->gen_info->suzuki.cnt);
                break;
            // Not needed for these types
            case GenData:
            case GenSecPlus1:
            default:
                furi_crash("Not implemented");
                break;
            }

            consumed = true;

            if(!generated_protocol) {
                furi_string_set(
                    subghz->error_str, "Function requires\nan SD card with\nfresh databases.");
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
            } else {
                subghz_file_name_clear(subghz);

                scene_manager_set_scene_state(
                    subghz->scene_manager, SubGhzSceneSetType, SubGhzCustomEventManagerSet);
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSaveName);
            }
        }
    }
    return consumed;
}

void subghz_scene_set_counter_on_exit(void* context) {
    SubGhz* subghz = context;

    // Clear view
    byte_input_set_result_callback(subghz->byte_input, NULL, NULL, NULL, NULL, 0);
    byte_input_set_header_text(subghz->byte_input, "");
}












