//standard libraries
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <conio.h>
#include <opencv\cv.h>
#include <opencv\cxcore.h>
#include <stdlib.h>


//custom includes
#include "dataEntry.h"
#include "dataReader.h"
#include "neuralNetwork.h"

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

//use standard namespace
using namespace std;

void main()
{	
	IplImage * img;
	IplImage * gray;
	IplImage * histogram;

	int height,width,step,channels,k,i_max;

	int * hist;
	uchar * data;
	uchar * * gray_arr;
	uchar * * histo_arr;
	img = cvLoadImage("img10110008_1.jpg");
	height = img->height;
	width = img->width;
	step = img->widthStep;
	channels = img->nChannels;
	data = (uchar *)img->imageData;
	hist = (int *)calloc(256,sizeof(int));
	histo_arr = (uchar * * )malloc(sizeof(uchar * )*(height + 1));
	gray_arr = (uchar * * )malloc(sizeof(uchar * )*(height + 1));

	for (int i=0; i<height; i++){
		histo_arr[i]=(uchar *)malloc(sizeof(uchar)*(width + 1));
		gray_arr[i] = (uchar *)malloc(sizeof(uchar)*(width +1));

		for (int j = 0; j < width; j++)
		{
			gray_arr[i][j] = (0.11 * data[i*step + j*channels] + 0.56*data[i*step + j*channels +1] + 0.33*data[i*step + j*channels +2]);
			histo_arr[i][j] = 0;
		}
	}

	FILE * pFile;
	pFile = fopen("Recognisi.txt","w");

	int peubah;
	for(int i=0;i<height;i++){
		int jml_brs=1;
		for (int j = 0; j < width; j++)
		{
				if (gray_arr[i][j] <= 15)
				{
					peubah = 0;
				}else if (gray_arr[i][j] <= 30)
				{
					peubah = 1;
				}else if (gray_arr[i][j] <= 45)
				{
					peubah = 2;
				}else if (gray_arr[i][j] <= 60)
				{
					peubah = 3;
				}else if (gray_arr[i][j] <= 75)
				{
					peubah = 4;
				}else if (gray_arr[i][j] <= 90)
				{
					peubah = 5;
				}else if (gray_arr[i][j] <= 105)
				{
					peubah = 6;
				}else if (gray_arr[i][j] <= 120)
				{
					peubah = 7;
				}else if (gray_arr[i][j] <= 135)
				{
					peubah = 8;
				}else if (gray_arr[i][j] <= 150)
				{
					peubah = 9;
				}else if (gray_arr[i][j] <= 165)
				{
					peubah = 10;
				}else if (gray_arr[i][j] <= 180)
				{
					peubah = 11;
				}else if (gray_arr[i][j] <= 195)
				{
					peubah = 12;
				}else if (gray_arr[i][j] <= 210)
				{
					peubah = 13;
				}else if (gray_arr[i][j] <= 225)
				{
					peubah = 14;
				}else
				{
					peubah = 15;
				}

			if (jml_brs <= 16)
			{
				k=gray_arr[i][j];
				fprintf (pFile, "%d,",peubah);
				hist[k]++;
				jml_brs++;
			}else if (jml_brs = 17)
			{
				k=gray_arr[i][j];
				fprintf (pFile, "%d\n",peubah);
				hist[k]++;
				jml_brs = 1;
			}
		}
		fprintf(pFile, "\n");
	}
	fclose(pFile);
	

	//create data set reader
	dataReader d;

	//load data file
	d.loadDataFile("Recognition.txt",16,1);
	d.setCreationApproach( STATIC );

	//create neural network
	neuralNetwork nn(16, 8, 1); //Input , Hidden, Output
	nn.enableLogging("trainingResults.csv");
	nn.setLearningParameters(0.01, 0.8);
	nn.setDesiredAccuracy(100);
	nn.setMaxEpochs(100);
	
	
	//dataset
	dataSet* dset;	


	for ( int i=0; i < d.nDataSets(); i++ )
	{
		dset = d.getDataSet();	
		nn.trainNetwork( dset->trainingSet, dset->generalizationSet, dset->validationSet );
	}	
	
	cout << "-- END OF PROGRAM --" << endl;
	char c; cin >> c;
}
