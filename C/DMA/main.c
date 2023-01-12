#include <stdio.h>
#include <iocslib.h>
#include <stdint.h>

#include "Common.h"
#include "DMA.h"

void main()
{  
  puts("A : DMAMOVE");
  puts("B : DMAMOV_A");
  puts("C : DMAMOV_L");
  puts("ESC : EXIT");

  while(1) {
    if(ESC_ON) { break; }
    
    #pragma region DMAMOVE
    if(A_ON) {
     if(DMA_MODE_NONE == DMAMODE()) {
        uint8_t Src[] = { 0xde, 0xad, 0xbe, 0xef };
        uint8_t Dst[] = { 0x00, 0x00, 0x00, 0x00 };

        if(SHIFT_ON){
          //!< Reverse
          puts("[ DMA_MOVE (R) ]");
        
          printf("\t0x");
          for(int i = 0;i < COUNTOF(Src);++i) { printf("%02x", Src[i]); }

          DMAMOVE(Src, Dst, DMA_MODE_R(DMA_INC, DMA_INC), sizeof(Dst));
        
          printf(" -> 0x");        
          for(int i = 0;i < COUNTOF(Src);++i) { printf("%02x", Src[i]); }
          puts("");
        } else {
          puts("[ DMA_MOVE ]");
        
          printf("\t0x");
          for(int i = 0;i < COUNTOF(Dst);++i) { printf("%02x", Dst[i]); }

          DMAMOVE(Src, Dst, DMA_MODE(DMA_INC, DMA_INC), sizeof(Dst));
        
          printf(" -> 0x");        
          for(int i = 0;i < COUNTOF(Dst);++i) { printf("%02x", Dst[i]); }
          puts("");
        }
      }
    } 
    #pragma endregion

    #pragma region DMAMOV_A
    if(B_ON) {
      if(DMA_MODE_NONE == DMAMODE()) {
        const uint8_t Src[] = { 0xde, 0xaa, 0xad, 0xbb, 0xbe, 0xcc, 0xef };
        struct CHAIN SrcChain[] = {
          { .adr = (int)&Src[0], .len = sizeof(Src[0]) },
          { .adr = (int)&Src[2], .len = sizeof(Src[0]) },
          { .adr = (int)&Src[4], .len = sizeof(Src[0]) },
          { .adr = (int)&Src[6], .len = sizeof(Src[0]) },
        };
        uint8_t Dst[] = { 0x00, 0x00, 0x00, 0x00 };

        if(SHIFT_ON){
          //!< Reverse
          puts("[ DMA_MOV_A (R) ]");

          printf("\t0x");
          for(int i = 0;i < COUNTOF(Src);++i) { printf("%02x", Src[i]); }

          DMAMOV_A(SrcChain, Dst, DMA_MODE_R(DMA_INC, DMA_INC), COUNTOF(SrcChain));
        
          printf(" -> 0x");
          for(int i = 0;i < COUNTOF(Src);++i) { printf("%02x", Src[i]); }
          puts("");
        }
        else {
          puts("[ DMA_MOV_A ]");

          printf("\t0x");
          for(int i = 0;i < COUNTOF(Dst);++i) { printf("%02x", Dst[i]); }

          DMAMOV_A(SrcChain, Dst, DMA_MODE(DMA_INC, DMA_INC), COUNTOF(SrcChain));
        
          printf(" -> 0x");
          for(int i = 0;i < COUNTOF(Dst);++i) { printf("%02x", Dst[i]); }
          puts("");
        }
      }
    }
    #pragma endregion

    #pragma region DMAMOV_L
    if(C_ON) {
      if(DMA_MODE_NONE == DMAMODE()) {
        const uint8_t Src[] = { 0xde, 0xaa, 0xad, 0xbb, 0xbe, 0xcc, 0xef };
        struct CHAIN2 SrcChain3 = { .adr = (int)&Src[6], .len = sizeof(Src[0]), .next = NULL };
        struct CHAIN2 SrcChain2 = { .adr = (int)&Src[4], .len = sizeof(Src[0]), .next = &SrcChain3};
        struct CHAIN2 SrcChain1 = { .adr = (int)&Src[2], .len = sizeof(Src[0]), .next = &SrcChain2 };
        struct CHAIN2 SrcChain0 = { .adr = (int)&Src[0], .len = sizeof(Src[0]), .next = &SrcChain1 };
        uint8_t Dst[] = { 0x00, 0x00, 0x00, 0x00 };

        if(SHIFT_ON){
          //!< Reverse
          puts("[ DMA_MOV_L (R) ]");

          printf("\t0x");
          for(int i = 0;i < COUNTOF(Src);++i) { printf("%02x", Src[i]); }

          DMAMOV_L(&SrcChain0, Dst, DMA_MODE_R(DMA_INC, DMA_INC));
        
          printf(" -> 0x");
          for(int i = 0;i < COUNTOF(Src);++i) { printf("%02x", Src[i]); }
          puts("");
        }
        else {
          puts("[ DMA_MOV_L ]");

          printf("\t0x");
          for(int i = 0;i < COUNTOF(Dst);++i) { printf("%02x", Dst[i]); }

          DMAMOV_L(&SrcChain0, Dst, DMA_MODE(DMA_INC, DMA_INC));
        
          printf(" -> 0x");
          for(int i = 0;i < COUNTOF(Dst);++i) { printf("%02x", Dst[i]); }
          puts("");
        }
      }
    }
    #pragma endregion

  }
}

