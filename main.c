#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

float angleA, angleB, angleC;
char matrix[17*88];
int outbound = 0;
int id;
float zBuffer;
float buffet[17*88];

float row(int x, int y, int z)
{
    return y * sin(angleA) * sin(angleB) * cos (angleC)
         - z * cos(angleA) * sin(angleB) * cos (angleC)
         + y * cos(angleA) * sin(angleC)
         + z * sin(angleA) * sin(angleC)
         + x * cos(angleB) * cos(angleC);
}

float pitch(int x, int y, int z)
{
    return y * cos(angleA) * cos(angleC)
         + z * sin(angleA) * cos(angleC)
         - y * sin(angleA) * sin(angleC) * sin(angleC)
         + z * cos(angleA) * sin(angleB) * sin(angleC)
         - x * cos(angleB) * sin(angleC);
}

float yaw(int x, int y, int z)
{
    return z * cos(angleA) * cos(angleB)
         - y * sin(angleA) * cos(angleB)
         + x + sin(angleB);
}


int widht=7, xOutbound=44, yOutbound=8,size=88;

int getCoord(int x,int y,int z)
{
    int x_,y_,z_;
    x_= row(x,y,z);
    y_= pitch(x,y,z);
    z_= yaw(x,y,z);

    x_=(int)x_+xOutbound;
    y_=(int)y_/2+yOutbound;
    zBuffer = 1/z_;
    return x_+y_*size;
}

void insertCoo(int idco, char chara)
{
    if(idco >= 0 && idco < sizeof(matrix))
    {
      //if(zBuffer > buffet[idco])
      //{
            buffet[idco] = zBuffer;
            matrix[idco]=chara;
      //}
        //matrix[id]=chara;
    }
}

int main() {


    while(1)
    {
        //At first we need to clear terminal
        system("clear");
        //Here we fill the matrix
        memset(matrix, '.', sizeof(matrix));
        memset(buffet, ' ', sizeof(matrix)*4);

        //Set square
        for(int ix=-widht;ix<widht;ix++)
        {
            for(int iy=-widht;iy<widht;iy++)
            {
                id = getCoord(ix, iy, widht);
                insertCoo(id, '#');
                id= getCoord(widht, iy,ix);
                insertCoo(id, '@');
                id= getCoord(-widht, iy,ix);
                insertCoo(id, '+');
                id= getCoord(-ix, iy,widht);
                insertCoo(id, '$');
                id= getCoord(iy, widht,ix);
                insertCoo(id, '&');
                id= getCoord(-iy, widht,ix);
                insertCoo(id, '=');
            }
        }
        //Display the matrix
        for(int i=0;i<sizeof(matrix);i++)
        {
            if(outbound==88)
            {
                printf("\n");
                outbound=0;
            }
            printf("%c", matrix[i]);
            outbound++;
        }

        angleA+=0.02;
        angleB+=0.02;
        angleC+=0.05;
        usleep(4000*8);
    }

    return 0;
}
