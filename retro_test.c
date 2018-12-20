#include <stdio.h>
//#include <unistd.h>
//#include <math.h>
//#include <Windows.h>
#include "led_tasks.h"

float hor_line_1;
float hor_line_2;
float hor_line_3;
float h = 20;				// Vysota vzglyada na polosku
float gamma_cos = 0.5f;		// Ugol naklona polosok
int a = 3;					// Shirina poloski

//#define LED_LENGTH 448
//#define LED_X 56
//#define LED_Y 24

rgb_c back_color;
rgb_c one_frame_pix[LED_X*LED_Y];


void calc_line(float d);
rgb_c clamp_max_intens(rgb_c pixel, int intens);

/*
int main()
{
	hor_line_1 = 20;
	hor_line_2 = -10;
	hor_line_3 = -40;
	back_color.r = 0x04;
	back_color.g = 0x00;
	back_color.b = 0x08;
	printf("RETRO: begin\r\n");
	while(1)
	{
		Sleep(100); //Sleep(50000); Sleep(50000); Sleep(50000);
		
		if(hor_line_1 > 20)
		{
			calc_line(hor_line_1);
		}
		if(hor_line_2 > 20)
		{
			calc_line(hor_line_2);
		}
		if(hor_line_3 > 20)
		{
			calc_line(hor_line_3);
		}
		
		hor_line_1+=0.1f;
		hor_line_2+=0.1f;
		hor_line_3+=0.1f;
		if(hor_line_1 >= 120)
			hor_line_1 = 20;
		if(hor_line_2 >= 120)
			hor_line_2 = 20;
		if(hor_line_3 >= 120)
			hor_line_3 = 20;
	}
}
*/

void effect_retrowave_start() 
{
	led_clear();
	hor_line_1 = 20;
	hor_line_2 = -10;
	hor_line_3 = -40;
	back_color.r = 0x04;
	back_color.g = 0x00;
	back_color.b = 0x08;
	for(int x = 0; x < LED_X; x++) {
		for(int y = 0; y < LED_Y; y++) {
			one_frame_pix[y*LED_X+x] = back_color;
			led_set_pixel_rgb(x, y, back_color.r, back_color.g, back_color.b);
        }
	}
	led_show();
	usleep(1000);
}

void effect_retrowave_end() 
{
	led_clear();
	usleep(1000);
}

void effect_retrowave_process() 
{
	//while(1)
	//{
		//Sleep(500);
		
		
		if(hor_line_1 > 20)
		{
			calc_line(hor_line_1);
		}
		if(hor_line_2 > 20)
		{
			calc_line(hor_line_2);
		}
		if(hor_line_3 > 20)
		{
			calc_line(hor_line_3);
		}
		
		hor_line_1+=0.1f;
		hor_line_2+=0.1f;
		hor_line_3+=0.1f;
		if(hor_line_1 >= 120)
			hor_line_1 = 20;
		if(hor_line_2 >= 120)
			hor_line_2 = 20;
		if(hor_line_3 >= 120)
			hor_line_3 = 20;
		for(int x = 0; x < LED_X; x++) 
		{
			for(int y = 0; y < LED_Y; y++) {
				led_set_pixel_rgb(x, y, one_frame_pix[y*LED_X+x].r, one_frame_pix[y*LED_X+x].g, one_frame_pix[y*LED_X+x].b);
			}
		}
		led_show();
		usleep(10000);
	//}
}

void calc_line(float d)
{
	//  . (tochka vzlyada)
	//    \-
	//  (e)\ \ 
	//      \/
	//     /
	//    /
	//  .   (tochka nachala dvizheniya poloski)
	//
	//
	// d - dlina puti poloski ot nachala
	// 1 pixel = 4 gradusa
	float rad2grad = 57.29;
	float c = sqrt(h*h + d*d - 2*h*d*gamma_cos);						// lenght ot vzglyada do nizhney granitsy poloski
	float e = sqrt(h*h + (d+a)*(d+a) - 2*h*(d+a)*gamma_cos); 			// lenght ot vzglyada do verhney granitsy poloski
	float beta = acos( (-d*d + h*h + c*c) / (2*h*c) ) * rad2grad;		// angle ot vzglyada do nizhney granitsy
	float mu = acos( (-(d+a)*(d+a) + h*h + e*e) / (2*h*e) ) * rad2grad;	// angle vzlyada do verhney granitsy
	float dif = mu - beta;												// vidimaya width poloski
	int central_pix;
	
	if(dif<4)
		dif = 4;
	
	float lower = (beta-48)/4;											// perevod ugla into pixels
	int lower_pix = floor(lower);
	if( (lower_pix >= 0) && (lower_pix < 24) )
	{
		int intensity = 255*(1-(lower-lower_pix));
		rgb_c new_color = clamp_max_intens(back_color, intensity);
		for(int x=0; x<LED_X; x++)
		{
			one_frame_pix[lower_pix*LED_X+x] = new_color;
		}
		printf("RETRO: Lower pixel, lower=%f, pix=%i, intens=%i\r\n",lower,lower_pix,intensity);
	}
	
	float upper = (beta + dif - 48)/4;
	int upper_pix = floor(upper);
	//printf("RETRO: Lower=%f, pix=%i, Upper=%f, pix=%i\r\n", lower, lower_pix, upper, upper_pix);
	if( (upper_pix >= 0) && (upper_pix < 24) && (upper_pix > lower_pix))
	{
		int intensity = 255*(upper-upper_pix);
		rgb_c new_color = clamp_max_intens(back_color, intensity);
		for(int x=0; x<LED_X; x++)
		{
			one_frame_pix[upper_pix*LED_X+x] = new_color;
		}
		printf("RETRO: Upper pixel, upper=%f, pix=%i, intens=%i\r\n",upper,upper_pix,intensity);
	}
	
	if( (upper_pix - lower_pix) > 1)
	{
		for(int i=lower_pix+1; i<=upper_pix-1; i++)
		{
			int intensity = 255;
			rgb_c new_color = clamp_max_intens(back_color, intensity);
			printf("RETRO: i=%i, color=%f\n",i,new_color.r);
			if (i>=0 && i<24)
			{
				for(int x=0; x<LED_X; x++)
				{
					one_frame_pix[i*LED_X+x] = new_color;
				}
			}
		}
	}
}

rgb_c clamp_max_intens(rgb_c pixel, int intens) 
{
	rgb_c result_color;
	result_color = pixel;
	result_color.r = result_color.r + intens*0.85;
	if(result_color.r > 216)  result_color.r = 216;
	result_color.g = result_color.g + intens*0.7;
	if(result_color.g > 179) result_color.g = 178;
	result_color.b = result_color.b + intens;
	if(result_color.b > 255) result_color.b = 255;
	return result_color;
}
