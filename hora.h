#include <stdio.h>
#include <time.h>

char *format(int number){
   char *retorno,ret[100];
   int i;

   if (number < 10){
      sprintf(ret,"0%d",number);
      retorno = ret;
      return retorno;
   }
   else{
      sprintf(ret,"%d",number);
      retorno = ret;
      return retorno;
   }
}

char *data(void){

   int dia,mes,ano;
   char var1[100],var2[100],var3[100],var4[100], *dataPtr;
   struct tm *local;
   time_t t;

   t = time(NULL);
   local = localtime(&t);

   dia = local -> tm_mday;
   mes = local -> tm_mon + 1;
   ano = local -> tm_year + 1900;

   //printf("%d/%d/%d\n", dia,mes,ano);

   sprintf(var1,"%s",format(dia));
   sprintf(var2,"%s",format(mes));
   sprintf(var3,"%s",format(ano));

   sprintf(var4,"%s/%s/%s",var1,var2,var3);

   dataPtr = var4;
   return dataPtr;

}

