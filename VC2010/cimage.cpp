// CImage.cpp: implementation of the CImage class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <new.h>
#include "cimage.h"
#include "imgio.h"
#include "macro.h"


/*-----------------------------------------------------------------------------
|  Routine Name: Constructors
|       Purpose:
|         Input: type, width, height
|        Output:
|       Returns:
|
|    Written By: Christian REY
|          Date: 16/05/2001
| Modifications:
|----------------------------------------------------------------------------*/
CImage::CImage(){
	nb_comp=0;
	width=0;
	height=0;
	C[0] = NULL; 	
	C[1] = NULL; 	
	C[2] = NULL; 
}

CImage::CImage(char t, int w, int h){
	type = t;
	width = w;
	height = h;
	 
	if (type == GRAY_IMAGE) nb_comp = 1;
	else nb_comp = 3; 

	for (int i=0;i<nb_comp;i++) {
		C[i] = new short[width*height];
		memset(C[i],0,sizeof(short)*width*height);
	}
}

CImage::CImage(const CImage &anImage){
	type = anImage.type;
	width = anImage.width;
	height = anImage.height;
	nb_comp = anImage.nb_comp;

	for (int i=0;i<nb_comp;i++) {
		if (C[i]!=NULL) delete(C[i]);
      C[i] = new short[width*height];
		memcpy(C[i], anImage.C[i], sizeof(short)*width*height);
	}
}

int CImage::Create(int t, int w, int h){
	type = t;
	width =w;
	height = h;

	if (type == GRAY_IMAGE) nb_comp = 1;
	else nb_comp = 3; 

	for (int i=0;i<nb_comp;i++) {
		if (C[i]!=NULL) delete(C[i]);
      C[i] = new short[width*height];
		if (C[i]==NULL)
			return ERROR;
	}
    
	return SUCCESS;
}

int CImage::Copy(const CImage &anImage){
	type = anImage.type;
	width = anImage.width;
	height = anImage.height;
	nb_comp = anImage.nb_comp;

	for (int i=0;i<nb_comp;i++) {
		if (C[i]!=NULL) delete(C[i]);
      C[i] = new short[width*height];
		memcpy(C[i], anImage.C[i], sizeof(short)*width*height);
	}
 
	return SUCCESS;
}

/*-----------------------------------------------------------------------------
|  Routine Name: Destructor
|       Purpose:
|         Input:
|        Output:
|       Returns:
|
|    Written By: Christian REY
|          Date: 16/05/2001
| Modifications:
|----------------------------------------------------------------------------*/
CImage::~CImage(){
	for (int i=0;i<nb_comp;i++) 
		if (C[i]!=NULL){
			delete(C[i]);
			C[i] = NULL;
		}
}

/*-----------------------------------------------------------------------------
|  Routine Name: ReadPPMFile
|       Purpose: Read a RGB image (binary PPM format)
|         Input: path
|        Output: CImage (this)
|       Returns: statut
|
|    Written By: Christian REY
|          Date: 16/05/2001
| Modifications:
|----------------------------------------------------------------------------*/
int CImage::ReadPPMFile(char *path){
	int err;
	int nb_levels;

	type = RGB_IMAGE;
	nb_comp = 3;
	for (int c=0;c<nb_comp; c++)
		if (C[c]!=NULL) delete(C[c]);
	
	err = ReadPPM(path, &width, &height, &nb_levels, &C[0], &C[1], &C[2]);
	
	if (err==ERROR)
		return ERR_IO_FILE;
	else
		return SUCCESS;
}

/*-----------------------------------------------------------------------------
|  Routine Name: WritePPMFile
|       Purpose: Write a RGB image (binary PPM format)
|         Input: path
|        Output: none
|       Returns: statut
|
|    Written By: Christian REY
|          Date: 16/05/2001
| Modifications: 
|----------------------------------------------------------------------------*/
int CImage::WritePPMFile(char *path){
	int err;

	switch (type) {
		case RGB_IMAGE :
			err = WritePPM(path, width, height, 255, C[0], C[1], C[2]);
			break;
		case GRAY_IMAGE :
			err = WritePPM(path, width, height, 255, C[0], C[0], C[0]);
			break;
		default :
			return ERR_UNKNOWN_IMAGE_TYPE;
	}
	
	if (!err)
		return ERR_IO_FILE;
	else
		return SUCCESS;
}

/*-----------------------------------------------------------------------------
|  Routine Name: ReadPGMFile
|       Purpose: Read a RGB or a Gray image (binary PGM format)
|         Input: path
|        Output: CImage (this)
|       Returns: statut
|
|    Written By: Christian REY
|          Date: 16/05/2001
| Modifications:
|----------------------------------------------------------------------------*/
int CImage::ReadPGMFile(char *path){
	type = GRAY_IMAGE;
	nb_comp = 1;
	
	if (C[0]!=NULL) delete(C[0]);

	ReadPGM(path, &C[0], &width, &height);
	
	if (C[0]==NULL)
		return ERR_IO_FILE;
	
	return SUCCESS;
}

/*-----------------------------------------------------------------------------
|  Routine Name: WritePGMFile
|       Purpose: Write a RGB or a Gray image (binary PGM format)
|         Input: path
|        Output: none
|       Returns: statut
|
|    Written By: Christian REY
|          Date: 16/05/2001
| Modifications: 
|----------------------------------------------------------------------------*/
int CImage::WritePGMFile(char *path){
	if (type!=GRAY_IMAGE)
		return ERROR;
	
	WritePGM(path, C[0], width, height);
	
	return SUCCESS;
}


/*-----------------------------------------------------------------------------
|  Routine Name: BlockMean
|       Purpose: Calcule la valeur moyenne du bloc
|         Input: c, posx, posy, bloc_width, block_height, min, max
|        Output: *value
|       Returns: status
|
|    Written By: Christian REY
|          Date: 29/06/2001
| Modifications:
|----------------------------------------------------------------------------*/
int CImage::BlockMean(short *value, int c, int posx, int posy,
							 int block_width, int block_height){
	int sum = 0;

	if (C[c]==NULL)
		return ERROR;
	if (posx<0 || posy<0 || posx+block_width-1>width
		 ||posy+block_height-1>height)
		return ERROR;
	
	for (int i = 0; i < block_width; i++) {
		for (int j = 0; j < block_height; j++) {
			sum = sum + C[c][posx + posy * width + i + j * block_width];
		}
	}

	(*value) = (short)(sum/(block_width*block_height));

	return SUCCESS;
}


/*-----------------------------------------------------------------------------
|  Routine Name: DrawBadBlock
|       Purpose: Dessine un carre
|         Input: posx, posy, bloc_width, block_height
|        Output: CImage (this)
|       Returns: status
|
|    Written By: Christian REY
|          Date: 29/06/2001
| Modifications:
|----------------------------------------------------------------------------*/
int CImage::DrawBadBlock(int posx, int posy, int block_width, int block_height){
	if (posx<0 || posy<0 || posx+block_width-1>width
		 ||posy+block_height-1>height)
		return ERROR;

	for (int c=0; c<nb_comp; c++) {
		if (C[c]==NULL)
			return ERROR;
		for (int j=0;j<block_height;j++)
			for (int i=0;i<block_width;i++){
				if (i==0 || j==0)
					C[c][i+posx+(j+posy)*width] = 255;
				else if (i==block_width-1 || j==block_height-1)
					C[c][i+posx+(j+posy)*width] = 0;
				else if (i==j || (block_width-1-i)==j) {
					if (c==0)
						C[c][i+posx+(j+posy)*width] = 255;
					else
						C[c][i+posx+(j+posy)*width] = 0;	
				}
				else
					C[c][i+posx+(j+posy)*width] = 240;
			}
	}
	
	return SUCCESS;
}

/*-----------------------------------------------------------------------------
|  Routine Name: DrawFlatBlock
|       Purpose:
|         Input: posx, posy, bloc_width, block_height, gray level
|        Output: CImage (this)
|       Returns: status
|
|    Written By: Christian REY
|          Date: 29/06/2001
| Modifications:
|----------------------------------------------------------------------------*/
int CImage::DrawFlatBlock(int c, int posx, int posy, int block_width,
								  int block_height, short g){
	if (posx<0 || posy<0 || posx+block_width-1>width
		 || posy+block_height-1>height)
		return ERROR;

	if (C[c]==NULL)
		return ERROR;
  
	for (int j=0;j<block_height;j++)
		for (int i=0;i<block_width;i++)
			C[c][i+posx+(j+posy)*width] = g;
	  
	return SUCCESS;
}


/*-----------------------------------------------------------------------------
|  Routine Name: CRCBlock
|       Purpose: Calculate CRC value of a block
|         Input: c, posx, posy, block_width, block_height, *crcTable
|        Output: none
|       Returns: crc
|
|    Written By: Christian REY
|          Date: 02/05/2002
| Modifications:
|----------------------------------------------------------------------------*/
unsigned long CImage::CRCBlock(int c, int posx, int posy, int block_width,
										 int block_height, const unsigned long *crcTable){
	register unsigned long crc;
	int val;

	crc = 0xFFFFFFFF;

	for (int k=0; k<block_width; k++)
		for (int l=0; l<block_height; l++) {
			val = (int)C[c][posx+k + (posy+l)*width];
			SETBIT(val,0,0);
			crc = ((crc>>8) & 0x00FFFFFF) ^ (crcTable[ (crc^val) & 0xFF ]);
		}

	return (crc^0xFFFFFFFF);
}


/*-----------------------------------------------------------------------------
|  Routine Name: InsertNoiseLSB	
|       Purpose: Met les LSB des pixels de l'image a zero 
|         Input: CImage (this)
|        Output: CImage (this)
|       Returns: status
|
|    Written By: Christian REY
|          Date: 25/04/2002
| Modifications:
|----------------------------------------------------------------------------*/
int CImage::InsertNoiseLSB(){
	int noise;
	srand(0);

	for (int c=0; c<nb_comp;c++) {
		if (C[c]==NULL)
			return ERROR;

		noise = rand() % 1;
		for (int n=0; n < width; n++) {
			for (int m=0; m < height; m++) {
				SETBIT(C[c][m*width+n], 0, noise);
			}
		}
	}

	return SUCCESS;
}

/*-----------------------------------------------------------------------------
|  Routine Name: ExtractNoiseLSB	
|       Purpose: 
|         Input: CImage (this)
|        Output: CImage (this)             
|       Returns: status
|
|    Written By: Christian REY
|          Date: 25/04/2002
| Modifications:
|----------------------------------------------------------------------------*/
int CImage::ExtractNoiseLSB(){
	int noise;
	srand(0);

	for (int c=0; c<nb_comp;c++) {
		if (C[c]==NULL)
			return ERROR;	
     
		noise = rand() % 1;
		for (int n=0; n < width; n++) {
			for (int m=0; m < height; m++) {
				if (GETBIT(C[c][m*width+n], 0) == noise) {
					for (int i=0; i < 8; i++) {
						SETBIT(C[c][m * width + n], i, 1);
					}
				}
				else {
					for (int i=0; i < 8; i++) {
						SETBIT(C[c][m * width + n], i, 0);
					}
				}
			}
		}
	}      
  
	return SUCCESS;
}

/*-----------------------------------------------------------------------------
|  Routine Name: InsertCRCLSB	
|       Purpose:
|         Input:
|        Output:
|       Returns: status
|
|    Written By: Christian REY
|          Date: 25/04/2002
| Modifications:
|----------------------------------------------------------------------------*/
int CImage::InsertCRCLSB(){
	int nb_xblocks = width/8;
	int nb_yblocks = height/8;
	unsigned long crc;
	unsigned long *crcTable;
	short bit;
	
	CRCTable(&crcTable);

	for (int c=0; c<nb_comp;c++) {
		if (C[c]==NULL)
			return ERROR;	

		for (int i=0; i<nb_xblocks; i++)
			for (int j=0; j<nb_yblocks; j++) {
				crc = CRCBlock(c, i * 8, j * 8, 8, 8, crcTable);

				for (int n = 0; n < 8; n++) {
					for (int m = 0; m < 4; m++) {
						bit = GETBIT(crc, m + n * 4);
						SETBIT(C[c][(i * 8 + n) + (m + j * 8) * width], 0, bit);
					}
				}
			}
	}

	free(crcTable);
  
	return SUCCESS;
}

/*-----------------------------------------------------------------------------
|  Routine Name: ExtractCRCLSB	
|       Purpose:  
|         Input: 
|        Output:              
|       Returns: status
|
|    Written By: Christian REY
|          Date: 25/04/2002
| Modifications:
|----------------------------------------------------------------------------*/
int CImage::ExtractCRCLSB(){
	int nb_xblocks = width/8;
	int nb_yblocks = height/8;
	unsigned long crc, xcrc;
	unsigned long *crcTable;
	short bit;

	CRCTable(&crcTable);
	
	for (int c=0; c<nb_comp;c++) {
		if (C[c]==NULL)
			return ERROR;	

		for (int i=0; i<nb_xblocks; i++)
			for (int j=0; j<nb_yblocks; j++) {	
				crc = CRCBlock(c, i * 8, j * 8, 8, 8, crcTable);
				xcrc = 0;

				for (int n = 0; n < 8; n++) {
					for (int m = 0; m < 4; m++) {
						bit = GETBIT(C[c][(i * 8 + n) + (m + j * 8) * width], 0);
						SETBIT(xcrc, m + n * 4, bit);
					}
				}
				if (crc != xcrc) {
					DrawBadBlock(i * 8, j * 8, 8, 8);
				}
			}
	}

	free(crcTable);
  
	return SUCCESS;
}

/*-----------------------------------------------------------------------------
|  Routine Name: InsertSelfEmbeddingLSB	
|       Purpose: 
|         Input: 
|        Output:              
|       Returns: status
|
|    Written By: Christian REY
|          Date: 25/04/2002
| Modifications:
|----------------------------------------------------------------------------*/
int CImage::InsertSelfEmbeddingLSB(){
	int nb_xblocks = width/8;
	int nb_yblocks = height/8;
	unsigned long crc;
	unsigned long *crcTable;
	short bit;
	short m[4];
	int ti,tj,k,l;
	
	CRCTable(&crcTable);

	for (int c=0; c<nb_comp;c++) {
		if (C[c]==NULL)
			return ERROR;	

		for (int i=0; i<nb_xblocks; i++)
			for (int j=0; j<nb_yblocks; j++) {
				crc = CRCBlock(c, i * 8, j * 8, 8, 8, crcTable);

				for (int n = 0; n < 8; n++) {
					for (int p = 0; p < 4; p++) {
						bit = GETBIT(crc, p + n * 4);
						SETBIT(C[c][(i * 8 + n) + (p + j * 8) * width], 0, bit);
					}
				}

				for (int b = 0; b < 4; b++) {
					ti = 4 * (b % 2);
					tj = 4 * (int)(b / 2);
					BlockMean(&m[b], c, i * 8 + ti, j * 8 + tj, 4, 4);
				}

				k = (i + 4) % nb_xblocks;
				l = (j + 4) % nb_yblocks;

				for (int b = 0; b < 4; b++) {
					for (int ti = 0; ti < 8; ti++) {
						bit = GETBIT(m[b], ti);
						SETBIT(C[c][(l * 8 + 4 + b) * width + k * 8 + ti], 0, bit);
					}
				}
			}
	}

	free(crcTable);

	return SUCCESS;
}

/*-----------------------------------------------------------------------------
|  Routine Name: ExtractSelfEmbeddingLSB	
|       Purpose: 
|         Input: 
|        Output:              
|       Returns: status
|
|    Written By: Christian REY
|          Date: 25/04/2002
| Modifications:
|----------------------------------------------------------------------------*/
int CImage::ExtractSelfEmbeddingLSB(){
	int nb_xblocks = width/8;
	int nb_yblocks = height/8;
	unsigned long crc, xcrc=0;
	unsigned long *crcTable;
	short bit;
	short m[4];
	int ti,tj,k,l;

	CRCTable(&crcTable);
	ti = 4;
	tj = 4;
	
	for (int c=0; c<nb_comp;c++) {
		if (C[c]==NULL)
			return ERROR;	

		for (int i=0; i<nb_xblocks; i++)
			for (int j=0; j<nb_yblocks; j++) {
				crc = CRCBlock(c, i * 8, j * 8, 8, 8, crcTable);
				xcrc = 0;

				for (int n = 0; n < 8; n++) {
					for (int m = 0; m < 4; m++) {
						bit = GETBIT(C[c][(i * 8 + n) + (m + j * 8) * width], 0);
						SETBIT(xcrc, m + n * 4, bit);
					}
				}

				if (crc != xcrc) {
					k = (i + 4) % nb_xblocks;
					l = (j + 4) % nb_yblocks;

					for (int b = 0; b < 4; b++) {
						m[b] = 0;
						for (int ti = 0; ti < 8; ti++) {
							bit = GETBIT(C[c][(l * 8 + 4 + b) * width + k * 8 + ti], 0);
							SETBIT(m[b], ti, bit);
						}
					}
					for (int b = 0; b < 4; b++) {
						ti = 4 * (b % 2);
						tj = 4 * (int)(b / 2);
						DrawFlatBlock(c, i * 8 + ti, j * 8 + tj, 4, 4, m[b]);
					}
				}
			}
	}

	free(crcTable);
	return SUCCESS;
}


/**************************************************************/
/*			     FONCTIONS A AMIES                               */
/**************************************************************/
void CRCTable(unsigned long **crcTable){
	unsigned long	crc, poly;
	int i, j;
  
	(*crcTable) = (unsigned long *)malloc(sizeof(unsigned long)*256);
	poly = 0xEDB88320L;
	
	for (i=0; i<256; i++) {
		crc = i;
		for (j=8; j>0; j--) {
			if (crc&1) 
				crc = (crc >> 1) ^ poly;
			else 
				crc >>= 1;
		}
		(*crcTable)[i] = crc;
	}
}
