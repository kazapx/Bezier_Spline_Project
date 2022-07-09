#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <graphics.h>


int main()
{
	FILE* f; //1
	f = fopen("coordinates.txt", "r");//1
	if (f == NULL) { // dosyaya erisilemiyorsa NULL olur //1
		printf("dosya acilamadi\n");//1
		exit(1);//1
	}



//BLOK------------------------------------------------------------------------------

// "x_y_sayisi" degeri "sayilar" dizisinin boyutunu belirliyor ve.
int x_y_sayisi=0;//1
char cha;//1
printf("TXT dosyasindan cekilecek metin: ");//1
while ((cha = fgetc(f)) != EOF) {//n*2
printf("%c", cha);                  //1      //kontrol icin sonra silinecek

if(cha=='}')         //n
    x_y_sayisi++;
}
x_y_sayisi=(x_y_sayisi-1)*2;

printf("\n\n Toplam x ve y sayisi: %d\n\n",x_y_sayisi);


//BLOK----------------------------------------------------------------------------------


// "sayilar" dizisinin her elemanini 0 a ataması yapılıyor
int sayilar[x_y_sayisi];
for(int f=0;x_y_sayisi>f;f++)
    sayilar[f]=0;


fclose(f);
f = fopen("coordinates.txt", "r"); //fgetc yuzunden cursor txt dosyasında ilerledi cursoru tekrar basa getirmek icin

   char al[999];
    fgets(al, 999, f); //txt dosyasından diziye kopyalama işlemi
    printf("Stringe atilan metin: %s  \n",al); //txtden kordinatlari alip al stringine yazdirdim ve suan stringi printliyorum.

fclose(f);    //Artık txt ile isimiz yok , kapatiyoruz


//BLOK-------------------------------------------------------------------------------------------


// SUSLU PARANTEZ VE VIRGUL ICIN BOSLUK ATAMASI YAPILAN KISIM
int ii;
for (ii = 0; al[ii] != '\0'; ii++) {
        if (al[ii] == ',' || al[ii] == '{' || al[ii] == '}')
            al[ii] = ' ';
    }

    printf("\n");
printf("Gereksiz isaretlerden sadelestirilen dizi: %s \n\n",al);


//BLOK---------------------------------------------------------------------------------------------


// STRING'TEN INTEGER'A ÇEVİRME VE SAYILAR(int) DIZISINE ATMA KISMI
int negatif_mi=0;
int j = -1;
int i;
 for (i = 0; al[i] != '\0'; i++) {
         if((al[i]==' ') && negatif_mi == 1)
        {      sayilar[j] = sayilar[j]*(-1);
               negatif_mi=0;
        }
         if (al[i] == ' '&& isdigit(al[i+1]) )
        { j++;
        }
        if (al[i] == '-'&& isdigit(al[i+1]) )
        { j++;
        i++;
        sayilar[j] = sayilar[j] * 10 + (al[i] - 48);
        negatif_mi =1;
        continue;
        }

        if(isdigit(al[i])) {
sayilar[j] = sayilar[j] * 10 + (al[i] - 48);  //48, 0'ın yani rakamların asciide baslangıc noktası.
        }


    }


printf("Integer dizisine atildi: ");
for(int asdf=0;x_y_sayisi>asdf;asdf++)  // DIZIYI YAZDIR
    printf(" %d ",sayilar[asdf]); //kontrol amaclı printledik

printf("\n");


//BLOK-------------------------------------------------------------------------------------------




// KOORDİNATLARI X VE Y DIZILERINE AYIRMA VE YAZDIRMA KISMI
int kordinat_sayisi = x_y_sayisi/2;
int x[kordinat_sayisi];
int y[kordinat_sayisi];
int xx=0;
int yy=0;
for(int asdfg=0;x_y_sayisi>asdfg;asdfg++)
  {

   x[xx]=sayilar[asdfg];xx++;
   asdfg++;
    y[yy]=sayilar[asdfg];yy++;

}



//Dosya işlemleri tamamlandı. Diziler hazırlandı. Buradan yukarısı değiştirilmeyecek.
//BLOK-----------------------------------------------------------------------------------------




//EKRAN İŞLEMLERİ
int gm = 800, gr = 800; //pencere boyutu ayarı
initwindow(gm,gr,"Bezier Curve"); //pencere açma

setbkcolor(RED);
outtextxy(10, 10, "Bezier Curve");


line(400,0,400,800); //y çizgisi
line(0,400,800,400); //x çizgisi
int yirmi = 20;

for(int i=0;800>i;i+=yirmi)//x belirteçleri
line(i,405,i,395);

for(int i=0;800>i;i+=yirmi)//y belirteçleri
line(395,i,405,i);

for(i=0;kordinat_sayisi>i;i++){
circle(400+x[i]*20,400-y[i]*20,6); //noktalari koyma

}

int x1;
int y1;


float xxx[kordinat_sayisi];
float yyy[kordinat_sayisi];
int v;

for (float t = 0.00; t < 1.0; t += 0.0001){


for(int i=0;kordinat_sayisi>i;i++){
xxx[i]=x[i];
yyy[i]=y[i];
}


for(int v=1;kordinat_sayisi>v;v++){

for(int i=0; kordinat_sayisi>i ; i++){//i dizi için , v for için

xxx[i]=(1-t)*xxx[i] + t*xxx[i+1];
yyy[i]=(1-t)*yyy[i] + t*yyy[i+1];


}
if(v==kordinat_sayisi-1){
putpixel(400+xxx[0]*20,400-yyy[0]*20,9);
putpixel((400+xxx[0]*20)+1,(400-yyy[0]*20)+1,12);}
}

}
system("pause");


	return 0;
}
