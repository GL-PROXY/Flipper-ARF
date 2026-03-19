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
