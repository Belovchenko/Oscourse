/* See COPYRIGHT for copyright information. */

#include <inc/x86.h>
#include <kern/kclock.h>

void
rtc_init(void) {
  nmi_disable(); // NMI - Non maskable Interrupt (прерывания, которые обрабатываются в любом случае, независимо от запретов на другие прерывания) ~outb(0x70, inb(0x70) | NMI_LOCK);
  // LAB 4: Your code here
  uint8_t a_reg, b_reg;
  outb(IO_RTC_CMND, RTC_AREG); //говорим CMOS, что выбираем регистр А
  a_reg = inb(IO_RTC_DATA);    //чтение из порта 71 содержимого в регистре А
  a_reg |= 0x0F;               //побитовое или с 15, то есть прерывание каждые 500 мс
  outb(IO_RTC_DATA, a_reg);    //вывод в порт 71 содержимого регистра А

  outb(IO_RTC_CMND, RTC_BREG); //говорим CMOS, что выбираем регистр B
  b_reg = inb(IO_RTC_DATA);    //чтение из порта 71 содержимого в регистре B
  b_reg |= RTC_PIE;            //установка бита RTC_PIE в регистре B, разрешение периодических прерываний
  outb(IO_RTC_DATA, b_reg);    //вывод в порт 71 содержимого регистра B

  nmi_enable(); //~outb(0x70, inb(0x70) & ~NMI_LOCK);
}

uint8_t
rtc_check_status(void) {
  uint8_t status = 0;
  // LAB 4: Your code here
  // прочитать значение регистра часов C
  outb(IO_RTC_CMND, RTC_CREG);
  status = inb(IO_RTC_DATA);
  return status;
}
