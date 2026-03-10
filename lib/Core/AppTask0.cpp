//
// Created by Plane on 2026/3/8.
//

#include <task.h>

#include "App.h"

void AppT::Task0(void *pvParameters) {
    for (;;) {
        // 任务代码
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}