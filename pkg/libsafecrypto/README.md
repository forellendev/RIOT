The following bash commands will configure an environment variable for the toolchain path and create a baremetal library for use on an embedded ARM Cortex-M4 system:

$ export TOOLCHAIN=/usr/bin/arm-none-eabi-gcc

./configure --host=arm-none-eabi --prefix=$TOOLCHAIN --without-tests --disable-multithreading
        CFLAGS="-mcpu=cortex-m4 -mthumb -mfpu=neon -O2 -falign-functions=16 -ffunction-sections
        -fdata-sections --specs=nosys.specs"
