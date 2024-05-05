# define BASE_PERIFERICO (0X40000000UL)
/* UL significa " Unsigned Long " ( Passo 1) */

# define APB2_PERIFERICO_OFFSET (0X00010000UL) /* Passo 2 */
# define APB2_PERIFERICO_BASE (BASE_PERIFERICO + APB2_PERIFERICO_OFFSET) /* Passo 2 */

# define GPIOB_OFFSET (0X0C00UL) /* Passo 3 */
# define GPIOB_BASE (APB2_PERIFERICO_BASE + GPIOB_OFFSET) /* Passo 3 */

# define RCC_OFFSET (0x00021000UL) /* Passo 4 */
# define RCC_BASE (BASE_PERIFERICO + RCC_OFFSET) /* Passo 4 */

# define RCC_APB2EN_R_OFFSET (0X18UL) /* Passo 5 */
# define RCC_APB2EN_R (*( volatile unsigned int *) (RCC_BASE + RCC_APB2EN_R_OFFSET)) /* Passo 5
 *(*( volatile unsigned int *) comumente usado para acessar e manipular registradores */

# define GPIOBEN (1U<<3) /* Passo 6 */

# define GPIOB_CRH_OFFSET (0x04UL) /* Passo 7 */
# define GPIOB_CRH (*(volatile unsigned int *) (GPIOB_BASE + GPIOB_CRH_OFFSET)) /* Passo 7 */

# define GPIOB_OD_R_OFFSET (0x0CUL) /* Passo 8 */
# define GPIOB_OD_R (*(volatile unsigned int *) (GPIOB_BASE + GPIOB_OD_R_OFFSET)) /* Passo 8 */

#define LED_PIN9 (1U<<9) /* Passo 8 */

int main (void)
{
	/* 1. Habilitar o acesso do sinal de clock do barramento
	 * APB2 ao GPIOB colocando 1 no bit 4 do registrador
	 * utilizando um operador " OU " para mudar apenas o bit 4 para 1. */
	 RCC_APB2EN_R |= GPIOBEN;

	/* 2. Setar o PB9 como pino de saida Passo 7 */
	 GPIOB_CRH |= (1U<<4) ; // Seta o bit 4 para 1
	 GPIOB_CRH &=~(1U<<5) ; // Seta o bit 5 para 0
	 GPIOB_CRH &=~(1U<<6) ; // Seta o bit 6 para 0
	 GPIOB_CRH &=~(1U<<7) ; // Seta o bit 7 para 0

	 while (1)
	{
		 /* 3. Alterna o bit 9 no registrador
		 * GPIOB_OD_R a cada fim da contagem */
		 GPIOB_OD_R ^= LED_PIN9;
		 for ( int i =0; i <100000; i ++) {}
		 /* funciona como um " delay " realizando uma contagem
		*/
	 }
}
