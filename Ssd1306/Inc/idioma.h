/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IDIOMA_H
#define __IDIOMA_H
//---------------------------------------------------------------------------
/* Includes ------------------------------------------------------------------*/

//---------------------------------------------------------------------------
                                    //"12345678901234567"
static const uint8_t tela_ok[3][17] = { "       OK       ", "       OK       ", "       OK       " };

static const uint8_t tela_confirma[2][3][5] = {
    {"NAO ", "NO  ", "NO  "}, // 00
    {"SIM ", "YES ", "SI  "}  // 01
};
static const uint8_t tela_erros[2][3][17] = {
    {"PC NAO HABILITADO", " PC NOT ENABLED  ", " PC NO HABILITADO"}, // 00
    {"   ERRO EEPROM   ", "  EEPROM ERROR   ", " ERROR DE EEPROM "} // 01
};

static const uint8_t tela_auditoria[4][3][20] = {
    {"  ERRO NO DISCO  ", "   DISK  ERROR   ", " ERROR DE DISCO  "}, // 00
    {"PRONTO P/ RECEBER", "READY TO RECEIVE ", "LISTO P. RICIBIR "}, // 01
    {"EM USO:          ", "USED:            ", "EM USO:          "}, // 02
    {"   EVENTOS:      ", "   EVENT:        ", "   EVENTOS:      "}  // 03
};

static const uint8_t tela_progrs[19][3][19] = {
    {"V1.0[          ]", "V1.0[          ]", "V1.0[          ]"}, // 00
    {"V2.0[          ]", "V2.0[          ]", "V2.0[          ]"}, // 01
    {"80-2[          ]", "80-2[          ]", "80-2[          ]"}, // 02
    {"80-8[          ]", "80-8[          ]", "80-8[          ]"}, // 03
    {" ERRO FECHADURA ", "  LOCK FAILURE  ", "CERRADURA  ERROR"}, // 04
    {"    INVALIDA    ", "    INVALID     ", "    INVALIDA    "}, // 05
    {"ERRO PROGRAMACAO", "PROGRAMMING ERR ", "ERROR DE PROGRAM"}, // 06
    {"ERRO BLOQUEIO   ", "ERROR BLOCKAED  ", "ERROR  BLOQUEO  "}, // 07
    {"ERRO NA ULTIMA  ", "ERROR IN LAST   ", "ERROR ULTIMA    "}, // 08
    {"PROGRAMACAO     ", "PROGRAMMING     ", "PROGRAMACION    "}, // 09
    {"MEMORIA  CHEIA  ", "MEMORY IS FULL  ", "MEMORIA COMPLETA"}, // 10
    {"TECLE (0) INICIO", "PRESS(0)TO START", "PULSE (0) INICIO"}, // 11
    {"CONECT FECHADURA", "CONNECT THE LOCK", "CONECT CERRADURA"}, // 12
    {"ERRO COMUNICACAO", "COMMUNICAT ERROR", "ERROR COMUNICACI"}, // 13
    {"AGUARDE ID ->   ", " ID WAITING->   ", "ESPERAR ID ->   "}, // 14
    {"..AGUARDE..     ", "...WAIT...      ", "..ESPERAR..     "}, // 15
    {"  PC  INVALIDO  ", "ERROR INVALID PC", "  PC NO VALIDO  "}, // 16
    {" ATUALIZADO     ", " AUTHORIZED     ", "  ATUALIZADO    "}, // 17
    {"  APAGANDO      ", "  DELETING      ", "   BORRANDO     "}  // 18

};

static const uint8_t tela_menu[9][3][19] = {
    {"COLETAR         ", "COLLECT         ", "COLECTA         "}, // 00
    {"AUDITORIA       ", "AUDIT           ", "AUDITORIA       "}, // 01
    {"PROGRAMAR       ", "PROGRAM         ", "PROGRAMA        "}, // 
    {"FECHADURAS      ", "LOCKS           ", "CERRADURAS      "}, // 03
    {"CRYPTO          ", "CRYPTO          ", "CRYPTO          "}, // 04
    {"BR11-80         ", "BR11-80         ", "BR11-80         "}, // 05
    {"SMARTGARD       ", "SMARTGARD       ", "SMARTGARD       "}, // 06
    {"DYNAMIC         ", "DYNAMIC         ", "DYNAMIC         "}, // 07
    {"CONFIGURACAO    ", "SETUP           ", "AJUSTES         "}  // 08
};

static const uint8_t tela_config[18][3][21] = {
    {"Product ID:      ", "Product ID:      ", "Product ID:      "}, // 00
    {"Audit:           ", "Audit:           ", "Audit:           "}, // 01
    {"Progr:           ", "Progr:           ", "Progr:           "}, // 02
    {"PRESO AO BD:     ", "STUCK TO DB:     ", "PRESO AL BD:     "}, // 03
    {" DUPLA COMBINACAO", "DOUBLE COMBINATIO", " DOBLE  CUSTODIA "}, // 04
    {"  NAO HABILITADO ", "     INACTIVE    ", "   NO HABILITADO "}, // 05
    {"    HABILITADO   ", "     ACTIVED     ", "    HABILITADO   "}, // 06
    {" SENHAS RANDOMICA", "  RAND PASSWORDS ", " CLAVES RANDOMICA"}, // 07
    {"   NAO  ATIVADO  ", "     INACTIVE    ", "   NO HABILITADO "}, // 08
    {"   TODOS ATIVOS  ", "    ALL ASSETS   ", "  TODOS  ACTIVOS "}, // 09
    {"   MASTER ATIVO  ", " ACTIVED MASTER  ", "  MASTER ACTIVO  "}, // 10
    {" MANAGER RANDOM  ", "  RAND  MANAGER  ", " MANAGER RANDOM  "}, // 11
    {" DEMAIS ESTATICOS", " OTHER  STATICS  ", " OTRAS  ESTATICAS"}, // 12
    {"NIVEL DA BATERIA ", "  BATTERY LEVEL  ", "NIVEL DE BATERIA "}, // 13
    {"     IDIOMA      ", "    LANGUAGE     ", "     IDIOMA      "}, // 14
    {"    PORTUGUES    ", "   PORTUGUESE    ", "    PORTUGUES    "}, // 15
    {"     INGLES      ", "     ENGLISH     ", "     INGLES      "}, // 16
    {"    ESPANHOL     ", "     SPANISH     ", "     ESPANOL     "}  // 17
};

static const uint8_t tela_usuarios[9][3][9] = {
    {"MASTER:  ", "MASTER:  ", "MASTER:  "}, // 00
    {"MANAGER :", "MANAGER :", "MANAGER :"}, // 01
    {"USUARIO2:", "USER2:   ", "USUARIO2:"}, // 02
    {"USUARIO3:", "USER3:   ", "USUARIO3:"}, // 03
    {"USUARIO4:", "USER4:   ", "USUARIO4:"}, // 04
    {"USUARIO5:", "USER5:   ", "USUARIO5:"}, // 05
    {"USUARIO6:", "USER6:   ", "USUARIO6:"}, // 06
    {"USUARIO7:", "USER7:   ", "USUARIO7:"}, // 07
    {"USUARIO8:", "USER8:   ", "USUARIO8:"}  // 08
};

extern uint8_t flag_idioma;
#endif /* __idioma__ */