#include <stdio.h>
#include <stdlib.h>

void KayitEkle();//Buradaki fonksiyonlar� istedi�imiz yerde kullanabilmek i�in ba�ta tan�mlad�k....
void KayitBul();
void KayitSil();
void KayitGuncelle();
void VeriDosyasiniGoster();
void IndexDosyasiniGoster();
void  IndexDosyasiniSil();



FILE *vptr,*fp;//Iki dosya i�aret�isi tan�mlad�k istedi�imiz zaman kullanabilmek i�in....

struct kayit{//Kay�t struct�n� olu�turduk....

    int ogrNo;//Struct�n i�ine tamsay� de�erinde ��renci numaras� tan�mlad�k....
    int *ogrNoAdres;//��rencilerin numaralar�n�n adresini tutabilmek i�in bir i�aret�i tan�mlad�k integer de�erinde....
    int dersKodu;//Ders kodunu integer de�erinde tan�mlad�k...
    int puan;//Puan� da ayn� �ekilde integer de�erinde tan�mlad�k...

};


struct index{//Ogrencilerin numaralar�n� ve numaralar�n�n adresini tutabilmesi i�in index ad� alt�nda ba�ka bir struct yap�s� tan�mlad�k..

    int ogrNo;//Ogrenci numaralar�n� atamak i�in integer de�erinde tan�mlad�k....
    int *ogrNoAdres;//Ogrenci numaralar�n�n adresini atamak i�in integer de�erinde tan�mlad�k......


};
void bsortDesc(struct index list[],int s);//Bubble sortu istedi�imiz yerde uygulayabilmek i�in fonksiyonun ad�n� ba�ta tan�mlad�k.....


void KayitEkle(){//Yeni bir ��renci ekleyebilmek i�in kayit ekle diye bir fonksiyon a�t�k...
    vptr=fopen("veri.bin","a");//Veri dosyas�n� binary �ekilde tan�mlay�p ekleme modunda a�t�k...
    struct kayit tmp;//Tmp diye ge�ici bir kay�t struct� tan�mlad�k...
    struct kayit ogm;//Ba�ka bir kay�t struct� a�t�k..
    struct index ogt;//Ayn� �ekilde index struct�na da �zel isim vererek a�t�k...
    struct index *ogs;//Bu ��rencileri diziye aktarabilmek i�in index struct�nda dinamik dizi kullanarak bir struct tan�mlad�k...
    int j=0;
    printf("Ogrenci no:");//Ogrenci numaras� kullan�c�dan al�nacak...
    scanf("%d",&tmp.ogrNo);
    printf("Ders kodu:");//Ders kodu kullan�c�dan al�nacak...
    scanf("%d",&tmp.dersKodu);
    printf("Puani:");//��rencinin notu kullan�c�dan al�nacak...
    scanf("%d",&tmp.puan);
    fwrite(&tmp,sizeof(struct kayit),1,vptr);//fwrite fonksiyonuyla bu structtaki verileri veri dosyas�na bast�r�yoruz.....
    fclose(vptr);//Veri dosyam�z� kapat�yoruz...
    vptr=fopen("veri.bin","r");//Veri dosyas�n� okuma modunda a��yoruz....

    ogs=(struct index*)malloc(2000*sizeof(struct index));//Dinamik dizi halinde bellekten maksimum ki�i kadar yer ay�rt�yoruz....
    int i=0;






    fclose(vptr);//Veri dosyam�z� kapat�yoruz.....

   fp=fopen("index.txt","a");//Indeks dosyas�n� txt format�nda belirleyip ekleme modunda a��yoruz...

     fprintf(fp,"%d %x\n",tmp.ogrNo,tmp.ogrNoAdres);//fprintf ile kullan�c�dan ald���m�z de�erleri index dosyas�na bast�r�yoruz...
     fclose(fp);//Indeks dosyam�z� kapat�yoruz...
     fp=fopen("index.txt","r");//Indeks dosyam�z� okuma modunda a��yoruz...
     fscanf(fp,"%d %x",&ogt.ogrNo,&ogt.ogrNoAdres);//Indeks dosyam�z�n i�indeki ilk ��rencinin  numaras�n� ve adresini fscanf kullanarak okuyup structa atama i�lemini ger�ekle�tiriyoruz....
     while(!feof(fp)){//Dosyan�n sonuna gelene kadar kontrol i�lemi ger�ekle�tiriyoruz...

         ogs[i].ogrNo=ogt.ogrNo;//��rencilerin numaralar�n� di�er dizi struct�na at�yoruz...
         ogs[i].ogrNoAdres=ogt.ogrNoAdres;//��rencilerin numaralar�n�n adreslerini di�er dizi struct�na at�yoruz..
         i++;//Sayma i�lemi ger�ekle�tiriyoruz...

         fscanf(fp,"%d %x",&ogt.ogrNo,&ogt.ogrNoAdres);//Dosyan�n sonuna gelene kadar okuma i�lemini ger�ekle�tiriyoruz...
     }
     fclose(fp);//Indeks dosyam�z� kapat�yoruz...
     bsortDesc(ogs,i);//Bu verileri bubble sort fonksiyonuna g�nderiyoruz....

     //Veriler structta s�raland�..






    fp=fopen("index.txt","w");//Indeks dosyam�z� yazma modunda a�t�k ve i�indeki her�ey silindi...
    for(int k=0;k<i;k++){
        fprintf(fp,"%d %x\n",ogs[k].ogrNo,ogs[k].ogrNoAdres);//O�rencilerin verilerini indeks dosyas�na bast�r�yoruz...
    }


    fclose(fp);//Indeks dosyam�z� kapatt�k..
     free(ogs);//Bellekten ayr�lan alan�n kullan�lmayan� serbest b�rak�ld�...


}


void KayitBul(){//Bir ��renciyi bulma i�lemini ger�ekle�tiriyoruz...

    int anahtar;//��rencinin numaras�n� almak i�in anahtar de�i�kenini integer �ekilde tan�mlad�k...
    //int dersKodu;//Ayn� �ekilde ders kodunu da �yle..

    printf("Anahtar degeri olan ogrenci nosunu giriniz:");
    scanf("%d",&anahtar);//Ogrenci numaras�n� kullan�c�dan ald�k...
    //printf("Anahtar degeri olan �grencinin ders kodunu giriniz:");
   //scanf("%d",&dersKodu);//Ders kodunu kullan�c�dan ald�k.
    vptr=fopen("veri.bin","r");//Veri dosyam�z� okuma modunda a�t�k.
    struct kayit ogl;//Bir struct tan�mlad�k..
    struct kayit *omp;//Dinamik dizi �eklinde alabilmek i�in i�aret�i struct tan�mlad�k..
    omp=(struct kayit*)malloc(500*sizeof(struct kayit));//Struct�n kapasitesini belirledik...
    fread(&ogl,sizeof(struct kayit),1,vptr);//Dosyadaki ilk ��rencini verilerini structa tan�mald�k..
    int t=0;//Bir integer de�i�ken tan�mald�k..
    printf("Anahtara ait kayitlar:\n");
    while(!feof(vptr)){//Dosyan�n sonuna gelene kadar...

        if(ogl.ogrNo==anahtar ){//Kullan�c�n�n bulmak istedi�i ��renci numaras�yla dosyadaki ��renci numaras� birbirine e�itse kontrol� yap�l�yor...
            printf("%d %d %d\n",ogl.ogrNo,ogl.dersKodu,ogl.puan);//E�itse ekrana ��rencinin bilgilerini bast�rd�...

        }

        omp[t]=ogl;//�lk ��renci atand�..
        t++;//�ndis artt�rma i�lemi yap�ld�...
        fread(&ogl,sizeof(struct kayit),1,vptr);//Bir sonraki ��rencinin verileri okundu..
    }

    int search(struct kayit *p, int n, int anaht)//Dosyadaki ilk kayd� bulma i�lemi yap�l�yor..
{
    int i;
    for (i = 0; i < n; i++)
        if (p[i].ogrNo == anaht)//Dosyadaki ��rencinin numaras� ile kullan�c�n�n girdi�i ��rencinin numaras� e�itse.
            return i;//O ��rencinin indeksini d�nd�r..
    return -1;//De�ilse -1 d�nd�r..
}

  int a=search(omp,t,anahtar);//Search fonksiyonundan ald���m�z indisi ba�ka de�i�kene atad�k...
  printf("Veri dosyasindaki ilk kayit:\n ogrenci no:%d\t ders kodu:%d\t puani:%d\n",omp[a].ogrNo,omp[a].dersKodu,omp[a].puan);//Ilk kay�t ekranda g�sterildi..
    free(omp);//Kullan�lmayan alan bellekten serbest b�rak�ld�.
    fclose(vptr);//Veri dosyas� kapat�ld�..

struct index *ogt;//Yeni bir indeks struct� i�aret�i kullan�larak tan�mland�....

  ogt=(struct index*)malloc(2000*sizeof(struct index));//Bellekten 500 ki�ilik indeks struct� yer ay�rt�ld�...
  int k=0;
  fp=fopen("index.txt","r");//Indeks dosyas� okuma modunda a��ld�...
  while(!feof(fp)){//Dosyan�n sonuna gelene kadar kontrol�...
      fscanf(fp,"%d %x\n",&ogt[k].ogrNo,&ogt[k].ogrNoAdres);//Indeks dosyas�nda okuma i�lemi yap�l�yor ve veriler structa atan�yor..
      k++;//Indis artt�r�m� yap�l�yor...
  }

  int binary_search(struct index *p, int MAX,struct kayit temp){//Indeks dosyas�ndaki ilk kayd� bulabilmek i�in bu fonksiyon a��l�yor...

            int sayac=0;
           for(int i=0;i<MAX;i++){
             if(p[i].ogrNo==temp.ogrNo)//Bir structta birden fazla ��renci olmas�na kar�� sayac de�i�keni tutup say�yoruz..
                sayac++;
           }

           if(sayac>=1){
          int low=0;//Bu dizinin en d���k indisi
          int high=MAX-sayac-1;//Dizi struct�n�n en y�ksek indisi
          int mid=0;//Ortanca indis
               while(low<high){//En k���k indis en b�y�k indisten k���k oldu�u ve e�it oldu�u s�rece d�ng� devam etsin...
                   mid=(low+high)/2;//En b�y�k ve en k���k indisin toplam�n�n ikiye b�l�m� ortanca indisi verir...
              if(p[mid].ogrNo==temp.ogrNo){//Structtaki ortanca indisin tan�ml� oldu�u ��rencini numaras� ile kullan�c�n�n girdi�i ��rencinin numaras� e�itse...


                   return mid;//Ortanca indisi d�nd�r....


                     }
                if(p[mid].ogrNo>temp.ogrNo){//Ortanca indise ba�l� ��rencinin ��renci numaras� kullan�c�n�n girdi�i ��renci numaras�ndan b�y�kse..
                      high=mid-1;//En y�ksek indis ortanca indisin bir eksi�i
                   }else{//B�y�k de�ilse
                       low=mid+1;//En d���k de�er ortanca indisin bir fazlas�
               }


            }

         return -1;
     }



  }


  int s=binary_search(ogt,k,omp[a]);
  printf("Indeks dosyasindaki ilk kayit:\n ogrenci no:%d\t adres:%x\n",ogt[s].ogrNo,ogt[s].ogrNoAdres);//Indeks dosyas�ndaki bu numarada kay�tl� ilk ��renci...

  free(ogt);
  free(omp);


}



void KayitSil(){//Silinmek istenen ��renci bu fonksiyonla silinir..
    vptr=fopen("veri.bin","r");//Veri dosyas� okuma modunda a��ld�...
    int sil;//Sil de�i�keni ad� alt�nda silinecek ��renci numaras� atanacak..
    printf("Silinecek kaydin anahtarini giriniz:");
    scanf("%d",&sil);//Kullan�c�dan ��renci numaras� girildi...
    struct kayit *temp;//Ge�ici bir struct tan�mland�..
    struct kayit ogr;//Bir kay�t struct� tan�mland�...
    struct index *ogd;//Bir indeks struct� tan�mland�..
    int i=0;//De�i�ken al�nd�...
    temp=(struct kayit*)malloc(2000*sizeof(struct kayit));//500 ki�ilik yer ayr�ld�..
    ogd=(struct index*)malloc(2000*sizeof(struct index));//500 ki�ilik yer ayr�ld�..
    while(!feof(vptr)){//Dosyan�n sonuna gelene kadar kontrol i�lemi....
        fread(&ogr,sizeof(struct kayit),1,vptr);//Dosyadaki veriler okunup kay�t struct�na atand�....
        temp[i]=ogr;//Kay�t struct�na atanan veriler dizi struct�na atand�..

        i++;//De�i�kenin indisi artt�r�ld�...

    }
    fclose(vptr);//Veri dosyas� kapat�ld�...
    int j=0;
    vptr=fopen("veri.bin","w");//Veri dosyas� yazma modunda a��ld�...
    for(j=0;j<i;j++){
        if(temp[j].ogrNo!=sil){//Kullan�c�n�n girdi�i ��renci numaras�yla dosyadaki ��renci numaras� e�it olmad��� s�rece dosyaya yazd�r..
          fwrite(temp,sizeof(struct kayit),1,vptr);//Veri dosyas�na bast�r�lma i�lemi...
          printf("Ogrenci No:%d Ders Kodu:%d Puani:%d\n",temp[j].ogrNo,temp[j].dersKodu,temp[j].puan);//Ekrana bast�r�lma i�lemi...
        }
    }
    fclose(vptr);//Veri dosyas� kapat�ld�...

    fp=fopen("index.txt","r");//Indeks dosyas�n� okuma modunda a�t�k...
    int k=0;
    while(!feof(fp)){//Dosyan�n sonuna gelene kadar kontrol i�lemi...
        fscanf(fp,"%d %x",&ogd[k].ogrNo,&ogd[k].ogrNoAdres);//Dosyadan ��renci numaras� ve adresini okuyup structa atad�k...
        k++;//�ndis artt�r�lma i�lemi ger�ekle�tirildi..
    }
    fclose(fp);//Indeks dosyas�n� kapatt�k...

    fp=fopen("index.txt","w");//Indeks dosyas�n� yazma modunda a�t�k...
    int t=0;
    printf("\n\nIndeks dosyasindaki veriler:\n");
    while(!feof(fp)){//Dosyan�n sonuna gelene kadar kontrol i�lemi...

        if(sil!=ogd[t].ogrNo){//Kullan�c�n�n girdi�i ��renci numaras� ile dosyadaki ��renci numaras� e�it olmad��� s�rece indeks dosyas�na bast�r...
            fprintf(fp,"%d %x\n",ogd[t].ogrNo,ogd[t].ogrNoAdres);//Dosyaya bast�r�lma i�lemi...
            printf("Ogrenci no:%d Adresi:%x\n",ogd[t].ogrNo,ogd[t].ogrNoAdres);
        }
        t++;
        if(t==(k-1))//Dosyaya bast�rd���m�z veri say�s� dosyadan okudu�umuz veri say�s�na e�it olursa d�ng� k�r�l�r...
          break;



        }


    free(temp);//Bellek alan� serbest b�rak�ld�..
    free(ogd);//Bellek alan� serbest b�rak�ld�..
    fclose(fp);//Indeks dosyas� kapat�ld�....










}



void KayitGuncelle(){//Bu fonksiyonda ��rencinin puan alan� g�ncellenecektir...

    int anahtar;//��renci numaras� bu de�i�kenle al�nacak...
    int lessonkey;//Ders kodu bu de�i�kenle al�nacak...
    printf("Ogrenci numarasini ve g�ncellenecek olan dersin notunun kodunu giriniz:");
    scanf("%d %d",&anahtar,&lessonkey);//��renci numaras� ve ders kodu kullan�c�dan al�nd�...
    vptr=fopen("veri.bin","r");//Veri dosyas� okuma modunda a��ld�...
    struct kayit ogr;//Kay�t struct� tan�malnd�...
    struct kayit *ogy;//Kay�t struct� i�aret�i olarak tan�mland�..
    int k=0;
    ogy=(struct kayit*)malloc(500*sizeof(struct kayit));//Kay�t struct�nda 500 ki�ilik bellek adresi yer tahsis edildi...
    while(!feof(vptr)){//Dosyan�n sonuna gelene kadar kontrol i�lemi...
        fread(&ogr,sizeof(struct kayit),1,fp);//Dosyadaki verileri okuyup kay�t struct�na atama i�lemi..
        ogy[k]=ogr;//Bir structtan di�erine atama i�lemi...
        k++;//Indis artt�r�m� yap�ld�...

    }
    fclose(vptr);//Veri dosyas� kapat�ld�...
    int puan;
    printf("Puani giriniz:");
    scanf("%d",&puan);//Yeni puan girildi..
    vptr=fopen("veri.bin","w");//Veri dosyas� yazma modunda a��ld�...
    int i=0;
    while(!feof(vptr)){//Dosyan�n sonuna gelene kadar kontrol i�lemi...
        if(ogy[i].ogrNo==anahtar && ogy[i].dersKodu==lessonkey){//Kullan�c�n�n girdi�i ��renci numaras� ve ders kodu ile structtaki ��renci numaras� ve ders kodu e�itse...
            ogy[i].puan=puan;//Yeni girilen puan� eski puan�n yerine at�yoruz...
        }
        fwrite(ogy,sizeof(struct kayit),1,vptr);//Structtaki bilgileri dosyaya bast�rma i�lemi yap�yoruz...
        printf("%d.Ogrenci no:%d Ders Kodu:%d Puani:%d Adresi:%x\n",(i+1),ogy[i].ogrNo,ogy[i].dersKodu,ogy[i].puan,ogy[i].ogrNoAdres);//Ekrana bast�rma i�lemi...
        i++;//�ndis artt�rma i�lemi...
        if(i==(k-1))//�ndis dosyadan okunan veri say�s�na e�it olursa
         break;//D�ng�y� k�rma i�lemi ger�ekle�tirilir...
    }


      free(ogy);





}





void bsortDesc(struct index list[], int s)//Bubble Sort kullanarak bu fonksiyonda ��renci nolar�n� ve adreslerini s�ralad�k...
{
    int i, j;
    struct index temp;//Ge�ici bir struct tan�mlad�k...



    for (i = 0; i < s - 1; i++)
    {
        for (j = 0; j < (s - 1-i); j++)
        {
            if (list[j].ogrNo > list[j + 1].ogrNo)//G�nderdi�imiz indeks struct�n�n i�indeki ��renci numaras� bir sonraki ��rencinin numaras�ndan b�y�kse....
            {
                temp = list[j];//Ald���m�z ilk ��rencinin verilerini ge�ici structa at�yoruz...
                list[j] = list[j + 1];//Bir sonraki ��rencinin verilerini ilk ��renciye...
                list[j + 1] = temp;//�lk ��rencininkini de bir sonraki ��renciye atama i�lemini ger�ekle�tiriyoruz....



                }


             if (list[j].ogrNo==list[j + 1].ogrNo)//E�er ��renci numaralar� e�itse...
            {
                if(list[j].ogrNoAdres>list[j+1].ogrNoAdres){//Adresleri kontrol ediyoruz.�lk ��rencinin adresi bir sonraki ��renciden b�y�kse...
                temp = list[j];//�lk ��rencilerinin verilerini ge�ici structa at�yoruz...
                list[j] = list[j + 1];//Bir sonrakini ilk ��renciye at�yoruz...
                list[j + 1] = temp;//Ge�ici structa atad���m�z ��rencideki verileri bir sonraki ��renciye aktar�yoruz...
                }



                }
            }
        }
    }





void VeriEkle(int j){//Kullan�c�dan kay�t alma i�lemi ger�ekle�tiriyoruz...
    vptr=fopen("veri.bin","a");//Veri dosyas�n� ekleme modunda a��yoruz...
    struct kayit *ogr=(struct kayit*)malloc(sizeof(struct kayit));//Dinamik bellekte yer ay�rtt�k...

    if(vptr!=NULL){//Dosyan�n adresi null de�ere e�it de�ilse...
        printf("%d.Ogrenci no:",j);
        scanf("%d",&ogr->ogrNo);//Kullan�c�dan ��renci numaras�n� ald�k....
        printf("Ders id:");
        scanf("%d",&ogr->dersKodu);//Kullan�c�dan ders kodunu ald�k...
        printf("Puani:");
        scanf("%d",&ogr->puan);//Kullan�c�dan puan� ald�k...
        ogr->ogrNoAdres=&ogr->ogrNo;
        fwrite(ogr,sizeof(struct kayit),1,vptr);//Structla ald���m�z verileri dosyaya bast�r�yoruz...
        fclose(vptr);//Veri dosyas�n� kapatt�k...

    }
    free(ogr);

}

void VeriYazdir(){//Girdi�imiz kay�tlar� ekranda g�steren fonksiyon....

    struct kayit ogr;//Kay�t struct�n� tan�mald�k...
    vptr=fopen("veri.bin","r");//Veri dosyas�n� okuma modunda a�t�k....
    if(vptr!=NULL){//Dosyan�n adresi null de�ere e�it olmad��� s�rece...
        fread(&ogr,sizeof(struct kayit),1,vptr);//Dosyadan veriyi okuyup structa atad�k...
            printf("%s\t%s\t  %s\t%s\n","OGRENCI NO:","ADRES:"," DERS KODU:","PUANI:");
        while(!feof(vptr)){//Dosyan�n sonuna gelene kadar kontrol i�lemi....


            printf("%d\t        %x\t %d\t %d\n",ogr.ogrNo,ogr.ogrNoAdres,ogr.dersKodu,ogr.puan);//Bu okudu�umuz verileri ekranda bast�rd�k..
            fread(&ogr,sizeof(struct kayit),1,vptr);//Dosyadaki verileri okuyup kay�t struct�na atad�k...

        }

    }

    fclose(vptr);//Veri dosyas�n� kapatt�k...



}


void VeriDosyasiniGoster(){//Veri dosyas�ndaki bilgileri bu fonksiyonla g�sterece�iz....

    vptr=fopen("veri.bin","r");//Veri dosyas�n� okuma modunda a�t�k...
    struct kayit *ogr;//Kay�t struct�n� i�aret�i olarak tan�mlad�k....
    struct kayit omp;//Ba�ka bir kay�t struct� tan�mlad�k...
    ogr=(struct kayit*)malloc(2000*sizeof(struct kayit));//Kay�t struct�nda 500 ki�ilik bellekten yer ay�rtt�k...
    int k=0;
    while(!feof(vptr)){//Dosyan�n sonuna gelene kadar kontrol i�lemi....
        fread(&omp,sizeof(struct kayit),1,fp);//Dosyadaki verileri okuyup structa atama....
        ogr[k]=omp;//Structtaki veriyi ba�ka bir structa atama...
        k++;//�ndis artt�rma i�lemi...

    }
    printf("Veri Dosyasi:\n");//Veri dosyas�ndaki bilgiler ekranda g�steriliyor...
    for(int i=0;i<(k-1);i++){
        printf("Ogrenci no:%d Ders Kodu:%d Puani:%d\n",ogr[i].ogrNo,ogr[i].dersKodu,ogr[i].puan);
    }

    fclose(fp);//Veri dosyas� kapat�ld�...
    free(ogr);//Bellekteki kullan�lmayan alan serbest b�rak�ld�...

}


void IndexDosyasiniGoster(){//�ndeks dosyas�ndaki verileri bu fonksiyonla g�sterece�iz....
    fp=fopen("index.txt","r");//�ndeks dosyas�n� okuma modunda a�t�k...
    int p=0;
    struct index *ogf;//Kay�t struct� tan�mlad�k...
    ogf=(struct index*)malloc(2000*sizeof(struct index));//Structta bellekten 500 ki�ilik yer ay�rtt�k....


    while(!feof(fp)){//Dosyan�n sonuna gelene kadar kontrol i�lemi....
        fscanf(fp,"%d %x",&ogf[p].ogrNo,&ogf[p].ogrNoAdres);//Dosyadaki bilgileri okuyup structa atama i�lemi...
        p++;//�ndis artt�r�ld�...
    }

    for(int j=0;j<(p-1);j++){//Dosyada okunan veri say�s� kadar ��rencinin bilgilerini ekrana bast�rma i�lemi...
        printf("Ogrenci no:%d  Ogrenci no adres:%x\n",ogf[j].ogrNo,ogf[j].ogrNoAdres);
    }
    free(ogf);//Structta bellekten kullan�lamayan alan serbest b�rak�ld�...
    fclose(fp);//Indeks dosyas� kapat�ld�...
}



void  IndexDosyasiniSil(){//�ndeks Dosyas� silme i�lemini bu fonksiyonla yapt�k...
    remove("index.txt");//�ndeks dosyas�n� diskten sildi...
}




void IndeksDosyasiOlustur(){//�ndeks dosyas�n� bu fonksiyonla olu�turduk...

    fp=fopen("index.txt","w");//�ndeks dosyas�n� yazma modunda a�t�k...




}


void BinaryDosyaOku(int x){//Binary dosyay� okuma i�lemini bu fonksiyonla yapt�k...
  vptr=fopen("veri.bin","r");//Binary dosyas�n� okuma modunda a�t�k..
  struct kayit ogr;//Kay�t struct� tan�mlad�k...

  struct index *ogp;//Kay�t struct�n� i�aret�i olarak tan�mlad�k...
  ogp=(struct index*)malloc(x*sizeof(struct index));//Bellekten girilecek ki�i say�s� kadar yer ay�rtt�k..




  fread(&ogr,sizeof(struct kayit),1,vptr);//Dosyadan ilk veriyi okuduk...
  int i=0;
  while(!feof(vptr)){//Dosyan�n sonuna gelene kadar kontrol i�lemi...

    ogp[i].ogrNo=ogr.ogrNo;//Kay�t struct�ndaki ��renci numaras�n� indeks struct�nda ��renci numaras�na atad�k..
    ogp[i].ogrNoAdres=ogr.ogrNoAdres;//Kay�t struct�ndaki ��renci numaras�n�n adresini indeks struct�ndaki ��renci numaras�n�n adresine atad�k...
    i++;//Indis artt�r�lma i�lemi yap�ld�...
    fread(&ogr,sizeof(struct kayit),1,vptr);//Bir sonraki veriyi dosyadan okuyup structa atad�k...

  }
  fclose(vptr);//Veri dosyas�n� kapatt�k..
  bsortDesc(ogp,i);//Structtaki verileri bu fonksiyona yollad�k..
  IndeksDosyasiOlustur();//�ndeks dosyas�n� buarada a�t�k...
  int j=0;
      for(j=0;j<i;j++){//Dosyadan okunan veri say�s� kadar indeks dosyas�na veri bast�rd�k.Ama s�ral� halde...
        fprintf(fp,"%d %x\n",ogp[j].ogrNo,ogp[j].ogrNoAdres);
      }


    printf("\n\n");
    printf("Txt dosyasindaki sirali hali:\n");//Dosyadaki verileri s�ral� halde g�rmek i�in ekrana bast�rd�k..
    for(j=0;j<i;j++){
        printf("%d %x\n",ogp[j].ogrNo,ogp[j].ogrNoAdres);
    }
    printf("\n\n");



  fclose(fp);//�ndeks dosyas�n� kapatt�k...







}
void BinaryDosyaAc(){//Bir binary dosya a�ma i�lemini ger�ekle�tirdik...
    vptr=fopen("veri.bin","wb");//Veri dosyas�n� yazma modunda a�t�k...
    fclose(vptr);//Veri dosyas�n� kapama i�lemini ger�ekle�tirdik...
}


int main()
{
    BinaryDosyaAc();//Veri dosyas� a�t�k...
    int kisi_sayisi;
    printf("Kac kayit ekleyeceksiniz:");
    scanf("%d",&kisi_sayisi);//Kullan�c�dan kay�t edilecek ki�i say�s� al�nd�...
    int i=0;
    for(i=0;i<kisi_sayisi;i++){//Ki�i say�s� kadar veri ekle fonksiyonu �a�r�ld�..
    VeriEkle(i+1);
    }
    printf("Kayit ekleme isi bitti.....\n\n\n");
    VeriYazdir();//Verileri ekrana bast�rd�k...
    BinaryDosyaOku(kisi_sayisi);//Ki�i say�s�n� bu fonksiyona g�nderdik...
    //rewind(vptr);//Dosyay� ba�a ald�k...
    int secim;
    do{
   printf("Ana Menu secimleriniz:\n"
     "1:Kayit Ekle\n"
     "2:Kayit Bul\n"
     "3:Kayit Sil\n"
     "4:Kayit Guncelle\n"
     "5:Veri Dosyasini Goster\n"
     "6:Indeks Dosyasini Goster\n"
     "7:Indeks Dosyasini Sil\n"
     "8:Cikis\n");
     scanf("%d",&secim);//Kullan�c�dan bir se�im yapmas�n� istedik..


     switch(secim){//Se�im de�erine g�re a�a��daki fonksiyonlara girdi...
         case 1:
         KayitEkle();
         break;






         case 2:
         KayitBul();
         break;


         case 3:
         KayitSil();
         break;

         case 4:
         KayitGuncelle();
         break;

         case 5:
         VeriDosyasiniGoster();
         break;

         case 6:
         IndexDosyasiniGoster();
         break;

         case 7:
         IndexDosyasiniSil();
         break;

         case 8:
         printf("Cikis yapildi....");
         return 0;


         default:
         printf("Gecersiz Islem.....\n");
         break;

     }

    }while(1);


           fflush(stdin);

    return 0;
}
