#include "../subghz_i.h"
#include "../helpers/subghz_txrx_create_protocol_key.h"

#define TAG "SubGhzSetButton"

void subghz_scene_set_button_byte_input_callback(void* context) {
    SubGhz* subghz = context;

    view_dispatcher_send_custom_event(subghz->view_dispatcher, SubGhzCustomEventByteInputDone);
}

void subghz_scene_set_button_on_enter(void* context) {
    SubGhz* subghz = context;

    uint8_t* byte_ptr = NULL;
    uint8_t byte_count = 0;

    switch(subghz->gen_info->type) {
    case GenFaacSLH:
        byte_ptr = &subghz->gen_info->faac_slh.btn;
        byte_count = sizeof(subghz->gen_info->faac_slh.btn);
        break;
    case GenKeeloq:
        byte_ptr = &subghz->gen_info->keeloq.btn;
        byte_count = sizeof(subghz->gen_info->keeloq.btn);
        break;
    case GenKeeloqBFT:
        byte_ptr = &subghz->gen_info->keeloq_bft.btn;
        byte_count = sizeof(subghz->gen_info->keeloq_bft.btn);
        break;
    case GenAlutechAt4n:
        byte_ptr = &subghz->gen_info->alutech_at_4n.btn;
        byte_count = sizeof(subghz->gen_info->alutech_at_4n.btn);
        break;
    case GenSomfyTelis:
        byte_ptr = &subghz->gen_info->somfy_telis.btn;
        byte_count = sizeof(subghz->gen_info->somfy_telis.btn);
        break;
    case GenKingGatesStylo4k:
        byte_ptr = &subghz->gen_info->kinggates_stylo_4k.btn;
        byte_count = sizeof(subghz->gen_info->kinggates_stylo_4k.btn);
        break;
    case GenBenincaARC:
        byte_ptr = &subghz->gen_info->beninca_arc.btn;
        byte_count = sizeof(subghz->gen_info->beninca_arc.btn);
        break;
    case GenJarolift:
        byte_ptr = &subghz->gen_info->jarolift.btn;
        byte_count = sizeof(subghz->gen_info->jarolift.btn);
        break;
    case GenNiceFlorS:
        byte_ptr = &subghz->gen_info->nice_flor_s.btn;
        byte_count = sizeof(subghz->gen_info->nice_flor_s.btn);
        break;
    case GenSecPlus2:
        byte_ptr = &subghz->gen_info->sec_plus_2.btn;
        byte_count = sizeof(subghz->gen_info->sec_plus_2.btn);
        break;
    case GenPorscheCayenne:
        byte_ptr = &subghz->gen_info->porsche_cayenne.btn;
        byte_count = sizeof(subghz->gen_info->porsche_cayenne.btn);
        break;
    case GenFordV0:
        byte_ptr = &subghz->gen_info->ford_v0.btn;
        byte_count = sizeof(subghz->gen_info->ford_v0.btn);
        break;
    case GenVAG:
        byte_ptr = &subghz->gen_info->vag.btn;
        byte_count = sizeof(subghz->gen_info->vag.btn);
        break;
    case GenFiatSpa:
        byte_ptr = &subghz->gen_info->fiat_spa.endbyte;
        byte_count = sizeof(subghz->gen_info->fiat_spa.endbyte);
        break;
    case GenKiaV0:
        byte_ptr = &subghz->gen_info->kia_v0.btn;
        byte_count = sizeof(subghz->gen_info->kia_v0.btn);
        break;
    case GenKiaV1:
        byte_ptr = &subghz->gen_info->kia_v1.btn;
        byte_count = sizeof(subghz->gen_info->kia_v1.btn);
        break;
    case GenKiaV2:
        byte_ptr = &subghz->gen_info->kia_v2.btn;
        byte_count = sizeof(subghz->gen_info->kia_v2.btn);
        break;
    case GenKiaV3:
    case GenKiaV4:
        byte_ptr = &subghz->gen_info->kia_v3v4.btn;
        byte_count = sizeof(subghz->gen_info->kia_v3v4.btn);
        break;
    case GenKiaV5:
        byte_ptr = &subghz->gen_info->kia_v5.btn;
        byte_count = sizeof(subghz->gen_info->kia_v5.btn);
        break;
    case GenKiaV6:
        byte_ptr = &subghz->gen_info->kia_v6.btn;
        byte_count = sizeof(subghz->gen_info->kia_v6.btn);
        break;
    case GenMitsubishiV0:
        byte_ptr = &subghz->gen_info->mitsubishi_v0.btn;
        byte_count = sizeof(subghz->gen_info->mitsubishi_v0.btn);
        break;
    case GenSubaru:
        byte_ptr = &subghz->gen_info->subaru.btn;
        byte_count = sizeof(subghz->gen_info->subaru.btn);
        break;
    case GenSuzuki:
        byte_ptr = &subghz->gen_info->suzuki.btn;
        byte_count = sizeof(subghz->gen_info->suzuki.btn);
        break;
    // Not needed for these types
    case GenPhoenixV2:
    case GenData:
    case GenSecPlus1:
    case GenCameAtomo:
    default:
        furi_crash("Not implemented");
        break;
    }

    furi_assert(byte_ptr);
    furi_assert(byte_count > 0);

    // Setup view
    ByteInput* byte_input = subghz->byte_input;
    if(subghz->gen_info->type == GenVAG) {
        byte_input_set_header_text(byte_input, "VAG Button (1 byte):\n10=Unlock 20=Lock\n40=Trunk  80=Panic");
    } else if(subghz->gen_info->type == GenPorscheCayenne) {
        byte_input_set_header_text(byte_input, "Porsche Btn:\n01=Lock 02=Unlock\n04=Trunk 08=Open");
    } else if(subghz->gen_info->type == GenFordV0) {
        byte_input_set_header_text(byte_input, "Ford Btn:\n01=Lock 02=Unlock\n04=Boot/Trunk");
    } else if(subghz->gen_info->type == GenMitsubishiV0) {
        byte_input_set_header_text(byte_input, "Mitsubishi Btn:\n01=Lock 02=Unlock\n04=Trunk");
    } else if(subghz->gen_info->type == GenSubaru) {
        byte_input_set_header_text(byte_input, "Subaru Btn:\n01=Lock  02=Unlock\n03=Trunk 04=Panic");
    } else if(subghz->gen_info->type == GenSuzuki) {
        byte_input_set_header_text(byte_input, "Suzuki Btn:\n03=Lock  04=Unlock\n02=Trunk 01=Panic");
    } else {
        byte_input_set_header_text(byte_input, "Enter BUTTON in hex");
    }
    byte_input_set_result_callback(
        byte_input,
        subghz_scene_set_button_byte_input_callback,
        NULL,
        subghz,
        byte_ptr,
        byte_count);
    view_dispatcher_switch_to_view(subghz->view_dispatcher, SubGhzViewIdByteInput);
}

bool subghz_scene_set_button_on_event(void* context, SceneManagerEvent event) {
    SubGhz* subghz = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == SubGhzCustomEventByteInputDone) {
            switch(subghz->gen_info->type) {
            case GenFaacSLH:
            case GenKeeloq:
            case GenKeeloqBFT:
            case GenAlutechAt4n:
            case GenSomfyTelis:
            case GenKingGatesStylo4k:
            case GenBenincaARC:
            case GenJarolift:
            case GenNiceFlorS:
            case GenSecPlus2:
            case GenFiatSpa:
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSetCounter);
                break;
            case GenKiaV0: {
                uint8_t kbtn = subghz->gen_info->kia_v0.btn;
                if(kbtn < 1 || kbtn > 4) {
                    furi_string_set(subghz->error_str, "Invalid Button!\n01=Lock 02=Unlock\n03=Trunk 04=Horn");
                    scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
                    return true;
                }
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSetCounter);
                break;
            }
            case GenKiaV1: {
                uint8_t kbtn = subghz->gen_info->kia_v1.btn;
                if(kbtn < 1 || kbtn > 4) {
                    furi_string_set(subghz->error_str, "Invalid Button!\n01=Lock 02=Unlock\n03=Trunk 04=Panic");
                    scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
                    return true;
                }
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSetCounter);
                break;
            }
            case GenKiaV2: {
                uint8_t kbtn = subghz->gen_info->kia_v2.btn;
                if(kbtn < 1 || kbtn > 4) {
                    furi_string_set(subghz->error_str, "Invalid Button!\n01=Lock 02=Unlock\n03=Trunk 04=Panic");
                    scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
                    return true;
                }
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSetCounter);
                break;
            }
            case GenKiaV3:
            case GenKiaV4: {
                uint8_t kbtn = subghz->gen_info->kia_v3v4.btn;
                if(kbtn != 0x01 && kbtn != 0x02 && kbtn != 0x03 && kbtn != 0x04 && kbtn != 0x08) {
                    furi_string_set(subghz->error_str, "Invalid Button!\n01 02 03 04 or 08\nLock Unlock Trunk\nPanic Horn");
                    scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
                    return true;
                }
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSetCounter);
                break;
            }
            case GenKiaV5: {
                uint8_t k5btn = subghz->gen_info->kia_v5.btn;
                if(k5btn != 0x01 && k5btn != 0x02 && k5btn != 0x04 && k5btn != 0x08) {
                    furi_string_set(subghz->error_str, "Invalid Button!\n01=Unlock 02=Lock\n04=Trunk  08=Horn");
                    scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
                    return true;
                }
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSetCounter);
                break;
            }
            case GenKiaV6: {
                uint8_t k6btn = subghz->gen_info->kia_v6.btn;
                if(k6btn != 0x01 && k6btn != 0x02 && k6btn != 0x03 && k6btn != 0x04) {
                    furi_string_set(subghz->error_str, "Invalid Button!\n01=Lock  02=Unlock\n03=Trunk 04=Panic");
                    scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
                    return true;
                }
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSetCounter);
                break;
            }
            case GenFordV0: {
                uint8_t fbtn = subghz->gen_info->ford_v0.btn;
                if(fbtn != 0x01 && fbtn != 0x02 && fbtn != 0x04) {
                    furi_string_set(
                        subghz->error_str,
                        "Invalid Button!\n01=Lock 02=Unlock\n04=Boot/Trunk");
                    scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
                    return true;
                }
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSetCounter);
                break;
            }
            case GenPorscheCayenne: {
                uint8_t pbtn = subghz->gen_info->porsche_cayenne.btn;
                if(pbtn != 0x01 && pbtn != 0x02 && pbtn != 0x04 && pbtn != 0x08) {
                    furi_string_set(
                        subghz->error_str,
                        "Invalid Button!\n01 02 04 or 08\nLock Unlock\nTrunk Open");
                    scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
                    return true;
                }
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSetCounter);
                break;
            }
            case GenVAG: {
                uint8_t vbtn = subghz->gen_info->vag.btn;
                if(vbtn != 0x10 && vbtn != 0x20 && vbtn != 0x40 && vbtn != 0x80) {
                    furi_string_set(
                        subghz->error_str,
                        "\nInvalid Button!\n10 20 40 or 80\nUnlock, Lock, \nTrunk, Panic");
                    scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
                    return true;
                }
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSetCounter);
                break;
            }
            case GenMitsubishiV0:
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSetCounter);
                break;
            case GenSubaru: {
                uint8_t sbtn = subghz->gen_info->subaru.btn;
                if(sbtn != 0x01 && sbtn != 0x02 && sbtn != 0x03 && sbtn != 0x04 && sbtn != 0x08) {
                    furi_string_set(
                        subghz->error_str,
                        "Invalid Button!\n01=Lock  02=Unlock\n03=Trunk 04=Panic");
                    scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
                    return true;
                }
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSetCounter);
                break;
            }
            case GenSuzuki: {
                uint8_t szbtn = subghz->gen_info->suzuki.btn;
                if(szbtn != 0x01 && szbtn != 0x02 && szbtn != 0x03 && szbtn != 0x04) {
                    furi_string_set(
                        subghz->error_str,
                        "Invalid Button!\n03=Lock  04=Unlock\n02=Trunk 01=Panic");
                    scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
                    return true;
                }
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSetCounter);
                break;
            }
            // Not needed for these types
            case GenCameAtomo:
            case GenPhoenixV2:
            case GenData:
            case GenSecPlus1:
            default:
                furi_crash("Not implemented");
                break;
            }

            consumed = true;
        }
    }
    return consumed;
}

void subghz_scene_set_button_on_exit(void* context) {
    SubGhz* subghz = context;

    // Clear view
    byte_input_set_result_callback(subghz->byte_input, NULL, NULL, NULL, NULL, 0);
    byte_input_set_header_text(subghz->byte_input, "");
}









