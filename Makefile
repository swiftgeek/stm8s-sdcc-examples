SDCC=sdcc
SDLD=sdld
OBJECTS=pwm.ihx

.PHONY: all clean flash

all: $(OBJECTS)

clean:
	rm -f $(OBJECTS)

flash: $(OBJECT).ihx
	stm8flash -cstlink -p stm8s103 -w $(OBJECT).ihx

%.ihx: %.c
	$(SDCC) -I./inc/ -I./ -lstm8 -mstm8 --out-fmt-ihx $(CFLAGS) $(LDFLAGS) $<
