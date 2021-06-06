/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "2016124087",           /* 학번 */

    "Kim_HyeonYong",     /* First member full name */
    "gusdyd1432@kau.kr",  /* First member email address */

    "",                   /* Second member full name (leave blank if none) */
    ""                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */

char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j, k;

    for (i = 0; i < dim; i += 32) { //Loop Unrolling
        for (j = 0; j < dim; j++) {
	    for (k = 0; k < 32; k++) {
		//k는 Loop Unrolling시 발생하는 i 간격의 계산 반복 (32일 때 최대 효율)
		//dst i,j를 바꾸고, i를 N-1-i로 변경
		dst[RIDX(dim-1-j, i+k, dim)] = src[RIDX(i+k, j, dim)];
	    }
        }
    }
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);    // 처음에는 반드시 naive_rotate를 등록 (기준이 됨)
    add_rotate_function(&rotate, rotate_descr);    // rotate함수의 성능이 점수에 반영됨.
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst)
{
    int i, j, tmp, tmpi;

    /*코너 처리 */
    //왼쪽 위(0,0)
    dst[0].red = (src[0].red + src[1].red + src[dim].red + src[dim + 1].red) >> 2;
    dst[0].blue = (src[0].blue + src[1].blue + src[dim].blue + src[dim + 1].blue) >> 2;
    dst[0].green = (src[0].green + src[1].green + src[dim].green + src[dim + 1].green) >> 2;

    //오른쪽 위(0,N)
    i = dim*2-1;
    dst[dim - 1].red = (src[dim - 1].red + src[dim - 2].red + src[i-1].red + src[i].red) >> 2;
    dst[dim - 1].blue = (src[dim - 1].blue + src[dim - 2].blue + src[i-1].blue + src[i].blue) >> 2;
    dst[dim - 1].green = (src[dim - 1].green + src[dim - 2].green + src[i-1].green + src[i].green) >> 2;

    //왼쪽 아래(N,0)
    j = dim * (dim - 1);
    i = dim * (dim - 2);
    dst[j].red = (src[j].red + src[j + 1].red + src[i].red + src[i + 1].red) >> 2;
    dst[j].blue = (src[j].blue + src[j + 1].blue + src[i].blue + src[i + 1].blue) >> 2;
    dst[j].green = (src[j].green + src[j + 1].green + src[i].green + src[i + 1].green) >> 2;  

    //오른쪽 아래(N,N)
    j = dim * dim -1;
    i = dim * (dim - 1) - 1;
    dst[j].red = (src[j - 1].red + src[j].red + src[i - 1].red + src[i].red) >> 2;
    dst[j].blue = (src[j - 1].blue + src[j].blue + src[i - 1].blue + src[i].blue) >> 2;
    dst[j].green = (src[j - 1].green + src[j].green + src[i - 1].green + src[i].green) >> 2;

    /*사이드라인 처리*/
    //위쪽 줄(0,1 ~ 0,N-1)
    for (j = 1; j < dim - 1; j++) 
    {
        dst[j].red = (src[j].red + src[j - 1].red + src[j + 1].red + 
                      src[j + dim].red + src[j + 1 + dim].red + src[j - 1 + dim].red) / 6;
        dst[j].blue = (src[j].blue + src[j - 1].blue + src[j + 1].blue + 
                       src[j + dim].blue + src[j + 1 + dim].blue + src[j - 1 + dim].blue) / 6;
        dst[j].green = (src[j].green + src[j - 1].green + src[j + 1].green + 
                        src[j + dim].green + src[j + 1 + dim].green + src[j - 1 + dim].green) / 6;
    }

    //아래 쪽 줄 (N,1 ~ N,N-1)
    for (j = dim * (dim - 1) + 1; j < dim * dim - 1; j++) 
    {
        dst[j].red = (src[j].red + src[j - 1].red + src[j + 1].red + 
                      src[j - dim].red + src[j + 1 - dim].red + src[j - 1 - dim].red) / 6;
        dst[j].blue = (src[j].blue + src[j - 1].blue + src[j + 1].blue + 
                       src[j - dim].blue + src[j + 1 - dim].blue + src[j - 1 - dim].blue) / 6;
        dst[j].green = (src[j].green + src[j - 1].green + src[j + 1].green + 
                        src[j - dim].green + src[j + 1 - dim].green + src[j - 1 - dim].green) / 6;
    }

    //왼쪽 줄 (1,0 ~ N-1,0)
    for (j = dim; j < dim * (dim - 1); j += dim) 
    {
        dst[j].red = (src[j].red + src[j - dim].red + src[j + 1].red + 
                      src[j + dim].red + src[j + 1 + dim].red + src[j - dim + 1].red) / 6;
        dst[j].blue = (src[j].blue + src[j - dim].blue + src[j + 1].blue + 
                       src[j + dim].blue + src[j + 1 + dim].blue + src[j - dim + 1].blue) / 6;
        dst[j].green = (src[j].green + src[j - dim].green + src[j + 1].green + 
                        src[j + dim].green + src[j + 1 + dim].green + src[j - dim + 1].green) / 6;
    }

    //오른쪽 줄 (1,N ~ N-1,N)
    for (j = dim + dim - 1; j < dim * dim - 1; j += dim) 
    {
        dst[j].red = (src[j].red + src[j - 1].red + src[j - dim].red + 
                      src[j + dim].red + src[j - dim - 1].red + src[j - 1 + dim].red) / 6;
        dst[j].blue = (src[j].blue + src[j - 1].blue + src[j - dim].blue + 
                       src[j + dim].blue + src[j - dim - 1].blue + src[j - 1 + dim].blue) / 6;
        dst[j].green = (src[j].green + src[j - 1].green + src[j - dim].green + 
                        src[j + dim].green + src[j - dim - 1].green + src[j - 1 + dim].green) / 6;
    }

    /* 나머지 경우 (중앙 픽셀 처리) (1,1 ~ N-1,N-1) */
    tmpi = dim;
    for (i = 1; i < dim - 1; i++)
    {
        for (j = 1; j < dim - 1; j++)
        {
		tmp = tmpi + j; //해당 행의 열
		dst[tmp].red = (src[tmp].red + src[tmp - 1].red + src[tmp + 1].red + src[tmp - dim].red + src[tmp - dim - 1].red + 
					src[tmp - dim + 1].red + src[tmp + dim].red + src[tmp + dim + 1].red + src[tmp + dim - 1].red) / 9;
		dst[tmp].green = (src[tmp].green + src[tmp - 1].green + src[tmp + 1].green + src[tmp - dim].green + src[tmp - dim - 1].green + 
					src[tmp - dim + 1].green + src[tmp + dim].green + src[tmp + dim + 1].green + src[tmp + dim - 1].green) / 9;
		dst[tmp].blue = (src[tmp].blue + src[tmp - 1].blue + src[tmp + 1].blue + src[tmp - dim].blue + src[tmp - dim - 1].blue + 
					src[tmp - dim + 1].blue + src[tmp + dim].blue + src[tmp + dim + 1].blue + src[tmp + dim - 1].blue) / 9;
        }
        tmpi += dim; // 다음 행
    }
}



/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&naive_smooth, naive_smooth_descr);// 처음에는 반드시 naive_rotate를 등록 (기준이 됨)
    add_smooth_function(&smooth, smooth_descr); // smooth 함수의 성능이점수에 반영됨
    /* ... Register additional test functions here */
}
