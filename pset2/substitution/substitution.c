#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
int main(int argc,char **argv){

    if(argc==1){
      printf("No arguments provided.\n");     // checking requirements for key
      return 1;
    }else if(argc>2){
      printf("Only 2 arguments are required.");
    }
    int i;
    for( i=0;argv[1][i]!='\0';i++){
      if(argv[1][i]>='a'&&argv[1][i]<='z'){      /* to check a charcter i'm going to use argv[] as argv[1][i] because 
      argv's second argument is stored in 1 and to access the character I need to use this*/ 
        continue;
      }else if(argv[1][i]>='A'&&argv[1][i]<='Z'){
        continue;
      }else{
        printf("Key isnot perfectly right. \n");
        return 1;
      }
    }
    if(i!=26){
      printf("Key must contain 26 characters.\n");
      return 1;
    }
    int temp;
    for (i=0;i<26;i++){
      int ctr=1;
      for(int j=0;j<26;j++){
        if(argv[1][i]==argv[1][j]){ 
          temp=ctr;
          ctr++;
          if(temp>1){
            printf("Key isnot perfectly right. \n");
            return 1;
          }
        }
      }
    }
    char text[300];
   printf("plaintext:");
   fgets(text,sizeof(text),stdin);
   for(i=0;text[i]!='\0';i++){
     if(text[i]>='a'&&text[i]<='z')
     { // if the character is lowercase then increment its value by 32 ,it would become lowercase
      unsigned int num=(text[i]-97);
      text[i]=argv[1][num];
      if(argv[1][num]>='A'&&argv[1][num]<='Z'){
        text[i]=(int)text[i]+32;   
      }
     }else if(text[i]>='A'&&text[i]<='Z')
     {// converting it to ciphertext
       unsigned int num=(text[i]-65);
      text[i]=argv[1][num];
       if(argv[1][num]>='a'&&argv[1][num]<='z'){
        text[i]=(int)text[i]-32;   
      }
     }
   }
   printf("ciphertext:%s\n",text);
}