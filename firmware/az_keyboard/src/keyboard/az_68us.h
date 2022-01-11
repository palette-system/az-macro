// AZ-60JIS �p�ݒ�


// �����N�����̃f�t�H���g�ݒ�
#include "setting_az68us_default.h"



// �L�[�{�[�h�̒�`
#define  KEYBOARD_AZ68US

// ESP32�̎�� (0 = ESP32 / 1 = ESP32-WROVER)
#define  AZESP32_TYPE  1

// �������ɕێ�����L�[�̐�(���������m�ۂ���T�C�Y)
#define KEY_INPUT_MAX  70

// ���C���[�؂�ւ������������e��
#define PRESS_KEY_MAX 16

// �}�E�X�ړ��{�^�������������e��
#define PRESS_MOUSE_MAX 4

// WIFI�A�N�Z�X�|�C���g�̖��O
#define WIFI_AP_SSI_NAME    "AZ-68US"

// Bluetooth �Ō����������\������閼�O
#define BLUETOOTH_SEARCH_NAME    "az-68us"

// EEPROM �ǂݍ��ݎ��̃T�C�Y
#define EEPROM_BUF_SIZE   256

// WEB�t�b�N�p�̃o�b�t�@�T�C�Y
#define WEBFOOK_BUF_SIZE 512

// JSON�o�b�t�@��PSRAM���g�����̃t���O
#define SETTING_JSON_BUF_PSRAM 1

// �ݒ�JSON�̃o�b�t�@�T�C�Y
#define SETTING_JSON_BUF_SIZE 262144

// �ݒ胂�[�h�ɓ��邽�߂̃L�[�ԍ�
#define SETTING_MODE_KEY 0

// �ËL�{�^���ňËL�ł��鐔
#define ANKEY_DATA_MAX_LENGTH  512

// Neopix�f�[�^���M���g��(400 or 800)
#define AZ_NEO_KHZ 400

// �f�B�X�v���C���W���[���̗L��
#define AZ_DISPLAY_ENABLE false

// remap�p �f�t�H���g�� vid  pid
#define BLE_HID_VID  0xE502
#define BLE_HID_PID  0x0500

// remap�p �f�[�^���M���̃L�[��
#define REMAP_KEY_MAX  72

// remap�pcol,row (remap�pJSON���Œ�`����ROW��COL)
#define REMAP_ROW  9
#define REMAP_COL  8

