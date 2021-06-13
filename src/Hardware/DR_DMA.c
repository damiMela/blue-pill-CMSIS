#include <Hardware/DR_DMA.h>

/*!-----------INCLUDES PUBLICOS-----------------------------------------------------------------------------*/
DMA_Channel_TypeDef *const DMA_CHN[] = {
    ((DMA_Channel_TypeDef *)DMA1_Channel1_BASE),
    ((DMA_Channel_TypeDef *)DMA1_Channel2_BASE),
    ((DMA_Channel_TypeDef *)DMA1_Channel3_BASE),
    ((DMA_Channel_TypeDef *)DMA1_Channel4_BASE),
    ((DMA_Channel_TypeDef *)DMA1_Channel5_BASE),
    ((DMA_Channel_TypeDef *)DMA1_Channel6_BASE),
    ((DMA_Channel_TypeDef *)DMA1_Channel7_BASE),
};

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/
extern inline void DMA_setPeripheralAddress(uint8_t chn, volatile void *periph) {
    DMA_CHN[chn]->CPAR = (uint32_t)periph;
}

extern inline void DMA_setMemoryAddress(uint8_t chn, volatile void *mem) {
    DMA_CHN[chn]->CMAR = (uint32_t)mem;
}

extern inline void DMA_setDataN(uint8_t chn, uint8_t num) {
    DMA_CHN[chn]->CNDTR = num;
}

extern inline void DMA_enableCircularMode(uint8_t chn) {
    DMA_CHN[chn]->CCR |= DMA_CCR_CIRC;
}

extern inline void DMA_enableIncrementMemoryAddress(uint8_t chn) {
    DMA_CHN[chn]->CCR |= DMA_CCR_MINC;
}

extern inline void DMA_setPeripheralDataSize(uint8_t chn, uint8_t size) {
    DMA_CHN[chn]->CCR |= (size << DMA_CCR_PSIZE_Pos);
}
extern inline void DMA_setMemoryDataSize(uint8_t chn, uint8_t size) {
    DMA_CHN[chn]->CCR |= (size << DMA_CCR_MSIZE_Pos);
}

extern inline void DMA_enable(uint8_t chn) {
    DMA_CHN[chn]->CCR |= DMA_CCR_EN;
}