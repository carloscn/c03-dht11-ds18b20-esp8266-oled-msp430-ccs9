################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/opt/ti/ccs9/ccs/tools/compiler/ti-cgt-msp430_18.12.1.LTS/bin/cl430" -vmsp --code_model=small --data_model=small --use_hw_mpy=16 --include_path="C:/opt/ti/ccs9/ccs/ccs_base/msp430/include" --include_path="../inc" --include_path="D:/workspace/CCS_V9/C03_TEMP_HUMI_SOCKET_MSP430_CCS8_3" --include_path="C:/opt/ti/ccs9/ccs/tools/compiler/ti-cgt-msp430_18.12.1.LTS/include" --advice:power="all" --define=__MSP430F149__ -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


