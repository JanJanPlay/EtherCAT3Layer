/*
2020.10.13
Author:Jan
*/

#include "el9800hw.h"
#include "esc_fsmc.h"
#include "main.h"

NOR_HandleTypeDef hnor1;

/* FSMC initialization function */
void MX_FSMC_Init(void)
{

	/* USER CODE BEGIN FSMC_Init 0 */

	/* USER CODE END FSMC_Init 0 */

	FSMC_NORSRAM_TimingTypeDef Timing = {0};

	/* USER CODE BEGIN FSMC_Init 1 */

	/* USER CODE END FSMC_Init 1 */

	/** Perform the NOR1 memory initialization sequence
	*/
	hnor1.Instance = FSMC_NORSRAM_DEVICE;
	hnor1.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
	/* hnor1.Init */
	hnor1.Init.NSBank = FSMC_NORSRAM_BANK4;
	hnor1.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_ENABLE;	//FSMC_DATA_ADDRESS_MUX_DISABLE
	hnor1.Init.MemoryType = FSMC_MEMORY_TYPE_NOR;
	hnor1.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
	hnor1.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
	hnor1.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
	hnor1.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
	hnor1.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
	hnor1.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
	hnor1.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
	hnor1.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
	hnor1.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
	hnor1.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
	hnor1.Init.PageSize = FSMC_PAGE_SIZE_NONE;
	/* Timing */
	Timing.AddressSetupTime = 15;
	Timing.AddressHoldTime = 15;
	Timing.DataSetupTime = 15;
	Timing.BusTurnAroundDuration = 15;
	Timing.CLKDivision = 0;	//16
	Timing.DataLatency = 0;	//17
	Timing.AccessMode = FSMC_ACCESS_MODE_A;
	/* ExtTiming */

	if (HAL_NOR_Init(&hnor1, &Timing, NULL) != HAL_OK)
	{
		Error_Handler( );
	}

	/* USER CODE BEGIN FSMC_Init 2 */

	/* USER CODE END FSMC_Init 2 */
}

UINT32 PMPReadDWord (UINT16 Address)
{
	UINT32_VAL res;

	//res.Val = (UINT32)(*(volatile UINT32 *)(Bank1_SRAM4_ADDR+(Address)));
	res.w[0]= *(__IO uint16_t*) (NOR_MEMORY_ADRESS4 + Address);
	/* Increment the address*/
	Address += 2;
	res.w[1]= *(__IO uint16_t*) (NOR_MEMORY_ADRESS4 + Address);

	return res.Val;
}

void PMPWriteDWord (UINT16 Address, UINT32 Val)
{
	UINT32_VAL res;
	res.Val=Val;

	//*(uint32_t *) (Bank1_SRAM4_ADDR + Address) = Val;
	*(uint16_t *) (NOR_MEMORY_ADRESS4 + Address) = res.w[0];

	/* Increment the address*/
	Address += 2;
	*(uint16_t *) (NOR_MEMORY_ADRESS4 + Address) = res.w[1];
}


void PMPReadRegUsingCSR(UINT8 *ReadBuffer, UINT16 Address, UINT8 Count)
{
	UINT32_VAL param32_1 = {0};
	UINT8 i = 0;
	UINT16_VAL wAddr;
	wAddr.Val = Address;

	param32_1.v[0] = wAddr.byte.LB;
	param32_1.v[1] = wAddr.byte.HB;
	param32_1.v[2] = Count;
	param32_1.v[3] = ESC_READ_BYTE;

    PMPWriteDWord (CSR_CMD_REG, param32_1.Val);

    do
    {
        param32_1.Val = PMPReadDWord (ESC_CSR_CMD_REG);
    }while(param32_1.v[3] & ESC_CSR_BUSY);

    param32_1.Val = PMPReadDWord (ESC_CSR_DATA_REG);
    
     for(i=0;i<Count;i++)
         ReadBuffer[i] = param32_1.v[i];
   
    return;
}

void PMPWriteRegUsingCSR( UINT8 *WriteBuffer, UINT16 Address, UINT8 Count)
{
	UINT32_VAL param32_1 = {0};
	UINT16_VAL wAddr;
	UINT8 i = 0;
		
    for(i=0;i<Count;i++)
         param32_1.v[i] = WriteBuffer[i];
		
	PMPWriteDWord (ESC_CSR_DATA_REG, param32_1.Val);

	wAddr.Val = Address;

    param32_1.v[0] = wAddr.byte.LB;
    param32_1.v[1] = wAddr.byte.HB;
    param32_1.v[2] = Count;
    param32_1.v[3] = ESC_WRITE_BYTE;

    PMPWriteDWord (0x304, param32_1.Val);
	do
	{
		param32_1.Val = PMPReadDWord (0x304);

	}while(param32_1.v[3] & ESC_CSR_BUSY);

    return;
}

void PMPReadPDRamRegister(UINT8 *ReadBuffer, UINT16 Address, UINT16 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0,nlength, nBytePosition;
    UINT8 nReadSpaceAvblCount;
//    UINT16 RefAddr = Address;

    /*Reset/Abort any previous commands.*/
    param32_1.Val = PRAM_RW_ABORT_MASK;                                                 

	PMPWriteDWord (PRAM_READ_CMD_REG, param32_1.Val);

	/*The host should not modify this field unless the PRAM Read Busy
	(PRAM_READ_BUSY) bit is a 0.*/
	do
	{
		param32_1.Val = PMPReadDWord (PRAM_READ_CMD_REG);

	}while((param32_1.v[3] & PRAM_RW_BUSY_8B));

    /*Write address and length in the EtherCAT Process RAM Read Address and
     * Length Register (ECAT_PRAM_RD_ADDR_LEN)*/
    param32_1.w[0] = Address;
    param32_1.w[1] = Count;

	PMPWriteDWord (PRAM_READ_ADDR_LEN_REG, param32_1.Val);

	param32_1.Val = PMPReadDWord (HBI_INDEXED_DATA2_REG );
	/*Set PRAM Read Busy (PRAM_READ_BUSY) bit(-EtherCAT Process RAM Read Command Register)
	 *  to start read operatrion*/

	param32_1.Val = PRAM_RW_BUSY_32B; /*TODO:replace with #defines*/

	PMPWriteDWord (PRAM_READ_CMD_REG, param32_1.Val);

	/*Read PRAM Read Data Available (PRAM_READ_AVAIL) bit is set*/
	do
	{
		param32_1.Val = PMPReadDWord (PRAM_READ_CMD_REG);
	}while(!(param32_1.v[0] & IS_PRAM_SPACE_AVBL_MASK));

    nReadSpaceAvblCount = param32_1.v[1] & PRAM_SPACE_AVBL_COUNT_MASK;

    /*Fifo registers are aliased address. In indexed it will read indexed data reg 0x04, but it will point to reg 0
     In other modes read 0x04 FIFO register since all registers are aliased*/

	param32_1.Val = PMPReadDWord (PRAM_READ_FIFO_REG);

	nReadSpaceAvblCount--;
	nBytePosition = (Address & 0x03);
	nlength = (4-nBytePosition) > Count ? Count:(4-nBytePosition);
	memcpy(ReadBuffer+i ,&param32_1.v[nBytePosition],nlength);
	Count-=nlength;
	i+=nlength;

    while(Count && nReadSpaceAvblCount)
    {
		param32_1.Val = PMPReadDWord (PRAM_READ_FIFO_REG);

		nlength = Count > 4 ? 4: Count;
		memcpy((ReadBuffer+i) ,&param32_1,nlength);

        i+=nlength;
        Count-=nlength;
        nReadSpaceAvblCount --;

        if (!nReadSpaceAvblCount)
        { 
			param32_1.Val = PMPReadDWord (PRAM_READ_CMD_REG);

			nReadSpaceAvblCount = param32_1.v[1] & PRAM_SPACE_AVBL_COUNT_MASK;
        }
    }
   
    return;
}
        

void PMPWritePDRamRegister(UINT8 *WriteBuffer, UINT16 Address, UINT16 Count)
{
	UINT32_VAL param32_1 = {0};
	UINT8 i = 0,nlength, nBytePosition,nWrtSpcAvlCount;
//	UINT16 RefAddr = Address;

	/*Reset or Abort any previous commands.*/
	param32_1.Val = PRAM_RW_ABORT_MASK;                                                 /*TODO:replace with #defines*/

	PMPWriteDWord (PRAM_WRITE_CMD_REG, param32_1.Val);
  
	/*Make sure there is no previous write is pending
	(PRAM Write Busy) bit is a 0 */
	do
	{
		param32_1.Val = PMPReadDWord (PRAM_WRITE_CMD_REG);
	}while((param32_1.v[3] & PRAM_RW_BUSY_8B));

	/*Write Address and Length Register (ECAT_PRAM_WR_ADDR_LEN) with the
	starting byte address and length)*/
	param32_1.w[0] = Address;
	param32_1.w[1] = Count;

	PMPWriteDWord (PRAM_WRITE_ADDR_LEN_REG, param32_1.Val);
   
    /*write to the EtherCAT Process RAM Write Command Register (ECAT_PRAM_WR_CMD) with the  PRAM Write Busy
    (PRAM_WRITE_BUSY) bit set*/

    param32_1.Val = PRAM_RW_BUSY_32B; 

	PMPWriteDWord (PRAM_WRITE_CMD_REG, param32_1.Val);


	/*Read PRAM write Data Available (PRAM_READ_AVAIL) bit is set*/
	do
	{
		param32_1.Val = PMPReadDWord (PRAM_WRITE_CMD_REG);
	}while(!(param32_1.v[0] & IS_PRAM_SPACE_AVBL_MASK));

    /*Check write data available count*/
    nWrtSpcAvlCount = param32_1.v[1] & PRAM_SPACE_AVBL_COUNT_MASK;

    /*Write data to Write FIFO) */ 
    /*get the byte lenth for first read*/
    nBytePosition = (Address & 0x03);

    nlength = (4-nBytePosition) > Count ? Count:(4-nBytePosition);

    param32_1.Val = 0;
	memcpy(&param32_1.v[nBytePosition],WriteBuffer+i, nlength);

	PMPWriteDWord (PRAM_WRITE_FIFO_REG,param32_1.Val);

	nWrtSpcAvlCount--;
	Count-=nlength;
	i+=nlength;

    while(nWrtSpcAvlCount && Count)
    {
        nlength = Count > 4 ? 4: Count;
        param32_1.Val = 0;
        memcpy(&param32_1, (WriteBuffer+i), nlength);

		PMPWriteDWord (PRAM_WRITE_FIFO_REG,param32_1.Val);

		i+=nlength;
		Count-=nlength;
		nWrtSpcAvlCount--;

        if (!nWrtSpcAvlCount)
        {
			param32_1.Val = PMPReadDWord (PRAM_WRITE_CMD_REG);

			/*Check write data available count*/
			nWrtSpcAvlCount = param32_1.v[1] & PRAM_SPACE_AVBL_COUNT_MASK;
        }
    }
    return;
}

void PMPReadDRegister(UINT8 *ReadBuffer, UINT16 Address, UINT16 Count)
{
    if (Address >= 0x1000)
    {
         PMPReadPDRamRegister(ReadBuffer, Address,Count);
    }
    else
    {
         PMPReadRegUsingCSR(ReadBuffer, Address,Count);
    }
}

void PMPWriteRegister( UINT8 *WriteBuffer, UINT16 Address, UINT16 Count)
{
   if (Address >= 0x1000)
   {
		PMPWritePDRamRegister(WriteBuffer, Address,Count);
   }
   else
   {
		PMPWriteRegUsingCSR(WriteBuffer, Address,Count);
   }
}
