// Bilal Ulutas - 2020
# include <stdio.h>
# include <stdbool.h>
# include <math.h>

//Prototip tanimlamalari
int createMatrix(int rows, int columns);
int getRandom(void);
void bubbleSort(int **array, int rows, int columns);
int createTranspose(int **array, int rows, int columns);
void printMatrix(int **myMatrix, int **myTranspose, int rows, int columns);
void printKaprekar(int **myTranspose, int rows, int columns);
bool checkKaprekar(int myNumber);
void freeMemory(int **myMatrix, int **myTranspose, int rows, int columns);

int main()
{
	// 2B dizi ve degisken tanimlamalari
	int **myMatrix;
	int **myTranspose;
	int rows, columns;
	
	// Farkli rastgele sayilar icin seed degerinin degistirilmesi
	srand(time(0));
	
	// Kullanicidan giris degerlerinin istenmesi
	printf ("Matrisin satir sayisini giriniz: ");
	scanf ("%d", &rows);
	
	printf ("Matrisin sutun sayisini giriniz: ");
	scanf ("%d", &columns);
	
	// Fonksiyonlarin ilgili parameterler gonderilerek cagirilmasi
	myMatrix = createMatrix(rows, columns);
	bubbleSort(myMatrix, rows, columns);
	myTranspose = createTranspose(myMatrix, rows, columns);
	printMatrix(myMatrix, myTranspose, rows, columns);
    printKaprekar(myTranspose, rows, columns);
    freeMemory(myMatrix, myTranspose, rows, columns);
    
    return(0);
}

int createMatrix(int rows, int columns)
{
	int **myMatrix;
	int m, n, i;
	// Matrisin satirlari icin bellekten alan ayrilmasi
	myMatrix = (int **) calloc(rows, sizeof(int*));
	
	// Her satira ait alt dizin olan sutunlar icin alan ayrilmasi
	for(i=0; i<rows; i++)
    myMatrix[i] = (int *) calloc(columns, sizeof(int));
	
	// Eger yeterli alan yoksa uyari ve hata kodu
	if( myMatrix == NULL )
  	printf("Yetersiz bellek alaný\n"), exit(1);
	
	// Matrisin mxn boyutunda olacak sekilde rastgele sayilarla doldurulmasi
	for(m = 0; m < rows; m++)
	{
		for(n = 0; n < columns; n++)
		{
			myMatrix[m][n] = getRandom();
        }
    }
    
    return myMatrix;
}

int getRandom(void)
{
    int value;
    // 5 - 40000 arasinda rastegele sayi
    value = rand() + rand() % 7230 + 5;
    return value;
}

void bubbleSort(int **array, int rows, int columns)
{
	/* Matrisi sakladigimiz dizimiz 2 boyutlu oldugu icin
	ic ice 2 for degil 4 for kullaniyoruz.*/
	int temp, x, y, i, j;
	for (x = 0; x < rows; x++)
	{
		for (y = 0; y < columns; y++)
		{
			for (i = 0; i < rows; i++)
			{
				for (j = 0; j < columns; j++)
				{
					if (array[i][j] > array[x][y])
					{
						temp = array[x][y];
						array[x][y] = array[i][j];
						array[i][j] = temp;
					}
				}
			}
		}
	}
}

int createTranspose(int **array, int rows, int columns)
{
	/* mxn boyutunda matrisimizin transpozesi nxm olacaktir
	Matrisin sutun sayisinda satir, satir sayisinda sutuna sahip
	bir baska matris olusturuyoruz*/
	int **myTranspose;
	myTranspose = createMatrix(columns, rows);
	
	int i, j;
	for (i = 0; i < rows; ++i)
	{
		for (j = 0; j < columns; ++j)
		{
			/* array = myMatrix nxm degleri 
			mxn seklinde transpoze matrise aktariliyor*/
            myTranspose[j][i] = array[i][j];
        }
	}
	
	return myTranspose;        
}

void printMatrix(int **myMatrix, int **myTranspose, int rows, int columns)
{
	// Dosyayi ac
	FILE * fp;
	fp = fopen ("transpoze.txt","w");
	
	// Dosyaya matrisi yaz
	fprintf (fp, "Matris:\n");
	int m, n;
	for	(m = 0; m < rows; m++)
	{
		for (n = 0; n < columns; n++)
		{
			fprintf (fp, "%5d ", myMatrix[m][n]);
		}
		fprintf (fp, "\n");
	}
	
	// Dosyaya transpoze matrisi yaz
	fprintf (fp, "\nTranspozesi:\n");
	for	(m = 0; m < columns; m++)
	{
		for (n = 0; n < rows; n++)
		{
			fprintf (fp, "%5d ", myTranspose[m][n]);
		}
		fprintf (fp, "\n");
	}
	
	// Dosyayi kapat
	fclose (fp);
	printf ("\n Yazdirma islemi tamam!\n");
}

void printKaprekar(int **myTranspose, int rows, int columns)
{	
	// Dosyayi ac
	FILE * fp;
	fp = fopen ("kaprekar.txt","w");

	int m, n;
	// Kaprekar sayi sayaci
	int myCounter = 0;
	for	(m = 0; m < columns; m++)
	{
		for (n = 0; n < rows; n++)
		{
			if(checkKaprekar(myTranspose[m][n]) == 1)
			{
				// Eger sayi kaprekar ise dosyaya yaz
				fprintf (fp, "%5d ", myTranspose[m][n]);
				fprintf (fp, "\n");
				// Kaprekar sayacini arttir
				myCounter++;
			}
			
		}
	}
	// Kaprekar sayaci 0 ise uyari mesaji yazdir
	if (myCounter == 0)
	{
		fprintf (fp, "Kaprekar Yok\n");
	}
	fclose(fp);
}

bool checkKaprekar(int myNumber)
{
	// 1 sayisi kaprekardir, isleme sokma
    if (myNumber == 1) return true;
    
    // Sayinin karesini al
    int sqrNumber = myNumber * myNumber;
    
    // Basamak sayisini hesapla
    int totalDigits = 0;
    while (sqrNumber)
    {
        totalDigits++;
        sqrNumber /= 10;
    }
    
    // Sayinin karesini duzelt
    sqrNumber = myNumber*myNumber; 
    
    int i;
    // Sayiyi her basamaktan ikiye ayirarak toplamlarini kontrol et
    for (i = 1; i < totalDigits; i++)
    {
    	// Ornek : 10^1 ile bolerek en buyuk basamaktan kalan kismi ayir
         int factor = pow(10, i);
         
         /* Eger sayi 10'un katiysa kaprekar degildir, isleme sokma
         Cunku iki parcadan birisi 0 olacaktir*/
         if (factor == myNumber) continue;
         
         /* 10'un kati ile bolerek basamagin ilk kismini,
         Bolumunden kalan ile basamagin diger kismini alip topla*/
         int mySum = sqrNumber/factor + sqrNumber % factor;
         
         // Toplam sayiya esit ise sayi kaprekardir
         if (mySum == myNumber) return true;
    }
    
    // Donus yapilmadiysa kaprekar degil
    return false;
}

void freeMemory(int **myMatrix, int **myTranspose, int rows, int columns)
{
	int i;
	
	// Bellekten matris icin ayrilan alani bosalt
	for(i = 0; i < rows; i++)
	free((void *) myMatrix[i]);
    free((void *) myMatrix);
    
    // Bellekten transpoze icin ayrilan alani bosalt
    for(i = 0; i < columns; i++)
	free((void *) myTranspose[i]);
    free((void *) myTranspose); 
}
