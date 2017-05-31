/*****************************************************
 * Kelompok 5
 * Tugas Besar Grafika Komputer
 * =============================================
 * Vincentius Andri Kurnianto - 140707902
 * Jonathan Wahyu Nugroho Pinulung - 140707910
 * =============================================
 *****************************************************/

/**************************
 * Includes
 *
 **************************/

#include <stdlib.h>
#include <windows.h>		
#include <stdio.h>			
#include <gl\gl.h>			
#include <gl\glu.h>			
#include "glaux.h"
#include "glut.h"

/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);

//perputaran (mubeng-mubeng)
GLfloat	xrot;				// deklarasi rotasi x 
GLfloat	yrot;				// deklarasi rotasi y
GLfloat	zrot;				// deklarasi rotasi z
GLfloat xrot2;
GLfloat yrot2;
GLfloat zrot2;
GLfloat xrot3;
GLfloat yrot3;
GLfloat zrot3;

GLuint	texture[6];			// digunakan untuk menampung 4 gambar

AUX_RGBImageRec *LoadBMP(char *Filename)				// fungsi menampilkan gambar
{
	FILE *File=NULL;									

	if (!Filename)										
	{
		return NULL;								
	}

	File=fopen(Filename,"r");							// digunakan untuk membaca file 

	if (File)											
	{
		fclose(File);									
		return auxDIBImageLoad(Filename);				// jika gambar ada tampilkan gambar
	}

	return NULL;										
}

//kalo butuh lebih dari satu gambar, dicopy lalu diganti nilai 0 nya menjadi 1,2 dst
int LoadGLTextures()									// fungsi menampilkan gambar dan  Convert ke Textures
{
	int Status=FALSE;									

	AUX_RGBImageRec *TextureImage[10];					// membuat temporary untuk menyimpan gambar

	memset(TextureImage,0,sizeof(void *)*1);           	

	if (TextureImage[0]=LoadBMP("foto1.bmp"))  //pengambilan data gambar (256X256)
	{
		Status=TRUE;									

		glGenTextures(1, &texture[0]);					

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	if (TextureImage[1]=LoadBMP("foto2.bmp"))  //pengambilan data gambar (256X256)
	{
		Status=TRUE;									

		glGenTextures(1, &texture[1]);					

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	if (TextureImage[2]=LoadBMP("batik.bmp"))  //pengambilan data gambar (256X256)
	{
		Status=TRUE;									

		glGenTextures(1, &texture[2]);					

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[2]->sizeX, TextureImage[2]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[2]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	if (TextureImage[3]=LoadBMP("lantaikayu.bmp"))  //pengambilan data gambar (256X256)
	{
		Status=TRUE;									

		glGenTextures(1, &texture[3]);					

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[3]->sizeX, TextureImage[3]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[3]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	if (TextureImage[4]=LoadBMP("dinding.bmp"))  //pengambilan data gambar (256X256)
	{
		Status=TRUE;									

		glGenTextures(1, &texture[4]);					

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[4]->sizeX, TextureImage[4]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[4]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	if (TextureImage[5]=LoadBMP("plafond.bmp"))  //pengambilan data gambar (256X256)
	{
		Status=TRUE;									

		glGenTextures(1, &texture[5]);					

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[5]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[5]->sizeX, TextureImage[5]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[5]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
}

int InitGL() // Inisialisasi OpenGL
{
	if (LoadGLTextures())								
	{	
       //hidupkan pencahayaan
	   glEnable(GL_TEXTURE_2D);							
	   glShadeModel(GL_SMOOTH);							
	   glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				
	   glClearDepth(1.0f);									
	   glEnable(GL_DEPTH_TEST);							
	   glDepthFunc(GL_LEQUAL);								
	   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
	}						
}

void Inisialisasi(int lebar, int tinggi)
{
	glShadeModel (GL_FLAT);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClearAccum(0.0, 0.0, 0.0, 0.0);   
	glViewport (0, 0, lebar, tinggi); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, (GLfloat) lebar/(GLfloat) tinggi, 1.0, 20.0);
	glMatrixMode (GL_MODELVIEW);
	// hidupkan pencahayaan
	InitGL();
	glEnable(GL_LIGHTING);	
	glEnable(GL_LIGHT0);	
	glEnable(GL_LIGHT1);	
	glEnable(GL_LIGHT2);	
	glEnable(GL_LIGHT3);	
	glShadeModel(GL_SMOOTH);	
	glEnable(GL_DEPTH_TEST);	
	glEnable(GL_NORMALIZE);
}

void kubus_foto1() //kubus kiri
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	    glTranslatef(-0.757f,-0.75f,-2.98f);
		glScalef(0.26f,0.26f,0.26f);
	    glRotatef(xrot2,-1.5f,0.0f,0.0f);
	    glRotatef(yrot2,0.0f,-2.5f,0.0f);
	    glRotatef(zrot2,0.0f,0.0f,-2.5f);
	
	    glBindTexture(GL_TEXTURE_2D, texture[0]);  // digunakan untuk menempatkan gambar pada object kubus ke - 0
	
	    glBegin(GL_QUADS);        
	    // Muka depan
	    glNormal3f( 0.0f, 0.0f, 1.0f);		// Normal menuju Anda
	    glTexCoord2f(0.0f, 0.0f); 			// kalo mau tanpa gambar di sisi ini, TexCoord dihilangkan
	    glVertex3f(-1.0f, -1.0f,  1.0f);	// Titik 1 (depan)
	    glTexCoord2f(1.0f, 0.0f); 
	    glVertex3f( 1.0f, -1.0f,  1.0f);	// Titik 2 (depan)
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex3f( 1.0f,  1.0f,  1.0f);	// Titik 3 (depan)
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex3f(-1.0f,  1.0f,  1.0f);	// Titik 4 (depan)
	
	    // Muka belakang		
	   	glNormal3f( 0.0f, 0.0f,-1.0f);		// Normal meninggalKan Anda
	   	glTexCoord2f(1.0f, 0.0f);
	   	glVertex3f(-1.0f, -1.0f, -1.0f);	// Titik 1 (belakang)
	   	glTexCoord2f(1.0f, 1.0f);
	   	glVertex3f(-1.0f,  1.0f, -1.0f);	// Titik 2 (belakang)
	   	glTexCoord2f(0.0f, 1.0f);
	   	glVertex3f( 1.0f,  1.0f, -1.0f);	// Titik 3 (belakang)
	   	glTexCoord2f(0.0f, 0.0f);
	   	glVertex3f( 1.0f, -1.0f, -1.0f);	// Titik 4 (belakang)
	
	    // Muka Atas	
	    glNormal3f( 0.0f, 1.0f, 0.0f);		// Normal berarah atas
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex3f(-1.0f,  1.0f, -1.0f);	// Titik 1 (atas)
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex3f(-1.0f,  1.0f,  1.0f);	// Titik 2 (atas)
	    glTexCoord2f(1.0f, 0.0f);
	    glVertex3f( 1.0f,  1.0f,  1.0f);	// Titik 3 (atas)
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex3f( 1.0f,  1.0f, -1.0f);	// Titik 4 (atas)
	
	    // Muka bawah
	    glNormal3f( 0.0f,-1.0f, 0.0f);		// Normal berarah bawah
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex3f(-1.0f, -1.0f, -1.0f);	// Titik 1 (bawah)
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex3f( 1.0f, -1.0f, -1.0f);	// Titik 2 (bawah)
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex3f( 1.0f, -1.0f,  1.0f);	// Titik 3 (bawah)
	    glTexCoord2f(1.0f, 0.0f);
	    glVertex3f(-1.0f, -1.0f,  1.0f);	// Titik 4 (bawah)
	
		// Muka kanan
		glNormal3f( 1.0f, 0.0f, 0.0f);		// Normal berarah ke kanan
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);	// Titik 1 (kanan)
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);	// Titik 2 (kanan)
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);	// Titik 3 (kanan)
		glTexCoord2f(0.0f, 0.0f);
	    glVertex3f( 1.0f, -1.0f,  1.0f);	// Titik 4 (kanan)
	
	    // Muka kiri
	    glNormal3f(-1.0f, 0.0f, 0.0f);		// Normal berarah ke kiri
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex3f(-1.0f, -1.0f, -1.0f);	// Titik 1 (kiri)
	    glTexCoord2f(1.0f, 0.0f);
	    glVertex3f(-1.0f, -1.0f,  1.0f);	// Titik 2 (kiri)
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex3f(-1.0f,  1.0f,  1.0f);	// Titik 3 (kiri)
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex3f(-1.0f,  1.0f, -1.0f);	// Titik 4 (kiri)
	
	glEnd();
    glPopMatrix();
}

void kubus_foto2() //kanan
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
        glTranslatef(0.757f,-0.75f,-2.98f);
		glScalef(0.26f,0.26f,0.26f);
        glRotatef(xrot,-1.5f,0.0f,0.0f);
        glRotatef(yrot,0.0f,-2.5f,0.0f);
        glRotatef(zrot,0.0f,0.0f,-2.5f);

        glBindTexture(GL_TEXTURE_2D, texture[1]);  // digunakan untuk menempatkan gambar pada object kubus ke - 0

        glBegin(GL_QUADS);
        // Muka depan
        glNormal3f( 0.0f, 0.0f, 1.0f);		// Normal menuju Anda
        glTexCoord2f(0.0f, 0.0f); 			// kalo mau tanpa gambar di sisi ini, TexCoord dihilangkan
        glVertex3f(-1.0f, -1.0f,  1.0f);	// Titik 1 (depan)
        glTexCoord2f(1.0f, 0.0f); 
        glVertex3f( 1.0f, -1.0f,  1.0f);	// Titik 2 (depan)
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);	// Titik 3 (depan)
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f,  1.0f,  1.0f);	// Titik 4 (depan)
    
        // Muka belakang		
       	glNormal3f( 0.0f, 0.0f,-1.0f);		// Normal meninggalKan Anda
       	glTexCoord2f(1.0f, 0.0f);
       	glVertex3f(-1.0f, -1.0f, -1.0f);	// Titik 1 (belakang)
       	glTexCoord2f(1.0f, 1.0f);
       	glVertex3f(-1.0f,  1.0f, -1.0f);	// Titik 2 (belakang)
       	glTexCoord2f(0.0f, 1.0f);
       	glVertex3f( 1.0f,  1.0f, -1.0f);	// Titik 3 (belakang)
       	glTexCoord2f(0.0f, 0.0f);
       	glVertex3f( 1.0f, -1.0f, -1.0f);	// Titik 4 (belakang)
	
	    // Muka Atas	
	    glNormal3f( 0.0f, 1.0f, 0.0f);		// Normal berarah atas
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex3f(-1.0f,  1.0f, -1.0f);	// Titik 1 (atas)
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex3f(-1.0f,  1.0f,  1.0f);	// Titik 2 (atas)
	    glTexCoord2f(1.0f, 0.0f);
	    glVertex3f( 1.0f,  1.0f,  1.0f);	// Titik 3 (atas)
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex3f( 1.0f,  1.0f, -1.0f);	// Titik 4 (atas)
	
	    // Muka bawah
	    glNormal3f( 0.0f,-1.0f, 0.0f);		// Normal berarah bawah
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex3f(-1.0f, -1.0f, -1.0f);	// Titik 1 (bawah)
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex3f( 1.0f, -1.0f, -1.0f);	// Titik 2 (bawah)
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex3f( 1.0f, -1.0f,  1.0f);	// Titik 3 (bawah)
	    glTexCoord2f(1.0f, 0.0f);
	    glVertex3f(-1.0f, -1.0f,  1.0f);	// Titik 4 (bawah)
	
    	// Muka kanan
    	glNormal3f( 1.0f, 0.0f, 0.0f);		// Normal berarah ke kanan
    	glTexCoord2f(1.0f, 0.0f);
    	glVertex3f( 1.0f, -1.0f, -1.0f);	// Titik 1 (kanan)
    	glTexCoord2f(1.0f, 1.0f);
    	glVertex3f( 1.0f,  1.0f, -1.0f);	// Titik 2 (kanan)
    	glTexCoord2f(0.0f, 1.0f);
    	glVertex3f( 1.0f,  1.0f,  1.0f);	// Titik 3 (kanan)
    	glTexCoord2f(0.0f, 0.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);	// Titik 4 (kanan)
   	
	    // Muka kiri
	    glNormal3f(-1.0f, 0.0f, 0.0f);		// Normal berarah ke kiri
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex3f(-1.0f, -1.0f, -1.0f);	// Titik 1 (kiri)
	    glTexCoord2f(1.0f, 0.0f);
	    glVertex3f(-1.0f, -1.0f,  1.0f);	// Titik 2 (kiri)
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex3f(-1.0f,  1.0f,  1.0f);	// Titik 3 (kiri)
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex3f(-1.0f,  1.0f, -1.0f);	// Titik 4 (kiri)
  		glEnd();
    glPopMatrix();
}

void kubus_meja()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
			glRotatef (0.0f, 0.0f, 180.0f, 0.0f);
			glTranslatef (0.0f, -1.4f, -3.5f);
			glScalef(2.1f,0.1f,0.7f);
			glBindTexture(GL_TEXTURE_2D, texture[2]);  // digunakan untuk menempatkan gambar pada object kubus ke - 2

            glBegin(GL_QUADS);
//             Muka depan
            glNormal3f( 0.0f, 0.0f, 1.0f);		// Normal menuju Anda
            glTexCoord2f(0.0f, 0.0f); 			// kalo mau tanpa gambar di sisi ini, TexCoord dihilangkan
            glVertex3f(-1.0f, -1.0f,  1.0f);	// Titik 1 (depan)
            glTexCoord2f(1.0f, 0.0f); 
            glVertex3f( 1.0f, -1.0f,  1.0f);	// Titik 2 (depan)
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f( 1.0f,  1.0f,  1.0f);	// Titik 3 (depan)
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-1.0f,  1.0f,  1.0f);	// Titik 4 (depan)
        
//             Muka belakang		
           	glNormal3f( 0.0f, 0.0f,-1.0f);		// Normal meninggalKan Anda
           	glTexCoord2f(1.0f, 0.0f);
           	glVertex3f(-1.0f, -1.0f, -1.0f);	// Titik 1 (belakang)
           	glTexCoord2f(1.0f, 1.0f);
           	glVertex3f(-1.0f,  1.0f, -1.0f);	// Titik 2 (belakang)
           	glTexCoord2f(0.0f, 1.0f);
           	glVertex3f( 1.0f,  1.0f, -1.0f);	// Titik 3 (belakang)
           	glTexCoord2f(0.0f, 0.0f);
           	glVertex3f( 1.0f, -1.0f, -1.0f);	// Titik 4 (belakang)
		
//		     Muka Atas	
		    glNormal3f( 0.0f, 1.0f, 0.0f);		// Normal berarah atas
		    glTexCoord2f(0.0f, 1.0f);
		    glVertex3f(-1.0f,  1.0f, -1.0f);	// Titik 1 (atas)
		    glTexCoord2f(0.0f, 0.0f);
		    glVertex3f(-1.0f,  1.0f,  1.0f);	// Titik 2 (atas)
		    glTexCoord2f(1.0f, 0.0f);
		    glVertex3f( 1.0f,  1.0f,  1.0f);	// Titik 3 (atas)
		    glTexCoord2f(1.0f, 1.0f);
		    glVertex3f( 1.0f,  1.0f, -1.0f);	// Titik 4 (atas)
		
		    // Muka bawah
		    glNormal3f( 0.0f,-1.0f, 0.0f);		// Normal berarah bawah
		    glTexCoord2f(1.0f, 1.0f);
		    glVertex3f(-1.0f, -1.0f, -1.0f);	// Titik 1 (bawah)
		    glTexCoord2f(0.0f, 1.0f);
		    glVertex3f( 1.0f, -1.0f, -1.0f);	// Titik 2 (bawah)
		    glTexCoord2f(0.0f, 0.0f);
		    glVertex3f( 1.0f, -1.0f,  1.0f);	// Titik 3 (bawah)
		    glTexCoord2f(1.0f, 0.0f);
		    glVertex3f(-1.0f, -1.0f,  1.0f);	// Titik 4 (bawah)	
	glEnd();
	glPopMatrix();
	glFlush();
}

void kubus_tengah() //bawah teapot
{
	glDisable(GL_TEXTURE_2D);
	glClearColor(1.0f,1.0f,0.5f,0.0f);
	glPushMatrix();
        glTranslatef(0.0f,-0.7f,-2.8f);
		glScalef(0.27f,0.27f,0.27f);

        glBegin(GL_QUADS);        
        // Muka depan
        glNormal3f( 0.0f, 0.0f, 1.0f);		// Normal menuju Anda
        glTexCoord2f(0.0f, 0.0f); 			// kalo mau tanpa gambar di sisi ini, TexCoord dihilangkan
        glVertex3f(-1.0f, -1.0f,  1.0f);	// Titik 1 (depan)
        glTexCoord2f(1.0f, 0.0f); 
        glVertex3f( 1.0f, -1.0f,  1.0f);	// Titik 2 (depan)
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);	// Titik 3 (depan)
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f,  1.0f,  1.0f);	// Titik 4 (depan)
    
        // Muka belakang		
       	glNormal3f( 0.0f, 0.0f,-1.0f);		// Normal meninggalKan Anda
       	glTexCoord2f(1.0f, 0.0f);
       	glVertex3f(-1.0f, -1.0f, -1.0f);	// Titik 1 (belakang)
       	glTexCoord2f(1.0f, 1.0f);
       	glVertex3f(-1.0f,  1.0f, -1.0f);	// Titik 2 (belakang)
       	glTexCoord2f(0.0f, 1.0f);
       	glVertex3f( 1.0f,  1.0f, -1.0f);	// Titik 3 (belakang)
       	glTexCoord2f(0.0f, 0.0f);
       	glVertex3f( 1.0f, -1.0f, -1.0f);	// Titik 4 (belakang)
	
	    // Muka Atas	
	    glNormal3f( 0.0f, 1.0f, 0.0f);		// Normal berarah atas
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex3f(-1.0f,  1.0f, -1.0f);	// Titik 1 (atas)
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex3f(-1.0f,  1.0f,  1.0f);	// Titik 2 (atas)
	    glTexCoord2f(1.0f, 0.0f);
	    glVertex3f( 1.0f,  1.0f,  1.0f);	// Titik 3 (atas)
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex3f( 1.0f,  1.0f, -1.0f);	// Titik 4 (atas)
	
	    // Muka bawah
	    glNormal3f( 0.0f,-1.0f, 0.0f);		// Normal berarah bawah
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex3f(-1.0f, -1.0f, -1.0f);	// Titik 1 (bawah)
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex3f( 1.0f, -1.0f, -1.0f);	// Titik 2 (bawah)
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex3f( 1.0f, -1.0f,  1.0f);	// Titik 3 (bawah)
	    glTexCoord2f(1.0f, 0.0f);
	    glVertex3f(-1.0f, -1.0f,  1.0f);	// Titik 4 (bawah)
	
    	// Muka kanan
    	glNormal3f( 1.0f, 0.0f, 0.0f);		// Normal berarah ke kanan
    	glTexCoord2f(1.0f, 0.0f);
    	glVertex3f( 1.0f, -1.0f, -1.0f);	// Titik 1 (kanan)
    	glTexCoord2f(1.0f, 1.0f);
    	glVertex3f( 1.0f,  1.0f, -1.0f);	// Titik 2 (kanan)
    	glTexCoord2f(0.0f, 1.0f);
    	glVertex3f( 1.0f,  1.0f,  1.0f);	// Titik 3 (kanan)
    	glTexCoord2f(0.0f, 0.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);	// Titik 4 (kanan)
   	
	    // Muka kiri
	    glNormal3f(-1.0f, 0.0f, 0.0f);		// Normal berarah ke kiri
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex3f(-1.0f, -1.0f, -1.0f);	// Titik 1 (kiri)
	    glTexCoord2f(1.0f, 0.0f);
	    glVertex3f(-1.0f, -1.0f,  1.0f);	// Titik 2 (kiri)
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex3f(-1.0f,  1.0f,  1.0f);	// Titik 3 (kiri)
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex3f(-1.0f,  1.0f, -1.0f);	// Titik 4 (kiri)
		
	glEnd();
	glPopMatrix();
}

void kubus_lantai() //lantai
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);  // digunakan untuk menempatkan gambar pada object kubus ke - 3
	glPushMatrix();
		glRotatef(0.0f,0.0f,0.0f,0.0f);
	    glTranslatef(0.0f,0.0f,-1.0f);
		glScalef(3.0f,2.0f,5.0f);
	    glBegin(GL_QUADS);
	    
	    // Muka bawah
	    glNormal3f( 0.0f,-1.0f, 0.0f);		// Normal berarah bawah
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex3f(-1.0f, -1.0f, -1.0f);	// Titik 1 (bawah)
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex3f( 1.0f, -1.0f, -1.0f);	// Titik 2 (bawah)
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex3f( 1.0f, -1.0f,  1.0f);	// Titik 3 (bawah)
	    glTexCoord2f(1.0f, 0.0f);
	    glVertex3f(-1.0f, -1.0f,  1.0f);	// Titik 4 (bawah)
		    
		glEnd();
    glPopMatrix();
}

void kubus_langit() //langit-langit a.k.a. plafond
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[5]);  // digunakan untuk menempatkan gambar pada object kubus ke - 3
	glPushMatrix();
		glRotatef(0.0f,0.0f,0.0f,0.0f);
	    glTranslatef(0.0f,0.0f,-1.0f);
		glScalef(3.0f,2.0f,5.0f);
	    glBegin(GL_QUADS);
	    
	    // Muka Atas	
	    glNormal3f( 0.0f, 1.0f, 0.0f);		// Normal berarah atas
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex3f(-1.0f,  1.0f, -1.0f);	// Titik 1 (atas)
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex3f(-1.0f,  1.0f,  1.0f);	// Titik 2 (atas)
	    glTexCoord2f(1.0f, 0.0f);
	    glVertex3f( 1.0f,  1.0f,  1.0f);	// Titik 3 (atas)
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex3f( 1.0f,  1.0f, -1.0f);	// Titik 4 (atas)
		    
		glEnd();
    glPopMatrix();
}

void kubus_dinding()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);  // digunakan untuk menempatkan gambar pada object kubus ke - 3
	glPushMatrix();
		glRotatef(0.0f,0.0f,0.0f,0.0f);
	    glTranslatef(0.0f,0.0f,-1.0f);
		glScalef(3.0f,2.0f,5.0f);
	    glBegin(GL_QUADS);     
        // Muka depan
        glNormal3f( 0.0f, 0.0f, 1.0f);		// Normal menuju Anda
        glTexCoord2f(0.0f, 0.0f); 			// kalo mau tanpa gambar di sisi ini, TexCoord dihilangkan
        glVertex3f(-1.0f, -1.0f,  1.0f);	// Titik 1 (depan)
        glTexCoord2f(1.0f, 0.0f); 
        glVertex3f( 1.0f, -1.0f,  1.0f);	// Titik 2 (depan)
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);	// Titik 3 (depan)
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f,  1.0f,  1.0f);	// Titik 4 (depan)
    
        // Muka belakang		
       	glNormal3f( 0.0f, 0.0f,-1.0f);		// Normal meninggalKan Anda
       	glTexCoord2f(1.0f, 0.0f);
       	glVertex3f(-1.0f, -1.0f, -1.0f);	// Titik 1 (belakang)
       	glTexCoord2f(1.0f, 1.0f);
       	glVertex3f(-1.0f,  1.0f, -1.0f);	// Titik 2 (belakang)
       	glTexCoord2f(0.0f, 1.0f);
       	glVertex3f( 1.0f,  1.0f, -1.0f);	// Titik 3 (belakang)
       	glTexCoord2f(0.0f, 0.0f);
       	glVertex3f( 1.0f, -1.0f, -1.0f);	// Titik 4 (belakang)
	
    	// Muka kanan
    	glNormal3f( 1.0f, 0.0f, 0.0f);		// Normal berarah ke kanan
    	glTexCoord2f(1.0f, 0.0f);
    	glVertex3f( 1.0f, -1.0f, -1.0f);	// Titik 1 (kanan)
    	glTexCoord2f(1.0f, 1.0f);
    	glVertex3f( 1.0f,  1.0f, -1.0f);	// Titik 2 (kanan)
    	glTexCoord2f(0.0f, 1.0f);
    	glVertex3f( 1.0f,  1.0f,  1.0f);	// Titik 3 (kanan)
    	glTexCoord2f(0.0f, 0.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);	// Titik 4 (kanan)
   	
	    // Muka kiri
	    glNormal3f(-1.0f, 0.0f, 0.0f);		// Normal berarah ke kiri
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex3f(-1.0f, -1.0f, -1.0f);	// Titik 1 (kiri)
	    glTexCoord2f(1.0f, 0.0f);
	    glVertex3f(-1.0f, -1.0f,  1.0f);	// Titik 2 (kiri)
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex3f(-1.0f,  1.0f,  1.0f);	// Titik 3 (kiri)
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex3f(-1.0f,  1.0f, -1.0f);	// Titik 4 (kiri)
		
	glEnd();
	glPopMatrix();	
	glFlush();
}

void teapot()
{
	glDisable(GL_TEXTURE_2D);
	GLfloat bahan0_ambient[]= {1.0f, 0.1f, 1.0f, 1.0f};
	GLfloat bahan0_diffuse[] = {1.0f, 0.0f, 1.0f, 1.0f};
	GLfloat bahan0_specular[] = {1.0f, 0.2f, 1.0f, 1.0f};
	GLfloat bahan0_shininess[] = {10.0f};
	
	GLfloat IntensitasCahaya0[] = {0.8f, 0.5f, 0.1f, 1.0f};
	
	GLfloat PosisiCahaya0[]={2.0f,6.0f,3.0f, 0.0f};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, bahan0_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, bahan0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, bahan0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, bahan0_shininess);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, IntensitasCahaya0);
	glLightfv(GL_LIGHT0, GL_POSITION, PosisiCahaya0);
	glPushMatrix();
		glRotatef (0.0f, 0.0f, 180.0f, 0.0f);
		glTranslatef (0.0f, -0.2, -2.8);
		glScalef(0.25,0.25,0.25);
		glRotatef(xrot3,-1.5f,0.0f,0.0f);
        glRotatef(yrot3,0.0f,-2.5f,0.0f);
        glRotatef(zrot3,0.0f,0.0f,-2.5f);
		glutSolidTeapot(1.2f);
	glPopMatrix();
	glFlush();
}

void sphere()
{
	glDisable(GL_TEXTURE_2D);
	GLfloat bahan0_ambient[]= {0.0f, 1.0f, 0.0f, 1.0f};
	GLfloat bahan0_diffuse[] = {0.3f, 0.0f, 0.6f, 1.0f};
	GLfloat bahan0_specular[] = {0.3f, 0.2f, 0.7f, 1.0f};
	GLfloat bahan0_shininess[] = {10.0f};
	
	GLfloat IntensitasCahaya0[] = {0.8f, 0.5f, 0.1f, 1.0f};
	
	GLfloat PosisiCahaya0[]={2.0f,6.0f,3.0f, 0.0f};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, bahan0_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, bahan0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, bahan0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, bahan0_shininess);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, IntensitasCahaya0);
	glLightfv(GL_LIGHT0, GL_POSITION, PosisiCahaya0);
	glPushMatrix();
		glTranslatef (0.0f, -0.7f, -2.0);
		glScalef(0.75f,0.75f,0.75f);
		glutSolidSphere(0.3f, 50, 50);
	glPopMatrix();	
	glFlush();
}

void kubusbenda()
{
	glDisable(GL_TEXTURE_2D);
	GLfloat bahan0_ambient[] = {0.1f, 0.1f, 1.0f, 1.0f};
	GLfloat bahan0_diffuse[] = {0.1f, 0.0f, 1.0f, 1.0f};
	GLfloat bahan0_specular[] = {0.1f, 0.2f, 1.0f, 1.0f};
	GLfloat bahan0_shininess[] = {10.0f};
	
	GLfloat IntensitasCahaya0[] = {0.8f, 0.5f, 0.1f, 1.0f};
	
	GLfloat PosisiCahaya0[]={-1.0f,3.0f,1.0f, 0.0f};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, bahan0_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, bahan0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, bahan0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, bahan0_shininess);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, IntensitasCahaya0);
	glLightfv(GL_LIGHT0, GL_POSITION, PosisiCahaya0);
	glPushMatrix();
		glScalef(0.3f,0.3f,0.3f);
		glTranslatef (-2.3f, -1.8f, -5.5f);
		glutSolidCube(1.0f);
	glPopMatrix();	
	glFlush();
}

void torus()
{
	glDisable(GL_TEXTURE_2D);
	GLfloat bahan0_ambient[] = {1.0f, 1.0f, 0.3f, 1.0f};
	GLfloat bahan0_diffuse[] = {0.7f, 0.6f, 0.3f, 1.0f};
	GLfloat bahan0_specular[] = {0.5f, 0.2f, 0.7f, 1.0f};
	GLfloat bahan0_shininess[] = {10.0f};
	
	GLfloat IntensitasCahaya0[] = {0.8f, 0.5f, 0.1f, 1.0f};
	
	GLfloat PosisiCahaya0[] ={ 2.0f,6.0f,3.0f, 0.0f};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, bahan0_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, bahan0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, bahan0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, bahan0_shininess);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, IntensitasCahaya0);
	glLightfv(GL_LIGHT0, GL_POSITION, PosisiCahaya0);
	glPushMatrix();
		glRotatef(0.0f, 0.0f, 180.0f, 90.0f);
		glTranslatef (0.8f, -0.7f, -2.0);
		glScalef(0.75f,0.75f,0.75f);
		glRotatef (10.0f, 0.0f, 0.0f, 0.0f);
		glutSolidTorus(0.09f, 0.2f, 150, 150);
	glPopMatrix();	
	glFlush();
}

void cone()
{
	glDisable(GL_TEXTURE_2D);
	GLfloat bahan0_ambient[] = {0.3f, 0.1f, 0.0f, 1.0f};
	GLfloat bahan0_diffuse[] = {0.3f, 0.0f, 0.0f, 1.0f};
	GLfloat bahan0_specular[] = {0.3f, 0.2f, 0.0f, 1.0f};
	GLfloat bahan0_shininess[] = {10.0f};
	
	GLfloat IntensitasCahaya0[] = {0.8f, 0.5f, 0.1f, 1.0f};
	
	GLfloat PosisiCahaya0[] ={ 2.0f,6.0f,3.0f, 0.0f};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, bahan0_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, bahan0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, bahan0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, bahan0_shininess);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, IntensitasCahaya0);
	glLightfv(GL_LIGHT0, GL_POSITION, PosisiCahaya0);
	glPushMatrix();
		glRotatef(0.0f,0.0f,0.0f,0.0f);
		glScalef(1.0f,1.0f,0.5f);
		glTranslatef (1.4f, -0.8f, -5.8f);
		glutSolidCone(0.2f, 0.8f, 150, 150);
	glPopMatrix();	
	glFlush();
}

/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    /* create main window */
    //angka 800 600 menandakan ukurang dari windows
    hWnd = CreateWindow (
      "GLSample", "Tugas Besar Grafika Komputer", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, 800, 600,
      NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);
    Inisialisasi(800,600);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */
            glClearColor (1.0f, 1.0f, 1.0f, 0.0f);					//warna latar belakang
            
            glEnable(GL_LIGHTING);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
			
			kubus_tengah(); 
			teapot();
			sphere();
			torus();
			cone();
			kubusbenda();
			
			glDisable(GL_LIGHTING);
			
			kubus_lantai();
			kubus_meja();
			kubus_dinding();
			kubus_langit();
			
			glLoadIdentity();
			

			kubus_foto1();
			kubus_foto2();
			
	        // Akhir kode yang diambil dari bukunya Suyoto
	        //******************************************************
	        xrot+=0.0f;   //Mengatur arah putaran object
	        yrot+=1.0f;   //Mengatur arah putaran object
	        zrot+=0.0f;   //Mengatur arah putaran object
	        xrot2-=0.0f;   //Mengatur arah putaran object
	        yrot2-=1.0f;   //Mengatur arah putaran object
	        zrot2-=0.0f;   //Mengatur arah putaran object
	        xrot3-=0.0f;   //Mengatur arah putaran object
	        yrot3-=0.5f;   //Mengatur arah putaran object
	        zrot3-=0.0f;   //Mengatur arah putaran object
    	    SwapBuffers(hDC);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
