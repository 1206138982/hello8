ARM GAS  /tmp/ccoFISer.s 			page 1


   1              	# 1 "startup_stm32f103xe.s"
   1              	/**
   1              	...
   0              	
   0              	
   2              	  *************** (C) COPYRIGHT 2017 STMicroelectronics ************************
   3              	  * @file      startup_stm32f103xe.s
   4              	  * @author    MCD Application Team
   5              	  * @brief     STM32F103xE Devices vector table for Atollic toolchain.
   6              	  *            This module performs:
   7              	  *                - Set the initial SP
   8              	  *                - Set the initial PC == Reset_Handler,
   9              	  *                - Set the vector table entries with the exceptions ISR address
  10              	  *                - Configure the clock system   
  11              	  *                - Configure external SRAM mounted on STM3210E-EVAL board
  12              	  *                  to be used as data memory (optional, to be enabled by user)
  13              	  *                - Branches to main in the C library (which eventually
  14              	  *                  calls main()).
  15              	  *            After Reset the Cortex-M3 processor is in Thread mode,
  16              	  *            priority is Privileged, and the Stack is set to Main.
  17              	  ******************************************************************************
  18              	  * @attention
  19              	  *
  20              	  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  21              	  * All rights reserved.</center></h2>
  22              	  *
  23              	  * This software component is licensed by ST under BSD 3-Clause license,
  24              	  * the "License"; You may not use this file except in compliance with the
  25              	  * License. You may obtain a copy of the License at:
  26              	  *                        opensource.org/licenses/BSD-3-Clause
  27              	  *
  28              	  ******************************************************************************
  29              	  */
  30              	
  31              	  .syntax unified
  32              	  .cpu cortex-m3
  33              	  .fpu softvfp
  34              	  .thumb
  35              	
  36              	.global g_pfnVectors
  37              	.global Default_Handler
  38              	
  39              	/* start address for the initialization values of the .data section.
  40              	defined in linker script */
  41 0000 00000000 	.word _sidata
  42              	/* start address for the .data section. defined in linker script */
  43 0004 00000000 	.word _sdata
  44              	/* end address for the .data section. defined in linker script */
  45 0008 00000000 	.word _edata
  46              	/* start address for the .bss section. defined in linker script */
  47 000c 00000000 	.word _sbss
  48              	/* end address for the .bss section. defined in linker script */
  49 0010 00000000 	.word _ebss
  50              	
  51              	.equ  BootRAM,        0xF1E0F85F
  52              	/**
  53              	 * @brief  This is the code that gets called when the processor first
ARM GAS  /tmp/ccoFISer.s 			page 2


  54              	 *          starts execution following a reset event. Only the absolutely
  55              	 *          necessary set is performed, after which the application
  56              	 *          supplied main() routine is called.
  57              	 * @param  None
  58              	 * @retval : None
  59              	*/
  60              	
  61              	  .section .text.Reset_Handler
  62              	  .weak Reset_Handler
  64              	Reset_Handler:
  65              	
  66              	/* Copy the data segment initializers from flash to SRAM */
  67 0000 0C48     	  ldr r0, =_sdata
  68 0002 0D49     	  ldr r1, =_edata
  69 0004 0D4A     	  ldr r2, =_sidata
  70 0006 0023     	  movs r3, #0
  71 0008 02E0     	  b LoopCopyDataInit
  72              	
  73              	CopyDataInit:
  74 000a D458     	  ldr r4, [r2, r3]
  75 000c C450     	  str r4, [r0, r3]
  76 000e 0433     	  adds r3, r3, #4
  77              	
  78              	LoopCopyDataInit:
  79 0010 C418     	  adds r4, r0, r3
  80 0012 8C42     	  cmp r4, r1
  81 0014 F9D3     	  bcc CopyDataInit
  82              	  
  83              	/* Zero fill the bss segment. */
  84 0016 0A4A     	  ldr r2, =_sbss
  85 0018 0A4C     	  ldr r4, =_ebss
  86 001a 0023     	  movs r3, #0
  87 001c 01E0     	  b LoopFillZerobss
  88              	
  89              	FillZerobss:
  90 001e 1360     	  str  r3, [r2]
  91 0020 0432     	  adds r2, r2, #4
  92              	
  93              	LoopFillZerobss:
  94 0022 A242     	  cmp r2, r4
  95 0024 FBD3     	  bcc FillZerobss
  96              	
  97              	/* Call the clock system intitialization function.*/
  98 0026 FFF7FEFF 	    bl  SystemInit
  99              	/* Call static constructors */
 100 002a FFF7FEFF 	    bl __libc_init_array
 101              	/* Call the application's entry point.*/
 102 002e FFF7FEFF 	  bl main
 103 0032 7047     	  bx lr
 105              	
 106              	/**
 107              	 * @brief  This is the code that gets called when the processor receives an
 108              	 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 109              	 *         the system state for examination by a debugger.
 110              	 *
 111              	 * @param  None
 112              	 * @retval : None
ARM GAS  /tmp/ccoFISer.s 			page 3


 113              	*/
 114              	    .section .text.Default_Handler,"ax",%progbits
 115              	Default_Handler:
 116              	Infinite_Loop:
 117 0000 FEE7     	  b Infinite_Loop
 119              	/******************************************************************************
 120              	*
 121              	* The minimal vector table for a Cortex M3.  Note that the proper constructs
 122              	* must be placed on this to ensure that it ends up at physical address
 123              	* 0x0000.0000.
 124              	*
 125              	******************************************************************************/
 126              	  .section .isr_vector,"a",%progbits
 129              	
 130              	
 131              	g_pfnVectors:
 132              	
 133 0000 00000000 	  .word _estack
 134 0004 00000000 	  .word Reset_Handler
 135 0008 00000000 	  .word NMI_Handler
 136 000c 00000000 	  .word HardFault_Handler
 137 0010 00000000 	  .word MemManage_Handler
 138 0014 00000000 	  .word BusFault_Handler
 139 0018 00000000 	  .word UsageFault_Handler
 140 001c 00000000 	  .word 0
 141 0020 00000000 	  .word 0
 142 0024 00000000 	  .word 0
 143 0028 00000000 	  .word 0
 144 002c 00000000 	  .word SVC_Handler
 145 0030 00000000 	  .word DebugMon_Handler
 146 0034 00000000 	  .word 0
 147 0038 00000000 	  .word PendSV_Handler
 148 003c 00000000 	  .word SysTick_Handler
 149 0040 00000000 	  .word WWDG_IRQHandler
 150 0044 00000000 	  .word PVD_IRQHandler
 151 0048 00000000 	  .word TAMPER_IRQHandler
 152 004c 00000000 	  .word RTC_IRQHandler
 153 0050 00000000 	  .word FLASH_IRQHandler
 154 0054 00000000 	  .word RCC_IRQHandler
 155 0058 00000000 	  .word EXTI0_IRQHandler
 156 005c 00000000 	  .word EXTI1_IRQHandler
 157 0060 00000000 	  .word EXTI2_IRQHandler
 158 0064 00000000 	  .word EXTI3_IRQHandler
 159 0068 00000000 	  .word EXTI4_IRQHandler
 160 006c 00000000 	  .word DMA1_Channel1_IRQHandler
 161 0070 00000000 	  .word DMA1_Channel2_IRQHandler
 162 0074 00000000 	  .word DMA1_Channel3_IRQHandler
 163 0078 00000000 	  .word DMA1_Channel4_IRQHandler
 164 007c 00000000 	  .word DMA1_Channel5_IRQHandler
 165 0080 00000000 	  .word DMA1_Channel6_IRQHandler
 166 0084 00000000 	  .word DMA1_Channel7_IRQHandler
 167 0088 00000000 	  .word ADC1_2_IRQHandler
 168 008c 00000000 	  .word USB_HP_CAN1_TX_IRQHandler
 169 0090 00000000 	  .word USB_LP_CAN1_RX0_IRQHandler
 170 0094 00000000 	  .word CAN1_RX1_IRQHandler
 171 0098 00000000 	  .word CAN1_SCE_IRQHandler
 172 009c 00000000 	  .word EXTI9_5_IRQHandler
ARM GAS  /tmp/ccoFISer.s 			page 4


 173 00a0 00000000 	  .word TIM1_BRK_IRQHandler
 174 00a4 00000000 	  .word TIM1_UP_IRQHandler
 175 00a8 00000000 	  .word TIM1_TRG_COM_IRQHandler
 176 00ac 00000000 	  .word TIM1_CC_IRQHandler
 177 00b0 00000000 	  .word TIM2_IRQHandler
 178 00b4 00000000 	  .word TIM3_IRQHandler
 179 00b8 00000000 	  .word TIM4_IRQHandler
 180 00bc 00000000 	  .word I2C1_EV_IRQHandler
 181 00c0 00000000 	  .word I2C1_ER_IRQHandler
 182 00c4 00000000 	  .word I2C2_EV_IRQHandler
 183 00c8 00000000 	  .word I2C2_ER_IRQHandler
 184 00cc 00000000 	  .word SPI1_IRQHandler
 185 00d0 00000000 	  .word SPI2_IRQHandler
 186 00d4 00000000 	  .word USART1_IRQHandler
 187 00d8 00000000 	  .word USART2_IRQHandler
 188 00dc 00000000 	  .word USART3_IRQHandler
 189 00e0 00000000 	  .word EXTI15_10_IRQHandler
 190 00e4 00000000 	  .word RTC_Alarm_IRQHandler
 191 00e8 00000000 	  .word USBWakeUp_IRQHandler
 192 00ec 00000000 	  .word TIM8_BRK_IRQHandler
 193 00f0 00000000 	  .word TIM8_UP_IRQHandler
 194 00f4 00000000 	  .word TIM8_TRG_COM_IRQHandler
 195 00f8 00000000 	  .word TIM8_CC_IRQHandler
 196 00fc 00000000 	  .word ADC3_IRQHandler
 197 0100 00000000 	  .word FSMC_IRQHandler
 198 0104 00000000 	  .word SDIO_IRQHandler
 199 0108 00000000 	  .word TIM5_IRQHandler
 200 010c 00000000 	  .word SPI3_IRQHandler
 201 0110 00000000 	  .word UART4_IRQHandler
 202 0114 00000000 	  .word UART5_IRQHandler
 203 0118 00000000 	  .word TIM6_IRQHandler
 204 011c 00000000 	  .word TIM7_IRQHandler
 205 0120 00000000 	  .word DMA2_Channel1_IRQHandler
 206 0124 00000000 	  .word DMA2_Channel2_IRQHandler
 207 0128 00000000 	  .word DMA2_Channel3_IRQHandler
 208 012c 00000000 	  .word DMA2_Channel4_5_IRQHandler
 209 0130 00000000 	  .word 0
 210 0134 00000000 	  .word 0
 211 0138 00000000 	  .word 0
 212 013c 00000000 	  .word 0
 213 0140 00000000 	  .word 0
 214 0144 00000000 	  .word 0
 215 0148 00000000 	  .word 0
 216 014c 00000000 	  .word 0
 217 0150 00000000 	  .word 0
 218 0154 00000000 	  .word 0
 219 0158 00000000 	  .word 0
 220 015c 00000000 	  .word 0
 221 0160 00000000 	  .word 0
 222 0164 00000000 	  .word 0
 223 0168 00000000 	  .word 0
 224 016c 00000000 	  .word 0
 225 0170 00000000 	  .word 0
 226 0174 00000000 	  .word 0
 227 0178 00000000 	  .word 0
 228 017c 00000000 	  .word 0
 229 0180 00000000 	  .word 0
ARM GAS  /tmp/ccoFISer.s 			page 5


 230 0184 00000000 	  .word 0
 231 0188 00000000 	  .word 0
 232 018c 00000000 	  .word 0
 233 0190 00000000 	  .word 0
 234 0194 00000000 	  .word 0
 235 0198 00000000 	  .word 0
 236 019c 00000000 	  .word 0
 237 01a0 00000000 	  .word 0
 238 01a4 00000000 	  .word 0
 239 01a8 00000000 	  .word 0
 240 01ac 00000000 	  .word 0
 241 01b0 00000000 	  .word 0
 242 01b4 00000000 	  .word 0
 243 01b8 00000000 	  .word 0
 244 01bc 00000000 	  .word 0
 245 01c0 00000000 	  .word 0
 246 01c4 00000000 	  .word 0
 247 01c8 00000000 	  .word 0
 248 01cc 00000000 	  .word 0
 249 01d0 00000000 	  .word 0
 250 01d4 00000000 	  .word 0
 251 01d8 00000000 	  .word 0
 252 01dc 00000000 	  .word 0
 253 01e0 5FF8E0F1 	  .word BootRAM       /* @0x1E0. This is for boot in RAM mode for
 254              	                         STM32F10x High Density devices. */
 255              	
 256              	/*******************************************************************************
 257              	*
 258              	* Provide weak aliases for each Exception handler to the Default_Handler.
 259              	* As they are weak aliases, any function with the same name will override
 260              	* this definition.
 261              	*
 262              	*******************************************************************************/
 263              	
 264              	  .weak NMI_Handler
 265              	  .thumb_set NMI_Handler,Default_Handler
 266              	
 267              	  .weak HardFault_Handler
 268              	  .thumb_set HardFault_Handler,Default_Handler
 269              	
 270              	  .weak MemManage_Handler
 271              	  .thumb_set MemManage_Handler,Default_Handler
 272              	
 273              	  .weak BusFault_Handler
 274              	  .thumb_set BusFault_Handler,Default_Handler
 275              	
 276              	  .weak UsageFault_Handler
 277              	  .thumb_set UsageFault_Handler,Default_Handler
 278              	
 279              	  .weak SVC_Handler
 280              	  .thumb_set SVC_Handler,Default_Handler
 281              	
 282              	  .weak DebugMon_Handler
 283              	  .thumb_set DebugMon_Handler,Default_Handler
 284              	
 285              	  .weak PendSV_Handler
 286              	  .thumb_set PendSV_Handler,Default_Handler
ARM GAS  /tmp/ccoFISer.s 			page 6


 287              	
 288              	  .weak SysTick_Handler
 289              	  .thumb_set SysTick_Handler,Default_Handler
 290              	
 291              	  .weak WWDG_IRQHandler
 292              	  .thumb_set WWDG_IRQHandler,Default_Handler
 293              	
 294              	  .weak PVD_IRQHandler
 295              	  .thumb_set PVD_IRQHandler,Default_Handler
 296              	
 297              	  .weak TAMPER_IRQHandler
 298              	  .thumb_set TAMPER_IRQHandler,Default_Handler
 299              	
 300              	  .weak RTC_IRQHandler
 301              	  .thumb_set RTC_IRQHandler,Default_Handler
 302              	
 303              	  .weak FLASH_IRQHandler
 304              	  .thumb_set FLASH_IRQHandler,Default_Handler
 305              	
 306              	  .weak RCC_IRQHandler
 307              	  .thumb_set RCC_IRQHandler,Default_Handler
 308              	
 309              	  .weak EXTI0_IRQHandler
 310              	  .thumb_set EXTI0_IRQHandler,Default_Handler
 311              	
 312              	  .weak EXTI1_IRQHandler
 313              	  .thumb_set EXTI1_IRQHandler,Default_Handler
 314              	
 315              	  .weak EXTI2_IRQHandler
 316              	  .thumb_set EXTI2_IRQHandler,Default_Handler
 317              	
 318              	  .weak EXTI3_IRQHandler
 319              	  .thumb_set EXTI3_IRQHandler,Default_Handler
 320              	
 321              	  .weak EXTI4_IRQHandler
 322              	  .thumb_set EXTI4_IRQHandler,Default_Handler
 323              	
 324              	  .weak DMA1_Channel1_IRQHandler
 325              	  .thumb_set DMA1_Channel1_IRQHandler,Default_Handler
 326              	
 327              	  .weak DMA1_Channel2_IRQHandler
 328              	  .thumb_set DMA1_Channel2_IRQHandler,Default_Handler
 329              	
 330              	  .weak DMA1_Channel3_IRQHandler
 331              	  .thumb_set DMA1_Channel3_IRQHandler,Default_Handler
 332              	
 333              	  .weak DMA1_Channel4_IRQHandler
 334              	  .thumb_set DMA1_Channel4_IRQHandler,Default_Handler
 335              	
 336              	  .weak DMA1_Channel5_IRQHandler
 337              	  .thumb_set DMA1_Channel5_IRQHandler,Default_Handler
 338              	
 339              	  .weak DMA1_Channel6_IRQHandler
 340              	  .thumb_set DMA1_Channel6_IRQHandler,Default_Handler
 341              	
 342              	  .weak DMA1_Channel7_IRQHandler
 343              	  .thumb_set DMA1_Channel7_IRQHandler,Default_Handler
ARM GAS  /tmp/ccoFISer.s 			page 7


 344              	
 345              	  .weak ADC1_2_IRQHandler
 346              	  .thumb_set ADC1_2_IRQHandler,Default_Handler
 347              	
 348              	  .weak USB_HP_CAN1_TX_IRQHandler
 349              	  .thumb_set USB_HP_CAN1_TX_IRQHandler,Default_Handler
 350              	
 351              	  .weak USB_LP_CAN1_RX0_IRQHandler
 352              	  .thumb_set USB_LP_CAN1_RX0_IRQHandler,Default_Handler
 353              	
 354              	  .weak CAN1_RX1_IRQHandler
 355              	  .thumb_set CAN1_RX1_IRQHandler,Default_Handler
 356              	
 357              	  .weak CAN1_SCE_IRQHandler
 358              	  .thumb_set CAN1_SCE_IRQHandler,Default_Handler
 359              	
 360              	  .weak EXTI9_5_IRQHandler
 361              	  .thumb_set EXTI9_5_IRQHandler,Default_Handler
 362              	
 363              	  .weak TIM1_BRK_IRQHandler
 364              	  .thumb_set TIM1_BRK_IRQHandler,Default_Handler
 365              	
 366              	  .weak TIM1_UP_IRQHandler
 367              	  .thumb_set TIM1_UP_IRQHandler,Default_Handler
 368              	
 369              	  .weak TIM1_TRG_COM_IRQHandler
 370              	  .thumb_set TIM1_TRG_COM_IRQHandler,Default_Handler
 371              	
 372              	  .weak TIM1_CC_IRQHandler
 373              	  .thumb_set TIM1_CC_IRQHandler,Default_Handler
 374              	
 375              	  .weak TIM2_IRQHandler
 376              	  .thumb_set TIM2_IRQHandler,Default_Handler
 377              	
 378              	  .weak TIM3_IRQHandler
 379              	  .thumb_set TIM3_IRQHandler,Default_Handler
 380              	
 381              	  .weak TIM4_IRQHandler
 382              	  .thumb_set TIM4_IRQHandler,Default_Handler
 383              	
 384              	  .weak I2C1_EV_IRQHandler
 385              	  .thumb_set I2C1_EV_IRQHandler,Default_Handler
 386              	
 387              	  .weak I2C1_ER_IRQHandler
 388              	  .thumb_set I2C1_ER_IRQHandler,Default_Handler
 389              	
 390              	  .weak I2C2_EV_IRQHandler
 391              	  .thumb_set I2C2_EV_IRQHandler,Default_Handler
 392              	
 393              	  .weak I2C2_ER_IRQHandler
 394              	  .thumb_set I2C2_ER_IRQHandler,Default_Handler
 395              	
 396              	  .weak SPI1_IRQHandler
 397              	  .thumb_set SPI1_IRQHandler,Default_Handler
 398              	
 399              	  .weak SPI2_IRQHandler
 400              	  .thumb_set SPI2_IRQHandler,Default_Handler
ARM GAS  /tmp/ccoFISer.s 			page 8


 401              	
 402              	  .weak USART1_IRQHandler
 403              	  .thumb_set USART1_IRQHandler,Default_Handler
 404              	
 405              	  .weak USART2_IRQHandler
 406              	  .thumb_set USART2_IRQHandler,Default_Handler
 407              	
 408              	  .weak USART3_IRQHandler
 409              	  .thumb_set USART3_IRQHandler,Default_Handler
 410              	
 411              	  .weak EXTI15_10_IRQHandler
 412              	  .thumb_set EXTI15_10_IRQHandler,Default_Handler
 413              	
 414              	  .weak RTC_Alarm_IRQHandler
 415              	  .thumb_set RTC_Alarm_IRQHandler,Default_Handler
 416              	
 417              	  .weak USBWakeUp_IRQHandler
 418              	  .thumb_set USBWakeUp_IRQHandler,Default_Handler
 419              	
 420              	  .weak TIM8_BRK_IRQHandler
 421              	  .thumb_set TIM8_BRK_IRQHandler,Default_Handler
 422              	
 423              	  .weak TIM8_UP_IRQHandler
 424              	  .thumb_set TIM8_UP_IRQHandler,Default_Handler
 425              	
 426              	  .weak TIM8_TRG_COM_IRQHandler
 427              	  .thumb_set TIM8_TRG_COM_IRQHandler,Default_Handler
 428              	
 429              	  .weak TIM8_CC_IRQHandler
 430              	  .thumb_set TIM8_CC_IRQHandler,Default_Handler
 431              	
 432              	  .weak ADC3_IRQHandler
 433              	  .thumb_set ADC3_IRQHandler,Default_Handler
 434              	
 435              	  .weak FSMC_IRQHandler
 436              	  .thumb_set FSMC_IRQHandler,Default_Handler
 437              	
 438              	  .weak SDIO_IRQHandler
 439              	  .thumb_set SDIO_IRQHandler,Default_Handler
 440              	
 441              	  .weak TIM5_IRQHandler
 442              	  .thumb_set TIM5_IRQHandler,Default_Handler
 443              	
 444              	  .weak SPI3_IRQHandler
 445              	  .thumb_set SPI3_IRQHandler,Default_Handler
 446              	
 447              	  .weak UART4_IRQHandler
 448              	  .thumb_set UART4_IRQHandler,Default_Handler
 449              	
 450              	  .weak UART5_IRQHandler
 451              	  .thumb_set UART5_IRQHandler,Default_Handler
 452              	
 453              	  .weak TIM6_IRQHandler
 454              	  .thumb_set TIM6_IRQHandler,Default_Handler
 455              	
 456              	  .weak TIM7_IRQHandler
 457              	  .thumb_set TIM7_IRQHandler,Default_Handler
ARM GAS  /tmp/ccoFISer.s 			page 9


 458              	
 459              	  .weak DMA2_Channel1_IRQHandler
 460              	  .thumb_set DMA2_Channel1_IRQHandler,Default_Handler
 461              	
 462              	  .weak DMA2_Channel2_IRQHandler
 463              	  .thumb_set DMA2_Channel2_IRQHandler,Default_Handler
 464              	
 465              	  .weak DMA2_Channel3_IRQHandler
 466              	  .thumb_set DMA2_Channel3_IRQHandler,Default_Handler
 467              	
 468              	  .weak DMA2_Channel4_5_IRQHandler
 469              	  .thumb_set DMA2_Channel4_5_IRQHandler,Default_Handler
ARM GAS  /tmp/ccoFISer.s 			page 10


DEFINED SYMBOLS
startup_stm32f103xe.s:131    .isr_vector:0000000000000000 g_pfnVectors
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 Default_Handler
startup_stm32f103xe.s:51     *ABS*:00000000f1e0f85f BootRAM
startup_stm32f103xe.s:64     .text.Reset_Handler:0000000000000000 Reset_Handler
startup_stm32f103xe.s:67     .text.Reset_Handler:0000000000000000 $t
startup_stm32f103xe.s:78     .text.Reset_Handler:0000000000000010 LoopCopyDataInit
startup_stm32f103xe.s:73     .text.Reset_Handler:000000000000000a CopyDataInit
startup_stm32f103xe.s:93     .text.Reset_Handler:0000000000000022 LoopFillZerobss
startup_stm32f103xe.s:89     .text.Reset_Handler:000000000000001e FillZerobss
startup_stm32f103xe.s:116    .text.Default_Handler:0000000000000000 Infinite_Loop
startup_stm32f103xe.s:117    .text.Default_Handler:0000000000000000 $t
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 NMI_Handler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 HardFault_Handler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 MemManage_Handler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 BusFault_Handler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 UsageFault_Handler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 SVC_Handler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 DebugMon_Handler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 PendSV_Handler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 SysTick_Handler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 WWDG_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 PVD_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 TAMPER_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 RTC_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 FLASH_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 RCC_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 EXTI0_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 EXTI1_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 EXTI2_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 EXTI3_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 EXTI4_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 DMA1_Channel1_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 DMA1_Channel2_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 DMA1_Channel3_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 DMA1_Channel4_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 DMA1_Channel5_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 DMA1_Channel6_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 DMA1_Channel7_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 ADC1_2_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 USB_HP_CAN1_TX_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 USB_LP_CAN1_RX0_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 CAN1_RX1_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 CAN1_SCE_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 EXTI9_5_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 TIM1_BRK_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 TIM1_UP_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 TIM1_TRG_COM_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 TIM1_CC_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 TIM2_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 TIM3_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 TIM4_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 I2C1_EV_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 I2C1_ER_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 I2C2_EV_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 I2C2_ER_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 SPI1_IRQHandler
ARM GAS  /tmp/ccoFISer.s 			page 11


startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 SPI2_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 USART1_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 USART2_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 USART3_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 EXTI15_10_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 RTC_Alarm_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 USBWakeUp_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 TIM8_BRK_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 TIM8_UP_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 TIM8_TRG_COM_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 TIM8_CC_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 ADC3_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 FSMC_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 SDIO_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 TIM5_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 SPI3_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 UART4_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 UART5_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 TIM6_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 TIM7_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 DMA2_Channel1_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 DMA2_Channel2_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 DMA2_Channel3_IRQHandler
startup_stm32f103xe.s:115    .text.Default_Handler:0000000000000000 DMA2_Channel4_5_IRQHandler
startup_stm32f103xe.s:469    .text.Reset_Handler:0000000000000034 $d
                            .text:0000000000000000 $d

UNDEFINED SYMBOLS
_sidata
_sdata
_edata
_sbss
_ebss
SystemInit
__libc_init_array
main
_estack
