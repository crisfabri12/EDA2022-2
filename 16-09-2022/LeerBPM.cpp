#include <iostream>
#include <vector>

using namespace std;

typedef struct bmpFileHeader
{
	/* 2 bytes de identificaci�n */
	uint32_t size;        /* Tama�o del archivo */
	uint16_t resv1;       /* Reservado */
	uint16_t resv2;       /* Reservado */
	uint32_t offset;      /* Offset hasta hasta los datos de imagen */
} bmpFileHeader;

typedef struct bmpInfoHeader
{
	uint32_t headersize;      /* Tama�o de la cabecera */
	uint32_t width;       /* Ancho */
	uint32_t height;      /* Alto */
	uint16_t planes;          /* Planos de color (Siempre 1) */
	uint16_t bpp;             /* bits por pixel */
	uint32_t compress;        /* compresi�n */
	uint32_t imgsize;     /* tama�o de los datos de imagen */
	uint32_t bpmx;        /* Resoluci�n X en bits por metro */
	uint32_t bpmy;        /* Resoluci�n Y en bits por metro */
	uint32_t colors;      /* colors used en la paleta */
	uint32_t imxtcolors;      /* Colores importantes. 0 si son todos */
} bmpInfoHeader;



unsigned char *LoadBMP(char *filename, bmpInfoHeader *bInfoHeader);
void DisplayInfo(bmpInfoHeader *info);
void TextDisplay(bmpInfoHeader *info, unsigned char *img);

int main(){
	bmpInfoHeader info;
	unsigned char *img;
	
	img=LoadBMP((char*)"poesia.bmp", &info);
	DisplayInfo(&info);
	TextDisplay(&info, img);
	
	return 0;
}
	
	void TextDisplay(bmpInfoHeader *info, unsigned char *img)
	{
		int x, y;
		/* Reducimos la resoluci�n vertical y horizontal para que la imagen entre en pantalla */
		static const int reduccionX=6, reduccionY=4;
		/* Si la componente supera el umbral, el color se marcar� como 1. */
		static const int umbral=90;
		/* Asignamos caracteres a los colores en pantalla */
		static unsigned char colores[9]=" bgfrRGB";
		int r,g,b;
		
		/* Dibujamos la imagen */
		for (y=info->height; y>0; y-=reduccionY)
		{
			for (x=0; x<info->width; x+=reduccionX)
			{
				b=(img[3*(x+y*info->width)]>umbral);
				g=(img[3*(x+y*info->width)+1]>umbral);
				r=(img[3*(x+y*info->width)+2]>umbral);
				
				printf("%c", colores[b+g*2+r*4]);
			}
			printf("\n");
		}
	}
	
	unsigned char *LoadBMP(char *filename, bmpInfoHeader *bInfoHeader)
	{
		
		FILE *f;
		bmpFileHeader header;     /* cabecera */
		unsigned char *imgdata;   /* datos de imagen */
		uint16_t type;        /* 2 bytes identificativos */
		
		f=fopen (filename, "r");
		if (!f)
			return NULL;        /* Si no podemos leer, no hay imagen*/
		
		/* Leemos los dos primeros bytes */
		fread(&type, sizeof(uint16_t), 1, f);
		if (type !=0x4D42)        /* Comprobamos el formato */
		{
			fclose(f);
			return NULL;
		}
		
		/* Leemos la cabecera de fichero completa */
		fread(&header, sizeof(bmpFileHeader), 1, f);
		
		/* Leemos la cabecera de informaci�n completa */
		fread(bInfoHeader, sizeof(bmpInfoHeader), 1, f);
		
		/* Reservamos memoria para la imagen, �cu�nta?
		Tanto como indique imgsize */
		imgdata=(unsigned char*)malloc(bInfoHeader->imgsize);
		
		/* Nos situamos en el sitio donde empiezan los datos de imagen,
		nos lo indica el offset de la cabecera de fichero*/
		fseek(f, header.offset, SEEK_SET);
		
		/* Leemos los datos de imagen, tantos bytes como imgsize */
		fread(imgdata, bInfoHeader->imgsize,1, f);
		
		/* Cerramos */
		fclose(f);
		
		/* Devolvemos la imagen */
		return imgdata;
	}
	
	void DisplayInfo(bmpInfoHeader *info)
	{
		printf("Tama�o de la cabecera: %u\n", info->headersize);
		printf("Anchura: %d\n", info->width);
		printf("Altura: %d\n", info->height);
		printf("Planos (1): %d\n", info->planes);
		printf("Bits por pixel: %d\n", info->bpp);
		printf("Compresi�n: %d\n", info->compress);
		printf("Tama�o de datos de imagen: %u\n", info->imgsize);
		printf("Resoluc�n horizontal: %u\n", info->bpmx);
		printf("Resoluc�n vertical: %u\n", info->bpmy);
		printf("Colores en paleta: %d\n", info->colors);
		printf("Colores importantes: %d\n", info->imxtcolors);
		
		
	}
	
