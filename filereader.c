#include<stdio.h>
#include<string.h>
#define wordLength 50 // constants in C
#define totWords 20

struct st  // similar to your symboltable
{
  int x;
  char word[wordLength];
};

// function prototypes
int process(FILE *);
void show(int);

struct st words[totWords];

int main()
{
  FILE * fp;
  fp = fopen("strings","r");

  int count = process(fp);
  show(count);
}

void show(int n)
{
  int i;
  for(i = 0; i < n; i++)
    printf("%s\n",words[i].word);
}

int process(FILE* fp)
{
  char word[wordLength];
  int count = 0, tot = 0;
  int ch;

  while((ch = fgetc(fp)) != EOF)
  {
    if(ch == ' ')
    {
      word[count] = '\0';
      printf("word = %s\n",word);
      strcpy(words[tot++].word,word);
      count = 0;
      ungetc(ch,fp);
      ch = fgetc(fp);
      printf("here is the space [%c]\n",ch);
    }
    else
     word[count++] = ch;
  }
  return tot;
}

