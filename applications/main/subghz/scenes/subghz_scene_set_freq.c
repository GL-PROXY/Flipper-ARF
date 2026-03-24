#include "../subghz_i.h"
#include "../helpers/subghz_gen_info.h"
#include <stdlib.h>

#define TAG "SubGhzSetFreq"

static char freq_str[12] = "434420000";

void subghz_scene_set_freq_text_input_callback(void* context) {
    SubGhz* subghz = context;
    view_dispatcher_send_custom_event(subghz->view_dispatcher, SubGhzCustomEventByteInputDone);
}

void subghz_scene_set_freq_on_enter(void* context) {
    SubGhz* subghz = context;
    snprintf(freq_str, sizeof(freq_str), "%lu", (unsigned long)subghz->gen_info->freq);
    TextInput* text_input = subghz->text_input;
    text_input_set_header_text(text_input, "Frequency in Hz");
    text_input_set_result_callback(
        text_input,
        subghz_scene_set_freq_text_input_callback,
        subghz,
        freq_str,
        sizeof(freq_str),
        false);
    view_dispatcher_switch_to_view(subghz->view_dispatcher, SubGhzViewIdTextInput);
}

bool subghz_scene_set_freq_on_event(void* context, SceneManagerEvent event) {
    SubGhz* subghz = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == SubGhzCustomEventByteInputDone) {
            uint32_t freq = (uint32_t)strtoul(freq_str, NULL, 10);

            if(freq < 1000000 || freq > 1000000000) {
                furi_string_set(
                    subghz->error_str,
                    "Invalid frequency!\nMust be between\n1MHz and 1GHz");
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneShowError);
                return true;
            }

            subghz->gen_info->freq = freq;

            // GenData car protocols go to SetKey, others go to SetSerial
            if(subghz->gen_info->type == GenData) {
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSetKey);
            } else {
                scene_manager_next_scene(subghz->scene_manager, SubGhzSceneSetSerial);
            }
            consumed = true;
        }
    }
    return consumed;
}

void subghz_scene_set_freq_on_exit(void* context) {
    SubGhz* subghz = context;
    text_input_set_result_callback(subghz->text_input, NULL, NULL, NULL, 0, false);
    text_input_set_header_text(subghz->text_input, "");
}
