SET PATH=C:\Keil\ARM\BIN40;C:\Documents and Settings\All Users\Application Data\Oracle\Java\javapath;C:\Program Files\STMicroelectronics\st_toolset\asm;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;D:\Program Files\Altium Designer Winter 09\System;C:\Cadence\SPB_16.6\openaccess\bin\win32\opt;C:\Cadence\SPB_16.6\tools\capture;C:\Cadence\SPB_16.6\tools\pspice;C:\Cadence\SPB_16.6\tools\specctra\bin;C:\Cadence\SPB_16.6\tools\fet\bin;C:\Cadence\SPB_16.6\tools\libutil\bin;C:\Cadence\SPB_16.6\tools\bin;C:\Cadence\SPB_16.6\tools\pcb\bin;
SET ARMCC41INC=C:\Keil\ARM\RV31\Inc
SET ARMCC41LIB=C:\Keil\ARM\RV31\Lib
SET CPU_TYPE=STM32F103VE
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=LED-Ctrl
SET CPU_CLOCK=0x007A1200
"C:\Keil\ARM\BIN40\ArmAsm" --Via ".\startup_stm32f10x_hd._ia"
"C:\Keil\ARM\BIN40\ArmCC" --Via "main.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "stm32f10x_it.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "usart.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "sys.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "delay.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "flash.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "spi.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "globalvar.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "config.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "crc16.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "datadeal.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "sth10.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "timer.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "utils.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "stmflash.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "stm32f10x_rcc.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "stm32f10x_gpio.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "stm32f10x_usart.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "misc.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "stm32f10x_exti.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "stm32f10x_flash.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "stm32f10x_spi.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "stm32f10x_tim.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "core_cm3.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via "system_stm32f10x.__i"
"C:\Keil\ARM\BIN40\ArmLink" --Via "STM32-ledCtrl.lnp"
C:\Keil\ARM\BIN40\fromelf.exe "STM32-ledCtrl.axf" --i32combined --output "STM32-ledCtrl.hex"
