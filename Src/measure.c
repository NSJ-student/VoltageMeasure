#include "measure.h"
#include "arm_math.h"

arm_cfft_radix4_instance_f32 S;
// arm_rfft_fast_instance_f32 S;

/* FFT settings */
#define SAMPLES					512 			/* 256 real party and 256 imaginary parts */
#define FFT_SIZE				SAMPLES / 2		/* FFT size is always the same size as we have samples, so 256 in our case */

#define FFT_BAR_MAX_HEIGHT		120 			/* 120 px on the LCD */
#define GROUP_STEP 50

float Input_test[SAMPLES];
float Input_in[SAMPLES];
float Output_test[FFT_SIZE];

float Measure_Mean(I16 * data, int size, int base, float graph_alpha)
{
	int total_cnt;
	int count = 0;
	float mean = *(data);
	float result;
	
	
	for(total_cnt=1; total_cnt<size; total_cnt++)
	{
		mean += *(data+total_cnt);
		count++;
		
		if(count == GROUP_STEP-1)
		{
			count = 0;
			mean = mean/GROUP_STEP;
		}
	}
	
	mean = mean / (count+1);
	
	result = base - mean;
	result = result / graph_alpha;
	
	return result;
}

void Init_FFT(void)
{
	int i;
	/* Initialize the CFFT/CIFFT module, intFlag = 0, doBitReverse = 1 */
	arm_cfft_radix4_init_f32(&S, FFT_SIZE, 0, 1);
	for(i=0; i<512; i++)
	{
		Input_test[i] = (float)0;
		Input_in[i] = 0;
	}
	//arm_rfft_fast_init_f32(&S, FFT_SIZE);
}

unsigned int Measure_FFT(I16 * Input, I16 * Output, int size)
{
	float maxValue;				/* Max FFT value is stored here */
	unsigned int maxIndex;				/* Index in Output array where max value is */
	int i;
	
	for(i=0; i<256; i++)
		Input_in[i] = Input_test[i];
	for(; i<512; i++)
		Input_in[i] = 0;
	
	/* Process the data through the CFFT/CIFFT module */
	arm_cfft_radix4_f32(&S, Input_in);
	//arm_rfft_fast_f32(&S, Input_in, Output_test, 0);
	
	/* Process the data through the Complex Magniture Module for calculating the magnitude at each bin */
	arm_cmplx_mag_f32(Input_in, Output_test, size);
	Output_test[0] = 0;
	Output_test[1] = 0;
	Output_test[255] = 0;
	Output_test[254] = 0;
	/* Calculates maxValue and returns corresponding value */
	arm_max_f32(Output_test, FFT_SIZE, &maxValue, &maxIndex);

	for(i=0; i<256; i++)
		Output[i] = (I16)Output_test[i];
	
	return maxIndex;
}

float Measure_Freq(I16 * data, int size, int base, float graph_alpha)
{
	int total_cnt;
	int count = 0;
	float mean = *(data);
	float result;
	
	
	for(total_cnt=1; total_cnt<size; total_cnt++)
	{
		mean += *(data+total_cnt);
		count++;
		
		if(count == GROUP_STEP-1)
		{
			count = 0;
			mean = mean/GROUP_STEP;
		}
	}
	
	mean = mean / (count+1);
	
	result = base - mean;
	result = result / graph_alpha;
	
	return result;
}
