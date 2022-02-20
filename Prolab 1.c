#include <stdio.h>
#include <stdlib.h>

void KayitEkle();//Buradaki fonksiyonlarý istediðimiz yerde kullanabilmek için baþta tanýmladýk....
void KayitBul();
void KayitSil();
void KayitGuncelle();
void VeriDosyasiniGoster();
void IndexDosyasiniGoster();
void  IndexDosyasiniSil();



FILE *vptr,*fp;//Iki dosya iþaretçisi tanýmladýk istediðimiz zaman kullanabilmek için....

struct kayit{//Kayýt structýný oluþturduk....

    int ogrNo;//Structýn içine tamsayý deðerinde öðrenci numarasý tanýmladýk....
    int *ogrNoAdres;//Öðrencilerin numaralarýnýn adresini tutabilmek için bir iþaretçi tanýmladýk integer deðerinde....
    int dersKodu;//Ders kodunu integer deðerinde tanýmladýk...
    int puan;//Puaný da ayný þekilde integer deðerinde tanýmladýk...

};


struct index{//Ogrencilerin numaralarýný ve numaralarýnýn adresini tutabilmesi için index adý altýnda baþka bir struct yapýsý tanýmladýk..

    int ogrNo;//Ogrenci numaralarýný atamak için integer deðerinde tanýmladýk....
    int *ogrNoAdres;//Ogrenci numaralarýnýn adresini atamak için integer deðerinde tanýmladýk......


};
void bsortDesc(struct index list[],int s);//Bubble sortu istediðimiz yerde uygulayabilmek için fonksiyonun adýný baþta tanýmladýk.....


void KayitEkle(){//Yeni bir öðrenci ekleyebilmek için kayit ekle diye bir fonksiyon açtýk...
    vptr=fopen("veri.bin","a");//Veri dosyasýný binary þekilde tanýmlayýp ekleme modunda açtýk...
    struct kayit tmp;//Tmp diye geçici bir kayýt structý tanýmladýk...
    struct kayit ogm;//Baþka bir kayýt structý açtýk..
    struct index ogt;//Ayný þekilde index structýna da özel isim vererek açtýk...
    struct index *ogs;//Bu öðrencileri diziye aktarabilmek için index structýnda dinamik dizi kullanarak bir struct tanýmladýk...
    int j=0;
    printf("Ogrenci no:");//Ogrenci numarasý kullanýcýdan alýnacak...
    scanf("%d",&tmp.ogrNo);
    printf("Ders kodu:");//Ders kodu kullanýcýdan alýnacak...
    scanf("%d",&tmp.dersKodu);
    printf("Puani:");//Öðrencinin notu kullanýcýdan alýnacak...
    scanf("%d",&tmp.puan);
    fwrite(&tmp,sizeof(struct kayit),1,vptr);//fwrite fonksiyonuyla bu structtaki verileri veri dosyasýna bastýrýyoruz.....
    fclose(vptr);//Veri dosyamýzý kapatýyoruz...
    vptr=fopen("veri.bin","r");//Veri dosyasýný okuma modunda açýyoruz....

    ogs=(struct index*)malloc(2000*sizeof(struct index));//Dinamik dizi halinde bellekten maksimum kiþi kadar yer ayýrtýyoruz....
    int i=0;






    fclose(vptr);//Veri dosyamýzý kapatýyoruz.....

   fp=fopen("index.txt","a");//Indeks dosyasýný txt formatýnda belirleyip ekleme modunda açýyoruz...

     fprintf(fp,"%d %x\n",tmp.ogrNo,tmp.ogrNoAdres);//fprintf ile kullanýcýdan aldýðýmýz deðerleri index dosyasýna bastýrýyoruz...
     fclose(fp);//Indeks dosyamýzý kapatýyoruz...
     fp=fopen("index.txt","r");//Indeks dosyamýzý okuma modunda açýyoruz...
     fscanf(fp,"%d %x",&ogt.ogrNo,&ogt.ogrNoAdres);//Indeks dosyamýzýn içindeki ilk öðrencinin  numarasýný ve adresini fscanf kullanarak okuyup structa atama iþlemini gerçekleþtiriyoruz....
     while(!feof(fp)){//Dosyanýn sonuna gelene kadar kontrol iþlemi gerçekleþtiriyoruz...

         ogs[i].ogrNo=ogt.ogrNo;//Öðrencilerin numaralarýný diðer dizi structýna atýyoruz...
         ogs[i].ogrNoAdres=ogt.ogrNoAdres;//Öðrencilerin numaralarýnýn adreslerini diðer dizi structýna atýyoruz..
         i++;//Sayma iþlemi gerçekleþtiriyoruz...

         fscanf(fp,"%d %x",&ogt.ogrNo,&ogt.ogrNoAdres);//Dosyanýn sonuna gelene kadar okuma iþlemini gerçekleþtiriyoruz...
     }
     fclose(fp);//Indeks dosyamýzý kapatýyoruz...
     bsortDesc(ogs,i);//Bu verileri bubble sort fonksiyonuna gönderiyoruz....

     //Veriler structta sýralandý..






    fp=fopen("index.txt","w");//Indeks dosyamýzý yazma modunda açtýk ve içindeki herþey silindi...
    for(int k=0;k<i;k++){
        fprintf(fp,"%d %x\n",ogs[k].ogrNo,ogs[k].ogrNoAdres);//Oðrencilerin verilerini indeks dosyasýna bastýrýyoruz...
    }


    fclose(fp);//Indeks dosyamýzý kapattýk..
     free(ogs);//Bellekten ayrýlan alanýn kullanýlmayaný serbest býrakýldý...


}


void KayitBul(){//Bir öðrenciyi bulma iþlemini gerçekleþtiriyoruz...

    int anahtar;//Öðrencinin numarasýný almak için anahtar deðiþkenini integer þekilde tanýmladýk...
    //int dersKodu;//Ayný þekilde ders kodunu da öyle..

    printf("Anahtar degeri olan ogrenci nosunu giriniz:");
    scanf("%d",&anahtar);//Ogrenci numarasýný kullanýcýdan aldýk...
    //printf("Anahtar degeri olan ögrencinin ders kodunu giriniz:");
   //scanf("%d",&dersKodu);//Ders kodunu kullanýcýdan aldýk.
    vptr=fopen("veri.bin","r");//Veri dosyamýzý okuma modunda açtýk.
    struct kayit ogl;//Bir struct tanýmladýk..
    struct kayit *omp;//Dinamik dizi þeklinde alabilmek için iþaretçi struct tanýmladýk..
    omp=(struct kayit*)malloc(500*sizeof(struct kayit));//Structýn kapasitesini belirledik...
    fread(&ogl,sizeof(struct kayit),1,vptr);//Dosyadaki ilk öðrencini verilerini structa tanýmaldýk..
    int t=0;//Bir integer deðiþken tanýmaldýk..
    printf("Anahtara ait kayitlar:\n");
    while(!feof(vptr)){//Dosyanýn sonuna gelene kadar...

        if(ogl.ogrNo==anahtar ){//Kullanýcýnýn bulmak istediði öðrenci numarasýyla dosyadaki öðrenci numarasý birbirine eþitse kontrolü yapýlýyor...
            printf("%d %d %d\n",ogl.ogrNo,ogl.dersKodu,ogl.puan);//Eþitse ekrana öðrencinin bilgilerini bastýrdý...

        }

        omp[t]=ogl;//Ýlk öðrenci atandý..
        t++;//Ýndis arttýrma iþlemi yapýldý...
        fread(&ogl,sizeof(struct kayit),1,vptr);//Bir sonraki öðrencinin verileri okundu..
    }

    int search(struct kayit *p, int n, int anaht)//Dosyadaki ilk kaydý bulma iþlemi yapýlýyor..
{
    int i;
    for (i = 0; i < n; i++)
        if (p[i].ogrNo == anaht)//Dosyadaki öðrencinin numarasý ile kullanýcýnýn girdiði öðrencinin numarasý eþitse.
            return i;//O öðrencinin indeksini döndür..
    return -1;//Deðilse -1 döndür..
}

  int a=search(omp,t,anahtar);//Search fonksiyonundan aldýðýmýz indisi baþka deðiþkene atadýk...
  printf("Veri dosyasindaki ilk kayit:\n ogrenci no:%d\t ders kodu:%d\t puani:%d\n",omp[a].ogrNo,omp[a].dersKodu,omp[a].puan);//Ilk kayýt ekranda gösterildi..
    free(omp);//Kullanýlmayan alan bellekten serbest býrakýldý.
    fclose(vptr);//Veri dosyasý kapatýldý..

struct index *ogt;//Yeni bir indeks structý iþaretçi kullanýlarak tanýmlandý....

  ogt=(struct index*)malloc(2000*sizeof(struct index));//Bellekten 500 kiþilik indeks structý yer ayýrtýldý...
  int k=0;
  fp=fopen("index.txt","r");//Indeks dosyasý okuma modunda açýldý...
  while(!feof(fp)){//Dosyanýn sonuna gelene kadar kontrolü...
      fscanf(fp,"%d %x\n",&ogt[k].ogrNo,&ogt[k].ogrNoAdres);//Indeks dosyasýnda okuma iþlemi yapýlýyor ve veriler structa atanýyor..
      k++;//Indis arttýrýmý yapýlýyor...
  }

  int binary_search(struct index *p, int MAX,struct kayit temp){//Indeks dosyasýndaki ilk kaydý bulabilmek için bu fonksiyon açýlýyor...

            int sayac=0;
           for(int i=0;i<MAX;i++){
             if(p[i].ogrNo==temp.ogrNo)//Bir structta birden fazla öðrenci olmasýna karþý sayac deðiþkeni tutup sayýyoruz..
                sayac++;
           }

           if(sayac>=1){
          int low=0;//Bu dizinin en düþük indisi
          int high=MAX-sayac-1;//Dizi structýnýn en yüksek indisi
          int mid=0;//Ortanca indis
               while(low<high){//En küçük indis en büyük indisten küçük olduðu ve eþit olduðu sürece döngü devam etsin...
                   mid=(low+high)/2;//En büyük ve en küçük indisin toplamýnýn ikiye bölümü ortanca indisi verir...
              if(p[mid].ogrNo==temp.ogrNo){//Structtaki ortanca indisin tanýmlý olduðu öðrencini numarasý ile kullanýcýnýn girdiði öðrencinin numarasý eþitse...


                   return mid;//Ortanca indisi döndür....


                     }
                if(p[mid].ogrNo>temp.ogrNo){//Ortanca indise baðlý öðrencinin öðrenci numarasý kullanýcýnýn girdiði öðrenci numarasýndan büyükse..
                      high=mid-1;//En yüksek indis ortanca indisin bir eksiði
                   }else{//Büyük deðilse
                       low=mid+1;//En düþük deðer ortanca indisin bir fazlasý
               }


            }

         return -1;
     }



  }


  int s=binary_search(ogt,k,omp[a]);
  printf("Indeks dosyasindaki ilk kayit:\n ogrenci no:%d\t adres:%x\n",ogt[s].ogrNo,ogt[s].ogrNoAdres);//Indeks dosyasýndaki bu numarada kayýtlý ilk öðrenci...

  free(ogt);
  free(omp);


}



void KayitSil(){//Silinmek istenen öðrenci bu fonksiyonla silinir..
    vptr=fopen("veri.bin","r");//Veri dosyasý okuma modunda açýldý...
    int sil;//Sil deðiþkeni adý altýnda silinecek öðrenci numarasý atanacak..
    printf("Silinecek kaydin anahtarini giriniz:");
    scanf("%d",&sil);//Kullanýcýdan öðrenci numarasý girildi...
    struct kayit *temp;//Geçici bir struct tanýmlandý..
    struct kayit ogr;//Bir kayýt structý tanýmlandý...
    struct index *ogd;//Bir indeks structý tanýmlandý..
    int i=0;//Deðiþken alýndý...
    temp=(struct kayit*)malloc(2000*sizeof(struct kayit));//500 kiþilik yer ayrýldý..
    ogd=(struct index*)malloc(2000*sizeof(struct index));//500 kiþilik yer ayrýldý..
    while(!feof(vptr)){//Dosyanýn sonuna gelene kadar kontrol iþlemi....
        fread(&ogr,sizeof(struct kayit),1,vptr);//Dosyadaki veriler okunup kayýt structýna atandý....
        temp[i]=ogr;//Kayýt structýna atanan veriler dizi structýna atandý..

        i++;//Deðiþkenin indisi arttýrýldý...

    }
    fclose(vptr);//Veri dosyasý kapatýldý...
    int j=0;
    vptr=fopen("veri.bin","w");//Veri dosyasý yazma modunda açýldý...
    for(j=0;j<i;j++){
        if(temp[j].ogrNo!=sil){//Kullanýcýnýn girdiði öðrenci numarasýyla dosyadaki öðrenci numarasý eþit olmadýðý sürece dosyaya yazdýr..
          fwrite(temp,sizeof(struct kayit),1,vptr);//Veri dosyasýna bastýrýlma iþlemi...
          printf("Ogrenci No:%d Ders Kodu:%d Puani:%d\n",temp[j].ogrNo,temp[j].dersKodu,temp[j].puan);//Ekrana bastýrýlma iþlemi...
        }
    }
    fclose(vptr);//Veri dosyasý kapatýldý...

    fp=fopen("index.txt","r");//Indeks dosyasýný okuma modunda açtýk...
    int k=0;
    while(!feof(fp)){//Dosyanýn sonuna gelene kadar kontrol iþlemi...
        fscanf(fp,"%d %x",&ogd[k].ogrNo,&ogd[k].ogrNoAdres);//Dosyadan öðrenci numarasý ve adresini okuyup structa atadýk...
        k++;//Ýndis arttýrýlma iþlemi gerçekleþtirildi..
    }
    fclose(fp);//Indeks dosyasýný kapattýk...

    fp=fopen("index.txt","w");//Indeks dosyasýný yazma modunda açtýk...
    int t=0;
    printf("\n\nIndeks dosyasindaki veriler:\n");
    while(!feof(fp)){//Dosyanýn sonuna gelene kadar kontrol iþlemi...

        if(sil!=ogd[t].ogrNo){//Kullanýcýnýn girdiði öðrenci numarasý ile dosyadaki öðrenci numarasý eþit olmadýðý sürece indeks dosyasýna bastýr...
            fprintf(fp,"%d %x\n",ogd[t].ogrNo,ogd[t].ogrNoAdres);//Dosyaya bastýrýlma iþlemi...
            printf("Ogrenci no:%d Adresi:%x\n",ogd[t].ogrNo,ogd[t].ogrNoAdres);
        }
        t++;
        if(t==(k-1))//Dosyaya bastýrdýðýmýz veri sayýsý dosyadan okuduðumuz veri sayýsýna eþit olursa döngü kýrýlýr...
          break;



        }


    free(temp);//Bellek alaný serbest býrakýldý..
    free(ogd);//Bellek alaný serbest býrakýldý..
    fclose(fp);//Indeks dosyasý kapatýldý....










}



void KayitGuncelle(){//Bu fonksiyonda öðrencinin puan alaný güncellenecektir...

    int anahtar;//Öðrenci numarasý bu deðiþkenle alýnacak...
    int lessonkey;//Ders kodu bu deðiþkenle alýnacak...
    printf("Ogrenci numarasini ve güncellenecek olan dersin notunun kodunu giriniz:");
    scanf("%d %d",&anahtar,&lessonkey);//Öðrenci numarasý ve ders kodu kullanýcýdan alýndý...
    vptr=fopen("veri.bin","r");//Veri dosyasý okuma modunda açýldý...
    struct kayit ogr;//Kayýt structý tanýmalndý...
    struct kayit *ogy;//Kayýt structý iþaretçi olarak tanýmlandý..
    int k=0;
    ogy=(struct kayit*)malloc(500*sizeof(struct kayit));//Kayýt structýnda 500 kiþilik bellek adresi yer tahsis edildi...
    while(!feof(vptr)){//Dosyanýn sonuna gelene kadar kontrol iþlemi...
        fread(&ogr,sizeof(struct kayit),1,fp);//Dosyadaki verileri okuyup kayýt structýna atama iþlemi..
        ogy[k]=ogr;//Bir structtan diðerine atama iþlemi...
        k++;//Indis arttýrýmý yapýldý...

    }
    fclose(vptr);//Veri dosyasý kapatýldý...
    int puan;
    printf("Puani giriniz:");
    scanf("%d",&puan);//Yeni puan girildi..
    vptr=fopen("veri.bin","w");//Veri dosyasý yazma modunda açýldý...
    int i=0;
    while(!feof(vptr)){//Dosyanýn sonuna gelene kadar kontrol iþlemi...
        if(ogy[i].ogrNo==anahtar && ogy[i].dersKodu==lessonkey){//Kullanýcýnýn girdiði öðrenci numarasý ve ders kodu ile structtaki öðrenci numarasý ve ders kodu eþitse...
            ogy[i].puan=puan;//Yeni girilen puaný eski puanýn yerine atýyoruz...
        }
        fwrite(ogy,sizeof(struct kayit),1,vptr);//Structtaki bilgileri dosyaya bastýrma iþlemi yapýyoruz...
        printf("%d.Ogrenci no:%d Ders Kodu:%d Puani:%d Adresi:%x\n",(i+1),ogy[i].ogrNo,ogy[i].dersKodu,ogy[i].puan,ogy[i].ogrNoAdres);//Ekrana bastýrma iþlemi...
        i++;//Ýndis arttýrma iþlemi...
        if(i==(k-1))//Ýndis dosyadan okunan veri sayýsýna eþit olursa
         break;//Döngüyü kýrma iþlemi gerçekleþtirilir...
    }


      free(ogy);





}





void bsortDesc(struct index list[], int s)//Bubble Sort kullanarak bu fonksiyonda öðrenci nolarýný ve adreslerini sýraladýk...
{
    int i, j;
    struct index temp;//Geçici bir struct tanýmladýk...



    for (i = 0; i < s - 1; i++)
    {
        for (j = 0; j < (s - 1-i); j++)
        {
            if (list[j].ogrNo > list[j + 1].ogrNo)//Gönderdiðimiz indeks structýnýn içindeki öðrenci numarasý bir sonraki öðrencinin numarasýndan büyükse....
            {
                temp = list[j];//Aldýðýmýz ilk öðrencinin verilerini geçici structa atýyoruz...
                list[j] = list[j + 1];//Bir sonraki öðrencinin verilerini ilk öðrenciye...
                list[j + 1] = temp;//Ýlk öðrencininkini de bir sonraki öðrenciye atama iþlemini gerçekleþtiriyoruz....



                }


             if (list[j].ogrNo==list[j + 1].ogrNo)//Eðer öðrenci numaralarý eþitse...
            {
                if(list[j].ogrNoAdres>list[j+1].ogrNoAdres){//Adresleri kontrol ediyoruz.Ýlk öðrencinin adresi bir sonraki öðrenciden büyükse...
                temp = list[j];//Ýlk öðrencilerinin verilerini geçici structa atýyoruz...
                list[j] = list[j + 1];//Bir sonrakini ilk öðrenciye atýyoruz...
                list[j + 1] = temp;//Geçici structa atadýðýmýz öðrencideki verileri bir sonraki öðrenciye aktarýyoruz...
                }



                }
            }
        }
    }





void VeriEkle(int j){//Kullanýcýdan kayýt alma iþlemi gerçekleþtiriyoruz...
    vptr=fopen("veri.bin","a");//Veri dosyasýný ekleme modunda açýyoruz...
    struct kayit *ogr=(struct kayit*)malloc(sizeof(struct kayit));//Dinamik bellekte yer ayýrttýk...

    if(vptr!=NULL){//Dosyanýn adresi null deðere eþit deðilse...
        printf("%d.Ogrenci no:",j);
        scanf("%d",&ogr->ogrNo);//Kullanýcýdan öðrenci numarasýný aldýk....
        printf("Ders id:");
        scanf("%d",&ogr->dersKodu);//Kullanýcýdan ders kodunu aldýk...
        printf("Puani:");
        scanf("%d",&ogr->puan);//Kullanýcýdan puaný aldýk...
        ogr->ogrNoAdres=&ogr->ogrNo;
        fwrite(ogr,sizeof(struct kayit),1,vptr);//Structla aldýðýmýz verileri dosyaya bastýrýyoruz...
        fclose(vptr);//Veri dosyasýný kapattýk...

    }
    free(ogr);

}

void VeriYazdir(){//Girdiðimiz kayýtlarý ekranda gösteren fonksiyon....

    struct kayit ogr;//Kayýt structýný tanýmaldýk...
    vptr=fopen("veri.bin","r");//Veri dosyasýný okuma modunda açtýk....
    if(vptr!=NULL){//Dosyanýn adresi null deðere eþit olmadýðý sürece...
        fread(&ogr,sizeof(struct kayit),1,vptr);//Dosyadan veriyi okuyup structa atadýk...
            printf("%s\t%s\t  %s\t%s\n","OGRENCI NO:","ADRES:"," DERS KODU:","PUANI:");
        while(!feof(vptr)){//Dosyanýn sonuna gelene kadar kontrol iþlemi....


            printf("%d\t        %x\t %d\t %d\n",ogr.ogrNo,ogr.ogrNoAdres,ogr.dersKodu,ogr.puan);//Bu okuduðumuz verileri ekranda bastýrdýk..
            fread(&ogr,sizeof(struct kayit),1,vptr);//Dosyadaki verileri okuyup kayýt structýna atadýk...

        }

    }

    fclose(vptr);//Veri dosyasýný kapattýk...



}


void VeriDosyasiniGoster(){//Veri dosyasýndaki bilgileri bu fonksiyonla göstereceðiz....

    vptr=fopen("veri.bin","r");//Veri dosyasýný okuma modunda açtýk...
    struct kayit *ogr;//Kayýt structýný iþaretçi olarak tanýmladýk....
    struct kayit omp;//Baþka bir kayýt structý tanýmladýk...
    ogr=(struct kayit*)malloc(2000*sizeof(struct kayit));//Kayýt structýnda 500 kiþilik bellekten yer ayýrttýk...
    int k=0;
    while(!feof(vptr)){//Dosyanýn sonuna gelene kadar kontrol iþlemi....
        fread(&omp,sizeof(struct kayit),1,fp);//Dosyadaki verileri okuyup structa atama....
        ogr[k]=omp;//Structtaki veriyi baþka bir structa atama...
        k++;//Ýndis arttýrma iþlemi...

    }
    printf("Veri Dosyasi:\n");//Veri dosyasýndaki bilgiler ekranda gösteriliyor...
    for(int i=0;i<(k-1);i++){
        printf("Ogrenci no:%d Ders Kodu:%d Puani:%d\n",ogr[i].ogrNo,ogr[i].dersKodu,ogr[i].puan);
    }

    fclose(fp);//Veri dosyasý kapatýldý...
    free(ogr);//Bellekteki kullanýlmayan alan serbest býrakýldý...

}


void IndexDosyasiniGoster(){//Ýndeks dosyasýndaki verileri bu fonksiyonla göstereceðiz....
    fp=fopen("index.txt","r");//Ýndeks dosyasýný okuma modunda açtýk...
    int p=0;
    struct index *ogf;//Kayýt structý tanýmladýk...
    ogf=(struct index*)malloc(2000*sizeof(struct index));//Structta bellekten 500 kiþilik yer ayýrttýk....


    while(!feof(fp)){//Dosyanýn sonuna gelene kadar kontrol iþlemi....
        fscanf(fp,"%d %x",&ogf[p].ogrNo,&ogf[p].ogrNoAdres);//Dosyadaki bilgileri okuyup structa atama iþlemi...
        p++;//Ýndis arttýrýldý...
    }

    for(int j=0;j<(p-1);j++){//Dosyada okunan veri sayýsý kadar öðrencinin bilgilerini ekrana bastýrma iþlemi...
        printf("Ogrenci no:%d  Ogrenci no adres:%x\n",ogf[j].ogrNo,ogf[j].ogrNoAdres);
    }
    free(ogf);//Structta bellekten kullanýlamayan alan serbest býrakýldý...
    fclose(fp);//Indeks dosyasý kapatýldý...
}



void  IndexDosyasiniSil(){//Ýndeks Dosyasý silme iþlemini bu fonksiyonla yaptýk...
    remove("index.txt");//Ýndeks dosyasýný diskten sildi...
}




void IndeksDosyasiOlustur(){//Ýndeks dosyasýný bu fonksiyonla oluþturduk...

    fp=fopen("index.txt","w");//Ýndeks dosyasýný yazma modunda açtýk...




}


void BinaryDosyaOku(int x){//Binary dosyayý okuma iþlemini bu fonksiyonla yaptýk...
  vptr=fopen("veri.bin","r");//Binary dosyasýný okuma modunda açtýk..
  struct kayit ogr;//Kayýt structý tanýmladýk...

  struct index *ogp;//Kayýt structýný iþaretçi olarak tanýmladýk...
  ogp=(struct index*)malloc(x*sizeof(struct index));//Bellekten girilecek kiþi sayýsý kadar yer ayýrttýk..




  fread(&ogr,sizeof(struct kayit),1,vptr);//Dosyadan ilk veriyi okuduk...
  int i=0;
  while(!feof(vptr)){//Dosyanýn sonuna gelene kadar kontrol iþlemi...

    ogp[i].ogrNo=ogr.ogrNo;//Kayýt structýndaki öðrenci numarasýný indeks structýnda öðrenci numarasýna atadýk..
    ogp[i].ogrNoAdres=ogr.ogrNoAdres;//Kayýt structýndaki öðrenci numarasýnýn adresini indeks structýndaki öðrenci numarasýnýn adresine atadýk...
    i++;//Indis arttýrýlma iþlemi yapýldý...
    fread(&ogr,sizeof(struct kayit),1,vptr);//Bir sonraki veriyi dosyadan okuyup structa atadýk...

  }
  fclose(vptr);//Veri dosyasýný kapattýk..
  bsortDesc(ogp,i);//Structtaki verileri bu fonksiyona yolladýk..
  IndeksDosyasiOlustur();//Ýndeks dosyasýný buarada açtýk...
  int j=0;
      for(j=0;j<i;j++){//Dosyadan okunan veri sayýsý kadar indeks dosyasýna veri bastýrdýk.Ama sýralý halde...
        fprintf(fp,"%d %x\n",ogp[j].ogrNo,ogp[j].ogrNoAdres);
      }


    printf("\n\n");
    printf("Txt dosyasindaki sirali hali:\n");//Dosyadaki verileri sýralý halde görmek için ekrana bastýrdýk..
    for(j=0;j<i;j++){
        printf("%d %x\n",ogp[j].ogrNo,ogp[j].ogrNoAdres);
    }
    printf("\n\n");



  fclose(fp);//Ýndeks dosyasýný kapattýk...







}
void BinaryDosyaAc(){//Bir binary dosya açma iþlemini gerçekleþtirdik...
    vptr=fopen("veri.bin","wb");//Veri dosyasýný yazma modunda açtýk...
    fclose(vptr);//Veri dosyasýný kapama iþlemini gerçekleþtirdik...
}


int main()
{
    BinaryDosyaAc();//Veri dosyasý açtýk...
    int kisi_sayisi;
    printf("Kac kayit ekleyeceksiniz:");
    scanf("%d",&kisi_sayisi);//Kullanýcýdan kayýt edilecek kiþi sayýsý alýndý...
    int i=0;
    for(i=0;i<kisi_sayisi;i++){//Kiþi sayýsý kadar veri ekle fonksiyonu çaðrýldý..
    VeriEkle(i+1);
    }
    printf("Kayit ekleme isi bitti.....\n\n\n");
    VeriYazdir();//Verileri ekrana bastýrdýk...
    BinaryDosyaOku(kisi_sayisi);//Kiþi sayýsýný bu fonksiyona gönderdik...
    //rewind(vptr);//Dosyayý baþa aldýk...
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
     scanf("%d",&secim);//Kullanýcýdan bir seçim yapmasýný istedik..


     switch(secim){//Seçim deðerine göre aþaðýdaki fonksiyonlara girdi...
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
