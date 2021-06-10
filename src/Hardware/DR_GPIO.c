#ifdef __cplusplus
extern "C" {
#endif

#include <Hardware/DR_GPIO.h>
#include <Hardware/DR_PLL.h>
#include <System.h>

#define MODE_OFFSET 0x00
#define CNF_OFFSET 0x02

typedef struct {
    __IO uint32_t CRL;
    __IO uint32_t CRH;
    __IO uint32_t IDR;
    __IO uint32_t ODR;
    __IO uint32_t BSRR;
    __IO uint32_t BRR;
    __IO uint32_t LCKR;
    __I uint32_t _[0xF9];  // PADDING
} GPIO_Padded_TypeDef;

#define GPIO ((GPIO_Padded_TypeDef*)GPIOA_BASE)

void GPIO_portEn(uint8_t port) {
    switch (port) {
        case PORTA:
            APB_Enable(APB2, GPIOA_APB);
            break;
        case PORTB:
            APB_Enable(APB2, GPIOB_APB);
            break;
        case PORTC:
            APB_Enable(APB2, GPIOC_APB);
            break;
    }
}

/** @brief 	setea un pin como entrada o salida
 *  @param	Puerto del pin que se quiere congurar
 *  @param 	Número de pin a configurar
 *  @param	Modo. USAR DEFINES INPUT y OUTPUT
 */
void GPIO_setDir(uint8_t port, uint8_t pin, uint8_t mode) {
    // Pongo los de modo en 0 para luego poder escribir
    // Quedan definidos como entradas

    if (pin > 7)
        GPIO[port].CRH &= ~(0x03 << ((pin - 8) * 4 + MODE_OFFSET));
    else
        GPIO[port].CRL &= ~(0x03 << (pin * 4 + MODE_OFFSET));

    if (mode != INPUT) {
        if (pin > 7)
            GPIO[port].CRH |= (0x01 << ((pin - 8) * 4 + MODE_OFFSET));
        else
            GPIO[port].CRL |= (0x01 << (pin * 4 + MODE_OFFSET));
        return;
    }
}

/** @brief 	poner un pin configurado como OUTPUT en push-pull o opendrain
 *  @param	Puerto del pin que se quiere congurar
 *  @param 	Número de pin a configurar
 *  @param	Modo. USAR DEFINES OUTPUT_PUSHPULL y OUTPUT_OPENDRAIN
 */
void GPIO_setOutputMode(uint8_t port, uint8_t pin, uint8_t mode) {
    //---reset bits to be set
    // pongo en 0 los bits de crl.cnf. Está configurado como analog
    if (pin > 7)
        GPIO[port].CRH &= ~(0x03 << ((pin - 8) * 4 + CNF_OFFSET));
    else
        GPIO[port].CRL &= ~(0x03 << (pin * 4 + CNF_OFFSET));

    //---set bits
    if (pin > 7)
        GPIO[port].CRH |= (mode << ((pin - 8) * 4 + CNF_OFFSET));
    else
        GPIO[port].CRL |= (mode << (pin * 4 + CNF_OFFSET));
}

/** @brief 	configurar máxima velocidad de salida de un pin configurado como
 * OUTPUT o como ALTERNATE
 *  @param	Puerto del pin que se quiere congurar
 *  @param 	Número de pin a configurar
 *  @param	máxima velocidad. usar defines MAX_VEL_10MHZ, MAX_VEL_2MHZ,
 * MAX_VEL_50MHZ
 */
void GPIO_setMaxOutputSpeed(uint8_t port, uint8_t pin, uint8_t vel) {
    //---set bits
    if (pin > 7)
        GPIO[port].CRH |= (vel << ((pin - 8) * 4 + MODE_OFFSET));
    else
        GPIO[port].CRL |= (vel << (pin * 4 + MODE_OFFSET));
}

/** @brief 	poner un pin configurado como input en pullup, pul down, etc
 *  @param	Puerto del pin que se quiere congurar
 *  @param 	Número de pin a configurar
 *  @param	Modo. USAR DEFINES INPUT_PULLUP, INPUT_PULLDOWN, INPUT_FLOATING e
 * INPUT_ANALOG
 */
void GPIO_setInputMode(uint8_t port, uint8_t pin, uint8_t mode) {
    //---reset bits to be set
    // pongo en 0 los bits de crl.cnf. Está configurado como analog
    GPIO[port].ODR &= ~(1 << pin);

    if (pin > 7)
        GPIO[port].CRH &= ~(0x03 << ((pin - 8) * 4 + CNF_OFFSET));
    else
        GPIO[port].CRL &= ~(0x03 << (pin * 4 + CNF_OFFSET));

    //---set bits
    if (pin > 7)
        GPIO[port].CRH |= (mode << ((pin - 8) * 4 + CNF_OFFSET));
    else
        GPIO[port].CRL |= (mode << (pin * 4 + CNF_OFFSET));
}

extern inline void GPIO_setPull(uint8_t port, uint8_t pin, uint8_t set){
    if (set == HIGH) 
        GPIO[port].ODR |= (1 << pin);
    else if(set == LOW)
        GPIO[port].ODR &= ~(1 << pin);
} 

/** @brief poner un pin configurado con funcion alternativa en push-pull o
 * opendrain
 *  @param	Puerto del pin que se quiere congurar
 *  @param 	Número de pin a configurar
 *  @param	Modo. USAR DEFINES ALTERNATE_PUSHPULL y ALTERNATE_OPENDRAIN
 */
void GPIO_setAltMode(uint8_t port, uint8_t pin, uint8_t mode) {
    //---reset bits to be set
    // pongo en 0 los bits de crl.cnf. Está configurado como analog
    if (pin > 7)
        GPIO[port].CRH &= ~(0x03 << ((pin - 8) * 4 + CNF_OFFSET));
    else
        GPIO[port].CRL &= ~(0x03 << (pin * 4 + CNF_OFFSET));

    //---set bits
    if (pin > 7)
        GPIO[port].CRH |= (mode << ((pin - 8) * 4 + CNF_OFFSET));
    else
        GPIO[port].CRL |= (mode << (pin * 4 + CNF_OFFSET));
}

/*!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!*/
/*!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!*/
/* Para setear o resetear un pin se usa el registro de atomic set. Cada pin
 * tiene asociados 2 bits. Uno en los primeros 16 bits del registro y otro en
 * los segundos 16 biuts. El primero se usa para setear y el segundo para
 * resetear Ej para pin 0 bit 0  -> set bit 16 -> clr
 *
 *
 * Cuando un pin está configurado como input, el estado del pin, setá guardado
 * en el Input data register (IDR). Hay un bit por pin. Los 16 bits mas
 * significativos son reservados
 *
 * Cuando un pin está configurado como output, el estado del pin está guardado
 * en el Output Data register (ODR)
 */
/*!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!*/
/*!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!*/

/** @brief 	setea un pin como entrada o salida
 *  @param	Puerto del pin que se quiere congurar
 *  @param 	Número de pin a configurar
 *  @param	Modo. USAR DEFINES HIGH y LOW
 */
void GPIO_setPin(uint8_t port, uint8_t pin, uint8_t val) {
    if (val == HIGH)
        GPIO[port].BSRR |= (1 << pin);
    else if (val == LOW)
        GPIO[port].BRR |= (1 << pin);

}

/** @brief devuelve el estado del pin Cuando está configurado como input
 *  @param	Puerto del pin que se quiere congurar
 *  @param 	Número de pin a configurar
 *  @return estado del pin. DEFINES HIGH y LOW
 */
uint8_t GPIO_getPin(uint8_t port, uint8_t pin) {
    return ((GPIO[port].IDR >> pin) & 0x01);
}

/** @brief devuelve el estado del pin Cuando está configurado como output
 *  @param	Puerto del pin que se quiere congurar
 *  @param 	Número de pin a configurar
 *  @return estado del pin. DEFINES HIGH y LOW
 */
uint8_t GPIO_getStatus(uint8_t port, uint8_t pin) {
    return ((GPIO[port].ODR >> pin) & 0x01);
}

#ifdef __cplusplus
}
#endif
