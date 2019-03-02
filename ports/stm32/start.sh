
BOARD=STM32F401CCU6
BOARD=M401

source /home/lq/tools/script/env.stm32.normal
# source /home/lq/tools/script/env.stm32f4.fpu
make BOARD=$BOARD $1
