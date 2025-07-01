#!/bin/sh
set -e

BOARD=WEACT_H562RGT6
PORTS_DIR="ports/stm32"
BUILD_DIR="$PORTS_DIR/build-$BOARD"
GENHDR_DIR="$BUILD_DIR/genhdr"
PINS_C="$BUILD_DIR/pins_${BOARD}.c"
PIN_H="$GENHDR_DIR/pin.h"
MAKEFILE="$PORTS_DIR/Makefile"

ADC_C_CONTENT='
const machine_pin_obj_t *pin_adc1[] = {
    &pin_A0_obj, &pin_A1_obj, &pin_A2_obj, &pin_A3_obj, &pin_A4_obj,
    &pin_A5_obj, &pin_A6_obj, &pin_A7_obj, &pin_B0_obj, &pin_B1_obj,
};
const machine_pin_obj_t *pin_adc2[] = {
    &pin_A0_obj, &pin_A1_obj, &pin_A2_obj, &pin_A3_obj, &pin_A4_obj,
    &pin_A5_obj, &pin_A6_obj, &pin_A7_obj, &pin_B0_obj, &pin_B1_obj,
};
'

ADC_H_CONTENT='
extern const machine_pin_obj_t *pin_adc1[];
extern const machine_pin_obj_t *pin_adc2[];
'

echo "=== 1. Patching $MAKEFILE to ensure -I\$(BUILD)/genhdr is first in INC ==="
# Patch only if not already present
if ! grep -qE 'INC.*-I\$(BUILD)/genhdr' "$MAKEFILE"; then
    # Try to find the line where INC is first set and add -I$(BUILD)/genhdr at the beginning
    cp "$MAKEFILE" "$MAKEFILE.bak"
    awk '
        BEGIN {patched=0}
        /^INC[[:space:]]*=.*$/ && !patched {
            sub(/=/, "= -I$(BUILD)/genhdr ");
            patched=1
        }
        {print}
    ' "$MAKEFILE.bak" > "$MAKEFILE"
    echo "-> Patched $MAKEFILE (backup at $MAKEFILE.bak)"
else
    echo "-> $MAKEFILE already patched."
fi

echo
echo "=== 2. Clean previous build ==="
make -C "$PORTS_DIR" BOARD="$BOARD" clean

echo
echo "=== 3. Generate only pins_<BOARD>.c ==="
make -C "$PORTS_DIR" BOARD="$BOARD" "build-$BOARD/pins_${BOARD}.c" || true

echo
echo "=== 4. Ensure genhdr/pin.h exists and patch with ADC externs ==="
if [ ! -f "$PIN_H" ]; then
    echo "Creating missing $PIN_H ..."
    mkdir -p "$GENHDR_DIR"
    echo "#ifndef MICROPY_INCLUDED_STM32_PIN_H" > "$PIN_H"
    echo "#define MICROPY_INCLUDED_STM32_PIN_H" >> "$PIN_H"
    echo "#endif" >> "$PIN_H"
fi

if ! grep -q 'extern const machine_pin_obj_t \*pin_adc1\[\];' "$PIN_H"; then
    echo "Patching $PIN_H with ADC extern declarations before final #endif..."
    tmpfile=$(mktemp)
    awk -v adc="$ADC_H_CONTENT" '
        BEGIN { inserted=0 }
        /^#endif/ && !inserted { print adc; inserted=1 }
        { print }
    ' "$PIN_H" > "$tmpfile" && mv "$tmpfile" "$PIN_H"
else
    echo "$PIN_H already contains extern pin_adc1."
fi

echo
echo "=== 5. Patch pins_<BOARD>.c with ADC arrays ==="
if ! grep -q 'const machine_pin_obj_t \*pin_adc1\[\]' "$PINS_C"; then
    echo "Patching $PINS_C with ADC arrays before final #endif..."
    tmpfile=$(mktemp)
    awk -v adc="$ADC_C_CONTENT" '
        BEGIN { inserted=0 }
        /^#endif/ && !inserted { print adc; inserted=1 }
        { print }
    ' "$PINS_C" > "$tmpfile" && mv "$tmpfile" "$PINS_C"
else
    echo "$PINS_C already contains pin_adc1."
fi

touch "$PINS_C" "$PIN_H"

echo
echo "=== 6. Run the full build ==="
make -C "$PORTS_DIR" BOARD="$BOARD" V=1

echo
echo "=== 7. Build completed! ==="
