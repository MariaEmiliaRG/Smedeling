#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#define fmin 1
#define fmax 24
#define cmin 1
#define cmax 79 
FILE *arch;
int x, y,a, b;// coordenadas para J1 y J2
typedef struct score
{
        char nombre[9];
        int puntos; 
};
void subrayar (char n[30],int color, int fondo, int c, int r)
{
     gotoxy(c,r);
     textbackground(fondo);
     textcolor (color);
     printf("%s",n);
     return;
}
void emilia ()
{
     textcolor(15);
     gotoxy(5,24);  
     printf("REALIZADO POR MAR%cA EMILIA RAM%cREZ G%cMEZ. 2017-2018",214,214,224);  
     return;
}
void borrar()
{
     textbackground(0);
     clrscr();
     return;
}
void limpiar (char mat[][cmax])
{
     int f,c;
     for (f=0; f<fmax; f++)
         for (c=0; c<cmax; c++)
             {
             mat[f][c]='0';
             }
     return;
}
void marco (char mat[][cmax], int color)
{
     int f,c;
     char espacio[2];
     strcpy(espacio," ");
     a='1';
     textbackground(2);
     for (f=fmin; f<=fmax; f++)//lineas verticales
         {
                  mat[f-1][cmax-1]='3';
                  mat[f-1][cmin-1]='3';
                  subrayar(espacio,0,color,cmin,f);
                  subrayar(espacio,0,color,cmax,f);
         } 
     for (c=cmin; c<=cmax; c++)//lineas horizontles
         {        
                  mat[fmax-1][c-1]='3';
                  mat[fmin-1][c-1]='3';
                  subrayar(espacio,0,color,c,fmin);
                  subrayar(espacio,0,color,c,fmax);  
         }     
     return;
}//Archivos
void abrir(char archivo[15], char modo[3])
{
     arch=fopen(archivo,modo); 
     return; 
}
void nombrearch(int vel,char nomarch[10])
{
     if (y==1)
        strcpy(nomarch,"1");
     else 
          strcpy(nomarch,"2");
     if (vel==125)
        strcat(nomarch,"1.emy");
     else 
          if (vel==105)
             strcat(nomarch,"2.emy");
          else 
               if (vel==60)
                  strcat(nomarch,"3.emy");
     return;
}
void crearscore(char archivo[20])//por si no existe el archivo
{
     score registro;
     int i;
     abrir(archivo,"wb+");
     fseek(arch,0,SEEK_SET);
     strcpy(registro.nombre,"JUGADOR");
     registro.puntos=0;
     for (i=0; i<=2; i++) 
         fwrite(&registro,sizeof(registro),1,arch);
     return; 
}
void comparar(score datos, char cadena[9], int puntos, int y)
{
     int i;
     char score1[6],score2[6];
     i=strcmp(datos.nombre, cadena);
     if (i<0||i>0)
        subrayar(cadena,15,0,11,7+y);
     else 
          {
          itoa(puntos,score1,10);
          itoa(datos.puntos,score2,10);
          i=strcmp(score1, score2);
          if (i<0||i>0)
             subrayar(cadena,15,0,11,7+y);
          else 
               subrayar(cadena,0,14,11,7+y);
               printf("     ");
          }
     return;
}
void record (score jugador, char nomarch[20])
{
     score puntuaciones[4];
     score persona, aux;
     int i, cont;
     textcolor(14); 
     abrir (nomarch,"rb");
           if (arch==NULL)
              crearscore(nomarch);
     fseek(arch,0,SEEK_SET);
     for (i=0; i<=2; i++)
         {   
         fread(&persona,sizeof(persona),1,arch);
         puntuaciones[i]=persona;
         }
     puntuaciones[i]=jugador; 
     for (i=1; i<4; i++)
         for (cont=1;cont<=4-i;cont++)
             if (puntuaciones[cont-1].puntos<puntuaciones[cont].puntos)
                {
                aux=puntuaciones[cont-1];
                puntuaciones[cont-1]=puntuaciones[cont];
                puntuaciones[cont]=aux;
                }
     for (i=0; i<=2;i++)
         {
         comparar(jugador,puntuaciones[i].nombre, puntuaciones[i].puntos, i);
         gotoxy(20,7+i);
         printf("%i",puntuaciones[i].puntos);
         }
     fclose(arch);
     abrir(nomarch,"wb");
     for (i=0; i<=2; i++) 
            fwrite(&puntuaciones[i],sizeof(persona),1,arch);
     fclose(arch);
     return; 
}
void color (char letra, int c, int f)
{
    int colores [7] = {0,15,10,11,12,14,13};
    char num[2]; 
    num[0] = letra; 
    subrayar(" ",15,colores[atoi(num)],c+1,f+1);
    return;   
}
void archivoLeer(int alto, int largo,int col, int reg,char nombre[9])
{
     int f,c;
     char n;
     abrir(nombre,"r");
     for (f=0+alto;f<col+alto;f++)
        for (c=0+largo;c<reg+largo;c++)
            color(fgetc(arch), c, f);
     fclose (arch);
     subrayar(" ",11,0,15,20);
     return; 
}
void leerarchivos ()
{
     score personas;
     int dif,vel,i;
     char cdif[7], cvel[5];
     textcolor(15);
     for (dif=1; dif<3; dif++)
         for (vel=1; vel<4; vel++)
             {
             itoa(dif,cdif,10);
             itoa(vel,cvel,10);
             strcat(cdif,cvel);
             strcat(cdif,".emy");
             abrir(cdif,"rb");
             if (arch==NULL)
              crearscore(cdif);
             for (i=1;i<4;i++)
                 {
                 gotoxy(20*vel,(7*dif)+i);
                 fread(&personas,sizeof(personas),1,arch);
                 printf("%i.%s ",i,personas.nombre);
                 gotoxy((20*vel)+10,(7*dif)+i);
                 printf("  %i",personas.puntos);
                 Sleep(1);
                 }
             fclose(arch);
             } 
     emilia();
     return;
}
void nombre(char cad[9], int col, int reg,int color )
{
     char tecla; 
     int cont=0; 
     emilia();
     while (tecla!=13)
           {
           if (cont<9)
              {
              gotoxy(col,reg);
              tecla=getch();
              tecla=toupper(tecla);
              if (isupper(tecla)!=0)
                 {
                 cad[cont]=tecla;
                 textcolor(color);
                 putchar(tecla);
                 cont++;
                 col++;
                 }
              else 
                if (tecla==8)
                   {
                   if (cont>=0&&col>11)
                      {
                      --cont;
                      col--;
                      subrayar(" ",color,0,col,reg);
                      }
                   }
              }
              else 
                   {
                   cont=8;
                   col--;
                   subrayar(" ",color,0,col,reg);
                   }
              fflush(stdin);
           }
     if (cont!=0)
        cad[cont]='\0';
     else 
          strcpy(cad,"JUGADOR");
     return;
}//menu
int menu(char arr,char ab,int c, int r, int &var, char modo1[30],char modo2[30],char carac,char letra,int color)
{
    char n;
    int *v=&var;
    int vel=1; 
    n='0'; 
    subrayar(modo1,15,0,c,r);
    subrayar(modo2,15,0,c,r+2);
    while (n!='?')
          {
          n=getch();
          n=tolower(n);
          if (n==arr)
             {
             subrayar(modo1,0,14,c,r);
             subrayar(modo2,15,0,c,r+2);
             subrayar("SALIR = X",color,0,60,23);
             a=1;
             vel=1;
             }
          else 
               {
               if (n==ab)
                  {
                  subrayar(modo1,15,0,c,r);
                  subrayar(modo2,0,14,c,r+2);
                  subrayar("SALIR = X",color,0,60,23);
                  a=2;
                  vel=1;
                  }
               else {
                    if (n==carac)
                       menu('w','s',16,12,b,"1 JUGADOR","2 JUGADORES",'~','~',0);
                    else 
                         if (n==letra)
                            {
                            subrayar("SALIR = X",0,color,60,23);
                            vel=0;
                            }
                    }
               if (n==13)
                  {
                  if (a==1||a==2)
                     n='?';
                  else
                   if (vel==0)
                      n='?';
                   }
               }
          } 
    if (a==1)
       {
       *v=1;
       subrayar(modo1,0,11,c,r);
       }
    else 
         if(a==2)
         {
         *v=2;
         subrayar(modo2,0,10,c,r+2);
         }
    return vel; 
}
int menu2(int color,char arr,char ab,int c,int f,char modo1[15],char modo2[15],char modo3[15],char letra,int z,int r,int z2,int r2,int valor,char carac)
{
    char n;
    int a,vel;
    n='w'; 
    subrayar(modo1,15,0,c,f);
    subrayar(modo2,15,0,c+z2,f+z);
    subrayar(modo3,15,0,c+r2,f+r);
    a=2;
    while (n!='?')
          {
          n=getch();
          n=tolower(n);
          if (n==arr)
             {
             if (a==4)
                a=2;
             else 
                  {
                  if (a==0)
                     a=1;
                  else 
                       --a;
                  }   
             }
          else 
               {
               if (n==ab)
                  {
                  if (a==0)  
                        a=2;
                  else 
                       {
                       if (a==4)
                          a=3;
                       else 
                            ++a;
                       }
                  }
                else
                   {
                   if (n==letra)
                      menu('w','s',39,12,y,"NORMAL","INVERTIDO",'a','~',0);
                   else
                       if (n==carac)
                          {
                          a=0;
                          vel=0;
                          subrayar("SALIR = X",0,color,60,23);
                          }
                   }
               }
          if (n==13)
             {
             if (a>=1||a<=3)
                n='?';
             else
                 if (vel==0)
                    n='?';
             }
          switch (a)
                 {
                 case 1:
                      {
                        subrayar(modo1,0,14,c,f);
                        subrayar(modo2,15,0,c+z2,f+z);
                        subrayar(modo3,15,0,c+r2,f+r);
                        subrayar("SALIR = X",color,0,60,23);
                        }
                 break;
                 case 2:
                      {
                      subrayar(modo1,15,0,c,f);
                      subrayar(modo2,0,14,c+z2,f+z);
                      subrayar(modo3,15,0,c+r2,f+r);
                      subrayar("SALIR = X",color,0,60,23);                      
                      }
                 break;
                 case 3:
                      {
                      subrayar(modo1,15,0,c,f);
                      subrayar(modo2,15,0,c+z2,f+z);
                      subrayar(modo3,0,14,c+r2,f+r);
                      subrayar("SALIR = X",color,0,60,23);
                      }
                 break;
                 }
          } 
    if (a==1||a==0)
       {
       vel=125;
       subrayar(modo1,0,11,c,f);
       }
    else 
         {
         if (a==2)
            {
            vel=105;
            subrayar(modo2,0,10,c,f+2);     
            }
         else
             if (vel!=0)
                {
                vel=valor;
                subrayar (modo3,0,13,c,f+4);
                }
         }
    return vel; 
}//Dinámica del Juego 
void iniciar (char matriz[][cmax])
{
     borrar();
     limpiar(matriz);
     marco(matriz,15);
     return; 
}
void opcion(int inc,char tecla,char mat [][cmax],char l,char j,char i,char k, int &col,int &reg)
{
     char ch;
     int *c,*r;
     c=&col;
     r=&reg;
     mat [*r-1][*c-1]='2';
     ch=tecla;
     ch=toupper(ch); 
     if (ch==l)//  derecha 
        *c=*c+inc;
     else 
          {
          if (ch==j)// izquierda
             *c=*c-inc;
          else 
               {
               if (ch==k)//  abajo
                  *r=*r+inc;
               else 
                    if (ch==i)//  arriba
                       *r=*r-inc;
               }
          }
     return; 
}  
void mensaje(char p1, char p2, char jugador2[9], char jugador1[9], int &punt1,int &punt2)
{
     int *s1, *s2;
     s1=&punt1;
     s2=&punt2;
     borrar();
     textcolor(15);
     if (p1=='1'||p1=='2'||p1=='3')
        *s2=*s2+1;
     else
         if (p2=='1'||p2=='2'||p2=='3')
            *s1=*s1+1;
     gotoxy(20,13);
     printf("%s  %i\t%s  %i",jugador1,*s1,jugador2,*s2);
     Sleep (1000);
     return;
}
void coordenada (int &col, int &reg, int res1, int suma, int res2, int suma2, int color)
{
     int *c,*r;
     c=&col;
     r=&reg;
     *c=rand()%res1+suma;
     *r=rand()%res2+suma2;
     subrayar(" ",0,color,*c,*r);
     return;     
}
void instrucciones(char arr[4],char ab [4],char der[4],char iz[4],int c,int r, int color, int dificultad, int n)
{
     gotoxy(4,2);
     textcolor(15);
     if (n==1)
        printf("DURANTE LAS SIGUIENTES TRES RONDAS OBTEN LA MAYOR CANTIDAD DE PUNTOS.\n    SI CHOCAS PIERDES."); 
     else
         printf("GANA DOS PARTIDAS DE TRES EVITANDO CHOCAR CON TU ADVERSARIO.\n");
     subrayar("ARRIBA",color,0,c+4,r);
     subrayar("ABAJO",color,0,c+4,r+1);
     subrayar("DERECHA",color,0,c+4,r+2);
     subrayar("IZQUIERDA",color,0,c+4,r+3);
     if (dificultad==1)
        {
        subrayar(arr,color,0,c,r);
        subrayar(ab,color,0,c,r+1);
        subrayar(der,color,0,c,r+2);
        subrayar(iz,color,0,c,r+3);
        }
     else 
          {
          subrayar(ab,color,0,c,r);
          subrayar(arr,color,0,c,r+1);
          subrayar(iz,color,0,c,r+2);
          subrayar(der,color,0,c,r+3);
          }     
     return;
}
void dinamica (int velocidad, int dificultad)
{
    char pantalla [fmax][cmax], j1[9],j2[9];
    char p1,p2,n,n1,n2;// variables para el jugrador 1 y jugador 2;
    int rep,punt1,punt2;
    textcolor(15);
    gotoxy(3,22);
    printf("PAUSA SE ACTIVA PRESIONANDO CUALQUIER TECLA DE CONTROL, FUNCI%CN O NAVEGACI%CN.",224,224);
    subrayar("INGRESA TU NOMBRE",13,0,11,6);
    instrucciones("W = ","S = ","D = ","A = ",40,6,13,dificultad,2);
    nombre(j1,11,8,13);
    subrayar("INGRESA TU NOMBRE",14,0,11,14);
    instrucciones("I = ","K = ","L = ","J = ",40,14,14,dificultad,2);
    nombre(j2,11,16,14);
    do
    {
    punt1=0;
    punt2=0;
    while(punt1<=1&&punt2<=1)
        {  
        if (punt1==1&&punt2==1)
           {
           borrar();
           archivoLeer(6,8,13,68,"fin.txt");
           Sleep(700);
           }
        iniciar(pantalla);
        srand(time(NULL));
        coordenada(x,y,37,2,22,2,13);
        coordenada(a,b,37,37,22,2,14);
        n1='D';
        n2='J';
        n='0';
        do 
        {
        n=getch();
        n=toupper(n);
        if (n==68||n==65||n==87||n==83)
           n1=n;
        else
            {
            if (n==73||n==74||n==75||n==76)
               n2=n;
            else
                   {
                   n1=n1;
                   n2=n2;
                   }
            }
        while (!kbhit())
              {
              subrayar(" ",0,14,a,b);
              subrayar(" ",0,13,x,y);
              p1=pantalla[y-1][x-1];
              p2=pantalla [b-1][a-1];
              if (p2=='0'&& p1=='0') 
                 {
                 opcion(dificultad,n1,pantalla,68,65,87,83,x,y);
                 opcion(dificultad,n2,pantalla,76,74,73,75,a,b);
                 Sleep(velocidad);
                 }
              else 
                 n='?';
              } 
       }
       while (n!='?');
       mensaje(p1,p2,j2,j1,punt1,punt2);
    }
    borrar();
    subrayar("GANA ",15,0,19,12);
    if (punt1==2&&punt2<=1)
       printf(j1);
    else 
         if (punt2==2&&punt1<=1)
            printf(j2);
    subrayar("¨QUIERES VOLVER A JUGAR?",15,0,8,16);
    subrayar("W = ARRIBA\t S = ABAJO",9,0,8,22);
    emilia();
    menu('w','s',12,18,b,"SI","NO",'~','~',0);
    borrar();
    }
    while (b==1);
    return;
}
int dinamica2 (int velocidad, int dificultad)
{
    char puntos[3];
    char pantalla[fmax][cmax];
    char p1,n1,n;
    int rep,punt=0;
    for (rep=1;rep<4;rep++)
        {
        if (rep==3)
           {
           borrar();
           archivoLeer(6,8,13,68,"fin.txt");
           Sleep(700);
           }
        iniciar(pantalla); 
        subrayar("PUNTOS: ",0,15,4,1);
        srand(time(NULL));
        coordenada(x,y,75,2,21,2,15);
        n1='a';
        do
          {
          n=getch();
          n=toupper(n);
          if (n=='A'||n=='S'||n=='W'||n=='D')
             n1=n;
          else 
               n1=n1;
          while (!kbhit())
                {
                subrayar(" ",0,14,x,y);
                p1=pantalla[y-1][x-1];
                if (p1=='0')
                   {
                   opcion(dificultad,n1,pantalla,'D','A','W','S',x,y);
                   punt++;
                   itoa(punt,puntos,10);
                   subrayar(puntos,0,15,14,1);
                   Sleep(velocidad);
                   }
                else 
                     n1='?';
                }
          }
    while (n1!='?');
    Sleep(1000);
    borrar();
    }  
    return punt;
}
int main ()
{
    int vel=0, noi,a; 
    char letra;
    score jugador; 
    emilia();
    archivoLeer(2,4,21,72,"s.txt");
    system("PAUSE");
    borrar();
    do
    {
    archivoLeer(2,15,13,53,"smini.txt");
    emilia();
    subrayar("A = IZQUIERDA\t D = DERECHA",9,0,8,22);
    vel=menu2(0,'a','d',20,17,"JUEGO","RECORDS","SALIR",'@',0,0,21,42,0,'~');
    noi=vel;
    borrar();
    if (vel==125)
       while (vel!=0)
          {
          subrayar("SALIR = X",15,0,60,23);
          subrayar("JUGADORES",12,0,16,10);
          subrayar("W = ARRIBA\t S = ABAJO\t A = REGRESAR",9,0,8,23);
          vel=menu('w','s',16,12,b,"1 JUGADOR","2 JUGADORES",'~','x',15);
          if (vel!=0)
             {
             subrayar("MODO DE JUEGO",12,0,39,10);
             vel=menu('w','s',39,12,y,"NORMAL","INVERTIDO",'a','x',15);
             if (vel!=0)
                {  
                subrayar("DIFICULTAD",12,0,58,10);
                vel=menu2(15,'w','s',58,12,"BAJA","MEDIA","ALTA",'a',2,4,0,0,60,'x');
                if (vel!=0)
                   {
                   Sleep (2000);
                   if (y==1)
                      noi=1;
                   else 
                     if (y==2)
                        noi=-1;
                   borrar();
                   if (b==1)
                      {
                      char archivo[20];
                      nombrearch(vel,archivo);
                      subrayar("INGRESA TU NOMBRE:",14,0,11,10);
                      instrucciones("W = ","S = ","D = ","A = ",40,11,14,noi,1);   
                      nombre(jugador.nombre,11,12,14);
                      do
                        {
                        jugador.puntos=dinamica2(vel,noi);            
                        record(jugador,archivo);
                        subrayar(jugador.nombre,14,0,11,11);
                        printf("\t%i",jugador.puntos);
                        gotoxy(5,5);                        
                        printf("\t   RECORDS\n\n\t1.\n\t2.\n\t3.");
                        subrayar("¨QUIERES VOLVER A JUGAR?",15,0,8,16);
                        subrayar("W = ARRIBA\t S = ABAJO",9,0,8,22);
                        emilia();
                        menu('w','s',12,18,b,"SI","NO",'~','~',0);
                        borrar();
                        }
                      while (b==1);
                   }
                   else 
                     if (b==2)
                        dinamica(vel,noi);
                   }
                } 
             }
          } 
    else
        if (vel==105)
        {
           subrayar("FACIL",0,11,22,5);
           subrayar("MEDIO",0,13,43,5);
           subrayar("COMPLICADO",0,14,61,5);
           subrayar("NORMAL",0,10,8,9);
           subrayar("INVERTIDO",0,12,8,16);
           subrayar("SALIR = X",11,0,60,23);
           leerarchivos();
           while (vel!=0)
                 {
                 letra=getch();
                 letra=toupper(letra);
                 if (letra=='X')
                    vel=0;
                 }
        }
    borrar();
    }
    while(noi!=0);     
    return 0;
}
