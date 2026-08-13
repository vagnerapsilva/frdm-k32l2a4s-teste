/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RTC_H
#define __RTC_H
#include "fsl_rtc.h"
// Estados para a máquina de estados do menu
typedef enum {
    EDIT_NONE,
    EDIT_DAY,
    EDIT_MONTH,
    EDIT_YEAR,
    EDIT_HOUR,
    EDIT_MINUTE,
    EDIT_SAVE
} edit_state_t;

// Menu states para seleção de opções
typedef enum {
    MENU_MOSTRAR,
    MENU_AJUSTAR,
    MENU_SAIR
} menu_state_t;

extern void ajustar_rtc(void);
extern void mostrar_data_hora(void);
extern void menu_data_hora(void);

#endif /* __RTC_H */